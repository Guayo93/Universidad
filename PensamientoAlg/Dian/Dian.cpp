#include <iostream>

using namespace std;

struct consulta
{
    string impuesto;
    string causa;
};

struct ciudadano
{
    int cedula;
    string nombre;
    string apellido;
    int numConsultas;
    consulta consultas[5];
};

struct resp
{
    string cedula;
    string nombre;
    string apellido;
    string impuesto;
};

void atenderCiudadano(ciudadano ciudadanos[], int numCiudadanos);
void generar(string causaC, ciudadano ciudadanos[], int numCiudadanos);

int main()
{
    ciudadano ciudadanos[100];
    int numCiudadanos;
}

void atenderCiudadano(ciudadano ciudadanos[], int numCiudadanos)
{
    for(int i = 0; i < numCiudadanos; i++)
    {
        int iva = 0, ret = 0, ren = 0, pat = 0;
        cout << "Cedula: " << ciudadanos[i].cedula << endl <<
            "Nombre: " << ciudadanos[i].nombre << endl <<
            "Apellido: " << ciudadanos[i].apellido << endl;

        for(int j = 0; j < ciudadanos[i].numConsultas; j++)
        {
            cout << ciudadanos[i].consultas[j].impuesto << " | " << cout << ciudadanos[i].consultas[j].causa << endl;
            if(cout << ciudadanos[i].consultas[j].impuesto == "IVA")
            {
                iva++;
            }
            if(ciudadanos[i].consultas[j].impuesto == "retencion")
            {
                ret++;
            }
            if(ciudadanos[i].consultas[j].impuesto == "renta")
            {
                ren++;
            }
            if(ciudadanos[i].consultas[j].impuesto == "patrimonio")
            {
                pat++;
            }
        }

        cout << "El total de consultas realizadas fue: \nIVA: " << iva << endl << "Retencion: " << ret << endl << "Renta: " << ren << endl << "Patrimonio: " << pat << endl;
    }
}

void generar(string causaC, ciudadano ciudadanos[], int numCiudadanos, resp nuevosC[])
{
    int tamN = 0;

    for(int i = 0; i < numCiudadanos; i++)
    {
        for(int j = 0; j < ciudadanos[i].numConsultas; j++)
        {
            if(ciudadanos[i].consultas[j].causa == causaC)
            {
                nuevosC[tamN].nombre = ciudadanos[i].nombre;
                nuevosC[tamN].apellido = ciudadanos[i].apellido;
                nuevosC[tamN].cedula = ciudadanos[i].cedula;
                nuevosC[tamN].impuesto = ciudadanos[i].consultas[j].impuesto;
                tamN++;
            }
        }
    }

    for(int i = 0; i < tamN; i++)
    {
        for(int j = i; j < tamN; j++)
        {
            if(nuevosC[i].apellido < nuevosC[j].apellido)
            {
                resp temp = nuevosC[i];
                nuevosC[i] = nuevosC[j];
                nuevosC[j] = temp;
            }
        }
    }

    cout << "Consulta por: " << causaC << endl;
    for(int i = 0; i < tamN; i++)
    {
        cout << nuevosC[i].cedula << " " << nuevosC[i].nombre << " " << nuevosC[i].apellido << " " << nuevosC[i].impuesto;
    }
}
