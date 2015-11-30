/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entity;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.Lob;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author aleja_000
 */
@Entity
@Table(name = "IMAGEN")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Imagen.findAll", query = "SELECT i FROM Imagen i"),
    @NamedQuery(name = "Imagen.findByIdPropiedad", query = "SELECT i FROM Imagen i WHERE i.idPropiedad = :idPropiedad"),
    @NamedQuery(name = "Imagen.findByDescripcion", query = "SELECT i FROM Imagen i WHERE i.descripcion = :descripcion"),
    @NamedQuery(name = "Imagen.findByFecha", query = "SELECT i FROM Imagen i WHERE i.fecha = :fecha")})
public class Imagen implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "ID_PROPIEDAD")
    private Short idPropiedad;
    @Lob
    @Column(name = "IMG")
    private Serializable img;
    @Column(name = "DESCRIPCION")
    private String descripcion;
    @Column(name = "FECHA")
    @Temporal(TemporalType.TIMESTAMP)
    private Date fecha;
    @JoinColumn(name = "ID_PROPIEDAD", referencedColumnName = "ID_PROPIEDAD", insertable = false, updatable = false)
    @OneToOne(optional = false)
    private Propiedad propiedad;

    public Imagen() {
    }

    public Imagen(Short idPropiedad) {
        this.idPropiedad = idPropiedad;
    }

    public Short getIdPropiedad() {
        return idPropiedad;
    }

    public void setIdPropiedad(Short idPropiedad) {
        this.idPropiedad = idPropiedad;
    }

    public Serializable getImg() {
        return img;
    }

    public void setImg(Serializable img) {
        this.img = img;
    }

    public String getDescripcion() {
        return descripcion;
    }

    public void setDescripcion(String descripcion) {
        this.descripcion = descripcion;
    }

    public Date getFecha() {
        return fecha;
    }

    public void setFecha(Date fecha) {
        this.fecha = fecha;
    }

    public Propiedad getPropiedad() {
        return propiedad;
    }

    public void setPropiedad(Propiedad propiedad) {
        this.propiedad = propiedad;
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
        if (!(object instanceof Imagen)) {
            return false;
        }
        Imagen other = (Imagen) object;
        if ((this.idPropiedad == null && other.idPropiedad != null) || (this.idPropiedad != null && !this.idPropiedad.equals(other.idPropiedad))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Entity.Imagen[ idPropiedad=" + idPropiedad + " ]";
    }
    
}
