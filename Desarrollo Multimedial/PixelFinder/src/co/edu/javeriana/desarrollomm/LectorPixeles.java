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
	
	public void iniciarProceso(int x, int y)
	{
		int ancho = mImagen.getWidth();
		int ancho2 = mImagen2.getWidth();
		int alto = mImagen.getHeight();
		int alto2 = mImagen2.getHeight();

		for(int i = 0; i < alto; i++)
		{
			for(int j = 0; j < ancho; j++)
			{
				if(i >= y && i < (y + alto2) && j >= x && j < (x + ancho2))
				{
					int pixel = mImagen2.getRGB((j - x), (i - y));
					int alpha = (pixel >> 24) & 0xff;
					
					if(alpha != 0)
					{
						mImagen.setRGB(j, i, pixel);
					}
				}
			}
		}
		
		try {
			ImageIO.write(mImagen, "png", new File("./gatos2.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		mImagen.flush();
		mImagen2.flush();
	}
}
