package com.example.cagua.claselayouts;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class FrameActivity extends AppCompatActivity
{
    TextView txt;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_frame);

        txt = (TextView) findViewById(R.id.txt);

        Bundle bundle = getIntent().getBundleExtra("bundle");
        String user = bundle.getString("user");
        String lvl = bundle.getString("lvl");

        txt.setText(user + " -> " + lvl);
    }
}
