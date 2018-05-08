package co.edu.javeriana.tallerpruebas.test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import co.edu.javeriana.tallerpruebas.mundo.InfoCredito;

public class InfoCreditoTest {
	private static InfoCredito ic;
	
	@BeforeAll
	@Test
	static void init( ) {
		ic = new InfoCredito();
		ic.crearUsuario("Cristian", "1.123.123", "Calle False # 123");
	}
	
	@Test
	void testCrearUsuario( ) {
		assertTrue( ic.crearUsuario("Manuel", "2.312.321", "Carrera Venezuela # 321") );
		assertFalse( ic.crearUsuario("Cristian", "1.123.123", "Calle False # 123") );
	}
	
	@Test
	void testBuscarAntecedente( ) {
		assertNotNull( ic.buscarUsuario("1.123.123") );
	}
	
	@Test
	void testEliminarAntecedente( ) {
		assertTrue( ic.elimianrUsuario("1.123.123") );
	}
}
