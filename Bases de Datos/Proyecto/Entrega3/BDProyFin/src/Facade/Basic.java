/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Facade;

/**
 *
 * @author aleja_000
 */

import Controllers.*;
import Controllers.exceptions.NonexistentEntityException;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import Entity.*;
import java.sql.Timestamp;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;
import oracle.sql.TIMESTAMP;

public class Basic {
    
    //login info
     static long userID = -1; //(cedula)
     static boolean comp = false,prop = false;
     
    /*
     ENTITY MANAGER/CONTROLLER CALLS.. ..
     static      EntityManagerFactory emf = Persistence.createEntityManagerFactory("BDProyFinPU");
     
     //controllers
     //-------------------------------------------
    static      AsesorJpaController         Asesor = new AsesorJpaController		(emf);
    static      CiudadJpaController         Ciudad = new CiudadJpaController 		(emf);
    static      CompradorJpaController      Comprador = new CompradorJpaController	(emf);
    static      PropietarioJpaController    Propietario = new PropietarioJpaController  (emf);
    static      ImagenJpaController         Imagen = new ImagenJpaController		(emf);
    static      ListaDeVisitaJpaController  ListaV = new ListaDeVisitaJpaController 	(emf);
    static      PropiedadJpaController      Propiedad = new PropiedadJpaController  	(emf);
    static      RentaJpaController          Renta = new RentaJpaController 		(emf);
    static      UsuarioJpaController        User = new UsuarioJpaController 		(emf);
     //-------------------------------------------
     */
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
 
        
        // TODO code application logic here

    }
    
    
    public static void Login(long cedula){
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("BDProyFinPU");
        PropietarioJpaController    Propietario = new PropietarioJpaController  (emf);
        CompradorJpaController      Comprador = new CompradorJpaController	(emf);
        UsuarioJpaController        User = new UsuarioJpaController 		(emf);
        if( User.findUsuario(cedula) != null ){
            userID = cedula;
            if(Comprador.cedCompradorCount(cedula) >0 ) {comp = true;}
            if(Propietario.cedPropietarioCount(cedula)> 0){prop = true;}
        }
        emf.close();
    }
    
    public static void ViewVisitList(){}//comprador
    
    public static void AddVisitList(Comprador comprador,Propiedad propiedad){
    if(comp){
        
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("BDProyFinPU");
        ListaDeVisitaJpaController  ListaV = new ListaDeVisitaJpaController 	(emf);
        try {
            ListaDeVisita nldv = new ListaDeVisita();
            nldv.setComprador(comprador);
            nldv.setFecha(new Timestamp(new Date().getTime()));
            nldv.setPropiedad(propiedad);
            ListaV.create(nldv);
        } 
        catch (Exception ex) {
            Logger.getLogger(Basic.class.getName()).log(Level.SEVERE, null, ex);
        }finally{
        emf.close();
        }
    }//fi
    else{
    //notificar q necesita logear como comprador para hacer ésto
    }
    }//comprador
    
    public static void removeVisitList(Propiedad propiedad, Comprador comprador){

        if(comp){
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("BDProyFinPU");
        ListaDeVisitaJpaController  ListaV = new ListaDeVisitaJpaController 	(emf);
            try {
                ListaDeVisitaPK lvpk = new ListaDeVisitaPK();
                lvpk.setIdPropiedad(propiedad.getIdPropiedad());
                lvpk.setIdc(comprador.getIdc());
                ListaV.destroy(lvpk);
            } catch (NonexistentEntityException ex) {
                Logger.getLogger(Basic.class.getName()).log(Level.SEVERE, null, ex);
            }finally{
                emf.close();
            }
        }
        
    }; //comprador
    
    public static void RentP(){
        //se envia al banco para combrobar (metodo comprobación financiera)
        if (autorizacionFinanciera(/*numero, fecha exp,...*/)){
            //si ya existe alguna aplicacion sobre la prop deja ésta en lsita de espera
        //mostrar pantalla de confirmación (max una(?) ésto está raro. ..)
        //generar la nueva renta
       
        }
        //
    }; //comprador
    public static void ViewProps(){
        
    
    }; //anyone
    public static void BrowsePropsLoc(){}; //anyone
    public static void SearchProps(){};   //anyone
    public static void DeleteProp(){
    //busca la propiedad seleccionada de la lista (recib el id) a través del propietario
    //si la encuentra cambia el estado a delete sino develv error
    };    // propietario
    public static void UpdateProp(){
    //busca prop a traves de propietario mediante el id
    //si la encuentra cmabia la renta sino develve error
    };    // propietario
    public static void AddProp(){};       // propietario
            

}