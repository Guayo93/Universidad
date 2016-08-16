package co.edu.javeriana.desarrollomm;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class LectorPixeles 
{
	private BufferedImage mImagen;
	private RGBPixel matrizRGB[][];
	private YCbCrPixel matrizYCbCr[][];
	private double matrizDCT[][];
	private double[][] matrizCuantizacion = 
		{
				{16, 11, 10, 16, 24, 40, 51, 61},
				{12, 12, 14, 19, 26, 58, 60, 55},
				{14, 13, 16, 24, 40, 57, 69, 56},
				{14, 17, 22, 29, 51, 87, 80, 62},
				{18, 22, 37, 56, 68, 109, 103, 77},
				{24, 35, 55, 64, 81, 104, 113, 92},
				{49, 64, 78, 87, 103, 121, 120, 101},
				{72, 92, 95, 98, 112, 100, 103, 99}
		};
	private long matrizCuantizada[][];
	private double matrizHuffman[][];
	private double matrizDescuantizada[][];
	private double matrizIDCT[][];
	private RGBPixel matrizFinal[][];

	public LectorPixeles(String file)
	{
		try 
		{
			mImagen = ImageIO.read(new File(file));
			matrizRGB = new RGBPixel[8][8];
			matrizYCbCr = new YCbCrPixel[8][8];
			matrizDCT = new double[8][8];
			matrizCuantizada = new long[8][8];
			matrizHuffman = new double[8][8];
			matrizDescuantizada = new double[8][8];
			matrizIDCT = new double[8][8];
			matrizFinal = new RGBPixel[8][8];
		} 
		catch (IOException e) 
		{
			System.err.println(e.getMessage());
		}
	}
	
	public void imprimirRGB(RGBPixel matriz[][])
	{
		for(int i = 0; i < 8; i++)
		{
			String linea = "";
			
			for(int j = 0; j < 8; j++)
			{
				linea += "(" + matriz[i][j].getRed() + "," + matriz[i][j].getGreen() + "," + matriz[i][j].getBlue() + ")";
			}
			
			System.out.println(linea);
		}
	}
	
	public void imprimirYCbCr()
	{
		for(int i = 0; i < 8; i++)
		{
			String linea = "";
			
			for(int j = 0; j < 8; j++)
			{
				linea += "(" + matrizYCbCr[i][j].getLuma() + "," + matrizYCbCr[i][j].getBlueContrast() + "," + matrizYCbCr[i][j].getRedContrast() + ")";
			}
			
			System.out.println(linea);
		}
	}
	
	public void imprimirMatriz(double[][] matriz)
	{
		for(int i = 0; i < 8; i++)
		{
			String linea = "";
			
			for(int j = 0; j < 8; j++)
			{
				linea += matriz[i][j] + " ";
			}
			
			System.out.println(linea);
		}		
	}
	
	public void imprimirMatriz(long[][] matriz)
	{
		for(int i = 0; i < 8; i++)
		{
			String linea = "";
			
			for(int j = 0; j < 8; j++)
			{
				linea += matriz[i][j] + " ";
			}
			
			System.out.println(linea);
		}		
	}
	
	public void iniciarProceso()
	{
		RGBtoYCbCr();
		System.out.println("RGB:");
		imprimirRGB(matrizRGB);
		System.out.println("YCbCr:");
		imprimirYCbCr();
		funcionDCT();
		System.out.println("DCT:");
		imprimirMatriz(matrizDCT);
		cuantizacion();
		System.out.println("Cuantizacion");
		imprimirMatriz(matrizCuantizada);
		huffman();
		System.out.println("Huffman:");
		imprimirMatriz(matrizHuffman);
		descuantizacion();
		System.out.println("Descuantizacion:");
		imprimirMatriz(matrizDescuantizada);
		funcionIDCT();
		System.out.println("IDCT:");
		imprimirMatriz(matrizIDCT);
		YCbCrtoRGB();
		System.out.println("RGB FINAL:");
		imprimirRGB(matrizFinal);
	}
	
	private RGBPixel obtenerRGBPixel(int pixel)
	{
		int rojo = (pixel >> 16) & 0xff;
		int verde = (pixel >> 8) & 0xff;
		int azul = (pixel) & 0xff;
		
		RGBPixel rgb = new RGBPixel(rojo, verde, azul);
		
		return rgb;
	}
	
	public void RGBtoYCbCr()
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				int pixel = mImagen.getRGB(j, i);
				
				matrizRGB[i][j] = obtenerRGBPixel(pixel);
				
				double l = 0 + (0.299 * matrizRGB[i][j].getRed()) + (0.587 * matrizRGB[i][j].getGreen()) + (0.114 * matrizRGB[i][j].getBlue());
				double cb = 128 - (0.168736 * matrizRGB[i][j].getRed()) - (0.331264 * matrizRGB[i][j].getGreen()) + (0.5 * matrizRGB[i][j].getBlue());
				double cr = 128 + (0.5 * matrizRGB[i][j].getRed()) - (0.418688 * matrizRGB[i][j].getGreen()) - (0.081312 * matrizRGB[i][j].getBlue());
				
				l -= 128;
				cb -= 128;
				cr -= 128;
				
				matrizYCbCr[i][j] = new YCbCrPixel(Math.round(l), Math.round(cb), Math.round(cr));
			}
		}
	}
	
	public double obtenerAlpha(int pos)
	{
		if(pos == 0)
		{
			return (1 / Math.sqrt(2));
		}
		else
		{
			return 1;
		}
	}
	
	public void funcionDCT()
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				double sumatoria = 0;
				
				double alphaU = obtenerAlpha(i);
				double alphaV = obtenerAlpha(j);
				
				for(int k = 0; k < 8; k++)
				{
					for(int l = 0; l < 8; l++)
					{
						int ycbcr = 0;
						ycbcr = ycbcr | ((int) matrizYCbCr[k][l].getLuma() << 16);
						ycbcr = ycbcr | ((int) matrizYCbCr[k][l].getBlueContrast() << 8);
						ycbcr = ycbcr | (int) matrizYCbCr[k][l].getRedContrast();

						sumatoria += ycbcr * Math.cos((Math.PI * ((2 * k) + 1) * i) / 16) * Math.cos((Math.PI * ((2 * l) + 1) * j) / 16);
					}
				}
				
				matrizDCT[i][j] = (alphaU * alphaV * sumatoria) / 4;
			}
		}
	}
	
	public void cuantizacion()
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				matrizCuantizada[i][j] = Math.round(matrizDCT[i][j] / matrizCuantizacion[i][j]);
			}
		}
	}
	
	public void huffman()
	{
		int k = 0;
		int l = 0;
		boolean der = true;
		boolean up = true;
		
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				matrizHuffman[i][j] = matrizCuantizada[k][l];
				
				if(up == true)
				{
					if(k == 7 && l == 0)
					{
						up = false;
						der = true;
						l++;
					}
					else
					{
						if(der == true)
						{
							if(k == 0)
							{
								l++;
								der = false;
							}
							
							if(k > 0)
							{
								k--;
								l++;
							}
						}
						else
						{
							if(l == 0)
							{
								k++;
								der = true;
							}
							
							if(l > 0)
							{
								k++;
								l--;
							}
						}
					}
				}
				else
				{
					if(der == true)
					{
						if(l == 7)
						{
							k++;
							der = false;
						}
						
						if(l < 7)
						{
							l++;
							k--;
						}
					}
					else
					{
						if(k == 7)
						{
							l++;
							der = true;
						}
						
						if(k < 7)
						{
							k++;
							l--;
						}
					}
				}
				
				if(k >= 8 && up == false)
				{
					k = 0;
				}
				
				if(l >= 8 && up == false)
				{
					l = 0;
				}
			}
		}
	}
	
	public void descuantizacion()
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				matrizDescuantizada[i][j] = matrizHuffman[i][j] * matrizCuantizacion[i][j];
			}
		}
	}
	
	public void funcionIDCT()
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				double sumatoria = 0;
				
				for(int k = 0; k < 8; k++)
				{
					for(int l = 0; l < 8; l++)
					{
						double alphaU = obtenerAlpha(k);
						double alphaV = obtenerAlpha(l);
						
						sumatoria += alphaU * alphaV * matrizDescuantizada[k][l] * Math.cos((Math.PI * ((2 * i) + 1) * k) / 16) * Math.cos((Math.PI * ((2 * j) + 1) * l) / 16);
					}
				}
				
				matrizIDCT[i][j] = Math.round((sumatoria / 4) + 128);
			}
		}
	}
	
	public void YCbCrtoRGB()
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				int pixel = (int) matrizIDCT[i][j];
				
				int luma = (pixel >> 16) & 0xff;
				int cb = (pixel >> 8) & 0xff;
				int cr = (pixel) & 0xff;
				
				int red = (int) Math.round(luma + (1.402 * (cr - 128)));
				int green = (int) Math.round((luma - 0.344136) * ((cb - 128) - 0.714136) * (cr - 128));
				int blue = (int) Math.round((luma + 1.772) * (cb - 128));
				
				matrizFinal[i][j] = new RGBPixel(red, green, blue);
			}
		}
	}
}
