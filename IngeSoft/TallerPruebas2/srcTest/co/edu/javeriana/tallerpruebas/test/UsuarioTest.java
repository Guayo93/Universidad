package co.edu.javeriana.tallerpruebas.test;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import co.edu.javeriana.tallerpruebas.mundo.Usuario;

public class UsuarioTest {
	private static Usuario user1;
	private static Usuario user2;
	
	@BeforeAll
	@Test
	static void init( ) {
		user1 = new Usuario( "Eduardo", "1.123.123", "Calle falsa # 123" );
		user2 = new Usuario( "Manuel", "2.321.321", "Carrera loca" );
		user1.crearAntecedente("January 2, 2013", "Demora de Entrega", 1);
	}
	
	@Test
	void testAgregarAntecedente( ) {
		assertTrue( user1.crearAntecedente("January 2, 2011", "Demora de Entrega", 1) );
		assertTrue( user2.crearAntecedente("January 2, 2011", "Demora de Entrega", 1) );
	}
	
	@Test
	void testEliminarAntecedente( ) {
		assertTrue( user1.eliminarAntecedente(1) );
		assertFalse( user2.eliminarAntecedente(4) );
	}
}
