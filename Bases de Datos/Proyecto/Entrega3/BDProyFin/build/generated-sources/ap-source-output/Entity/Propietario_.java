package Entity;

import Entity.Propiedad;
import Entity.Usuario;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2015-11-28T23:19:00")
@StaticMetamodel(Propietario.class)
public class Propietario_ { 

    public static volatile CollectionAttribute<Propietario, Propiedad> propiedadCollection;
    public static volatile SingularAttribute<Propietario, Short> idp;
    public static volatile SingularAttribute<Propietario, Usuario> cedula;
    public static volatile SingularAttribute<Propietario, String> usuario;
    public static volatile SingularAttribute<Propietario, String> contrasena;

}