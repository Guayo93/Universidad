package Entity;

import Entity.Propiedad;
import java.io.Serializable;
import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2015-11-28T23:19:00")
@StaticMetamodel(Imagen.class)
public class Imagen_ { 

    public static volatile SingularAttribute<Imagen, String> descripcion;
    public static volatile SingularAttribute<Imagen, Date> fecha;
    public static volatile SingularAttribute<Imagen, Short> idPropiedad;
    public static volatile SingularAttribute<Imagen, Serializable> img;
    public static volatile SingularAttribute<Imagen, Propiedad> propiedad;

}