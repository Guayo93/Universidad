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

import java.util.ArrayList;
import java.util.List;

public class Punto3_Activity extends AppCompatActivity
{
    EditText txtIts;
    Button btnFib;
    Intent intent;
    int n1, n2, n3, nIts;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_punto3);

        txtIts = (EditText) findViewById(R.id.txtIts);
        btnFib = (Button) findViewById(R.id.fib2);

        intent = new Intent(this, Punto3A_Activity.class);

        btnFib.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                n1 = 0; n2 = 0; n3 = 1;

                try
                {
                    nIts = Integer.parseInt(txtIts.getText().toString());
                }
                catch (Exception e)
                {
                    AlertDialog.Builder builder = new AlertDialog.Builder(view.getContext());
                    builder.setTitle("Input Error");
                    builder.setMessage("El texto ingresado no es un numero.");
                    builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int id) {
                            dialog.dismiss();
                        }
                    });
                    AlertDialog alertDialog = builder.create();
                    alertDialog.show();

                    nIts = 0;
                }

                ArrayList<String> txts = new ArrayList<String>();

                for(int i = 0; i < nIts; i++)
                {
                    n2 = n1;
                    n1 = n3;
                    n3 = n1 + n2;

                    txts.add(n1 + "");
                }

                intent.putStringArrayListExtra("txts", txts);
                startActivity(intent);
            }
        });
    }
}
