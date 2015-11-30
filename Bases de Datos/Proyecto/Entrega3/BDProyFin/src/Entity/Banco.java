/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entity;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author aleja_000
 */
@Entity
@Table(name = "BANCO")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Banco.findAll", query = "SELECT b FROM Banco b"),
    @NamedQuery(name = "Banco.findByNumTarjeta", query = "SELECT b FROM Banco b WHERE b.numTarjeta = :numTarjeta"),
    @NamedQuery(name = "Banco.findBySaldo", query = "SELECT b FROM Banco b WHERE b.saldo = :saldo")})
public class Banco implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "NUM_TARJETA")
    private Long numTarjeta;
    @Column(name = "SALDO")
    private Long saldo;

    public Banco() {
    }

    public Banco(Long numTarjeta) {
        this.numTarjeta = numTarjeta;
    }

    public Long getNumTarjeta() {
        return numTarjeta;
    }

    public void setNumTarjeta(Long numTarjeta) {
        this.numTarjeta = numTarjeta;
    }

    public Long getSaldo() {
        return saldo;
    }

    public void setSaldo(Long saldo) {
        this.saldo = saldo;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (numTarjeta != null ? numTarjeta.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Banco)) {
            return false;
        }
        Banco other = (Banco) object;
        if ((this.numTarjeta == null && other.numTarjeta != null) || (this.numTarjeta != null && !this.numTarjeta.equals(other.numTarjeta))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Entity.Banco[ numTarjeta=" + numTarjeta + " ]";
    }
    
}
