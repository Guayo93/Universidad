/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controllers;

import Controllers.exceptions.IllegalOrphanException;
import Controllers.exceptions.NonexistentEntityException;
import Controllers.exceptions.PreexistingEntityException;
import Entity.Comprador;
import java.io.Serializable;
import javax.persistence.Query;
import javax.persistence.EntityNotFoundException;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import Entity.Usuario;
import Entity.Propiedad;
import java.util.ArrayList;
import java.util.Collection;
import Entity.ListaDeVisita;
import Entity.Renta;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

/**
 *
 * @author aleja_000
 */
public class CompradorJpaController implements Serializable {

    public CompradorJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Comprador comprador) throws PreexistingEntityException, Exception {
        if (comprador.getPropiedadCollection() == null) {
            comprador.setPropiedadCollection(new ArrayList<Propiedad>());
        }
        if (comprador.getListaDeVisitaCollection() == null) {
            comprador.setListaDeVisitaCollection(new ArrayList<ListaDeVisita>());
        }
        if (comprador.getRentaCollection() == null) {
            comprador.setRentaCollection(new ArrayList<Renta>());
        }
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Usuario cedula = comprador.getCedula();
            if (cedula != null) {
                cedula = em.getReference(cedula.getClass(), cedula.getCedula());
                comprador.setCedula(cedula);
            }
            Collection<Propiedad> attachedPropiedadCollection = new ArrayList<Propiedad>();
            for (Propiedad propiedadCollectionPropiedadToAttach : comprador.getPropiedadCollection()) {
                propiedadCollectionPropiedadToAttach = em.getReference(propiedadCollectionPropiedadToAttach.getClass(), propiedadCollectionPropiedadToAttach.getIdPropiedad());
                attachedPropiedadCollection.add(propiedadCollectionPropiedadToAttach);
            }
            comprador.setPropiedadCollection(attachedPropiedadCollection);
            Collection<ListaDeVisita> attachedListaDeVisitaCollection = new ArrayList<ListaDeVisita>();
            for (ListaDeVisita listaDeVisitaCollectionListaDeVisitaToAttach : comprador.getListaDeVisitaCollection()) {
                listaDeVisitaCollectionListaDeVisitaToAttach = em.getReference(listaDeVisitaCollectionListaDeVisitaToAttach.getClass(), listaDeVisitaCollectionListaDeVisitaToAttach.getListaDeVisitaPK());
                attachedListaDeVisitaCollection.add(listaDeVisitaCollectionListaDeVisitaToAttach);
            }
            comprador.setListaDeVisitaCollection(attachedListaDeVisitaCollection);
            Collection<Renta> attachedRentaCollection = new ArrayList<Renta>();
            for (Renta rentaCollectionRentaToAttach : comprador.getRentaCollection()) {
                rentaCollectionRentaToAttach = em.getReference(rentaCollectionRentaToAttach.getClass(), rentaCollectionRentaToAttach.getIdRenta());
                attachedRentaCollection.add(rentaCollectionRentaToAttach);
            }
            comprador.setRentaCollection(attachedRentaCollection);
            em.persist(comprador);
            if (cedula != null) {
                cedula.getCompradorCollection().add(comprador);
                cedula = em.merge(cedula);
            }
            for (Propiedad propiedadCollectionPropiedad : comprador.getPropiedadCollection()) {
                Comprador oldIdcOfPropiedadCollectionPropiedad = propiedadCollectionPropiedad.getIdc();
                propiedadCollectionPropiedad.setIdc(comprador);
                propiedadCollectionPropiedad = em.merge(propiedadCollectionPropiedad);
                if (oldIdcOfPropiedadCollectionPropiedad != null) {
                    oldIdcOfPropiedadCollectionPropiedad.getPropiedadCollection().remove(propiedadCollectionPropiedad);
                    oldIdcOfPropiedadCollectionPropiedad = em.merge(oldIdcOfPropiedadCollectionPropiedad);
                }
            }
            for (ListaDeVisita listaDeVisitaCollectionListaDeVisita : comprador.getListaDeVisitaCollection()) {
                Comprador oldCompradorOfListaDeVisitaCollectionListaDeVisita = listaDeVisitaCollectionListaDeVisita.getComprador();
                listaDeVisitaCollectionListaDeVisita.setComprador(comprador);
                listaDeVisitaCollectionListaDeVisita = em.merge(listaDeVisitaCollectionListaDeVisita);
                if (oldCompradorOfListaDeVisitaCollectionListaDeVisita != null) {
                    oldCompradorOfListaDeVisitaCollectionListaDeVisita.getListaDeVisitaCollection().remove(listaDeVisitaCollectionListaDeVisita);
                    oldCompradorOfListaDeVisitaCollectionListaDeVisita = em.merge(oldCompradorOfListaDeVisitaCollectionListaDeVisita);
                }
            }
            for (Renta rentaCollectionRenta : comprador.getRentaCollection()) {
                Comprador oldIdcOfRentaCollectionRenta = rentaCollectionRenta.getIdc();
                rentaCollectionRenta.setIdc(comprador);
                rentaCollectionRenta = em.merge(rentaCollectionRenta);
                if (oldIdcOfRentaCollectionRenta != null) {
                    oldIdcOfRentaCollectionRenta.getRentaCollection().remove(rentaCollectionRenta);
                    oldIdcOfRentaCollectionRenta = em.merge(oldIdcOfRentaCollectionRenta);
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findComprador(comprador.getIdc()) != null) {
                throw new PreexistingEntityException("Comprador " + comprador + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Comprador comprador) throws IllegalOrphanException, NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Comprador persistentComprador = em.find(Comprador.class, comprador.getIdc());
            Usuario cedulaOld = persistentComprador.getCedula();
            Usuario cedulaNew = comprador.getCedula();
            Collection<Propiedad> propiedadCollectionOld = persistentComprador.getPropiedadCollection();
            Collection<Propiedad> propiedadCollectionNew = comprador.getPropiedadCollection();
            Collection<ListaDeVisita> listaDeVisitaCollectionOld = persistentComprador.getListaDeVisitaCollection();
            Collection<ListaDeVisita> listaDeVisitaCollectionNew = comprador.getListaDeVisitaCollection();
            Collection<Renta> rentaCollectionOld = persistentComprador.getRentaCollection();
            Collection<Renta> rentaCollectionNew = comprador.getRentaCollection();
            List<String> illegalOrphanMessages = null;
            for (ListaDeVisita listaDeVisitaCollectionOldListaDeVisita : listaDeVisitaCollectionOld) {
                if (!listaDeVisitaCollectionNew.contains(listaDeVisitaCollectionOldListaDeVisita)) {
                    if (illegalOrphanMessages == null) {
                        illegalOrphanMessages = new ArrayList<String>();
                    }
                    illegalOrphanMessages.add("You must retain ListaDeVisita " + listaDeVisitaCollectionOldListaDeVisita + " since its comprador field is not nullable.");
                }
            }
            if (illegalOrphanMessages != null) {
                throw new IllegalOrphanException(illegalOrphanMessages);
            }
            if (cedulaNew != null) {
                cedulaNew = em.getReference(cedulaNew.getClass(), cedulaNew.getCedula());
                comprador.setCedula(cedulaNew);
            }
            Collection<Propiedad> attachedPropiedadCollectionNew = new ArrayList<Propiedad>();
            for (Propiedad propiedadCollectionNewPropiedadToAttach : propiedadCollectionNew) {
                propiedadCollectionNewPropiedadToAttach = em.getReference(propiedadCollectionNewPropiedadToAttach.getClass(), propiedadCollectionNewPropiedadToAttach.getIdPropiedad());
                attachedPropiedadCollectionNew.add(propiedadCollectionNewPropiedadToAttach);
            }
            propiedadCollectionNew = attachedPropiedadCollectionNew;
            comprador.setPropiedadCollection(propiedadCollectionNew);
            Collection<ListaDeVisita> attachedListaDeVisitaCollectionNew = new ArrayList<ListaDeVisita>();
            for (ListaDeVisita listaDeVisitaCollectionNewListaDeVisitaToAttach : listaDeVisitaCollectionNew) {
                listaDeVisitaCollectionNewListaDeVisitaToAttach = em.getReference(listaDeVisitaCollectionNewListaDeVisitaToAttach.getClass(), listaDeVisitaCollectionNewListaDeVisitaToAttach.getListaDeVisitaPK());
                attachedListaDeVisitaCollectionNew.add(listaDeVisitaCollectionNewListaDeVisitaToAttach);
            }
            listaDeVisitaCollectionNew = attachedListaDeVisitaCollectionNew;
            comprador.setListaDeVisitaCollection(listaDeVisitaCollectionNew);
            Collection<Renta> attachedRentaCollectionNew = new ArrayList<Renta>();
            for (Renta rentaCollectionNewRentaToAttach : rentaCollectionNew) {
                rentaCollectionNewRentaToAttach = em.getReference(rentaCollectionNewRentaToAttach.getClass(), rentaCollectionNewRentaToAttach.getIdRenta());
                attachedRentaCollectionNew.add(rentaCollectionNewRentaToAttach);
            }
            rentaCollectionNew = attachedRentaCollectionNew;
            comprador.setRentaCollection(rentaCollectionNew);
            comprador = em.merge(comprador);
            if (cedulaOld != null && !cedulaOld.equals(cedulaNew)) {
                cedulaOld.getCompradorCollection().remove(comprador);
                cedulaOld = em.merge(cedulaOld);
            }
            if (cedulaNew != null && !cedulaNew.equals(cedulaOld)) {
                cedulaNew.getCompradorCollection().add(comprador);
                cedulaNew = em.merge(cedulaNew);
            }
            for (Propiedad propiedadCollectionOldPropiedad : propiedadCollectionOld) {
                if (!propiedadCollectionNew.contains(propiedadCollectionOldPropiedad)) {
                    propiedadCollectionOldPropiedad.setIdc(null);
                    propiedadCollectionOldPropiedad = em.merge(propiedadCollectionOldPropiedad);
                }
            }
            for (Propiedad propiedadCollectionNewPropiedad : propiedadCollectionNew) {
                if (!propiedadCollectionOld.contains(propiedadCollectionNewPropiedad)) {
                    Comprador oldIdcOfPropiedadCollectionNewPropiedad = propiedadCollectionNewPropiedad.getIdc();
                    propiedadCollectionNewPropiedad.setIdc(comprador);
                    propiedadCollectionNewPropiedad = em.merge(propiedadCollectionNewPropiedad);
                    if (oldIdcOfPropiedadCollectionNewPropiedad != null && !oldIdcOfPropiedadCollectionNewPropiedad.equals(comprador)) {
                        oldIdcOfPropiedadCollectionNewPropiedad.getPropiedadCollection().remove(propiedadCollectionNewPropiedad);
                        oldIdcOfPropiedadCollectionNewPropiedad = em.merge(oldIdcOfPropiedadCollectionNewPropiedad);
                    }
                }
            }
            for (ListaDeVisita listaDeVisitaCollectionNewListaDeVisita : listaDeVisitaCollectionNew) {
                if (!listaDeVisitaCollectionOld.contains(listaDeVisitaCollectionNewListaDeVisita)) {
                    Comprador oldCompradorOfListaDeVisitaCollectionNewListaDeVisita = listaDeVisitaCollectionNewListaDeVisita.getComprador();
                    listaDeVisitaCollectionNewListaDeVisita.setComprador(comprador);
                    listaDeVisitaCollectionNewListaDeVisita = em.merge(listaDeVisitaCollectionNewListaDeVisita);
                    if (oldCompradorOfListaDeVisitaCollectionNewListaDeVisita != null && !oldCompradorOfListaDeVisitaCollectionNewListaDeVisita.equals(comprador)) {
                        oldCompradorOfListaDeVisitaCollectionNewListaDeVisita.getListaDeVisitaCollection().remove(listaDeVisitaCollectionNewListaDeVisita);
                        oldCompradorOfListaDeVisitaCollectionNewListaDeVisita = em.merge(oldCompradorOfListaDeVisitaCollectionNewListaDeVisita);
                    }
                }
            }
            for (Renta rentaCollectionOldRenta : rentaCollectionOld) {
                if (!rentaCollectionNew.contains(rentaCollectionOldRenta)) {
                    rentaCollectionOldRenta.setIdc(null);
                    rentaCollectionOldRenta = em.merge(rentaCollectionOldRenta);
                }
            }
            for (Renta rentaCollectionNewRenta : rentaCollectionNew) {
                if (!rentaCollectionOld.contains(rentaCollectionNewRenta)) {
                    Comprador oldIdcOfRentaCollectionNewRenta = rentaCollectionNewRenta.getIdc();
                    rentaCollectionNewRenta.setIdc(comprador);
                    rentaCollectionNewRenta = em.merge(rentaCollectionNewRenta);
                    if (oldIdcOfRentaCollectionNewRenta != null && !oldIdcOfRentaCollectionNewRenta.equals(comprador)) {
                        oldIdcOfRentaCollectionNewRenta.getRentaCollection().remove(rentaCollectionNewRenta);
                        oldIdcOfRentaCollectionNewRenta = em.merge(oldIdcOfRentaCollectionNewRenta);
                    }
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Short id = comprador.getIdc();
                if (findComprador(id) == null) {
                    throw new NonexistentEntityException("The comprador with id " + id + " no longer exists.");
                }
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void destroy(Short id) throws IllegalOrphanException, NonexistentEntityException {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Comprador comprador;
            try {
                comprador = em.getReference(Comprador.class, id);
                comprador.getIdc();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The comprador with id " + id + " no longer exists.", enfe);
            }
            List<String> illegalOrphanMessages = null;
            Collection<ListaDeVisita> listaDeVisitaCollectionOrphanCheck = comprador.getListaDeVisitaCollection();
            for (ListaDeVisita listaDeVisitaCollectionOrphanCheckListaDeVisita : listaDeVisitaCollectionOrphanCheck) {
                if (illegalOrphanMessages == null) {
                    illegalOrphanMessages = new ArrayList<String>();
                }
                illegalOrphanMessages.add("This Comprador (" + comprador + ") cannot be destroyed since the ListaDeVisita " + listaDeVisitaCollectionOrphanCheckListaDeVisita + " in its listaDeVisitaCollection field has a non-nullable comprador field.");
            }
            if (illegalOrphanMessages != null) {
                throw new IllegalOrphanException(illegalOrphanMessages);
            }
            Usuario cedula = comprador.getCedula();
            if (cedula != null) {
                cedula.getCompradorCollection().remove(comprador);
                cedula = em.merge(cedula);
            }
            Collection<Propiedad> propiedadCollection = comprador.getPropiedadCollection();
            for (Propiedad propiedadCollectionPropiedad : propiedadCollection) {
                propiedadCollectionPropiedad.setIdc(null);
                propiedadCollectionPropiedad = em.merge(propiedadCollectionPropiedad);
            }
            Collection<Renta> rentaCollection = comprador.getRentaCollection();
            for (Renta rentaCollectionRenta : rentaCollection) {
                rentaCollectionRenta.setIdc(null);
                rentaCollectionRenta = em.merge(rentaCollectionRenta);
            }
            em.remove(comprador);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Comprador> findCompradorEntities() {
        return findCompradorEntities(true, -1, -1);
    }

    public List<Comprador> findCompradorEntities(int maxResults, int firstResult) {
        return findCompradorEntities(false, maxResults, firstResult);
    }

    private List<Comprador> findCompradorEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Comprador.class));
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

    public Comprador findComprador(Short id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Comprador.class, id);
        } finally {
            em.close();
        }
    }

    public int getCompradorCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Comprador> rt = cq.from(Comprador.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
