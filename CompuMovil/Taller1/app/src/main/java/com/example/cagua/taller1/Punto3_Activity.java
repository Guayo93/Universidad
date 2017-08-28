package com.example.cagua.taller1;

import android.content.DialogInterface;
import android.content.Intent;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Date;

public class Punto3_Activity extends AppCompatActivity
{
    EditText txtIts;
    TextView counter;
    Button btnFib;
    Button btnFact;
    Button btnPaises;
    Intent fibIntent;
    Intent factIntent;
    Intent paisesIntent;
    int contFact, contFib;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_punto3);

        txtIts = (EditText) findViewById(R.id.txtIts);
        btnFib = (Button) findViewById(R.id.fib2);
        btnFact = (Button) findViewById(R.id.fact);
        counter = (TextView) findViewById(R.id.txtCounter);
        btnPaises = (Button) findViewById(R.id.btnPaises);

        factIntent = new Intent(this, Punto3B_Activity.class);
        fibIntent = new Intent(this, Punto3A_Activity.class);
        paisesIntent = new Intent(this, Paises_Activity.class);

        btnFib.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                contFib++;
                //Toast.makeText(view.getContext(), "Fibonacci: " + contFib + " - Factorial: " + contFact, Toast.LENGTH_SHORT).show();
                counter.setText("Fibonacci: " + contFib + " - Factorial: " + contFact + " - " + DateFormat.getTimeInstance().format(new Date()));
                String txt = txtIts.getText().toString();
                if(txt.isEmpty())
                {
                    factIntent.putExtra("nIts", Integer.parseInt("0"));
                }
                else
                {
                    factIntent.putExtra("nIts", Integer.parseInt(txt));
                }
                startActivity(fibIntent);
            }
        });

        btnFact.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                contFact++;
                //Toast.makeText(view.getContext(), "Fibonacci: " + contFib + " - Factorial: " + contFact, Toast.LENGTH_SHORT).show();
                counter.setText("Fibonacci: " + contFib + " - Factorial: " + contFact + " - " + DateFormat.getTimeInstance().format(new Date()));
                String txt = txtIts.getText().toString();
                if(txt.isEmpty())
                {
                    factIntent.putExtra("nIts", Integer.parseInt("0"));
                }
                else
                {
                    factIntent.putExtra("nIts", Integer.parseInt(txt));
                }
                startActivity(factIntent);
            }
        });

        btnPaises.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                startActivity(paisesIntent);
            }
        });
    }
}
