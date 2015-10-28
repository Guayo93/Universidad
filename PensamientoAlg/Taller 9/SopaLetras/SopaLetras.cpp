#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

#define MAXF 50
#define MAXC 50

void llenarSopa(char sopa[][MAXC], int tamF, int tamC);
void imprimirSopa(char sopa[][MAXC], int tamF, int tamC);
bool buscarPalabra(string pal, char sopa[][MAXC], int tamF, int tamC, string resp[]);
bool buscarPalabraArr(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[]);
bool buscarPalabraAb(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[]);
bool buscarPalabraDer(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[]);
bool buscarPalabraIzq(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[]);
bool buscarPalabraDAD(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[]);
bool buscarPalabraDAI(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[]);
bool buscarPalabraDBD(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[]);
bool buscarPalabraDBI(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[]);

int main()
{
    char sopa[MAXF][MAXC];
    int tamF, tamC;
    string resp[3];

    cout << "Cuantas filas desea que tenga la sopa de letras?" << endl;
    cin >> tamF;

    cout << "Cuantas columnas desea que tenga la sopa de letras?" << endl;
    cin >> tamC;

    llenarSopa(sopa, tamF, tamC);

    cout << "La sopa de letras queda de la siguiente manera: " << endl << endl;
    imprimirSopa(sopa, tamF, tamC);

    string op;
    while(op != "terminar")
    {
        cout << endl << "Que palabra desea buscar? (\"terminar\" para finalizar)" << endl;
        cin >> op;
        if(op != "terminar")
        {
            bool esta = buscarPalabra(op, sopa, tamF, tamC, resp);

            if(esta)
            {
                cout << "La palabra fue encontrada! Y esta en la posicion " << resp[0] << "," << resp[1] << " en la direccion: " << resp[2] << endl;
            }
            else
            {
                cout << "La palabra NO fue encontrada." << endl;
            }
        }
        else
        {
            cout << "La ejecucion ha terminado." << endl;
        }
    }
}

void llenarSopa(char sopa[][MAXC], int tamF, int tamC)
{
    for(int i = 0; i < tamF; i++)
    {
        for(int j = 0; j < tamC; j++)
        {
            sopa[i][j] = 'a' + rand()%26;
        }
    }
}

void imprimirSopa(char sopa[][MAXC], int tamF, int tamC)
{
    for(int i = 0; i < tamF; i++)
    {
        for(int j = 0; j < tamC; j++)
        {
            cout << sopa[i][j] << " ";
        }
        cout << endl;
    }
}

bool buscarPalabra(string pal, char sopa[][MAXC], int tamF, int tamC, string resp[])
{
    bool esta = false;
    for(int i = 0; i < tamF && esta == false; i++)
    {
        for(int j = 0; j < tamC && esta == false; j++)
        {
            for(int k = 0; k < 8 && esta == false; k++)
            {
                if(k == 0 && (i - pal.length()) >= 0)
                {
                    esta = buscarPalabraArr(pal, sopa, tamF, tamC, i, j, resp);
                }
                if(k == 1 && (i + pal.length()) <= (unsigned)tamF)
                {
                    esta = buscarPalabraAb(pal, sopa, tamF, tamC, i, j, resp);
                }
                if(k == 2 && (j + pal.length()) <= (unsigned)tamC)
                {
                    esta = buscarPalabraDer(pal, sopa, tamF, tamC, i, j, resp);
                }
                if(k == 3 && (j - pal.length()) >= 0)
                {
                    esta = buscarPalabraIzq(pal, sopa, tamF, tamC, i, j, resp);
                }
                if(k == 4 && (i - pal.length()) >= 0 && (j + pal.length()) <= (unsigned)tamC)
                {
                    esta = buscarPalabraDAD(pal, sopa, tamF, tamC, i, j, resp);
                }
                if(k == 5 && (i - pal.length()) >= 0 && (j - pal.length()) >= 0)
                {
                    esta = buscarPalabraDAI(pal, sopa, tamF, tamC, i, j, resp);
                }
                if(k == 6 && (i + pal.length()) <= (unsigned)tamF  && (j + pal.length()) <= (unsigned)tamC)
                {
                    esta = buscarPalabraDBD(pal, sopa, tamF, tamC, i, j, resp);
                }
                if(k == 7 && (i + pal.length()) <= (unsigned)tamF && (j - pal.length()) >= 0)
                {
                    esta = buscarPalabraDBI(pal, sopa, tamF, tamC, i, j, resp);
                }
            }
        }
    }

    return esta;
}

bool buscarPalabraArr(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[])
{
    int cont = 0;
    int tam = pal.length();
    bool esta = false;
    for(int i = posF; i > (posF - tam); i--)
    {
        if(sopa[i][posC] == pal[cont])
        {
            cont++;
        }
    }

    if(cont == tam)
    {
        esta = true;
        resp[0] = posF + 48;
        resp[1] = posC + 48;
        resp[2] = "Arriba";
    }

    return esta;
}

bool buscarPalabraAb(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[])
{
    int cont = 0;
    int tam = pal.length();
    bool esta = false;
    for(int i = posF; i < (posF + tam); i++)
    {
        if(sopa[i][posC] == pal[cont])
        {
            cont++;
        }
    }

    if(cont == tam)
    {
        esta = true;
        resp[0] = posF + 48;
        resp[1] = posC + 48;
        resp[2] = "Abajo";
    }

    return esta;
}

bool buscarPalabraDer(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[])
{
    int cont = 0;
    int tam = pal.length();
    bool esta = false;
    for(int i = posC; i < (posC + tam); i++)
    {
        if(sopa[posF][i] == pal[cont])
        {
            cont++;
        }
    }

    if(cont == tam)
    {
        esta = true;
        resp[0] = posF + 48;
        resp[1] = posC + 48;
        resp[2] = "Derecha";
    }

    return esta;
}

bool buscarPalabraIzq(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[])
{
    int cont = 0;
    int tam = pal.length();
    bool esta = false;
    for(int i = posC; i > (posC - tam); i--)
    {
        if(sopa[posF][i] == pal[cont])
        {
            cont++;
        }
    }

    if(cont == tam)
    {
        esta = true;
        resp[0] = posF + 48;
        resp[1] = posC + 48;
        resp[2] = "Izquierda";
    }

    return esta;
}

bool buscarPalabraDAD(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[])
{
    int cont = 0;
    int tam = pal.length();
    bool esta = false;
    for(int i = posF, j = posC; i > (posF - tam) && j < (posC + tam); i--, j++)
    {
        if(sopa[i][j] == pal[cont])
        {
            cont++;
        }
    }

    if(cont == tam)
    {
        esta = true;
        resp[0] = posF + 48;
        resp[1] = posC + 48;
        resp[2] = "Diagonal Arriba Derecha";
    }

    return esta;
}

bool buscarPalabraDAI(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[])
{
    int cont = 0;
    int tam = pal.length();
    bool esta = false;
    for(int i = posF, j = posC; i > (posF - tam) && j > (posC - tam); i--, j--)
    {
        if(sopa[i][j] == pal[cont])
        {
            cont++;
        }
    }

    if(cont == tam)
    {
        esta = true;
        resp[0] = posF + 48;
        resp[1] = posC + 48;
        resp[2] = "Diagonal Arriba Izquierda";
    }

    return esta;
}

bool buscarPalabraDBD(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[])
{
    int cont = 0;
    int tam = pal.length();
    bool esta = false;
    for(int i = posF; i < (posF + tam) && i < (posC + tam); i++)
    {
        if(sopa[i][i] == pal[cont])
        {
            cont++;
        }
    }

    if(cont == tam)
    {
        esta = true;
        resp[0] = posF + 48;
        resp[1] = posC + 48;
        resp[2] = "Diagonal Abajo Derecha";
    }

    return esta;
}

bool buscarPalabraDBI(string pal, char sopa[][MAXC], int tamF, int tamC, int posF, int posC, string resp[])
{
    int cont = 0;
    int tam = pal.length();
    bool esta = false;
    for(int i = posF, j = posC; i < (posF + tam) && j > (posC - tam); i++, j--)
    {
        if(sopa[i][j] == pal[cont])
        {
            cont++;
        }
    }

    if(cont == tam)
    {
        esta = true;
        resp[0] = posF + 48;
        resp[1] = posC + 48;
        resp[2] = "Diagonal Abajo Izquierda";
    }

    return esta;
}
