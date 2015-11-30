/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controllers;

import Controllers.exceptions.NonexistentEntityException;
import Controllers.exceptions.PreexistingEntityException;
import java.io.Serializable;
import javax.persistence.Query;
import javax.persistence.EntityNotFoundException;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import Entity.Usuario;
import Entity.Propiedad;
import Entity.Propietario;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

/**
 *
 * @author aleja_000
 */
public class PropietarioJpaController implements Serializable {

    public PropietarioJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Propietario propietario) throws PreexistingEntityException, Exception {
        if (propietario.getPropiedadCollection() == null) {
            propietario.setPropiedadCollection(new ArrayList<Propiedad>());
        }
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Usuario cedula = propietario.getCedula();
            if (cedula != null) {
                cedula = em.getReference(cedula.getClass(), cedula.getCedula());
                propietario.setCedula(cedula);
            }
            Collection<Propiedad> attachedPropiedadCollection = new ArrayList<Propiedad>();
            for (Propiedad propiedadCollectionPropiedadToAttach : propietario.getPropiedadCollection()) {
                propiedadCollectionPropiedadToAttach = em.getReference(propiedadCollectionPropiedadToAttach.getClass(), propiedadCollectionPropiedadToAttach.getIdPropiedad());
                attachedPropiedadCollection.add(propiedadCollectionPropiedadToAttach);
            }
            propietario.setPropiedadCollection(attachedPropiedadCollection);
            em.persist(propietario);
            if (cedula != null) {
                cedula.getPropietarioCollection().add(propietario);
                cedula = em.merge(cedula);
            }
            for (Propiedad propiedadCollectionPropiedad : propietario.getPropiedadCollection()) {
                Propietario oldIdpOfPropiedadCollectionPropiedad = propiedadCollectionPropiedad.getIdp();
                propiedadCollectionPropiedad.setIdp(propietario);
                propiedadCollectionPropiedad = em.merge(propiedadCollectionPropiedad);
                if (oldIdpOfPropiedadCollectionPropiedad != null) {
                    oldIdpOfPropiedadCollectionPropiedad.getPropiedadCollection().remove(propiedadCollectionPropiedad);
                    oldIdpOfPropiedadCollectionPropiedad = em.merge(oldIdpOfPropiedadCollectionPropiedad);
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findPropietario(propietario.getIdp()) != null) {
                throw new PreexistingEntityException("Propietario " + propietario + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Propietario propietario) throws NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Propietario persistentPropietario = em.find(Propietario.class, propietario.getIdp());
            Usuario cedulaOld = persistentPropietario.getCedula();
            Usuario cedulaNew = propietario.getCedula();
            Collection<Propiedad> propiedadCollectionOld = persistentPropietario.getPropiedadCollection();
            Collection<Propiedad> propiedadCollectionNew = propietario.getPropiedadCollection();
            if (cedulaNew != null) {
                cedulaNew = em.getReference(cedulaNew.getClass(), cedulaNew.getCedula());
                propietario.setCedula(cedulaNew);
            }
            Collection<Propiedad> attachedPropiedadCollectionNew = new ArrayList<Propiedad>();
            for (Propiedad propiedadCollectionNewPropiedadToAttach : propiedadCollectionNew) {
                propiedadCollectionNewPropiedadToAttach = em.getReference(propiedadCollectionNewPropiedadToAttach.getClass(), propiedadCollectionNewPropiedadToAttach.getIdPropiedad());
                attachedPropiedadCollectionNew.add(propiedadCollectionNewPropiedadToAttach);
            }
            propiedadCollectionNew = attachedPropiedadCollectionNew;
            propietario.setPropiedadCollection(propiedadCollectionNew);
            propietario = em.merge(propietario);
            if (cedulaOld != null && !cedulaOld.equals(cedulaNew)) {
                cedulaOld.getPropietarioCollection().remove(propietario);
                cedulaOld = em.merge(cedulaOld);
            }
            if (cedulaNew != null && !cedulaNew.equals(cedulaOld)) {
                cedulaNew.getPropietarioCollection().add(propietario);
                cedulaNew = em.merge(cedulaNew);
            }
            for (Propiedad propiedadCollectionOldPropiedad : propiedadCollectionOld) {
                if (!propiedadCollectionNew.contains(propiedadCollectionOldPropiedad)) {
                    propiedadCollectionOldPropiedad.setIdp(null);
                    propiedadCollectionOldPropiedad = em.merge(propiedadCollectionOldPropiedad);
                }
            }
            for (Propiedad propiedadCollectionNewPropiedad : propiedadCollectionNew) {
                if (!propiedadCollectionOld.contains(propiedadCollectionNewPropiedad)) {
                    Propietario oldIdpOfPropiedadCollectionNewPropiedad = propiedadCollectionNewPropiedad.getIdp();
                    propiedadCollectionNewPropiedad.setIdp(propietario);
                    propiedadCollectionNewPropiedad = em.merge(propiedadCollectionNewPropiedad);
                    if (oldIdpOfPropiedadCollectionNewPropiedad != null && !oldIdpOfPropiedadCollectionNewPropiedad.equals(propietario)) {
                        oldIdpOfPropiedadCollectionNewPropiedad.getPropiedadCollection().remove(propiedadCollectionNewPropiedad);
                        oldIdpOfPropiedadCollectionNewPropiedad = em.merge(oldIdpOfPropiedadCollectionNewPropiedad);
                    }
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Short id = propietario.getIdp();
                if (findPropietario(id) == null) {
                    throw new NonexistentEntityException("The propietario with id " + id + " no longer exists.");
                }
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void destroy(Short id) throws NonexistentEntityException {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Propietario propietario;
            try {
                propietario = em.getReference(Propietario.class, id);
                propietario.getIdp();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The propietario with id " + id + " no longer exists.", enfe);
            }
            Usuario cedula = propietario.getCedula();
            if (cedula != null) {
                cedula.getPropietarioCollection().remove(propietario);
                cedula = em.merge(cedula);
            }
            Collection<Propiedad> propiedadCollection = propietario.getPropiedadCollection();
            for (Propiedad propiedadCollectionPropiedad : propiedadCollection) {
                propiedadCollectionPropiedad.setIdp(null);
                propiedadCollectionPropiedad = em.merge(propiedadCollectionPropiedad);
            }
            em.remove(propietario);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Propietario> findPropietarioEntities() {
        return findPropietarioEntities(true, -1, -1);
    }

    public List<Propietario> findPropietarioEntities(int maxResults, int firstResult) {
        return findPropietarioEntities(false, maxResults, firstResult);
    }

    private List<Propietario> findPropietarioEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Propietario.class));
            Query q = em.createQuery(cq);
            if (!all) {
                q.setMaxResults(maxResults);
                q.setFirstResult(firstResult);
            }
            return q.getResultList();
        } finally {
            em.close();
        }
    }

    public Propietario findPropietario(Short id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Propietario.class, id);
        } finally {
            em.close();
        }
    }

    public int getPropietarioCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Propietario> rt = cq.from(Propietario.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }

    public int cedPropietarioCount(long cedula) {
        EntityManager em = getEntityManager();
        try {
            Query q ;
            q = em.createQuery("SELECT COUNT(x) FROM Propietario x WHERE x.cedula = ?1");
            q.setParameter(1, cedula);
            return ((int)q.getSingleResult());
        } finally {
            em.close();
        }
    }
    
}
