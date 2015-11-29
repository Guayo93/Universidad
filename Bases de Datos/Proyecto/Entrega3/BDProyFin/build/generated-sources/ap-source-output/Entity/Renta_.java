package Entity;

import Entity.Asesor;
import Entity.Comprador;
import Entity.Propiedad;
import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2015-11-28T23:18:59")
@StaticMetamodel(Renta.class)
public class Renta_ { 

    public static volatile SingularAttribute<Renta, Date> fechaInicio;
    public static volatile SingularAttribute<Renta, Long> valor;
    public static volatile SingularAttribute<Renta, Comprador> idc;
    public static volatile SingularAttribute<Renta, Short> idRenta;
    public static volatile SingularAttribute<Renta, Asesor> cedAse;
    public static volatile SingularAttribute<Renta, Propiedad> idprop;
    public static volatile SingularAttribute<Renta, Date> fechaFin;

}