package com.example.cagua.taller1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class Punto3A_Activity extends AppCompatActivity
{
    LinearLayout txtContainer;
    TextView txtFib;
    int nIts;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_punto3_a);

        txtContainer = (LinearLayout) findViewById(R.id.txtContainer2);
        txtFib = (TextView) findViewById(R.id.txtFib2);
        nIts = getIntent().getIntExtra("nIts", 0);

        int n1 = 0, n2 = 0, n3 = 1;

        for(int i = 0; i < nIts; i++)
        {
            n2 = n1;
            n1 = n3;
            n3 = n1 + n2;

            TextView txt = new TextView(this);

            txt.setText(n1 + "");
            txt.setHeight(txtFib.getHeight());
            txt.setWidth(txtFib.getWidth());
            txt.setGravity(txtFib.getGravity());

            txtContainer.addView(txt);
        }
    }
}
