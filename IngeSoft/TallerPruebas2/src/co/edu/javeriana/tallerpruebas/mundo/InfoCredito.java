package co.edu.javeriana.tallerpruebas.mundo;

import java.util.ArrayList;
import java.util.List;

public class InfoCredito {
	private List<Usuario> usuarios;
	
	public InfoCredito( ) {
		this.usuarios = new ArrayList<Usuario>();
	}
	
	public boolean crearUsuario( String nombre, String cedula, String direccion ) {
		boolean flag = false;
		if( this.buscarUsuario(cedula) == null ) {
			Usuario user = new Usuario( nombre, cedula, direccion );
			this.usuarios.add(user);
			flag = true;
		}
		
		return flag;
	}
	
	public boolean elimianrUsuario( String cedula ) {
		boolean flag = false;
		Usuario user = this.buscarUsuario(cedula);
		
		if( user != null ) {
			this.usuarios.remove(user);
			flag = true;
		}
		
		return flag;
	}
	
	public Usuario buscarUsuario( String cedula ) {
		Usuario user = null;
		
		for( Usuario u : usuarios ) {
			if( u.getCedula().equals(cedula) ) {
				user = u;
			}
		}
		
		return user;
	}
	
	public boolean agregarAntecedente( String cedula, String fecha, String descripcion, int tipo ) {
		boolean flag = false;
		Usuario user = this.buscarUsuario(cedula);
		
		if( user != null ) {
			flag = user.crearAntecedente( fecha, descripcion, tipo );
		}
		
		return flag;
	}
	
	public boolean eliminarAntecedente( String cedula, int indice ) {
		boolean flag = false;
		Usuario user = this.buscarUsuario(cedula);
		
		if( user != null ) {
			flag = user.eliminarAntecedente( indice );
		}
		
		return flag;
	}

	public List<Usuario> getUsuarios() {
		return usuarios;
	}

	public void setUsuarios(List<Usuario> usuarios) {
		this.usuarios = usuarios;
	}
}
