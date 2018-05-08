package co.edu.javeriana.TallerPruebas.mundo;

public class Calculadora {	
	public Calculadora( ) {
		
	}
	
	public double suma( double a, double b ) {
		return a + b;
	}
	
	public double resta( double a, double b ) {
		return a - b;
	}
	
	public double multiplicacion( double a, double b ) {
		return a * b;
	}
	
	public double division(double a, double b ) {
		return a / b;
	}
	
	public boolean esPalindrome( String cadena ) {
		boolean flag = true;
		int i = 0, j = cadena.length() - 1;
		
		while( flag && i < (cadena.length() / 2) ) {
			if ( cadena.charAt(i) != cadena.charAt(j) ) {
				flag = false;
			}
			else {
				i++;
				j--;
			}
		}
		
		return flag;
	}

	public static void main(String[] args) {
		// TODO - J - Puesta en marcha :D
	}

}
