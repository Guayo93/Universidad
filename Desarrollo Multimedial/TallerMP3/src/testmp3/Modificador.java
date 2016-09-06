/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testmp3;

import java.io.*;

/**
 *
 * @author Sala_b
 */
public class Modificador 
{
    private final int mVarA;
    private final int mVarB;
    private final int mVarC;
    private final String mArchivo;
    private final String mArchivo2;

    public Modificador(String nombreArchivo, String nombreArchivo2) 
    {
    	//Cada cuantos bytes se inyecta el modificador
        mVarA = 100000;
        //El modificador del byte
        mVarB = 5;
        //Controla  que el byte actual no se pase de 255 despues de la suma
        mVarC = 255;
        mArchivo = nombreArchivo;
        mArchivo2 = nombreArchivo2;
    }

    public void modificar() 
    {
        try 
        {
            File cancion = new File(mArchivo);
            FileInputStream archivo = new FileInputStream(cancion);
            File modificada = new File("cancion.mp3");
            FileOutputStream salida = new FileOutputStream(modificada);
            //Archivo secundario
            File cancion2 = new File(mArchivo2);
            FileInputStream archivo2 = new FileInputStream(cancion2);
            boolean eof = false;
            //Variable de cambio
            boolean cambio = false;
            int count = 0;
            while (!eof) 
            {
                int entrada = archivo.read();
                int entrada2 = archivo2.read();
                if (entrada == -1 || entrada2 == -1) 
                {
                    eof = true;
                } 
                else 
                {
                    count++;
                    if (count % mVarA == 0) 
                    {
                    	cambio = !cambio;
                        /**int entradaNueva = entrada + entrada2;
                        if (entradaNueva > mVarC) 
                        {
                            entradaNueva = entradaNueva - mVarC;
                        }
                        salida.write(entradaNueva);*/
                    } 
                    /**else 
                    {
                    	salida.write(entrada);
                    }*/
                    
                    if(cambio == true)
                    {
                    	salida.write(entrada2);
                    }
                    else
                    {
                    	salida.write(entrada);
                    }
                }
            }
            System.out.println("Termino! :3");
            archivo.close();
            archivo2.close();
            salida.close();
        } 
        catch (Exception e) 
        {
            System.out.println("Error â€” " + e.toString());
        }
    }
}