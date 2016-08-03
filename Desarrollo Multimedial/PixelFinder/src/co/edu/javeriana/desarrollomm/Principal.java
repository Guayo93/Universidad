package co.edu.javeriana.desarrollomm;


 
public class Principal {
 
  public static void main(String[] foo) {
	  LectorPixeles miLector = new LectorPixeles("art.gif", "art.jpg", LectorPixeles.ARGB,LectorPixeles.ARGB);
	  miLector.iniciarProceso();
  }
}