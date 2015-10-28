#include <iostream>

using namespace std;

void imprimirMatriz(int m[][3]);
void aplicarInversa(int mA[][3], int mB[][3]);
void aplicarTranspuesta(int mA[][3], int mB[][3]);

int main()
{
    int mA[3][3];
    int mB[3][3];

    int cont = 1, opcion;

    //Se llena la matriz de numeros
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            mA[i][j] = cont;
            cont++;
        }
    }

    cout << "Usted tiene una matriz de 3 x 3 que contiene los numeros de 1 a 9, como la siguiente: " << endl;

    imprimirMatriz(mA);

    cout << endl << "Usted que propiedad desea aplicar: " << endl << "1: Inversa.\n2: Transpuesta." << endl;
    cin >> opcion;

    if(opcion == 1)
    {
        aplicarInversa(mA, mB);
        cout << "La inversa de la matriz es: " << endl;
        imprimirMatriz(mB);
    }
    else if(opcion == 2)
    {
        aplicarTranspuesta(mA, mB);
        cout << "La transpuesta de la matriz es: " << endl;
        imprimirMatriz(mB);
    }
    else
    {
        cout << "Opcion incorrecta.";
    }
}

void imprimirMatriz(int m[][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

void aplicarInversa(int mA[][3], int mB[][3])
{

}

void aplicarTranspuesta(int mA[][3], int mB[][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            mB[j][i] = mA[i][j];
        }
    }
}
