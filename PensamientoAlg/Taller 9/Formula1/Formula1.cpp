#include <iostream>

using namespace std;

#define MAXC 25
#define MAXV 100
#define NOT 999

void ingresarDatos(int f1[][MAXV], int tamC, int tamV);
int tiempoParcial(int f1[][MAXV], int corr, int vuelta);
int corredoresRetirados(int f1[][MAXV], int tamC, int tamV);
int ganador(int f1[][MAXV], int tamC, int tamV);

int main()
{
    int formula1[MAXC][MAXV];
    int tamC, tamV;

    cout << "Cuantos corredores va a haber?" << endl;
    cin >> tamC;

    cout << "Cuantas vueltas van a haber?" << endl;
    cin >> tamV;

    int op;
    while(op != -1)
    {
        cout << "Usted que desea hacer?" << endl;
        cout << "   1. Ingresar Resultados.\n   2. Determinar tiempo parcial de algun corredor.\n   3.Determinar numero de corredores retirados.\n   4.Determinar el Ganador." << endl;
        cin >> op;
        switch(op)
        {
            case 1:
                ingresarDatos(formula1, tamC, tamV);
                break;

            case 2:
                {
                    int corr, vuelt;
                    cout << "Cual es el numero del corredor que desea averiguar?" << endl;
                    cin >> corr;
                    cout << "Hasta que vuelta desea averiguar?" << endl;
                    cin >> vuelt;
                    int parc = tiempoParcial(formula1, corr, vuelt);
                    cout << "El tiempo parcial del corredor numero " << corr << " hasta la vuelta " << vuelt << " es: " << parc << endl;
                }
                break;

            case 3:
                {
                    int ret = corredoresRetirados(formula1, tamC, tamV);
                    cout << "El numero de corredores retirados es: " << ret << endl;
                }
                break;

            case 4:
                {
                    int ganad = ganador(formula1, tamC, tamV);
                    cout << "El corredor ganador es el del numero: " << ganad << "!!" << endl;
                }
                break;

            default:
                cout << "Opcion no valida, porfavor vuelva a intentar." << endl;
                break;
        }
    }
}

void ingresarDatos(int f1[][MAXV], int tamC, int tamV)
{
    for(int i = 0; i < tamC; i++)
    {
        for(int j = 0; j < tamV; j++)
        {
            int op;
            cout << "Que tiempo (en segundos) desea para el corredor " << i << " en la vuelta " << j << "? (-1 para retirado)" << endl;
            cin >> op;
            if(op == -1)
            {
                f1[i][j] = NOT;
            }
            else
            {
                if(f1[i][j-1] == NOT)
                {
                    f1[i][j] = NOT;
                }
                else
                {
                    f1[i][j] = op;
                }
            }
        }
    }
}

int tiempoParcial(int f1[][MAXV], int corr, int vuelta)
{
    int resp = 0;
    for(int i = 0; i < vuelta; i++)
    {
        resp += f1[corr][i];
    }

    return resp;
}

int corredoresRetirados(int f1[][MAXV], int tamC, int tamV)
{
    int cont = 0;
    for(int i = 0; i < tamC; i++)
    {
        bool ret = false;
        for(int j = 0; j < tamV && ret == false; j++)
        {
            if(f1[i][j] == NOT)
            {
                ret = true;
                cont++;
            }
        }
    }

    return cont;
}

int ganador(int f1[][MAXV], int tamC, int tamV)
{
    int ganador = 0, tGan = tiempoParcial(f1, 0, tamV);
    for(int i = 1; i < tamC; i++)
    {
        int temp = tiempoParcial(f1, i, tamV);
        if(tGan > temp)
        {
            ganador = i;
            tGan = temp;
        }
    }

    return ganador;
}
