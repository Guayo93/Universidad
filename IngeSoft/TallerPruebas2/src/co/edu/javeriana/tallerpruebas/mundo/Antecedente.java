package co.edu.javeriana.tallerpruebas.mundo;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class Antecedente {
	public enum Tipo {
		GRAVE, MEDIANO, LIVIANO
	}
	
	private Date fecha;
	private String descripcion;
	private Tipo tipo;
	
	public Antecedente( String date, String descripcionP, Tipo tipoP ) {
		DateFormat format = new SimpleDateFormat("MMMM d, yyyy", Locale.US);
		try {
			this.fecha = format.parse(date);
		} catch (ParseException e) {
			this.fecha = null;
			System.out.println("Fecha Equivocada. Usar formato - MMMM d, yyyy");
		}
		this.descripcion = descripcionP;
		this.tipo = tipoP;
	}

	public Date getFecha() {
		return fecha;
	}

	public void setFecha(Date fecha) {
		this.fecha = fecha;
	}

	public String getDescripcion() {
		return descripcion;
	}

	public void setDescripcion(String descripcion) {
		this.descripcion = descripcion;
	}

	public Tipo getTipo() {
		return tipo;
	}

	public void setTipo(Tipo tipo) {
		this.tipo = tipo;
	}
}
