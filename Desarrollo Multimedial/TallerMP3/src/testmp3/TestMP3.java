/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testmp3;

/**
 *
 * @author Sala_b
 */
public class TestMP3 
{
	/**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Modificador mod = new Modificador("data/archivo.mp3", "data/archivo2.mp3");
        mod.modificar();
    }
    
}