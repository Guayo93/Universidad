package com.example.cagua.taller1;

public class Pais
{
    private String capital;
    private String nombre;
    private String nombreInternacional;
    private String sigla;

    public Pais(String capitalP, String nombreP, String nombreInternacionalP, String siglaP)
    {
        this.capital = capitalP;
        this.nombre = nombreP;
        this.nombreInternacional = nombreInternacionalP;
        this.sigla = siglaP;
    }

    public String getCapital() {
        return capital;
    }

    public void setCapital(String capital) {
        this.capital = capital;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public String getNombreInternacional() {
        return nombreInternacional;
    }

    public void setNombreInternacional(String nombreInternacional) {
        this.nombreInternacional = nombreInternacional;
    }

    public String getSigla() {
        return sigla;
    }

    public void setSigla(String sigla) {
        this.sigla = sigla;
    }

    @Override
    public String toString()
    {
        return getNombre();
    }
}
