
public class Vela 
{
	private double valorMax;
	private double valorMin;
	private double valorApertura;
	private double valorCierre;
	
	public Vela(double valorAperturaP)
	{
		this.valorApertura = valorAperturaP;
		this.valorCierre = 0;
		this.valorMax = 0;
		this.valorMin = 0;
	}

	public double getValorMax() {
		return valorMax;
	}

	public void setValorMax(double valorMax) {
		this.valorMax = valorMax;
	}

	public double getValorMin() {
		return valorMin;
	}

	public void setValorMin(double valorMin) {
		this.valorMin = valorMin;
	}

	public double getValorApertura() {
		return valorApertura;
	}

	public void setValorApertura(double valorApertura) {
		this.valorApertura = valorApertura;
	}

	public double getValorCierre() {
		return valorCierre;
	}

	public void setValorCierre(double valorCierre) {
		this.valorCierre = valorCierre;
	}
}
