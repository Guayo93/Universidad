package com.example.cagua.clasepermisos;

import android.Manifest;
import android.content.pm.PackageManager;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class PermisoDetail_Activity extends AppCompatActivity
{
    public final static int MY_PERMISSIONS_REQUEST_READ_CONTACTS = 123;
    TextView txtState;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_permiso_detail);

        txtState = (TextView) findViewById(R.id.txtState);

        if(ContextCompat.checkSelfPermission(this, Manifest.permission.READ_CONTACTS) != PackageManager.PERMISSION_GRANTED)
        {
            if(ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.READ_CONTACTS))
            {

            }
            else
            {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_CONTACTS}, MY_PERMISSIONS_REQUEST_READ_CONTACTS);
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults)
    {
        switch (requestCode)
        {
            case MY_PERMISSIONS_REQUEST_READ_CONTACTS:
            {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
                {
                    txtState.setText("PERMISO CONCEDIDO!");
                    txtState.setTextColor(Color.parseColor("#76FF03"));
                    Toast.makeText(this, "Gracias!", Toast.LENGTH_SHORT).show();
                }
                else
                {
                    txtState.setText("PERMISO DENEGADO!");
                    txtState.setTextColor(Color.parseColor("#F44336"));
                    Toast.makeText(this, "Funcionalidad Limitada!", Toast.LENGTH_SHORT).show();
                }
                return;
            }

            // other 'case' lines to check for other
            // permissions this app might request
        }
    }
}
