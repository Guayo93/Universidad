package com.example.cagua.taller1;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class Punto2_Activity extends AppCompatActivity
{
    LinearLayout txtContainer;
    TextView txtFibRoot;
    TextView txtFib;
    Button btnFib;
    Button btnNext;
    Intent i;
    int n1, n2, n3;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_punto2);

        txtContainer = (LinearLayout) findViewById(R.id.txtContainer);
        txtFibRoot = (TextView) findViewById(R.id.txtFib1);
        btnFib = (Button) findViewById(R.id.fib1);
        btnNext = (Button) findViewById(R.id.n1);

        n1 = 0;
        n2 = 0;
        n3 = 1;

        i = new Intent(this, Punto3_Activity.class);

        btnFib.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                n2 = n1;
                n1 = n3;
                n3 = n1 + n2;

                txtFib = new TextView(view.getContext());
                txtFib.setHeight(txtFibRoot.getHeight());
                txtFib.setWidth(txtFibRoot.getWidth());
                txtFib.setGravity(txtFibRoot.getGravity());
                txtFib.setText(n1 + "");
                txtContainer.addView(txtFib);
            }
        });

        btnNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                startActivity(i);
            }
        });
    }
}
