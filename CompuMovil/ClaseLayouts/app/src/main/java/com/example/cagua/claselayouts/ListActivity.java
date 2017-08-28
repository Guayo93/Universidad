package com.example.cagua.claselayouts;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;

public class ListActivity extends AppCompatActivity
{
    Pais[] paises;
    String[] nombresPaises;
    JSONObject json;
    JSONArray paisesJsonArray;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);

        try
        {
            json = new JSONObject(loadJSONfromAsset());
            paisesJsonArray = json.getJSONArray("paises");
            paises = new Pais[paisesJsonArray.length()];

            for(int i = 0; i < paisesJsonArray.length(); i++)
            {
                JSONObject jsonObject = paisesJsonArray.getJSONObject(i);

                String capital = jsonObject.getString("capital");
                String nomPais = jsonObject.getString("nombre_pais");
                String nomPaisInt = jsonObject.getString("nombre_pais_int");
                String sigla = jsonObject.getString("DE");
            }
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, nombresPaises);
        ListView listview = (ListView) findViewById(R.id.listview);
        listview.setAdapter(adapter);
    }

    private void initArray()
    {
        nombresPaises = new String[paises.length];

        for(int i = 0; i < paises.length; i++)
        {

        }
    }

    public String loadJSONfromAsset()
    {
        String json = null;

        try
        {
            InputStream is = this.getAssets().open("paises.json");
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            json = new String(buffer, "UTF-8");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return null;
        }

        return json;
    }
}
