package co.edu.javeriana.tallerpruebas.test;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import co.edu.javeriana.tallerpruebas.mundo.Antecedente;

public class AntecedenteTest {
	private static Antecedente ant1;
	private static Antecedente ant2;
	
	@BeforeAll
	@Test
	static void init( ) {
		ant1 = new Antecedente("January 2, 2011", "Demora de Entrega", Antecedente.Tipo.GRAVE);
		ant2 = null;
	}
	
	@Test
	void testInit( ) {
		assertNotNull( ant1 );
		assertNull( ant2 );
	}
}
