package com.example.cagua.taller1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.LinearLayout;
import android.widget.TextView;

public class Punto3B_Activity extends AppCompatActivity
{

    LinearLayout txtContainer;
    TextView txtFact;
    TextView txtMult;
    int nIts;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_punto3_b);

        txtContainer = (LinearLayout) findViewById(R.id.txtContainer3);
        txtFact = (TextView) findViewById(R.id.txtFact);
        txtMult = (TextView) findViewById(R.id.txtMult);

        nIts = getIntent().getIntExtra("nIts", 0);
        String factString = "Multiplicacion: ";
        int fact = 1;

        for(int i = nIts; i > 0; i--)
        {
            fact *= i;
            factString += i;

            if(i != 1)
            {
                factString += "*";
            }
        }

        txtMult.setText(factString);
        txtFact.setText("Resultado: " + fact);
    }
}
