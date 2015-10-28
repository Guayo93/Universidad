#include <iostream>
#include <cstdlib>

using namespace std;

//FUNCIONES
void imprimirSudoku(int s[][9]);
void llenarSudoku(int s[][9]);
bool verificarFila(int s[][9], int fila);
bool verificarColumna(int s[][9], int col);
bool verificarRegion(int s[][9], int region);

//MAIN
int main()
{
    int sudoku[9][9], op;
    bool fila, colu, regi;

    while(op != 5)
    {
        cout << "Que desea hacer?" << endl << "\t1. Llenar sudoku." << endl <<
            "\t2. Verificar filas." << endl <<
            "\t3. Verificar columnas." << endl <<
            "\t4. Verificar regiones." << endl <<
            "\t5. Salir." << endl;
        cin >> op;

        switch(op)
        {
            case 1:
                {
                    llenarSudoku(sudoku);
                    cout << "Asi quedo el sudoku: " << endl;
                    imprimirSudoku(sudoku);
                }
                break;
            case 2:
                {
                    int fil;
                    cout << "Que fila desea verificar?" << endl;
                    cin >> fil;
                    fila = verificarFila(sudoku, fil-1);
                    if(fila)
                    {
                        cout << "La fila " << fil << " es valida."<< endl;
                    }
                    else
                    {
                        cout << "La fila " << fil << " NO es valida."<< endl;
                    }
                }
                break;
            case 3:
                {
                    int col;
                    cout << "Que colmuna desea verificar?" << endl;
                    cin >> col;
                    colu = verificarColumna(sudoku, col-1);
                    if(colu)
                    {
                        cout << "La columna " << col << " es valida."<< endl;
                    }
                    else
                    {
                        cout << "La columna " << col << " NO es valida."<< endl;
                    }
                }
                break;
            case 4:
                {
                    int reg;
                    cout << "Que region desea verificar?" << endl;
                    cin >> reg;
                    regi = verificarRegion(sudoku, reg-1);
                    if(regi)
                    {
                        cout << "La region " << reg << " es valida."<< endl;
                    }
                    else
                    {
                        cout << "La region " << reg << " NO es valida."<< endl;
                    }
                }
                break;
            case 5:
                {
                    cout << "Gracias por jugar!" << endl;
                }
                break;
            default:
                cout << "BRUTO! Opcion invalida, vuelva a intentar." << endl;
                break;
        }
    }
}

//IMPRIMIR SUDOKU
void imprimirSudoku(int s[][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
}

//LLENAR SUDOKU
void llenarSudoku(int s[][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cout << "Que numero desea ingresar en el espacio " << i << "," << j << " ? (De 1 a 9)" << endl;
            cin >> s[i][j];
        }
    }
}

//VERIFICAR FILA
bool verificarFila(int s[][9], int fila)
{
    bool bien = true;
    for(int i = 0; i < 9 && bien; i++)
    {
        int ocurr = 0;
        for(int j = 0; j < 9; j++)
        {
            if(s[fila][j] == i+1)
            {
                ocurr++;
            }
        }

        if(ocurr != 1)
        {
            bien = false;
        }
    }

    return bien;
}

//VERIFICAR COLUMNA
bool verificarColumna(int s[][9], int col)
{
    bool bien = true;
    for(int i = 0; i < 9 && bien; i++)
    {
        int ocurr = 0;
        for(int j = 0; j < 9; j++)
        {
            if(s[j][col] == i+1)
            {
                ocurr++;
            }
        }

        if(ocurr != 1)
        {
            bien = false;
        }
    }

    return bien;
}

//VERIFICAR REGION
bool verificarRegion(int s[][9], int reg)
{
    bool bien = true;
    for(int i = 0; i < 9 && bien; i++)
    {
        int ocurr = 0;
        for(int j = (reg - 1) / 3; j < ((reg - 1) / 3) + 3; j++)
        {
            for(int k = (reg - 1) % 3; k < ((reg - 1) % 3) + 3; k++)
            {
                if(s[j][k] == i+1)
                {
                    ocurr++;
                }
            }
        }

        if(ocurr != 1)
        {
            bien = false;
        }
    }

    return bien;
}
