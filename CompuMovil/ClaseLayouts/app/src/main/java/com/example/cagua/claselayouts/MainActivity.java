package com.example.cagua.claselayouts;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity
{
    TextView txt;
    Spinner spin;

    Button btnWeb;
    Button btnFrame;
    Button btnList;

    Intent intWeb;
    Intent intFrame;
    Intent intList;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        txt = (TextView) findViewById(R.id.txtInput);
        spin = (Spinner) findViewById(R.id.spinEdu);

        btnWeb = (Button) findViewById(R.id.btnWeb);
        intWeb = new Intent(this, WebActivity.class);

        btnFrame = (Button) findViewById(R.id.btnFrame);
        intFrame = new Intent(this, FrameActivity.class);

        btnList = (Button) findViewById(R.id.btnList);
        intList = new Intent(this, ListActivity.class);

        btnWeb.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                startActivity(intWeb);
            }
        });

        btnFrame.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                Bundle bundle = new Bundle();
                bundle.putString("user", txt.getText().toString());
                bundle.putString("lvl", spin.getSelectedItem().toString());

                intFrame.putExtra("bundle", bundle);
                startActivity(intFrame);
            }
        });

        btnList.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                startActivity(intList);
            }
        });
    }
}
