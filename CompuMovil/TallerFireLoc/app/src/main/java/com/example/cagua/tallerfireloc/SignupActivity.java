package com.example.cagua.tallerfireloc;

import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.UserProfileChangeRequest;

public class SignupActivity extends AppCompatActivity
{
    private FirebaseAuth mAuth;
    private FirebaseAuth.AuthStateListener mAuthListener;

    private EditText edtNombre;
    private EditText edtApellido;
    private EditText edtCorreo;
    private EditText edtPass;

    private ImageView imgPerfil;

    private Button btnGaleria;
    private Button btnCamara;
    private Button btnRegisto;

    private Intent homeIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup);

        edtNombre = (EditText) findViewById(R.id.edtNombre);
        edtApellido = (EditText) findViewById(R.id.edtApellido);
        edtCorreo = (EditText) findViewById(R.id.edtCorreo);
        edtPass = (EditText) findViewById(R.id.edtPassword);

        imgPerfil = (ImageView) findViewById(R.id.imgPerfil);

        btnGaleria = (Button) findViewById(R.id.btnGaleria);
        btnCamara = (Button) findViewById(R.id.btnCamara);
        btnRegisto = (Button) findViewById(R.id.btnRegistro);

        homeIntent = new Intent(this, HomeActivity.class);

        mAuth = FirebaseAuth.getInstance();
        mAuthListener = new FirebaseAuth.AuthStateListener()
        {
            @Override
            public void onAuthStateChanged(@NonNull FirebaseAuth firebaseAuth)
            {
                FirebaseUser user = firebaseAuth.getCurrentUser();

                if( user != null )
                {
                    startActivity(homeIntent);
                }
                else
                {
                    //signed out
                }
            }
        };

        btnRegisto.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                signUp();
            }
        });
    }

    private boolean validateForm()
    {
        boolean valid = true;
        String name = edtNombre.getText().toString();
        String lName = edtApellido.getText().toString();
        String email = edtCorreo.getText().toString();
        String pass = edtPass.getText().toString();

        if( name.isEmpty() )
        {
            edtNombre.setError("Required");
            valid = false;
        }

        if( lName.isEmpty() )
        {
            edtApellido.setError("Required");
            valid = false;
        }

        if( !email.contains("@") || !email.contains(".com") || email.length() < 5 || email.isEmpty() )
        {
            edtCorreo.setError("Required");
            valid = false;
        }

        if( pass.isEmpty() )
        {
            edtPass.setError("Required");
            valid = false;
        }

        return valid;
    }

    public void signUp()
    {
        if( validateForm() )
        {
            String email = edtCorreo.getText().toString();
            String pass = edtPass.getText().toString();

            mAuth.createUserWithEmailAndPassword(email, pass).addOnCompleteListener(this, new OnCompleteListener<AuthResult>()
            {
                @Override
                public void onComplete(@NonNull Task<AuthResult> task)
                {
                    if( task.isSuccessful() )
                    {
                        FirebaseUser user = mAuth.getCurrentUser();

                        if (user != null) {
                            UserProfileChangeRequest.Builder upcrb = new UserProfileChangeRequest.Builder();
                            upcrb.setDisplayName(edtNombre.getText().toString() + " " + edtApellido.getText().toString());
                            user.updateProfile(upcrb.build());
                            startActivity(homeIntent);
                        }
                    }
                    else
                    {
                        Toast.makeText(SignupActivity.this, R.string.sgnup_failed, Toast.LENGTH_SHORT).show();
                    }
                }
            });
        }
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        mAuth.addAuthStateListener(mAuthListener);
    }

    @Override
    protected void onStop()
    {
        super.onStop();
        if( mAuthListener != null )
        {
            mAuth.removeAuthStateListener(mAuthListener);
        }
    }
}
