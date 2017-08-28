package com.example.cagua.claselayouts;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebView;

public class WebActivity extends AppCompatActivity
{
    WebView webview;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_web);

        webview = (WebView) findViewById(R.id.webview);
        webview.loadUrl("https://www.google.com");
    }
}
