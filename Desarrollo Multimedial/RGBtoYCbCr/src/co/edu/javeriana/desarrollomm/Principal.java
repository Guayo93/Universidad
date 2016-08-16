package co.edu.javeriana.desarrollomm;


 
public class Principal 
{
  public static void main(String[] foo) 
  {
	  LectorPixeles miLector = new LectorPixeles("data/avatar.bmp");
	  miLector.iniciarProceso();
  }
}