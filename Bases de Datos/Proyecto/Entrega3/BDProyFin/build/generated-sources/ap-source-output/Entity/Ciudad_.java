package Entity;

import Entity.Propiedad;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2015-11-28T23:19:00")
@StaticMetamodel(Ciudad.class)
public class Ciudad_ { 

    public static volatile CollectionAttribute<Ciudad, Propiedad> propiedadCollection;
    public static volatile SingularAttribute<Ciudad, Short> codCiudad;
    public static volatile SingularAttribute<Ciudad, String> nombre;

}