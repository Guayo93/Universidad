package com.example.cagua.taller1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class PaisDetail_Activity extends AppCompatActivity
{
    TextView txtCapital;
    TextView txtNombre;
    TextView txtNomInt;
    TextView txtSigla;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pais_detail);

        ArrayList<String> datos = getIntent().getStringArrayListExtra("detail");

        txtCapital = (TextView) findViewById(R.id.paisCapital);
        txtNombre = (TextView) findViewById(R.id.paisNombre);
        txtNomInt = (TextView) findViewById(R.id.paisNomInt);
        txtSigla = (TextView) findViewById(R.id.paisSigla);

        txtCapital.setText("Capital: " + datos.get(0));
        txtNombre.setText("Nombre: " + datos.get(1));
        txtNomInt.setText("Nombre Internacional: " + datos.get(2));
        txtSigla.setText("Sigla: " + datos.get(3));
    }
}
