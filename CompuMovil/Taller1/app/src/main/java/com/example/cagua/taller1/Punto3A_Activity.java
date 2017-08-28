package com.example.cagua.taller1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class Punto3A_Activity extends AppCompatActivity
{
    LinearLayout txtContainer;
    TextView txtFib;
    ArrayList<String> txts;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_punto3_a);

        txtContainer = (LinearLayout) findViewById(R.id.txtContainer2);
        txtFib = (TextView) findViewById(R.id.txtFib2);
        txts = getIntent().getStringArrayListExtra("txts");

        for(int i = 0; i < txts.size(); i++)
        {
            TextView txt = new TextView(getBaseContext());

            txt.setHeight(txtFib.getHeight());
            txt.setWidth(txtFib.getWidth());
            txt.setGravity(txtFib.getGravity());
            txt.setText(txts.get(i));

            txtContainer.addView(txt);
        }
    }
}
