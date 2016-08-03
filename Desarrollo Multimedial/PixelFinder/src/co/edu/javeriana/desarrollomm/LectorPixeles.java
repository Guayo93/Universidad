package co.edu.javeriana.desarrollomm;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class LectorPixeles {
	public static final int RGB = 10;
	public static final int ARGB = 11;

	private int mModo;
	private int mModo2;
	private BufferedImage mImagen;
	private BufferedImage mImagen2;

	public LectorPixeles(String file, String file2, int modo, int modo2)
	{
		try {
			mImagen = ImageIO.read(new File(file));
			mImagen2 = ImageIO.read(new File(file2));
			mModo = modo;
			mModo2 = modo2;
		} catch (IOException e) {
			System.err.println(e.getMessage());
		}
	}
	
	public void iniciarProceso()
	{
		int ancho = mImagen.getWidth();
		int ancho2 = mImagen2.getWidth();
		int alto = mImagen.getHeight();
		int alto2 = mImagen2.getHeight();
		long sumatoria = 0;
		
		double ecm = 0;
		double psnr = 0;
		
		//System.out.println("ancho, alto: " + ancho + ", " + alto);
		
		for (int i = 0; i < alto; i++) 
		{
			for (int j = 0; j < ancho; j++) 
			{
				int resta = 0;
				if(alto == alto2 && ancho == ancho2)
				{
					//System.out.println("x,y: " + j + ", " + i);
					int pixel = mImagen.getRGB(j, i);
					int pixel2 = mImagen2.getRGB(j, i);
					imprimirARGB(pixel);
					resta = pixel - pixel2;
					
					sumatoria += Math.pow(resta, 2);
				}
			}
		}
		
		ecm = sumatoria / (ancho * alto);
		System.out.println("ECM: " + ecm);
		
		if(ecm == 0)
		{
			System.out.println("PSNR: No hay, pues el error es 0.");
		}
		else
		{
			long canales = (long) Math.pow(2, 24);
			psnr = Math.log10(Math.pow(canales, 2) / ecm);
			psnr *= 10;
			System.out.println("PSNR: " + psnr);
		}
		
		mImagen.flush();
	}

	private void imprimirARGB(int pixel)
	{
		int alpha = 0;
		int rojo = (pixel >> 16) & 0xff;
		int verde = (pixel >> 8) & 0xff;
		int azul = (pixel) & 0xff;
		StringBuilder sbuilder = new StringBuilder();

		if (mModo == ARGB) {
			alpha = (pixel >> 24) & 0xff;

			sbuilder.append("alpha: ");
			sbuilder.append(alpha);
			sbuilder.append(", ");
		}

		sbuilder.append("rojo: ");
		sbuilder.append(rojo);
		sbuilder.append(", ");

		sbuilder.append("verde: ");
		sbuilder.append(verde);
		sbuilder.append(", ");

		sbuilder.append("azul: ");
		sbuilder.append(azul);
		sbuilder.append(".");

		//System.out.println(sbuilder.toString());

	}

}
