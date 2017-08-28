package com.example.cagua.taller1;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

public class Paises_Activity extends AppCompatActivity
{
    Pais[] paises;
    String[] nombresPaises;
    JSONObject json;
    JSONArray paisesJsonArray;
    Intent paisDetIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_paises);

        try
        {
            json = new JSONObject(loadJSONfromAsset());
            paisesJsonArray = json.getJSONArray("paises");
            paises = new Pais[paisesJsonArray.length()];
            nombresPaises = new String[paisesJsonArray.length()];

            for(int i = 0; i < paisesJsonArray.length(); i++)
            {
                JSONObject jsonObject = paisesJsonArray.getJSONObject(i);

                String capital = jsonObject.getString("capital");
                String nomPais = jsonObject.getString("nombre_pais");
                String nomPaisInt = jsonObject.getString("nombre_pais_int");
                String sigla = jsonObject.getString("sigla");

                Pais p = new Pais(capital, nomPais, nomPaisInt, sigla);
                paises[i] = p;
                nombresPaises[i] = nomPais;
            }
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }

        paisDetIntent = new Intent(this, PaisDetail_Activity.class);

        final ArrayAdapter<Pais> adapter = new ArrayAdapter<Pais>(this, android.R.layout.simple_list_item_1, paises);
        ListView listview = (ListView) findViewById(R.id.paisesList);
        listview.setAdapter(adapter);

        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long id)
            {
                String pais = adapterView.getItemAtPosition(position).toString();
                Pais p = null;
                boolean flag = false;

                for(int j = 0; j < paisesJsonArray.length() && flag == false; j++)
                {
                    if(pais.equals(nombresPaises[position]))
                    {
                        flag = true;
                        p = paises[position];
                    }
                }

                ArrayList<String> datos = new ArrayList<String>();
                datos.add(p.getCapital());
                datos.add(p.getNombre());
                datos.add(p.getNombreInternacional());
                datos.add(p.getSigla());

                paisDetIntent.putStringArrayListExtra("detail", datos);
                startActivity(paisDetIntent);
            }
        });
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
        catch(IOException e)
        {
            e.printStackTrace();
            return null;
        }

        return json;
    }
}
