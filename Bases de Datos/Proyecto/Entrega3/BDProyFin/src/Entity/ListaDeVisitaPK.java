/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entity;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Embeddable;

/**
 *
 * @author aleja_000
 */
@Embeddable
public class ListaDeVisitaPK implements Serializable {

    @Basic(optional = false)
    @Column(name = "ID_PROPIEDAD")
    private short idPropiedad;
    @Basic(optional = false)
    @Column(name = "IDC")
    private short idc;

    public ListaDeVisitaPK() {
    }

    public ListaDeVisitaPK(short idPropiedad, short idc) {
        this.idPropiedad = idPropiedad;
        this.idc = idc;
    }

    public short getIdPropiedad() {
        return idPropiedad;
    }

    public void setIdPropiedad(short idPropiedad) {
        this.idPropiedad = idPropiedad;
    }

    public short getIdc() {
        return idc;
    }

    public void setIdc(short idc) {
        this.idc = idc;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (int) idPropiedad;
        hash += (int) idc;
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof ListaDeVisitaPK)) {
            return false;
        }
        ListaDeVisitaPK other = (ListaDeVisitaPK) object;
        if (this.idPropiedad != other.idPropiedad) {
            return false;
        }
        if (this.idc != other.idc) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Entity.ListaDeVisitaPK[ idPropiedad=" + idPropiedad + ", idc=" + idc + " ]";
    }
    
}
