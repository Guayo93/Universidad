package co.edu.javeriana.TallerPruebas.pruebas;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import co.edu.javeriana.TallerPruebas.mundo.Calculadora;

public class CalculadoraTest {
	private static Calculadora calc;
	
	@BeforeAll
	static void initAll( ) {
		calc = new Calculadora( );
	}
	
	@Test
	void testInit( ) {
		assertNotNull( calc );
	}
	
	@Test
	void testSuma( ) {
		assertEquals( 4, calc.suma( 2, 2 ) );
	}
	
	@Test
	void testResta( ) {
		assertEquals( 4, calc.resta( 6, 2 ) );
	}
	
	@Test
	void testMultiplicacion( ) {
		assertEquals( 4, calc.multiplicacion( 2, 2 ) );
	}
	
	@Test
	void testDivision( ) {
		assertEquals( 4, calc.division( 8, 2 ) );
	}
	
	@ParameterizedTest
	@ValueSource( strings = { "racecar", "radar" } )
	void palindromeTest( String cadena ) {
		assertTrue( calc.esPalindrome( cadena ) );
	}
}