#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>

using namespace std;

struct Persona
{
    char* nombre;
    char* apellido;
    int edad;
};

char* convertirEnteroACadena(int num)
{
    int num2 = num, cont = 0;

    while(num2 != 0)
    {
        num2 /= 10;
        cont++;
    }

    char * cad = new char [cont+1];
    int i = cont - 1;

    while(i >= 0)
    {
        *(cad + i) = '0' + (num % 10);
        num /= 10;
        i--;
    }

    *(cad+cont) = '\0';

    return cad;
}

int main()
{
    Persona personas[5];
    int tam = 0;
    ifstream entrada;
    ofstream salida;

    entrada.open("registros.txt", ios::in);
    salida.open("ordenado.txt", ios::out);

    while(!entrada.eof())
    {
        char* linea = new char [100];
        entrada.getline(linea, 100);
        Persona p;

        p.nombre = strtok(linea, "-");
        p.apellido = strtok(NULL, "-");
        p.edad = atoi(strtok(NULL, "-"));

        personas[tam] = p;
        tam++;
    }

    for(int i = 0; i < tam-1; i++)
    {
        for(int j = i+1; j < tam; j++)
        {
            if(strcmp(personas[j].nombre, personas[i].nombre) < 0)
            {
                Persona temp = personas[j];
                personas[j] = personas[i];
                personas[i] = temp;
            }
        }
    }

    for(int i = 0; i < tam; i++)
    {
        char* linea = new char [100];
        strcpy(linea, (personas + i)->nombre);
        strcat(linea, " ");
        strcat(linea, (personas + i)->apellido);
        strcat(linea, " ");
        strcat(linea, convertirEnteroACadena((personas + i)->edad));

        salida << linea << endl;
    }
}
