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
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author aleja_000
 */
@Entity
@Table(name = "RENTA")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Renta.findAll", query = "SELECT r FROM Renta r"),
    @NamedQuery(name = "Renta.findByIdRenta", query = "SELECT r FROM Renta r WHERE r.idRenta = :idRenta"),
    @NamedQuery(name = "Renta.findByFechaInicio", query = "SELECT r FROM Renta r WHERE r.fechaInicio = :fechaInicio"),
    @NamedQuery(name = "Renta.findByFechaFin", query = "SELECT r FROM Renta r WHERE r.fechaFin = :fechaFin"),
    @NamedQuery(name = "Renta.findByValor", query = "SELECT r FROM Renta r WHERE r.valor = :valor")})
public class Renta implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "ID_RENTA")
    private Short idRenta;
    @Column(name = "FECHA_INICIO")
    @Temporal(TemporalType.TIMESTAMP)
    private Date fechaInicio;
    @Column(name = "FECHA_FIN")
    @Temporal(TemporalType.TIMESTAMP)
    private Date fechaFin;
    @Column(name = "VALOR")
    private Long valor;
    @JoinColumn(name = "CED_ASE", referencedColumnName = "CEDULA")
    @ManyToOne
    private Asesor cedAse;
    @JoinColumn(name = "IDC", referencedColumnName = "IDC")
    @ManyToOne
    private Comprador idc;
    @JoinColumn(name = "IDPROP", referencedColumnName = "ID_PROPIEDAD")
    @ManyToOne
    private Propiedad idprop;

    public Renta() {
    }

    public Renta(Short idRenta) {
        this.idRenta = idRenta;
    }

    public Short getIdRenta() {
        return idRenta;
    }

    public void setIdRenta(Short idRenta) {
        this.idRenta = idRenta;
    }

    public Date getFechaInicio() {
        return fechaInicio;
    }

    public void setFechaInicio(Date fechaInicio) {
        this.fechaInicio = fechaInicio;
    }

    public Date getFechaFin() {
        return fechaFin;
    }

    public void setFechaFin(Date fechaFin) {
        this.fechaFin = fechaFin;
    }

    public Long getValor() {
        return valor;
    }

    public void setValor(Long valor) {
        this.valor = valor;
    }

    public Asesor getCedAse() {
        return cedAse;
    }

    public void setCedAse(Asesor cedAse) {
        this.cedAse = cedAse;
    }

    public Comprador getIdc() {
        return idc;
    }

    public void setIdc(Comprador idc) {
        this.idc = idc;
    }

    public Propiedad getIdprop() {
        return idprop;
    }

    public void setIdprop(Propiedad idprop) {
        this.idprop = idprop;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idRenta != null ? idRenta.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Renta)) {
            return false;
        }
        Renta other = (Renta) object;
        if ((this.idRenta == null && other.idRenta != null) || (this.idRenta != null && !this.idRenta.equals(other.idRenta))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "bdproyfin.Renta[ idRenta=" + idRenta + " ]";
    }
    
}
