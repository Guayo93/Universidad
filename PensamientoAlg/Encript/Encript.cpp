#include <iostream>
#include <string.h>

using namespace std;

string encrypt(string frase, string llave);
string desencrypt(string frase, string llave);
string decimalABinario(int num);
int binarioADecimal(string num);

int main()
{
     string frase, nuevaFrase, llave;
     int op;

     while(op != 3)
     {
         cout << "Que desea hacer?" << endl <<
            "\t1. Encriptar." << endl <<
            "\t2. DesEncriptar." << endl <<
            "\t3. Salir." << endl;
         cin >> op;
         switch(op)
         {
             case 1:
                {
                    cout << "Que frase desea encriptar?" << endl;
                    cin.ignore();
                    getline(cin, frase);
                    cout << "Cual es la llave de encripcion?" << endl;
                    cin >> llave;
                    nuevaFrase = encrypt(frase, llave);
                    for(int i = 0; (unsigned)i < nuevaFrase.length(); i++)
                    {
                        if(nuevaFrase[i] != ' ')
                        {
                            cout << decimalABinario(nuevaFrase[i]);
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                    cout << endl;
                }
                break;
             case 2:
                {
                    cout << "Que frase desea desencriptar?" << endl;
                    getline(cin, frase);
                    cout << "Cual fue la llave de encripcion?" << endl;
                    cin >> llave;
                    encrypt(frase, llave);
                }
                break;
             case 3:
                cout << "Gracias por usar la herramienta!" << endl;
                break;
             default:
                cout << "BRUTO! Opcion invalida, vuelva a intentar." << endl;
                break;
         }
     }
}

string encrypt(string frase, string llave)
{
    int ascii, numLL, numFin;
    string resp = frase;
    for(int i = 0; (unsigned)i < frase.length(); i++)
    {
        if(frase[i] != ' ')
        {
            ascii = frase[i];
            numLL = llave[1] - 48;
            if(llave[0] == 'i' || llave[0] == 'I')
            {
                numFin = ascii - numLL;
                if(numFin < 97)
                {
                    int temp = ((97 - numFin) * (-1));
                    numFin = 122 - temp;
                }
            }
            if(llave[0] == 'd' || llave[0] == 'D')
            {
                numFin = ascii + numLL;
                if(numFin > 122)
                {
                    int temp = ((122 - numFin) * (-1));
                    numFin = 97 + temp;
                }
            }
            char respC = numFin;
            resp[i] = respC;
        }
        else
        {
            resp[i] = ' ';
        }
    }

    return resp;
}

string desencrypt(string frase, string llave)
{
    return "";
}

string decimalABinario(int num)
{
    if ( num == 0 )
    {
        return "0";
    }
    if ( num == 1 )
    {
        return "1";
    }

    if ( num % 2 == 0 )
    {
        return decimalABinario(num / 2) + "0";
    }
    else
    {
        return decimalABinario(num / 2) + "1";
    }
}

int binarioADecimal(string num)
{
    int result = 0, pow = 1;
    for ( int i = num.length() - 1; i >= 0; --i, pow <<= 1 )
    {
        result += (num[i] - '0') * pow;
    }

    return result;
}
