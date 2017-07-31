package com.example.cagua.toasts;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity
{
    Button btnEnviar;
    Button btnActivity;
    EditText et;
    int numOprimidas;
    Intent i;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnEnviar = (Button) findViewById(R.id.btnEnviar);
        btnActivity = (Button) findViewById(R.id.btnActivity);
        et = (EditText) findViewById(R.id.txtEdit);
        numOprimidas = 0;
        i = new Intent(this, TextoActivity.class);

        btnEnviar.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
                numOprimidas++;
                Toast.makeText(getBaseContext(), et.getText().toString(), Toast.LENGTH_SHORT).show();
                Log.i("MainActivity", "Numero de veces oprimidas: " + numOprimidas);
            }
        });

        btnActivity.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
                i.putExtra("txtActivity", et.getText().toString());
                startActivity(i);
            }
        });
    }
}
