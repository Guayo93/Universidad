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
import Entity.Asesor;
import Entity.Comprador;
import Entity.Propiedad;
import Entity.Renta;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

/**
 *
 * @author aleja_000
 */
public class RentaJpaController implements Serializable {

    public RentaJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Renta renta) throws PreexistingEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Asesor cedAse = renta.getCedAse();
            if (cedAse != null) {
                cedAse = em.getReference(cedAse.getClass(), cedAse.getCedula());
                renta.setCedAse(cedAse);
            }
            Comprador idc = renta.getIdc();
            if (idc != null) {
                idc = em.getReference(idc.getClass(), idc.getIdc());
                renta.setIdc(idc);
            }
            Propiedad idprop = renta.getIdprop();
            if (idprop != null) {
                idprop = em.getReference(idprop.getClass(), idprop.getIdPropiedad());
                renta.setIdprop(idprop);
            }
            em.persist(renta);
            if (cedAse != null) {
                cedAse.getRentaCollection().add(renta);
                cedAse = em.merge(cedAse);
            }
            if (idc != null) {
                idc.getRentaCollection().add(renta);
                idc = em.merge(idc);
            }
            if (idprop != null) {
                idprop.getRentaCollection().add(renta);
                idprop = em.merge(idprop);
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findRenta(renta.getIdRenta()) != null) {
                throw new PreexistingEntityException("Renta " + renta + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Renta renta) throws NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Renta persistentRenta = em.find(Renta.class, renta.getIdRenta());
            Asesor cedAseOld = persistentRenta.getCedAse();
            Asesor cedAseNew = renta.getCedAse();
            Comprador idcOld = persistentRenta.getIdc();
            Comprador idcNew = renta.getIdc();
            Propiedad idpropOld = persistentRenta.getIdprop();
            Propiedad idpropNew = renta.getIdprop();
            if (cedAseNew != null) {
                cedAseNew = em.getReference(cedAseNew.getClass(), cedAseNew.getCedula());
                renta.setCedAse(cedAseNew);
            }
            if (idcNew != null) {
                idcNew = em.getReference(idcNew.getClass(), idcNew.getIdc());
                renta.setIdc(idcNew);
            }
            if (idpropNew != null) {
                idpropNew = em.getReference(idpropNew.getClass(), idpropNew.getIdPropiedad());
                renta.setIdprop(idpropNew);
            }
            renta = em.merge(renta);
            if (cedAseOld != null && !cedAseOld.equals(cedAseNew)) {
                cedAseOld.getRentaCollection().remove(renta);
                cedAseOld = em.merge(cedAseOld);
            }
            if (cedAseNew != null && !cedAseNew.equals(cedAseOld)) {
                cedAseNew.getRentaCollection().add(renta);
                cedAseNew = em.merge(cedAseNew);
            }
            if (idcOld != null && !idcOld.equals(idcNew)) {
                idcOld.getRentaCollection().remove(renta);
                idcOld = em.merge(idcOld);
            }
            if (idcNew != null && !idcNew.equals(idcOld)) {
                idcNew.getRentaCollection().add(renta);
                idcNew = em.merge(idcNew);
            }
            if (idpropOld != null && !idpropOld.equals(idpropNew)) {
                idpropOld.getRentaCollection().remove(renta);
                idpropOld = em.merge(idpropOld);
            }
            if (idpropNew != null && !idpropNew.equals(idpropOld)) {
                idpropNew.getRentaCollection().add(renta);
                idpropNew = em.merge(idpropNew);
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Short id = renta.getIdRenta();
                if (findRenta(id) == null) {
                    throw new NonexistentEntityException("The renta with id " + id + " no longer exists.");
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
            Renta renta;
            try {
                renta = em.getReference(Renta.class, id);
                renta.getIdRenta();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The renta with id " + id + " no longer exists.", enfe);
            }
            Asesor cedAse = renta.getCedAse();
            if (cedAse != null) {
                cedAse.getRentaCollection().remove(renta);
                cedAse = em.merge(cedAse);
            }
            Comprador idc = renta.getIdc();
            if (idc != null) {
                idc.getRentaCollection().remove(renta);
                idc = em.merge(idc);
            }
            Propiedad idprop = renta.getIdprop();
            if (idprop != null) {
                idprop.getRentaCollection().remove(renta);
                idprop = em.merge(idprop);
            }
            em.remove(renta);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Renta> findRentaEntities() {
        return findRentaEntities(true, -1, -1);
    }

    public List<Renta> findRentaEntities(int maxResults, int firstResult) {
        return findRentaEntities(false, maxResults, firstResult);
    }

    private List<Renta> findRentaEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Renta.class));
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

    public Renta findRenta(Short id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Renta.class, id);
        } finally {
            em.close();
        }
    }

    public int getRentaCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Renta> rt = cq.from(Renta.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
