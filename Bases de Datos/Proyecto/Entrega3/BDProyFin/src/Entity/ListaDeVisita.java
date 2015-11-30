/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entity;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
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
@Table(name = "LISTA_DE_VISITA")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "ListaDeVisita.findAll", query = "SELECT l FROM ListaDeVisita l"),
    @NamedQuery(name = "ListaDeVisita.findByIdPropiedad", query = "SELECT l FROM ListaDeVisita l WHERE l.listaDeVisitaPK.idPropiedad = :idPropiedad"),
    @NamedQuery(name = "ListaDeVisita.findByIdc", query = "SELECT l FROM ListaDeVisita l WHERE l.listaDeVisitaPK.idc = :idc"),
    @NamedQuery(name = "ListaDeVisita.findByFecha", query = "SELECT l FROM ListaDeVisita l WHERE l.fecha = :fecha")})
public class ListaDeVisita implements Serializable {

    private static final long serialVersionUID = 1L;
    @EmbeddedId
    protected ListaDeVisitaPK listaDeVisitaPK;
    @Column(name = "FECHA")
    @Temporal(TemporalType.TIMESTAMP)
    private Date fecha;
    @JoinColumn(name = "IDC", referencedColumnName = "IDC", insertable = false, updatable = false)
    @ManyToOne(optional = false)
    private Comprador comprador;
    @JoinColumn(name = "ID_PROPIEDAD", referencedColumnName = "ID_PROPIEDAD", insertable = false, updatable = false)
    @ManyToOne(optional = false)
    private Propiedad propiedad;

    public ListaDeVisita() {
    }

    public ListaDeVisita(ListaDeVisitaPK listaDeVisitaPK) {
        this.listaDeVisitaPK = listaDeVisitaPK;
    }

    public ListaDeVisita(short idPropiedad, short idc) {
        this.listaDeVisitaPK = new ListaDeVisitaPK(idPropiedad, idc);
    }

    public ListaDeVisitaPK getListaDeVisitaPK() {
        return listaDeVisitaPK;
    }

    public void setListaDeVisitaPK(ListaDeVisitaPK listaDeVisitaPK) {
        this.listaDeVisitaPK = listaDeVisitaPK;
    }

    public Date getFecha() {
        return fecha;
    }

    public void setFecha(Date fecha) {
        this.fecha = fecha;
    }

    public Comprador getComprador() {
        return comprador;
    }

    public void setComprador(Comprador comprador) {
        this.comprador = comprador;
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
        hash += (listaDeVisitaPK != null ? listaDeVisitaPK.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof ListaDeVisita)) {
            return false;
        }
        ListaDeVisita other = (ListaDeVisita) object;
        if ((this.listaDeVisitaPK == null && other.listaDeVisitaPK != null) || (this.listaDeVisitaPK != null && !this.listaDeVisitaPK.equals(other.listaDeVisitaPK))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Entity.ListaDeVisita[ listaDeVisitaPK=" + listaDeVisitaPK + " ]";
    }
    
}
