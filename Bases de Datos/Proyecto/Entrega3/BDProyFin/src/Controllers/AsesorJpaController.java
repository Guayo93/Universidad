/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controllers;

import Controllers.exceptions.NonexistentEntityException;
import Controllers.exceptions.PreexistingEntityException;
import Entity.Asesor;
import java.io.Serializable;
import javax.persistence.Query;
import javax.persistence.EntityNotFoundException;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import Entity.Renta;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

/**
 *
 * @author aleja_000
 */
public class AsesorJpaController implements Serializable {

    public AsesorJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Asesor asesor) throws PreexistingEntityException, Exception {
        if (asesor.getRentaCollection() == null) {
            asesor.setRentaCollection(new ArrayList<Renta>());
        }
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Collection<Renta> attachedRentaCollection = new ArrayList<Renta>();
            for (Renta rentaCollectionRentaToAttach : asesor.getRentaCollection()) {
                rentaCollectionRentaToAttach = em.getReference(rentaCollectionRentaToAttach.getClass(), rentaCollectionRentaToAttach.getIdRenta());
                attachedRentaCollection.add(rentaCollectionRentaToAttach);
            }
            asesor.setRentaCollection(attachedRentaCollection);
            em.persist(asesor);
            for (Renta rentaCollectionRenta : asesor.getRentaCollection()) {
                Asesor oldCedAseOfRentaCollectionRenta = rentaCollectionRenta.getCedAse();
                rentaCollectionRenta.setCedAse(asesor);
                rentaCollectionRenta = em.merge(rentaCollectionRenta);
                if (oldCedAseOfRentaCollectionRenta != null) {
                    oldCedAseOfRentaCollectionRenta.getRentaCollection().remove(rentaCollectionRenta);
                    oldCedAseOfRentaCollectionRenta = em.merge(oldCedAseOfRentaCollectionRenta);
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findAsesor(asesor.getCedula()) != null) {
                throw new PreexistingEntityException("Asesor " + asesor + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Asesor asesor) throws NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Asesor persistentAsesor = em.find(Asesor.class, asesor.getCedula());
            Collection<Renta> rentaCollectionOld = persistentAsesor.getRentaCollection();
            Collection<Renta> rentaCollectionNew = asesor.getRentaCollection();
            Collection<Renta> attachedRentaCollectionNew = new ArrayList<Renta>();
            for (Renta rentaCollectionNewRentaToAttach : rentaCollectionNew) {
                rentaCollectionNewRentaToAttach = em.getReference(rentaCollectionNewRentaToAttach.getClass(), rentaCollectionNewRentaToAttach.getIdRenta());
                attachedRentaCollectionNew.add(rentaCollectionNewRentaToAttach);
            }
            rentaCollectionNew = attachedRentaCollectionNew;
            asesor.setRentaCollection(rentaCollectionNew);
            asesor = em.merge(asesor);
            for (Renta rentaCollectionOldRenta : rentaCollectionOld) {
                if (!rentaCollectionNew.contains(rentaCollectionOldRenta)) {
                    rentaCollectionOldRenta.setCedAse(null);
                    rentaCollectionOldRenta = em.merge(rentaCollectionOldRenta);
                }
            }
            for (Renta rentaCollectionNewRenta : rentaCollectionNew) {
                if (!rentaCollectionOld.contains(rentaCollectionNewRenta)) {
                    Asesor oldCedAseOfRentaCollectionNewRenta = rentaCollectionNewRenta.getCedAse();
                    rentaCollectionNewRenta.setCedAse(asesor);
                    rentaCollectionNewRenta = em.merge(rentaCollectionNewRenta);
                    if (oldCedAseOfRentaCollectionNewRenta != null && !oldCedAseOfRentaCollectionNewRenta.equals(asesor)) {
                        oldCedAseOfRentaCollectionNewRenta.getRentaCollection().remove(rentaCollectionNewRenta);
                        oldCedAseOfRentaCollectionNewRenta = em.merge(oldCedAseOfRentaCollectionNewRenta);
                    }
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Long id = asesor.getCedula();
                if (findAsesor(id) == null) {
                    throw new NonexistentEntityException("The asesor with id " + id + " no longer exists.");
                }
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void destroy(Long id) throws NonexistentEntityException {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Asesor asesor;
            try {
                asesor = em.getReference(Asesor.class, id);
                asesor.getCedula();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The asesor with id " + id + " no longer exists.", enfe);
            }
            Collection<Renta> rentaCollection = asesor.getRentaCollection();
            for (Renta rentaCollectionRenta : rentaCollection) {
                rentaCollectionRenta.setCedAse(null);
                rentaCollectionRenta = em.merge(rentaCollectionRenta);
            }
            em.remove(asesor);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Asesor> findAsesorEntities() {
        return findAsesorEntities(true, -1, -1);
    }

    public List<Asesor> findAsesorEntities(int maxResults, int firstResult) {
        return findAsesorEntities(false, maxResults, firstResult);
    }

    private List<Asesor> findAsesorEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Asesor.class));
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

    public Asesor findAsesor(Long id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Asesor.class, id);
        } finally {
            em.close();
        }
    }

    public int getAsesorCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Asesor> rt = cq.from(Asesor.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
