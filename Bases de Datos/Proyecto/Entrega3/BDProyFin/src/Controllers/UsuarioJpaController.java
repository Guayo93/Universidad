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
import java.util.ArrayList;
import java.util.Collection;
import Entity.Propietario;
import Entity.Usuario;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

/**
 *
 * @author aleja_000
 */
public class UsuarioJpaController implements Serializable {

    public UsuarioJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Usuario usuario) throws PreexistingEntityException, Exception {
        if (usuario.getCompradorCollection() == null) {
            usuario.setCompradorCollection(new ArrayList<Comprador>());
        }
        if (usuario.getPropietarioCollection() == null) {
            usuario.setPropietarioCollection(new ArrayList<Propietario>());
        }
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Collection<Comprador> attachedCompradorCollection = new ArrayList<Comprador>();
            for (Comprador compradorCollectionCompradorToAttach : usuario.getCompradorCollection()) {
                compradorCollectionCompradorToAttach = em.getReference(compradorCollectionCompradorToAttach.getClass(), compradorCollectionCompradorToAttach.getIdc());
                attachedCompradorCollection.add(compradorCollectionCompradorToAttach);
            }
            usuario.setCompradorCollection(attachedCompradorCollection);
            Collection<Propietario> attachedPropietarioCollection = new ArrayList<Propietario>();
            for (Propietario propietarioCollectionPropietarioToAttach : usuario.getPropietarioCollection()) {
                propietarioCollectionPropietarioToAttach = em.getReference(propietarioCollectionPropietarioToAttach.getClass(), propietarioCollectionPropietarioToAttach.getIdp());
                attachedPropietarioCollection.add(propietarioCollectionPropietarioToAttach);
            }
            usuario.setPropietarioCollection(attachedPropietarioCollection);
            em.persist(usuario);
            for (Comprador compradorCollectionComprador : usuario.getCompradorCollection()) {
                Usuario oldCedulaOfCompradorCollectionComprador = compradorCollectionComprador.getCedula();
                compradorCollectionComprador.setCedula(usuario);
                compradorCollectionComprador = em.merge(compradorCollectionComprador);
                if (oldCedulaOfCompradorCollectionComprador != null) {
                    oldCedulaOfCompradorCollectionComprador.getCompradorCollection().remove(compradorCollectionComprador);
                    oldCedulaOfCompradorCollectionComprador = em.merge(oldCedulaOfCompradorCollectionComprador);
                }
            }
            for (Propietario propietarioCollectionPropietario : usuario.getPropietarioCollection()) {
                Usuario oldCedulaOfPropietarioCollectionPropietario = propietarioCollectionPropietario.getCedula();
                propietarioCollectionPropietario.setCedula(usuario);
                propietarioCollectionPropietario = em.merge(propietarioCollectionPropietario);
                if (oldCedulaOfPropietarioCollectionPropietario != null) {
                    oldCedulaOfPropietarioCollectionPropietario.getPropietarioCollection().remove(propietarioCollectionPropietario);
                    oldCedulaOfPropietarioCollectionPropietario = em.merge(oldCedulaOfPropietarioCollectionPropietario);
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findUsuario(usuario.getCedula()) != null) {
                throw new PreexistingEntityException("Usuario " + usuario + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Usuario usuario) throws NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Usuario persistentUsuario = em.find(Usuario.class, usuario.getCedula());
            Collection<Comprador> compradorCollectionOld = persistentUsuario.getCompradorCollection();
            Collection<Comprador> compradorCollectionNew = usuario.getCompradorCollection();
            Collection<Propietario> propietarioCollectionOld = persistentUsuario.getPropietarioCollection();
            Collection<Propietario> propietarioCollectionNew = usuario.getPropietarioCollection();
            Collection<Comprador> attachedCompradorCollectionNew = new ArrayList<Comprador>();
            for (Comprador compradorCollectionNewCompradorToAttach : compradorCollectionNew) {
                compradorCollectionNewCompradorToAttach = em.getReference(compradorCollectionNewCompradorToAttach.getClass(), compradorCollectionNewCompradorToAttach.getIdc());
                attachedCompradorCollectionNew.add(compradorCollectionNewCompradorToAttach);
            }
            compradorCollectionNew = attachedCompradorCollectionNew;
            usuario.setCompradorCollection(compradorCollectionNew);
            Collection<Propietario> attachedPropietarioCollectionNew = new ArrayList<Propietario>();
            for (Propietario propietarioCollectionNewPropietarioToAttach : propietarioCollectionNew) {
                propietarioCollectionNewPropietarioToAttach = em.getReference(propietarioCollectionNewPropietarioToAttach.getClass(), propietarioCollectionNewPropietarioToAttach.getIdp());
                attachedPropietarioCollectionNew.add(propietarioCollectionNewPropietarioToAttach);
            }
            propietarioCollectionNew = attachedPropietarioCollectionNew;
            usuario.setPropietarioCollection(propietarioCollectionNew);
            usuario = em.merge(usuario);
            for (Comprador compradorCollectionOldComprador : compradorCollectionOld) {
                if (!compradorCollectionNew.contains(compradorCollectionOldComprador)) {
                    compradorCollectionOldComprador.setCedula(null);
                    compradorCollectionOldComprador = em.merge(compradorCollectionOldComprador);
                }
            }
            for (Comprador compradorCollectionNewComprador : compradorCollectionNew) {
                if (!compradorCollectionOld.contains(compradorCollectionNewComprador)) {
                    Usuario oldCedulaOfCompradorCollectionNewComprador = compradorCollectionNewComprador.getCedula();
                    compradorCollectionNewComprador.setCedula(usuario);
                    compradorCollectionNewComprador = em.merge(compradorCollectionNewComprador);
                    if (oldCedulaOfCompradorCollectionNewComprador != null && !oldCedulaOfCompradorCollectionNewComprador.equals(usuario)) {
                        oldCedulaOfCompradorCollectionNewComprador.getCompradorCollection().remove(compradorCollectionNewComprador);
                        oldCedulaOfCompradorCollectionNewComprador = em.merge(oldCedulaOfCompradorCollectionNewComprador);
                    }
                }
            }
            for (Propietario propietarioCollectionOldPropietario : propietarioCollectionOld) {
                if (!propietarioCollectionNew.contains(propietarioCollectionOldPropietario)) {
                    propietarioCollectionOldPropietario.setCedula(null);
                    propietarioCollectionOldPropietario = em.merge(propietarioCollectionOldPropietario);
                }
            }
            for (Propietario propietarioCollectionNewPropietario : propietarioCollectionNew) {
                if (!propietarioCollectionOld.contains(propietarioCollectionNewPropietario)) {
                    Usuario oldCedulaOfPropietarioCollectionNewPropietario = propietarioCollectionNewPropietario.getCedula();
                    propietarioCollectionNewPropietario.setCedula(usuario);
                    propietarioCollectionNewPropietario = em.merge(propietarioCollectionNewPropietario);
                    if (oldCedulaOfPropietarioCollectionNewPropietario != null && !oldCedulaOfPropietarioCollectionNewPropietario.equals(usuario)) {
                        oldCedulaOfPropietarioCollectionNewPropietario.getPropietarioCollection().remove(propietarioCollectionNewPropietario);
                        oldCedulaOfPropietarioCollectionNewPropietario = em.merge(oldCedulaOfPropietarioCollectionNewPropietario);
                    }
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Long id = usuario.getCedula();
                if (findUsuario(id) == null) {
                    throw new NonexistentEntityException("The usuario with id " + id + " no longer exists.");
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
            Usuario usuario;
            try {
                usuario = em.getReference(Usuario.class, id);
                usuario.getCedula();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The usuario with id " + id + " no longer exists.", enfe);
            }
            Collection<Comprador> compradorCollection = usuario.getCompradorCollection();
            for (Comprador compradorCollectionComprador : compradorCollection) {
                compradorCollectionComprador.setCedula(null);
                compradorCollectionComprador = em.merge(compradorCollectionComprador);
            }
            Collection<Propietario> propietarioCollection = usuario.getPropietarioCollection();
            for (Propietario propietarioCollectionPropietario : propietarioCollection) {
                propietarioCollectionPropietario.setCedula(null);
                propietarioCollectionPropietario = em.merge(propietarioCollectionPropietario);
            }
            em.remove(usuario);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Usuario> findUsuarioEntities() {
        return findUsuarioEntities(true, -1, -1);
    }

    public List<Usuario> findUsuarioEntities(int maxResults, int firstResult) {
        return findUsuarioEntities(false, maxResults, firstResult);
    }

    private List<Usuario> findUsuarioEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Usuario.class));
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

    public Usuario findUsuario(Long id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Usuario.class, id);
        } finally {
            em.close();
        }
    }

    public int getUsuarioCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Usuario> rt = cq.from(Usuario.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
