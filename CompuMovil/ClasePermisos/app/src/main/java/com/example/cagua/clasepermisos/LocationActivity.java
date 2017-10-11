package com.example.cagua.clasepermisos;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.IntentSender;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.location.Location;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.common.api.CommonStatusCodes;
import com.google.android.gms.common.api.ResolvableApiException;
import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationCallback;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationResult;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.location.LocationSettingsRequest;
import com.google.android.gms.location.LocationSettingsResponse;
import com.google.android.gms.location.LocationSettingsStatusCodes;
import com.google.android.gms.location.SettingsClient;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.Writer;
import java.util.Date;

public class LocationActivity extends AppCompatActivity
{
    public final static int MY_PERMISSIONS_REQUEST_LOCATION = 234;
    public final static int REQUEST_CHECK_SETTINGS = 123;
    public final static double RADIUS_OF_EARTH_KM = 6371;

    TextView txtLatitud;
    TextView txtLongitud;
    TextView txtAltitud;
    TextView txtDistancia;

    LinearLayout linearTxt;
    Button btnSave;

    Activity thisActivy;

    Location actualLocation;

    JSONArray locaciones;

    private FusedLocationProviderClient mFusedLocationClient;
    private LocationRequest mLocationRequest;
    private LocationCallback mLocationCallback;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_location);

        thisActivy = this;

        txtLatitud = (TextView) findViewById(R.id.txtLatitud);
        txtLongitud = (TextView) findViewById(R.id.txtLongitud);
        txtAltitud = (TextView) findViewById(R.id.txtAltitud);
        txtDistancia = (TextView) findViewById(R.id.txtDistance);

        linearTxt = (LinearLayout) findViewById(R.id.linearTxt);
        btnSave = (Button) findViewById(R.id.btnSave);

        locaciones = new JSONArray();

        mFusedLocationClient =	LocationServices.getFusedLocationProviderClient(this);
        mLocationRequest = createLocationRequest();
        mLocationCallback = new LocationCallback()
        {
            @Override
            public void onLocationResult(LocationResult locationResult)
            {
                getLocation();
            }
        };

        if(ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, MY_PERMISSIONS_REQUEST_LOCATION);
        }
        else
        {
            requestLocationActivation();
            getLocation();
        }

        btnSave.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                Date fecha = new Date(System.currentTimeMillis());
                writeJSONObject(fecha);

                String lat = "Latitud: " + actualLocation.getLatitude();
                String lon = "Longitud: " + actualLocation.getLongitude();

                TextView txt = new TextView(getApplicationContext());
                String save = lat + ", " + lon + ", " + "Fecha: " + fecha;
                txt.setText(save);
                txt.setTextColor(Color.BLACK);

                linearTxt.addView(txt);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);
        switch	(requestCode)
        {
            case REQUEST_CHECK_SETTINGS:
            {
                if (resultCode == RESULT_OK)
                {
                    startLocationUpdates();		//Se	encendió la	localización!!!
                }
                else
                {
                    Toast.makeText(this, "Sin acceso a localización, hardware deshabilitado!", Toast.LENGTH_LONG).show();
                }
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults)
    {
        switch (requestCode)
        {
            case MY_PERMISSIONS_REQUEST_LOCATION:
            {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
                {
                    requestLocationActivation();
                    getLocation();
                }
                else
                {
                    Toast.makeText(this, "Esta funcionalidad requiere permisos!", Toast.LENGTH_SHORT).show();
                }
            }
            // other 'case' lines to check for other
            // permissions this app might request
        }
    }

    private void getLocation()
    {
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED)
        {
            mFusedLocationClient.getLastLocation().addOnSuccessListener(thisActivy, new OnSuccessListener<Location>()
            {
                @Override
                public void onSuccess(Location location)
                {
                    if (location != null)
                    {
                        actualLocation = location;

                        String lat = "Latitud: " + actualLocation.getLatitude();
                        String lon = "Longitud: " + actualLocation.getLongitude();
                        String alt = "Altitud: " + actualLocation.getAltitude();
                        String dist = "Distancia a la Plaza de Toros: " + distance(location.getLatitude(), location.getLongitude(), 4.613195, -74.068072) + " Km";

                        txtLatitud.setText(lat);
                        txtLongitud.setText(lon);
                        txtAltitud.setText(alt);
                        txtDistancia.setText(dist);
                    }
                }
            });
        }
    }

    protected LocationRequest createLocationRequest()
    {
        LocationRequest mLocationRequest = new LocationRequest();
        mLocationRequest.setInterval(2000);	//tasa de	refresco en	milisegundos
        mLocationRequest.setFastestInterval(5000);	//máxima tasa de	refresco
        mLocationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        return mLocationRequest;
    }

    private void requestLocationActivation()
    {
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED)
        {
            //Una	vez se	tengan permisos
            LocationSettingsRequest.Builder builder	= new LocationSettingsRequest.Builder().addLocationRequest(mLocationRequest);
            SettingsClient client =	LocationServices.getSettingsClient(this);
            Task<LocationSettingsResponse> task	= client.checkLocationSettings(builder.build());

            task.addOnSuccessListener(this,	new	OnSuccessListener<LocationSettingsResponse>()
            {
                @Override
                public void onSuccess(LocationSettingsResponse locationSettingsResponse)
                {
                    startLocationUpdates();	//Todas las condiciones para	recibir localizaciones
                }
            });

            task.addOnFailureListener(this, new OnFailureListener()
            {
                @Override
                public void	onFailure(@NonNull Exception e)
                {
                    int statusCode = ((ApiException) e).getStatusCode();
                    switch (statusCode)
                    {
                        case CommonStatusCodes.RESOLUTION_REQUIRED:
                            //	Location settings are not satisfied, but this can be fixed by showing the user a dialog.
                            try
                            {
                                // Show the	dialog	by	calling	startResolutionForResult(),	and check the result in onActivityResult().
                                ResolvableApiException resolvable =	(ResolvableApiException) e;
                                resolvable.startResolutionForResult(thisActivy, REQUEST_CHECK_SETTINGS);
                            }
                            catch(IntentSender.SendIntentException sendEx)
                            {
                                //	Ignore	the	error.
                            }
                            break;
                        case LocationSettingsStatusCodes.SETTINGS_CHANGE_UNAVAILABLE:
                            //	Location settings are not satisfied. No way to fix	the	settings so	we won't show the	dialog.
                            break;
                    }
                }
            });
        }
    }

    private void startLocationUpdates()
    {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED)
        {
            mFusedLocationClient.requestLocationUpdates(mLocationRequest, mLocationCallback, null);
        }
    }

    public double distance(double lat1, double long1, double lat2, double long2)
    {
        double latDistance = Math.toRadians(lat1 - lat2);
        double lngDistance = Math.toRadians(long1 - long2);
        double a = Math.sin(latDistance / 2) * Math.sin(latDistance / 2) + Math.cos(Math.toRadians(lat1)) * Math.cos(Math.toRadians(lat2)) * Math.sin(lngDistance /	2) * Math.sin(lngDistance /	2);
        double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1	- a));
        double result = RADIUS_OF_EARTH_KM * c;

        return Math.round(result*100.0)/100.0;
    }

    private void writeJSONObject(Date date)
	{
        locaciones.put(toJSON(date));
		Writer output = null;
		String filename = "locations.json";

		try
        {
			File file = new File(getBaseContext().getExternalFilesDir(null), filename);
			output = new BufferedWriter(new FileWriter(file));
			output.write(locaciones.toString());
			output.close();
			Toast.makeText(getApplicationContext(), "Location saved", Toast.LENGTH_SHORT).show();
		}
		catch (Exception e)
        {
			Toast.makeText(getBaseContext(), e.getMessage(), Toast.LENGTH_LONG).show();
		}
	}

	public JSONObject toJSON(Date date)
    {
		JSONObject obj = new JSONObject();

		try
        {
			obj.put("latitud", actualLocation.getLatitude());
			obj.put("longitud", actualLocation.getLongitude());
			obj.put("date", date);
		}
		catch (JSONException e)
        {
			e.printStackTrace();
		}

		return	obj;
	}
}
