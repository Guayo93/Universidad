import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;

public class Main 
{
	public static void main(String[] args) 
	{
		// <Dia, ValorMaximoDia>
		Map<Integer, Integer> dias = obtenerDatos();
		// <Hora, Vela>
		Map<Integer, Vela> velas = usarLagrangePoly(dias);
		completarVelas(velas);
		
		imprimirArchivo(velas);
	}
	
	public static Map<Integer, Integer> obtenerDatos()
	{
		Map<Integer, Integer> dias = new HashMap<Integer, Integer>();
		Scanner scanner;
		try 
		{
			scanner = new Scanner(new File("data/datos.csv"));
	        while(scanner.hasNext())
	        {
	            String[] afterSplit = scanner.nextLine().split(",");
	            dias.put(Integer.parseInt(afterSplit[0]), Integer.parseInt(afterSplit[1]));
	        }
	        scanner.close();
		} 
		catch (FileNotFoundException e) 
		{
			e.printStackTrace();
		}
		
		return dias;
	}
	
	public static Map<Integer, Vela> usarLagrangePoly(Map<Integer, Integer> dias)
	{
		Map<Integer, Vela> velas = new HashMap<Integer, Vela>();
		double cont = 1, mult = 1, sum = 0;
		
		Set<Integer> keys = dias.keySet();
		while(cont <= 168)
		{
			double valor = 1 + (cont / 24);
			sum = 0;
			
			for(int i : keys)
			{
				mult = 1;
				for(int j : keys)
				{
					if(i != j)
					{
						mult *= ((valor - j) / (i - j));
					}
				}
				
				sum += (mult * dias.get(i));
			}
			
			velas.put((int) cont, new Vela(sum));
			cont++;
		}
		return velas;
	}
	
	public static void completarVelas(Map<Integer, Vela> velas)
	{
		SortedSet<Integer> sortedKeys = new TreeSet<Integer>(velas.keySet());
		
		for(int key : sortedKeys)
		{
			if(key < 168)
			{
				Vela vela = velas.get(key);
				vela.setValorCierre(velas.get(key + 1).getValorApertura());
				
				if(vela.getValorApertura() < vela.getValorCierre())
				{
					vela.setValorMax(vela.getValorCierre());
					vela.setValorMin(vela.getValorApertura());
				}
				else
				{
					vela.setValorMax(vela.getValorApertura());
					vela.setValorMin(vela.getValorCierre());
				}
			}
		}
	}
	
	public static void imprimirArchivo(Map<Integer, Vela> velas)
	{
		try 
		{
			SortedSet<Integer> sortedKeys = new TreeSet<Integer>(velas.keySet());
			PrintWriter writer = new PrintWriter("data/velas.csv", "UTF-8");
			
			for(int key : sortedKeys)
			{
				Vela vela = velas.get(key);
				writer.println(key + "," + vela.getValorMax()  + "," + vela.getValorMin() + 
						"," + vela.getValorApertura() + "," + vela.getValorCierre());
			}
			
			writer.close();
		} 
		catch (FileNotFoundException e) 
		{
			e.printStackTrace();
		} 
		catch (UnsupportedEncodingException e) 
		{
			e.printStackTrace();
		}
	}
}
