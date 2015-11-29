package Entity;

import Entity.Comprador;
import Entity.ListaDeVisitaPK;
import Entity.Propiedad;
import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2015-11-28T23:19:00")
@StaticMetamodel(ListaDeVisita.class)
public class ListaDeVisita_ { 

    public static volatile SingularAttribute<ListaDeVisita, Date> fecha;
    public static volatile SingularAttribute<ListaDeVisita, Propiedad> propiedad;
    public static volatile SingularAttribute<ListaDeVisita, Comprador> comprador;
    public static volatile SingularAttribute<ListaDeVisita, ListaDeVisitaPK> listaDeVisitaPK;

}