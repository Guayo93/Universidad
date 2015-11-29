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
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author aleja_000
 */
@Entity
@Table(name = "PROPIEDAD")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Propiedad.findAll", query = "SELECT p FROM Propiedad p"),
    @NamedQuery(name = "Propiedad.findByIdPropiedad", query = "SELECT p FROM Propiedad p WHERE p.idPropiedad = :idPropiedad"),
    @NamedQuery(name = "Propiedad.findByTipo", query = "SELECT p FROM Propiedad p WHERE p.tipo = :tipo"),
    @NamedQuery(name = "Propiedad.findByNumHabitaciones", query = "SELECT p FROM Propiedad p WHERE p.numHabitaciones = :numHabitaciones"),
    @NamedQuery(name = "Propiedad.findByDireccion", query = "SELECT p FROM Propiedad p WHERE p.direccion = :direccion"),
    @NamedQuery(name = "Propiedad.findByEstado", query = "SELECT p FROM Propiedad p WHERE p.estado = :estado")})
public class Propiedad implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "ID_PROPIEDAD")
    private Short idPropiedad;
    @Column(name = "TIPO")
    private String tipo;
    @Column(name = "NUM_HABITACIONES")
    private Short numHabitaciones;
    @Column(name = "DIRECCION")
    private String direccion;
    @Column(name = "ESTADO")
    private Short estado;
    @JoinColumn(name = "COD_CIUDAD", referencedColumnName = "COD_CIUDAD")
    @ManyToOne
    private Ciudad codCiudad;
    @JoinColumn(name = "IDC", referencedColumnName = "IDC")
    @ManyToOne
    private Comprador idc;
    @JoinColumn(name = "IDP", referencedColumnName = "IDP")
    @ManyToOne
    private Propietario idp;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "propiedad")
    private Collection<ListaDeVisita> listaDeVisitaCollection;
    @OneToMany(mappedBy = "idprop")
    private Collection<Renta> rentaCollection;
    @OneToOne(cascade = CascadeType.ALL, mappedBy = "propiedad")
    private Imagen imagen;

    public Propiedad() {
    }

    public Propiedad(Short idPropiedad) {
        this.idPropiedad = idPropiedad;
    }

    public Short getIdPropiedad() {
        return idPropiedad;
    }

    public void setIdPropiedad(Short idPropiedad) {
        this.idPropiedad = idPropiedad;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public Short getNumHabitaciones() {
        return numHabitaciones;
    }

    public void setNumHabitaciones(Short numHabitaciones) {
        this.numHabitaciones = numHabitaciones;
    }

    public String getDireccion() {
        return direccion;
    }

    public void setDireccion(String direccion) {
        this.direccion = direccion;
    }

    public Short getEstado() {
        return estado;
    }

    public void setEstado(Short estado) {
        this.estado = estado;
    }

    public Ciudad getCodCiudad() {
        return codCiudad;
    }

    public void setCodCiudad(Ciudad codCiudad) {
        this.codCiudad = codCiudad;
    }

    public Comprador getIdc() {
        return idc;
    }

    public void setIdc(Comprador idc) {
        this.idc = idc;
    }

    public Propietario getIdp() {
        return idp;
    }

    public void setIdp(Propietario idp) {
        this.idp = idp;
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

    public Imagen getImagen() {
        return imagen;
    }

    public void setImagen(Imagen imagen) {
        this.imagen = imagen;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idPropiedad != null ? idPropiedad.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Propiedad)) {
            return false;
        }
        Propiedad other = (Propiedad) object;
        if ((this.idPropiedad == null && other.idPropiedad != null) || (this.idPropiedad != null && !this.idPropiedad.equals(other.idPropiedad))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "bdproyfin.Propiedad[ idPropiedad=" + idPropiedad + " ]";
    }
    
}
