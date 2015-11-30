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
import Entity.Comprador;
import Entity.ListaDeVisita;
import Entity.ListaDeVisitaPK;
import Entity.Propiedad;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

/**
 *
 * @author aleja_000
 */
public class ListaDeVisitaJpaController implements Serializable {

    public ListaDeVisitaJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(ListaDeVisita listaDeVisita) throws PreexistingEntityException, Exception {
        if (listaDeVisita.getListaDeVisitaPK() == null) {
            listaDeVisita.setListaDeVisitaPK(new ListaDeVisitaPK());
        }
        listaDeVisita.getListaDeVisitaPK().setIdc(listaDeVisita.getComprador().getIdc());
        listaDeVisita.getListaDeVisitaPK().setIdPropiedad(listaDeVisita.getPropiedad().getIdPropiedad());
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Comprador comprador = listaDeVisita.getComprador();
            if (comprador != null) {
                comprador = em.getReference(comprador.getClass(), comprador.getIdc());
                listaDeVisita.setComprador(comprador);
            }
            Propiedad propiedad = listaDeVisita.getPropiedad();
            if (propiedad != null) {
                propiedad = em.getReference(propiedad.getClass(), propiedad.getIdPropiedad());
                listaDeVisita.setPropiedad(propiedad);
            }
            em.persist(listaDeVisita);
            if (comprador != null) {
                comprador.getListaDeVisitaCollection().add(listaDeVisita);
                comprador = em.merge(comprador);
            }
            if (propiedad != null) {
                propiedad.getListaDeVisitaCollection().add(listaDeVisita);
                propiedad = em.merge(propiedad);
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findListaDeVisita(listaDeVisita.getListaDeVisitaPK()) != null) {
                throw new PreexistingEntityException("ListaDeVisita " + listaDeVisita + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(ListaDeVisita listaDeVisita) throws NonexistentEntityException, Exception {
        listaDeVisita.getListaDeVisitaPK().setIdc(listaDeVisita.getComprador().getIdc());
        listaDeVisita.getListaDeVisitaPK().setIdPropiedad(listaDeVisita.getPropiedad().getIdPropiedad());
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            ListaDeVisita persistentListaDeVisita = em.find(ListaDeVisita.class, listaDeVisita.getListaDeVisitaPK());
            Comprador compradorOld = persistentListaDeVisita.getComprador();
            Comprador compradorNew = listaDeVisita.getComprador();
            Propiedad propiedadOld = persistentListaDeVisita.getPropiedad();
            Propiedad propiedadNew = listaDeVisita.getPropiedad();
            if (compradorNew != null) {
                compradorNew = em.getReference(compradorNew.getClass(), compradorNew.getIdc());
                listaDeVisita.setComprador(compradorNew);
            }
            if (propiedadNew != null) {
                propiedadNew = em.getReference(propiedadNew.getClass(), propiedadNew.getIdPropiedad());
                listaDeVisita.setPropiedad(propiedadNew);
            }
            listaDeVisita = em.merge(listaDeVisita);
            if (compradorOld != null && !compradorOld.equals(compradorNew)) {
                compradorOld.getListaDeVisitaCollection().remove(listaDeVisita);
                compradorOld = em.merge(compradorOld);
            }
            if (compradorNew != null && !compradorNew.equals(compradorOld)) {
                compradorNew.getListaDeVisitaCollection().add(listaDeVisita);
                compradorNew = em.merge(compradorNew);
            }
            if (propiedadOld != null && !propiedadOld.equals(propiedadNew)) {
                propiedadOld.getListaDeVisitaCollection().remove(listaDeVisita);
                propiedadOld = em.merge(propiedadOld);
            }
            if (propiedadNew != null && !propiedadNew.equals(propiedadOld)) {
                propiedadNew.getListaDeVisitaCollection().add(listaDeVisita);
                propiedadNew = em.merge(propiedadNew);
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                ListaDeVisitaPK id = listaDeVisita.getListaDeVisitaPK();
                if (findListaDeVisita(id) == null) {
                    throw new NonexistentEntityException("The listaDeVisita with id " + id + " no longer exists.");
                }
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void destroy(ListaDeVisitaPK id) throws NonexistentEntityException {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            ListaDeVisita listaDeVisita;
            try {
                listaDeVisita = em.getReference(ListaDeVisita.class, id);
                listaDeVisita.getListaDeVisitaPK();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The listaDeVisita with id " + id + " no longer exists.", enfe);
            }
            Comprador comprador = listaDeVisita.getComprador();
            if (comprador != null) {
                comprador.getListaDeVisitaCollection().remove(listaDeVisita);
                comprador = em.merge(comprador);
            }
            Propiedad propiedad = listaDeVisita.getPropiedad();
            if (propiedad != null) {
                propiedad.getListaDeVisitaCollection().remove(listaDeVisita);
                propiedad = em.merge(propiedad);
            }
            em.remove(listaDeVisita);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<ListaDeVisita> findListaDeVisitaEntities() {
        return findListaDeVisitaEntities(true, -1, -1);
    }

    public List<ListaDeVisita> findListaDeVisitaEntities(int maxResults, int firstResult) {
        return findListaDeVisitaEntities(false, maxResults, firstResult);
    }

    private List<ListaDeVisita> findListaDeVisitaEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(ListaDeVisita.class));
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

    public ListaDeVisita findListaDeVisita(ListaDeVisitaPK id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(ListaDeVisita.class, id);
        } finally {
            em.close();
        }
    }

    public int getListaDeVisitaCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<ListaDeVisita> rt = cq.from(ListaDeVisita.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
