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
import android.widget.Toast;

public class MainActivity extends AppCompatActivity
{
    public final static int MY_PERMISSIONS_REQUEST_READ_CONTACTS = 123;

    ImageButton btnContactos;
    ImageButton btnCamara;
    Intent detailIntent;
    Intent camaraIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnContactos = (ImageButton) findViewById(R.id.btnContactos);
        btnCamara = (ImageButton) findViewById(R.id.btnCamara);

        detailIntent = new Intent(this, ContactsListActivity.class);
        camaraIntent = new Intent(this, CameraGalleryActivity.class);

        btnContactos.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                startActivity(detailIntent);
            }
        });

        btnCamara.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(camaraIntent);
            }
        });
    }
}
