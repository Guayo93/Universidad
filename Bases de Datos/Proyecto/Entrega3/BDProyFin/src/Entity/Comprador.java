/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entity;

import java.io.Serializable;
import java.util.Collection;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author aleja_000
 */
@Entity
@Table(name = "COMPRADOR")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Comprador.findAll", query = "SELECT c FROM Comprador c"),
    @NamedQuery(name = "Comprador.findByIdc", query = "SELECT c FROM Comprador c WHERE c.idc = :idc"),
    @NamedQuery(name = "Comprador.findByUsuario", query = "SELECT c FROM Comprador c WHERE c.usuario = :usuario"),
    @NamedQuery(name = "Comprador.findByContrasena", query = "SELECT c FROM Comprador c WHERE c.contrasena = :contrasena")})
public class Comprador implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "IDC")
    private Short idc;
    @Column(name = "USUARIO")
    private String usuario;
    @Column(name = "CONTRASENA")
    private String contrasena;
    @OneToMany(mappedBy = "idc")
    private Collection<Propiedad> propiedadCollection;
    @JoinColumn(name = "CEDULA", referencedColumnName = "CEDULA")
    @ManyToOne
    private Usuario cedula;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "comprador")
    private Collection<ListaDeVisita> listaDeVisitaCollection;
    @OneToMany(mappedBy = "idc")
    private Collection<Renta> rentaCollection;

    public Comprador() {
    }

    public Comprador(Short idc) {
        this.idc = idc;
    }

    public Short getIdc() {
        return idc;
    }

    public void setIdc(Short idc) {
        this.idc = idc;
    }

    public String getUsuario() {
        return usuario;
    }

    public void setUsuario(String usuario) {
        this.usuario = usuario;
    }

    public String getContrasena() {
        return contrasena;
    }

    public void setContrasena(String contrasena) {
        this.contrasena = contrasena;
    }

    @XmlTransient
    public Collection<Propiedad> getPropiedadCollection() {
        return propiedadCollection;
    }

    public void setPropiedadCollection(Collection<Propiedad> propiedadCollection) {
        this.propiedadCollection = propiedadCollection;
    }

    public Usuario getCedula() {
        return cedula;
    }

    public void setCedula(Usuario cedula) {
        this.cedula = cedula;
    }

    @XmlTransient
    public Collection<ListaDeVisita> getListaDeVisitaCollection() {
        return listaDeVisitaCollection;
    }

    public void setListaDeVisitaCollection(Collection<ListaDeVisita> listaDeVisitaCollection) {
        this.listaDeVisitaCollection = listaDeVisitaCollection;
    }

    @XmlTransient
    public Collection<Renta> getRentaCollection() {
        return rentaCollection;
    }

    public void setRentaCollection(Collection<Renta> rentaCollection) {
        this.rentaCollection = rentaCollection;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idc != null ? idc.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Comprador)) {
            return false;
        }
        Comprador other = (Comprador) object;
        if ((this.idc == null && other.idc != null) || (this.idc != null && !this.idc.equals(other.idc))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "bdproyfin.Comprador[ idc=" + idc + " ]";
    }
    
}
