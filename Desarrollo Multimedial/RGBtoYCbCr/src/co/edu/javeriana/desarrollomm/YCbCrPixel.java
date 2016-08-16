package co.edu.javeriana.desarrollomm;

public class YCbCrPixel 
{
	private double luma;
	private double blueContrast;
	private double redContrast;
	
	public YCbCrPixel(double luma, double blueContrast, double redContrast)
	{
		this.luma = luma;
		this.blueContrast = blueContrast;
		this.redContrast = redContrast;
	}

	public double getLuma() {
		return luma;
	}

	public void setLuma(double luma) {
		this.luma = luma;
	}

	public double getBlueContrast() {
		return blueContrast;
	}

	public void setBlueContrast(double blueContrast) {
		this.blueContrast = blueContrast;
	}

	public double getRedContrast() {
		return redContrast;
	}

	public void setRedContrast(double redContrast) {
		this.redContrast = redContrast;
	}
}
