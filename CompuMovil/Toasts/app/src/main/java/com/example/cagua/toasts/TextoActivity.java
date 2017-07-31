package com.example.cagua.toasts;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class TextoActivity extends AppCompatActivity
{
    TextView tv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_texto);
        tv = (TextView) findViewById(R.id.txtView);
        String txt = getIntent().getStringExtra("txtActivity");
        tv.setText(txt);
    }
}
