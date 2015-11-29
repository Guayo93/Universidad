package Entity;

import Entity.Renta;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2015-11-28T23:19:00")
@StaticMetamodel(Asesor.class)
public class Asesor_ { 

    public static volatile SingularAttribute<Asesor, Long> cedula;
    public static volatile CollectionAttribute<Asesor, Renta> rentaCollection;
    public static volatile SingularAttribute<Asesor, String> apellido;
    public static volatile SingularAttribute<Asesor, String> correo;
    public static volatile SingularAttribute<Asesor, String> nombre;

}