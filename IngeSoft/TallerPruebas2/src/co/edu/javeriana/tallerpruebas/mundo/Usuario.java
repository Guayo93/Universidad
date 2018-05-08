package co.edu.javeriana.tallerpruebas.mundo;

import java.util.ArrayList;
import java.util.List;

public class Usuario {
	private String nombre;
	private String cedula;
	private String direccion;
	private List<Antecedente> antecedentes;
	
	public Usuario(String nombre, String cedula, String direccion) {
		this.nombre = nombre;
		this.cedula = cedula;
		this.direccion = direccion;
		this.antecedentes = new ArrayList<Antecedente>();
	}
	
	public boolean crearAntecedente( String date, String descripcion, int tipo ) {
		boolean flag = true;
		Antecedente ant = null;
		switch (tipo) {
			case 1: { 
				ant = new Antecedente(date, descripcion, Antecedente.Tipo.GRAVE);
				antecedentes.add(ant);
				break;
			}
			
			case 2: {
				ant = new Antecedente(date, descripcion, Antecedente.Tipo.MEDIANO);
				antecedentes.add(ant);
				break;
			}
			
			case 3: {
				ant = new Antecedente(date, descripcion, Antecedente.Tipo.LIVIANO);
				antecedentes.add(ant);
				break;
			}
			
			default: {
				flag = false;
				break;
			}
		}
				
		return flag;
	}
	
	public boolean eliminarAntecedente( int indice ) {
		boolean flag = false;
		
		if( indice <= this.antecedentes.size() && indice > 0 ) {
			this.antecedentes.remove(indice - 1 );
			flag = true;
		}
		
		return flag;
	}
	
	public String getNombre() {
		return nombre;
	}
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}
	public String getCedula() {
		return cedula;
	}
	public void setCedula(String cedula) {
		this.cedula = cedula;
	}
	public String getDireccion() {
		return direccion;
	}
	public void setDireccion(String direccion) {
		this.direccion = direccion;
	}
	public List<Antecedente> getAntecedentes() {
		return antecedentes;
	}
	public void setAntecedentes(List<Antecedente> antecedentes) {
		this.antecedentes = antecedentes;
	}
}
