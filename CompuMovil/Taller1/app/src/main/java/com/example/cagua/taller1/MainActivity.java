package com.example.cagua.taller1;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity
{
    TextView txtFib;
    Button btnFib;
    Button btnNext;
    Intent i;
    int n1, n2, n3;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnFib = (Button) findViewById(R.id.fib0);
        btnNext = (Button) findViewById(R.id.n0);
        txtFib = (TextView) findViewById(R.id.txtFib0);
        n1 = 0;
        n2 = 0;
        n3 = 1;

        i =  new Intent(this, Punto2_Activity.class);

        btnFib.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                n2 = n1;
                n1 = n3;
                n3 = n1 + n2;
                String txt = (String) txtFib.getText();
                txtFib.setText(txt + ", " + n1);
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
