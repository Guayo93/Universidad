/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controllers;

import Controllers.exceptions.IllegalOrphanException;
import Controllers.exceptions.NonexistentEntityException;
import Controllers.exceptions.PreexistingEntityException;
import java.io.Serializable;
import javax.persistence.Query;
import javax.persistence.EntityNotFoundException;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import Entity.Ciudad;
import Entity.Comprador;
import Entity.Propietario;
import Entity.Imagen;
import Entity.ListaDeVisita;
import Entity.Propiedad;
import java.util.ArrayList;
import java.util.Collection;
import Entity.Renta;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

/**
 *
 * @author aleja_000
 */
public class PropiedadJpaController implements Serializable {

    public PropiedadJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Propiedad propiedad) throws PreexistingEntityException, Exception {
        if (propiedad.getListaDeVisitaCollection() == null) {
            propiedad.setListaDeVisitaCollection(new ArrayList<ListaDeVisita>());
        }
        if (propiedad.getRentaCollection() == null) {
            propiedad.setRentaCollection(new ArrayList<Renta>());
        }
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Ciudad codCiudad = propiedad.getCodCiudad();
            if (codCiudad != null) {
                codCiudad = em.getReference(codCiudad.getClass(), codCiudad.getCodCiudad());
                propiedad.setCodCiudad(codCiudad);
            }
            Comprador idc = propiedad.getIdc();
            if (idc != null) {
                idc = em.getReference(idc.getClass(), idc.getIdc());
                propiedad.setIdc(idc);
            }
            Propietario idp = propiedad.getIdp();
            if (idp != null) {
                idp = em.getReference(idp.getClass(), idp.getIdp());
                propiedad.setIdp(idp);
            }
            Imagen imagen = propiedad.getImagen();
            if (imagen != null) {
                imagen = em.getReference(imagen.getClass(), imagen.getIdPropiedad());
                propiedad.setImagen(imagen);
            }
            Collection<ListaDeVisita> attachedListaDeVisitaCollection = new ArrayList<ListaDeVisita>();
            for (ListaDeVisita listaDeVisitaCollectionListaDeVisitaToAttach : propiedad.getListaDeVisitaCollection()) {
                listaDeVisitaCollectionListaDeVisitaToAttach = em.getReference(listaDeVisitaCollectionListaDeVisitaToAttach.getClass(), listaDeVisitaCollectionListaDeVisitaToAttach.getListaDeVisitaPK());
                attachedListaDeVisitaCollection.add(listaDeVisitaCollectionListaDeVisitaToAttach);
            }
            propiedad.setListaDeVisitaCollection(attachedListaDeVisitaCollection);
            Collection<Renta> attachedRentaCollection = new ArrayList<Renta>();
            for (Renta rentaCollectionRentaToAttach : propiedad.getRentaCollection()) {
                rentaCollectionRentaToAttach = em.getReference(rentaCollectionRentaToAttach.getClass(), rentaCollectionRentaToAttach.getIdRenta());
                attachedRentaCollection.add(rentaCollectionRentaToAttach);
            }
            propiedad.setRentaCollection(attachedRentaCollection);
            em.persist(propiedad);
            if (codCiudad != null) {
                codCiudad.getPropiedadCollection().add(propiedad);
                codCiudad = em.merge(codCiudad);
            }
            if (idc != null) {
                idc.getPropiedadCollection().add(propiedad);
                idc = em.merge(idc);
            }
            if (idp != null) {
                idp.getPropiedadCollection().add(propiedad);
                idp = em.merge(idp);
            }
            if (imagen != null) {
                Propiedad oldPropiedadOfImagen = imagen.getPropiedad();
                if (oldPropiedadOfImagen != null) {
                    oldPropiedadOfImagen.setImagen(null);
                    oldPropiedadOfImagen = em.merge(oldPropiedadOfImagen);
                }
                imagen.setPropiedad(propiedad);
                imagen = em.merge(imagen);
            }
            for (ListaDeVisita listaDeVisitaCollectionListaDeVisita : propiedad.getListaDeVisitaCollection()) {
                Propiedad oldPropiedadOfListaDeVisitaCollectionListaDeVisita = listaDeVisitaCollectionListaDeVisita.getPropiedad();
                listaDeVisitaCollectionListaDeVisita.setPropiedad(propiedad);
                listaDeVisitaCollectionListaDeVisita = em.merge(listaDeVisitaCollectionListaDeVisita);
                if (oldPropiedadOfListaDeVisitaCollectionListaDeVisita != null) {
                    oldPropiedadOfListaDeVisitaCollectionListaDeVisita.getListaDeVisitaCollection().remove(listaDeVisitaCollectionListaDeVisita);
                    oldPropiedadOfListaDeVisitaCollectionListaDeVisita = em.merge(oldPropiedadOfListaDeVisitaCollectionListaDeVisita);
                }
            }
            for (Renta rentaCollectionRenta : propiedad.getRentaCollection()) {
                Propiedad oldIdpropOfRentaCollectionRenta = rentaCollectionRenta.getIdprop();
                rentaCollectionRenta.setIdprop(propiedad);
                rentaCollectionRenta = em.merge(rentaCollectionRenta);
                if (oldIdpropOfRentaCollectionRenta != null) {
                    oldIdpropOfRentaCollectionRenta.getRentaCollection().remove(rentaCollectionRenta);
                    oldIdpropOfRentaCollectionRenta = em.merge(oldIdpropOfRentaCollectionRenta);
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findPropiedad(propiedad.getIdPropiedad()) != null) {
                throw new PreexistingEntityException("Propiedad " + propiedad + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Propiedad propiedad) throws IllegalOrphanException, NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Propiedad persistentPropiedad = em.find(Propiedad.class, propiedad.getIdPropiedad());
            Ciudad codCiudadOld = persistentPropiedad.getCodCiudad();
            Ciudad codCiudadNew = propiedad.getCodCiudad();
            Comprador idcOld = persistentPropiedad.getIdc();
            Comprador idcNew = propiedad.getIdc();
            Propietario idpOld = persistentPropiedad.getIdp();
            Propietario idpNew = propiedad.getIdp();
            Imagen imagenOld = persistentPropiedad.getImagen();
            Imagen imagenNew = propiedad.getImagen();
            Collection<ListaDeVisita> listaDeVisitaCollectionOld = persistentPropiedad.getListaDeVisitaCollection();
            Collection<ListaDeVisita> listaDeVisitaCollectionNew = propiedad.getListaDeVisitaCollection();
            Collection<Renta> rentaCollectionOld = persistentPropiedad.getRentaCollection();
            Collection<Renta> rentaCollectionNew = propiedad.getRentaCollection();
            List<String> illegalOrphanMessages = null;
            if (imagenOld != null && !imagenOld.equals(imagenNew)) {
                if (illegalOrphanMessages == null) {
                    illegalOrphanMessages = new ArrayList<String>();
                }
                illegalOrphanMessages.add("You must retain Imagen " + imagenOld + " since its propiedad field is not nullable.");
            }
            for (ListaDeVisita listaDeVisitaCollectionOldListaDeVisita : listaDeVisitaCollectionOld) {
                if (!listaDeVisitaCollectionNew.contains(listaDeVisitaCollectionOldListaDeVisita)) {
                    if (illegalOrphanMessages == null) {
                        illegalOrphanMessages = new ArrayList<String>();
                    }
                    illegalOrphanMessages.add("You must retain ListaDeVisita " + listaDeVisitaCollectionOldListaDeVisita + " since its propiedad field is not nullable.");
                }
            }
            if (illegalOrphanMessages != null) {
                throw new IllegalOrphanException(illegalOrphanMessages);
            }
            if (codCiudadNew != null) {
                codCiudadNew = em.getReference(codCiudadNew.getClass(), codCiudadNew.getCodCiudad());
                propiedad.setCodCiudad(codCiudadNew);
            }
            if (idcNew != null) {
                idcNew = em.getReference(idcNew.getClass(), idcNew.getIdc());
                propiedad.setIdc(idcNew);
            }
            if (idpNew != null) {
                idpNew = em.getReference(idpNew.getClass(), idpNew.getIdp());
                propiedad.setIdp(idpNew);
            }
            if (imagenNew != null) {
                imagenNew = em.getReference(imagenNew.getClass(), imagenNew.getIdPropiedad());
                propiedad.setImagen(imagenNew);
            }
            Collection<ListaDeVisita> attachedListaDeVisitaCollectionNew = new ArrayList<ListaDeVisita>();
            for (ListaDeVisita listaDeVisitaCollectionNewListaDeVisitaToAttach : listaDeVisitaCollectionNew) {
                listaDeVisitaCollectionNewListaDeVisitaToAttach = em.getReference(listaDeVisitaCollectionNewListaDeVisitaToAttach.getClass(), listaDeVisitaCollectionNewListaDeVisitaToAttach.getListaDeVisitaPK());
                attachedListaDeVisitaCollectionNew.add(listaDeVisitaCollectionNewListaDeVisitaToAttach);
            }
            listaDeVisitaCollectionNew = attachedListaDeVisitaCollectionNew;
            propiedad.setListaDeVisitaCollection(listaDeVisitaCollectionNew);
            Collection<Renta> attachedRentaCollectionNew = new ArrayList<Renta>();
            for (Renta rentaCollectionNewRentaToAttach : rentaCollectionNew) {
                rentaCollectionNewRentaToAttach = em.getReference(rentaCollectionNewRentaToAttach.getClass(), rentaCollectionNewRentaToAttach.getIdRenta());
                attachedRentaCollectionNew.add(rentaCollectionNewRentaToAttach);
            }
            rentaCollectionNew = attachedRentaCollectionNew;
            propiedad.setRentaCollection(rentaCollectionNew);
            propiedad = em.merge(propiedad);
            if (codCiudadOld != null && !codCiudadOld.equals(codCiudadNew)) {
                codCiudadOld.getPropiedadCollection().remove(propiedad);
                codCiudadOld = em.merge(codCiudadOld);
            }
            if (codCiudadNew != null && !codCiudadNew.equals(codCiudadOld)) {
                codCiudadNew.getPropiedadCollection().add(propiedad);
                codCiudadNew = em.merge(codCiudadNew);
            }
            if (idcOld != null && !idcOld.equals(idcNew)) {
                idcOld.getPropiedadCollection().remove(propiedad);
                idcOld = em.merge(idcOld);
            }
            if (idcNew != null && !idcNew.equals(idcOld)) {
                idcNew.getPropiedadCollection().add(propiedad);
                idcNew = em.merge(idcNew);
            }
            if (idpOld != null && !idpOld.equals(idpNew)) {
                idpOld.getPropiedadCollection().remove(propiedad);
                idpOld = em.merge(idpOld);
            }
            if (idpNew != null && !idpNew.equals(idpOld)) {
                idpNew.getPropiedadCollection().add(propiedad);
                idpNew = em.merge(idpNew);
            }
            if (imagenNew != null && !imagenNew.equals(imagenOld)) {
                Propiedad oldPropiedadOfImagen = imagenNew.getPropiedad();
                if (oldPropiedadOfImagen != null) {
                    oldPropiedadOfImagen.setImagen(null);
                    oldPropiedadOfImagen = em.merge(oldPropiedadOfImagen);
                }
                imagenNew.setPropiedad(propiedad);
                imagenNew = em.merge(imagenNew);
            }
            for (ListaDeVisita listaDeVisitaCollectionNewListaDeVisita : listaDeVisitaCollectionNew) {
                if (!listaDeVisitaCollectionOld.contains(listaDeVisitaCollectionNewListaDeVisita)) {
                    Propiedad oldPropiedadOfListaDeVisitaCollectionNewListaDeVisita = listaDeVisitaCollectionNewListaDeVisita.getPropiedad();
                    listaDeVisitaCollectionNewListaDeVisita.setPropiedad(propiedad);
                    listaDeVisitaCollectionNewListaDeVisita = em.merge(listaDeVisitaCollectionNewListaDeVisita);
                    if (oldPropiedadOfListaDeVisitaCollectionNewListaDeVisita != null && !oldPropiedadOfListaDeVisitaCollectionNewListaDeVisita.equals(propiedad)) {
                        oldPropiedadOfListaDeVisitaCollectionNewListaDeVisita.getListaDeVisitaCollection().remove(listaDeVisitaCollectionNewListaDeVisita);
                        oldPropiedadOfListaDeVisitaCollectionNewListaDeVisita = em.merge(oldPropiedadOfListaDeVisitaCollectionNewListaDeVisita);
                    }
                }
            }
            for (Renta rentaCollectionOldRenta : rentaCollectionOld) {
                if (!rentaCollectionNew.contains(rentaCollectionOldRenta)) {
                    rentaCollectionOldRenta.setIdprop(null);
                    rentaCollectionOldRenta = em.merge(rentaCollectionOldRenta);
                }
            }
            for (Renta rentaCollectionNewRenta : rentaCollectionNew) {
                if (!rentaCollectionOld.contains(rentaCollectionNewRenta)) {
                    Propiedad oldIdpropOfRentaCollectionNewRenta = rentaCollectionNewRenta.getIdprop();
                    rentaCollectionNewRenta.setIdprop(propiedad);
                    rentaCollectionNewRenta = em.merge(rentaCollectionNewRenta);
                    if (oldIdpropOfRentaCollectionNewRenta != null && !oldIdpropOfRentaCollectionNewRenta.equals(propiedad)) {
                        oldIdpropOfRentaCollectionNewRenta.getRentaCollection().remove(rentaCollectionNewRenta);
                        oldIdpropOfRentaCollectionNewRenta = em.merge(oldIdpropOfRentaCollectionNewRenta);
                    }
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Short id = propiedad.getIdPropiedad();
                if (findPropiedad(id) == null) {
                    throw new NonexistentEntityException("The propiedad with id " + id + " no longer exists.");
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
            Propiedad propiedad;
            try {
                propiedad = em.getReference(Propiedad.class, id);
                propiedad.getIdPropiedad();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The propiedad with id " + id + " no longer exists.", enfe);
            }
            List<String> illegalOrphanMessages = null;
            Imagen imagenOrphanCheck = propiedad.getImagen();
            if (imagenOrphanCheck != null) {
                if (illegalOrphanMessages == null) {
                    illegalOrphanMessages = new ArrayList<String>();
                }
                illegalOrphanMessages.add("This Propiedad (" + propiedad + ") cannot be destroyed since the Imagen " + imagenOrphanCheck + " in its imagen field has a non-nullable propiedad field.");
            }
            Collection<ListaDeVisita> listaDeVisitaCollectionOrphanCheck = propiedad.getListaDeVisitaCollection();
            for (ListaDeVisita listaDeVisitaCollectionOrphanCheckListaDeVisita : listaDeVisitaCollectionOrphanCheck) {
                if (illegalOrphanMessages == null) {
                    illegalOrphanMessages = new ArrayList<String>();
                }
                illegalOrphanMessages.add("This Propiedad (" + propiedad + ") cannot be destroyed since the ListaDeVisita " + listaDeVisitaCollectionOrphanCheckListaDeVisita + " in its listaDeVisitaCollection field has a non-nullable propiedad field.");
            }
            if (illegalOrphanMessages != null) {
                throw new IllegalOrphanException(illegalOrphanMessages);
            }
            Ciudad codCiudad = propiedad.getCodCiudad();
            if (codCiudad != null) {
                codCiudad.getPropiedadCollection().remove(propiedad);
                codCiudad = em.merge(codCiudad);
            }
            Comprador idc = propiedad.getIdc();
            if (idc != null) {
                idc.getPropiedadCollection().remove(propiedad);
                idc = em.merge(idc);
            }
            Propietario idp = propiedad.getIdp();
            if (idp != null) {
                idp.getPropiedadCollection().remove(propiedad);
                idp = em.merge(idp);
            }
            Collection<Renta> rentaCollection = propiedad.getRentaCollection();
            for (Renta rentaCollectionRenta : rentaCollection) {
                rentaCollectionRenta.setIdprop(null);
                rentaCollectionRenta = em.merge(rentaCollectionRenta);
            }
            em.remove(propiedad);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Propiedad> findPropiedadEntities() {
        return findPropiedadEntities(true, -1, -1);
    }

    public List<Propiedad> findPropiedadEntities(int maxResults, int firstResult) {
        return findPropiedadEntities(false, maxResults, firstResult);
    }

    private List<Propiedad> findPropiedadEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Propiedad.class));
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

    public Propiedad findPropiedad(Short id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Propiedad.class, id);
        } finally {
            em.close();
        }
    }

    public int getPropiedadCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Propiedad> rt = cq.from(Propiedad.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
