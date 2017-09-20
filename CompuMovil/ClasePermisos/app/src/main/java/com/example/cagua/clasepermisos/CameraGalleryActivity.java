package com.example.cagua.clasepermisos;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

import java.io.FileNotFoundException;
import java.io.InputStream;

public class CameraGalleryActivity extends AppCompatActivity
{
    public final static int MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE = 234;
    public final static int IMAGE_PICKER_REQUEST = 345;
    public final static int TAKE_PICTURE_REQUEST = 456;
    public final static int MY_PERMISSIONS_REQUEST_CAMERA = 567;

    Button btnLaunchCamera;
    Button btnGallery;
    ImageView imgActual;
    Intent pickImage;
    Activity thisActivity;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera_gallery);

        imgActual = (ImageView) findViewById(R.id.imgActual);

        btnLaunchCamera = (Button) findViewById(R.id.btnLaunchCamera);
        btnGallery = (Button) findViewById(R.id.btnGallery);

        pickImage = new Intent(Intent.ACTION_PICK);
        pickImage.setType("image/");

        thisActivity = this;

        btnLaunchCamera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(ContextCompat.checkSelfPermission(thisActivity, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED)
                {
                    ActivityCompat.requestPermissions(thisActivity, new String[]{Manifest.permission.CAMERA}, MY_PERMISSIONS_REQUEST_CAMERA);
                }
                else
                {
                    takePicture();
                }
            }
        });

        btnGallery.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(ContextCompat.checkSelfPermission(thisActivity, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)
                {
                    ActivityCompat.requestPermissions(thisActivity, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE);
                }
                else
                {
                    startActivityForResult(pickImage, IMAGE_PICKER_REQUEST);
                }
            }
        });
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults)
    {
        switch (requestCode)
        {
            case MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE:
            {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
                {
                    startActivityForResult(pickImage, IMAGE_PICKER_REQUEST);;
                }
                else
                {
                    Toast.makeText(this, "Esta funcionalidad requiere permisos!", Toast.LENGTH_SHORT).show();
                }
                return;
            }
            case MY_PERMISSIONS_REQUEST_CAMERA:
            {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
                {
                    takePicture();
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

    protected void onActivityResult( int requestCode, int resultCode, Intent data )
    {
        super.onActivityResult(requestCode, resultCode, data);

        if(requestCode == IMAGE_PICKER_REQUEST && resultCode == RESULT_OK)
        {
            loadImage(data);
        }
        else if(requestCode == TAKE_PICTURE_REQUEST && resultCode == RESULT_OK)
        {
            loadCameraPicture(data);
        }
    }

    private void loadImage(Intent data)
    {
        try
        {
            final Uri imageUri = data.getData();
            final InputStream imageStream = getContentResolver().openInputStream(imageUri);
            final Bitmap selectedImage = BitmapFactory.decodeStream(imageStream);
            imgActual.setImageBitmap(selectedImage);
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }

    private void loadCameraPicture( Intent data )
    {
        Bundle extras = data.getExtras();
        Bitmap imageBitmap = (Bitmap) extras.get("data");
        imgActual.setImageBitmap(imageBitmap);
    }

    private void takePicture()
    {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if(takePictureIntent.resolveActivity(getPackageManager()) != null)
        {
            startActivityForResult(takePictureIntent, TAKE_PICTURE_REQUEST);
        }
    }
}
