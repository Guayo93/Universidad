package Entity;

import Entity.Ciudad;
import Entity.Comprador;
import Entity.Imagen;
import Entity.ListaDeVisita;
import Entity.Propietario;
import Entity.Renta;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2015-11-28T23:19:00")
@StaticMetamodel(Propiedad.class)
public class Propiedad_ { 

    public static volatile SingularAttribute<Propiedad, Short> idPropiedad;
    public static volatile SingularAttribute<Propiedad, String> tipo;
    public static volatile SingularAttribute<Propiedad, Short> estado;
    public static volatile SingularAttribute<Propiedad, Propietario> idp;
    public static volatile CollectionAttribute<Propiedad, Renta> rentaCollection;
    public static volatile SingularAttribute<Propiedad, String> direccion;
    public static volatile SingularAttribute<Propiedad, Comprador> idc;
    public static volatile CollectionAttribute<Propiedad, ListaDeVisita> listaDeVisitaCollection;
    public static volatile SingularAttribute<Propiedad, Imagen> imagen;
    public static volatile SingularAttribute<Propiedad, Ciudad> codCiudad;
    public static volatile SingularAttribute<Propiedad, Short> numHabitaciones;

}