/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controllers;

import Controllers.exceptions.IllegalOrphanException;
import Controllers.exceptions.NonexistentEntityException;
import Controllers.exceptions.PreexistingEntityException;
import Entity.Imagen;
import java.io.Serializable;
import javax.persistence.Query;
import javax.persistence.EntityNotFoundException;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import Entity.Propiedad;
import java.util.ArrayList;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

/**
 *
 * @author aleja_000
 */
public class ImagenJpaController implements Serializable {

    public ImagenJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Imagen imagen) throws IllegalOrphanException, PreexistingEntityException, Exception {
        List<String> illegalOrphanMessages = null;
        Propiedad propiedadOrphanCheck = imagen.getPropiedad();
        if (propiedadOrphanCheck != null) {
            Imagen oldImagenOfPropiedad = propiedadOrphanCheck.getImagen();
            if (oldImagenOfPropiedad != null) {
                if (illegalOrphanMessages == null) {
                    illegalOrphanMessages = new ArrayList<String>();
                }
                illegalOrphanMessages.add("The Propiedad " + propiedadOrphanCheck + " already has an item of type Imagen whose propiedad column cannot be null. Please make another selection for the propiedad field.");
            }
        }
        if (illegalOrphanMessages != null) {
            throw new IllegalOrphanException(illegalOrphanMessages);
        }
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Propiedad propiedad = imagen.getPropiedad();
            if (propiedad != null) {
                propiedad = em.getReference(propiedad.getClass(), propiedad.getIdPropiedad());
                imagen.setPropiedad(propiedad);
            }
            em.persist(imagen);
            if (propiedad != null) {
                propiedad.setImagen(imagen);
                propiedad = em.merge(propiedad);
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findImagen(imagen.getIdPropiedad()) != null) {
                throw new PreexistingEntityException("Imagen " + imagen + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Imagen imagen) throws IllegalOrphanException, NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Imagen persistentImagen = em.find(Imagen.class, imagen.getIdPropiedad());
            Propiedad propiedadOld = persistentImagen.getPropiedad();
            Propiedad propiedadNew = imagen.getPropiedad();
            List<String> illegalOrphanMessages = null;
            if (propiedadNew != null && !propiedadNew.equals(propiedadOld)) {
                Imagen oldImagenOfPropiedad = propiedadNew.getImagen();
                if (oldImagenOfPropiedad != null) {
                    if (illegalOrphanMessages == null) {
                        illegalOrphanMessages = new ArrayList<String>();
                    }
                    illegalOrphanMessages.add("The Propiedad " + propiedadNew + " already has an item of type Imagen whose propiedad column cannot be null. Please make another selection for the propiedad field.");
                }
            }
            if (illegalOrphanMessages != null) {
                throw new IllegalOrphanException(illegalOrphanMessages);
            }
            if (propiedadNew != null) {
                propiedadNew = em.getReference(propiedadNew.getClass(), propiedadNew.getIdPropiedad());
                imagen.setPropiedad(propiedadNew);
            }
            imagen = em.merge(imagen);
            if (propiedadOld != null && !propiedadOld.equals(propiedadNew)) {
                propiedadOld.setImagen(null);
                propiedadOld = em.merge(propiedadOld);
            }
            if (propiedadNew != null && !propiedadNew.equals(propiedadOld)) {
                propiedadNew.setImagen(imagen);
                propiedadNew = em.merge(propiedadNew);
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Short id = imagen.getIdPropiedad();
                if (findImagen(id) == null) {
                    throw new NonexistentEntityException("The imagen with id " + id + " no longer exists.");
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
            Imagen imagen;
            try {
                imagen = em.getReference(Imagen.class, id);
                imagen.getIdPropiedad();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The imagen with id " + id + " no longer exists.", enfe);
            }
            Propiedad propiedad = imagen.getPropiedad();
            if (propiedad != null) {
                propiedad.setImagen(null);
                propiedad = em.merge(propiedad);
            }
            em.remove(imagen);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Imagen> findImagenEntities() {
        return findImagenEntities(true, -1, -1);
    }

    public List<Imagen> findImagenEntities(int maxResults, int firstResult) {
        return findImagenEntities(false, maxResults, firstResult);
    }

    private List<Imagen> findImagenEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Imagen.class));
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

    public Imagen findImagen(Short id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Imagen.class, id);
        } finally {
            em.close();
        }
    }

    public int getImagenCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Imagen> rt = cq.from(Imagen.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
