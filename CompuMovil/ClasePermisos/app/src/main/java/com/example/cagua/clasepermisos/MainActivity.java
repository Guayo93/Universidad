package com.example.cagua.clasepermisos;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity
{
    ImageButton btnContactos;
    ImageButton btnCamara;
    Intent detailIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnContactos = (ImageButton) findViewById(R.id.btnContactos);
        btnCamara = (ImageButton) findViewById(R.id.btnCamara);

        detailIntent = new Intent(this, PermisoDetail_Activity.class);

        btnContactos.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(detailIntent);
            }
        });
    }
}
