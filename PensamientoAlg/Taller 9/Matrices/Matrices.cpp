#include <iostream>

using namespace std;

#define MAXF 50
#define MAXC 50

void llenarMatrices(int m[][MAXC], int tamF, int tamC);
bool sonIdenticas(int mA[][MAXC], int mB[][MAXC], int tamFA, int tamCA, int tamFB, int tamCB);

int main()
{
    int mA[MAXF][MAXC], mB[MAXF][MAXC], tamFA, tamCA, tamFB, tamCB;

    cout << "Cuantas filas desea para la Matriz A?" << endl;
    cin >> tamFA;
    cout << "Cuantas columnas desea para la Matriz A?" << endl;
    cin >> tamCA;

    llenarMatrices(mA, tamFA, tamCA);

    cout << "Cuantas filas desea para la Matriz B?" << endl;
    cin >> tamFB;
    cout << "Cuantas columnas desea para la Matriz B?" << endl;
    cin >> tamCB;

    llenarMatrices(mB, tamFB, tamCB);

    bool identicas = sonIdenticas(mA, mB, tamFA, tamCA, tamFB, tamCB);

    if(identicas)
    {
        cout << "Las matrices A y B son identicas!" << endl;
    }
    else
    {
        cout << "Las matrices A y B NO son identicas!" <<endl;
    }
}

void llenarMatrices(int m[][MAXC], int tamF, int tamC)
{
    for(int i = 0; i < tamF; i++)
    {
        for(int j = 0; j < tamC; j++)
        {
            cout << "Que numero entero desea guardar en la posicion " << i << "," << j << "?" << endl;
            cin >> m[i][j];
        }
    }
}

bool sonIdenticas(int mA[][MAXC], int mB[][MAXC], int tamFA, int tamCA, int tamFB, int tamCB)
{
    bool iden = false;
    int cont = 0;
    if(tamFA == tamFB && tamCA == tamCB)
    {
        for(int i = 0; i < tamFA; i++)
        {
            for(int j = 0; j < tamCA; j++)
            {
                if(mA[i][j] == mB[i][j])
                {
                    cont++;
                }
            }
        }
    }

    if(cont == (tamFA*tamCA))
    {
        iden = true;
    }

    return iden;
}
