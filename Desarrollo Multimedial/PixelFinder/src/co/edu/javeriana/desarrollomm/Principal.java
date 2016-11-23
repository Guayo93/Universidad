package co.edu.javeriana.desarrollomm;


 
public class Principal {
 
  public static void main(String[] foo) {
	  LectorPixeles miLector = new LectorPixeles("gatos.jpg", "ubisoft.png", LectorPixeles.ARGB,LectorPixeles.ARGB);
	  miLector.iniciarProceso(100, 75);
  }
}