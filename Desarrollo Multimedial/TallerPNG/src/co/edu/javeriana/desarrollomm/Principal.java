package co.edu.javeriana.desarrollomm;

import java.util.ArrayList;
import java.util.List;

public class Principal 
{
	public List<Componente> compresion(String cadena)
	{
		List<Componente> cifrado = new ArrayList<Componente>();
		int ventana = 0;
		
		for(int i = 0; i < cadena.length(); i++)
		{
			if(i > 3)
			{
				ventana = i - 3;
			}
			
			String subS = cadena.substring(ventana, i);
			
			if(subS.length() > 0)
			{
				int posInterior = subS.lastIndexOf(cadena.charAt(i));
				
				if(posInterior != -1)
				{
					int cont  = 0;
					boolean flag = true;
					
					for(int j = posInterior; j < subS.length() && flag == true; j++)
					{
						if(subS.charAt(j) == cadena.charAt(i + cont))
						{
							cont++;
						}
						else
						{
							flag = false;
						}
					}
					
					Componente comp = new Componente(posInterior, posInterior + cont, "" + cadena.charAt(i + cont));
					cifrado.add(comp);
					i += cont;
				}
				else
				{
					Componente comp = new Componente(0, 0, "" + cadena.charAt(i));
					cifrado.add(comp);
				}
			}
			else
			{
				Componente comp = new Componente(0, 0, "" + cadena.charAt(i));
				cifrado.add(comp);
			}
		}
		
		return cifrado;
	}
	
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
	}
}
