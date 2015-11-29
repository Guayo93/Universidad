package Entity;

import Entity.ListaDeVisita;
import Entity.Propiedad;
import Entity.Renta;
import Entity.Usuario;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2015-11-28T23:19:00")
@StaticMetamodel(Comprador.class)
public class Comprador_ { 

    public static volatile CollectionAttribute<Comprador, Propiedad> propiedadCollection;
    public static volatile SingularAttribute<Comprador, Usuario> cedula;
    public static volatile CollectionAttribute<Comprador, Renta> rentaCollection;
    public static volatile SingularAttribute<Comprador, Short> idc;
    public static volatile CollectionAttribute<Comprador, ListaDeVisita> listaDeVisitaCollection;
    public static volatile SingularAttribute<Comprador, String> usuario;
    public static volatile SingularAttribute<Comprador, String> contrasena;

}