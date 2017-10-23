package com.example.cagua.tallerfireloc;

import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class MainActivity extends AppCompatActivity
{
    private FirebaseAuth mAuth;
    private FirebaseAuth.AuthStateListener mAuthListener;

    private EditText txtEmail;
    private EditText txtPass;

    private Button btnLogin;
    private Button btnSignup;

    private Intent homeIntent;
    private Intent signupIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        txtEmail = (EditText) findViewById(R.id.txtEmail);
        txtPass = (EditText) findViewById(R.id.txtPass);

        btnLogin = (Button) findViewById(R.id.btnLogin);
        btnSignup = (Button) findViewById(R.id.btnSignup);

        homeIntent = new Intent(this, HomeActivity2.class);
        signupIntent = new Intent(this, SignupActivity.class);

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

        btnLogin.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                signIn();
            }
        });

        btnSignup.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                startActivity(signupIntent);
            }
        });
    }

    private boolean validateForm()
    {
        boolean valid = true;
        String email = txtEmail.getText().toString();
        String pass = txtPass.getText().toString();

        if( !email.contains("@") || !email.contains(".com") || email.length() < 5 || email.isEmpty() )
        {
            txtEmail.setError("Required");
            valid = false;
        }

        if( pass.isEmpty() )
        {
            txtPass.setError("Required");
            valid = false;
        }

        return valid;
    }

    public void signIn( )
    {
        if( validateForm() )
        {
            String email = txtEmail.getText().toString();
            String password = txtPass.getText().toString();

            mAuth.signInWithEmailAndPassword(email, password).addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
                @Override
                public void onComplete(@NonNull Task<AuthResult> task) {
                    if (!task.isSuccessful())
                    {
                        Toast.makeText(MainActivity.this, R.string.auth_failed, Toast.LENGTH_SHORT).show();
                        txtEmail.setText("");
                        txtPass.setText("");
                    }
                    else
                    {
                        startActivity(homeIntent);
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