/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entity;

import java.io.Serializable;
import java.util.Collection;
import javax.persistence.Basic;
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
@Table(name = "PROPIETARIO")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Propietario.findAll", query = "SELECT p FROM Propietario p"),
    @NamedQuery(name = "Propietario.findByIdp", query = "SELECT p FROM Propietario p WHERE p.idp = :idp"),
    @NamedQuery(name = "Propietario.findByUsuario", query = "SELECT p FROM Propietario p WHERE p.usuario = :usuario"),
    @NamedQuery(name = "Propietario.findByContrasena", query = "SELECT p FROM Propietario p WHERE p.contrasena = :contrasena")})
public class Propietario implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "IDP")
    private Short idp;
    @Column(name = "USUARIO")
    private String usuario;
    @Column(name = "CONTRASENA")
    private String contrasena;
    @OneToMany(mappedBy = "idp")
    private Collection<Propiedad> propiedadCollection;
    @JoinColumn(name = "CEDULA", referencedColumnName = "CEDULA")
    @ManyToOne
    private Usuario cedula;

    public Propietario() {
    }

    public Propietario(Short idp) {
        this.idp = idp;
    }

    public Short getIdp() {
        return idp;
    }

    public void setIdp(Short idp) {
        this.idp = idp;
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

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idp != null ? idp.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Propietario)) {
            return false;
        }
        Propietario other = (Propietario) object;
        if ((this.idp == null && other.idp != null) || (this.idp != null && !this.idp.equals(other.idp))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Entity.Propietario[ idp=" + idp + " ]";
    }
    
}
