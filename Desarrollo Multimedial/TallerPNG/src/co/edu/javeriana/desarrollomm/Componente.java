package co.edu.javeriana.desarrollomm;

public class Componente 
{
	private int posMatch;
	private int corrimiento;
	private String comboBreaker;
	
	public Componente(int posMatch, int corrimiento, String comboBreaker) 
	{
		super();
		this.posMatch = posMatch;
		this.corrimiento = corrimiento;
		this.comboBreaker = comboBreaker;
	}

	public int getPosMatch() 
	{
		return posMatch;
	}

	public void setPosMatch(int posMatch) 
	{
		this.posMatch = posMatch;
	}

	public int getCorrimiento() 
	{
		return corrimiento;
	}

	public void setCorrimiento(int corrimiento) 
	{
		this.corrimiento = corrimiento;
	}

	public String getComboBreaker() 
	{
		return comboBreaker;
	}

	public void setComboBreaker(String comboBreaker) 
	{
		this.comboBreaker = comboBreaker;
	}

	@Override
	public String toString() 
	{
		return "(" + posMatch + "," + corrimiento + "," + comboBreaker + ")";
	}
}
