package co.edu.javeriana.desarrollomm;

import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JTextArea;
import javax.swing.JButton;

public class GUI extends JFrame 
{
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JLabel lblComprimir;
	private JTextArea textAreaComprimir;
	private JLabel lblDescomprimir;
	private JTextArea textAreaDescomprimir;
	private JButton btnComprimir;
	private JButton btnDescomprimir;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					GUI frame = new GUI();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public GUI() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		setTitle("Taller LZ77");
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		lblComprimir = new JLabel("Comprimir");
		lblComprimir.setBounds(182, 12, 81, 15);
		contentPane.add(lblComprimir);
		
		textAreaComprimir = new JTextArea();
		textAreaComprimir.setBounds(25, 35, 400, 50);
		contentPane.add(textAreaComprimir);
		
		lblDescomprimir = new JLabel("Descomprimir");
		lblDescomprimir.setBounds(179, 126, 102, 15);
		contentPane.add(lblDescomprimir);
		
		textAreaDescomprimir = new JTextArea();
		textAreaDescomprimir.setBounds(25, 150, 400, 50);
		contentPane.add(textAreaDescomprimir);
		
		btnComprimir = new JButton("Comprimir");
		btnComprimir.setBounds(87, 233, 117, 25);
		btnComprimir.addActionListener(new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				String cadena = textAreaComprimir.getText();
				String resp = "";
				List<Componente> lista = Principal.compresion(cadena);
				
				for(int i = 0; i < lista.size(); i++)
				{
					resp += lista.get(i).toString();
				}
				
				textAreaDescomprimir.setText(resp);
			}
		});
		contentPane.add(btnComprimir);
		
		btnDescomprimir = new JButton("Descomprimir");
		btnDescomprimir.setBounds(250, 233, 130, 25);
		btnDescomprimir.addActionListener(new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				List<Componente> elementosMensaje = new ArrayList<Componente>();
				
				String mensaje = textAreaDescomprimir.getText();
				String[] subMensajes = mensaje.split("\\(");
				
				for(int i = 1; i < subMensajes.length; i++)
				{
					String[] temp = subMensajes[i].split(",");
					
					Componente comp = new Componente(Integer.parseInt("" + temp[0].charAt(0)), Integer.parseInt("" + temp[1].charAt(0)), "" + temp[2].charAt(0));
					elementosMensaje.add(comp);
				}
				
				textAreaComprimir.setText(Principal.descompresion(elementosMensaje));
			}
		});
		contentPane.add(btnDescomprimir);
	}
}
