#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int ciclo(int i, int maxi, int suma)
{
    if(i <= maxi)
    {
        suma += i;
        cout << i << "\t";
        i++;
        suma = ciclo(i, maxi, suma);
    }

    return suma;
}

void fibonacci(int lim, int vectFib[])
{
    if(lim == 0)
    {
        vectFib[0] = 0;
    }
    else if(lim == 1)
    {
        vectFib[1] = 1;
    }
    else
    {
        //cout << "entre" << vectFib[lim] << endl;
        if(vectFib[lim] == 0)
        {
            //cout << "entre" << lim << endl;
            fibonacci(lim-1, vectFib);
            fibonacci(lim-2, vectFib);

            // << "entre" << lim << endl;
            //cout << "entre" << lim << endl;

            vectFib[lim] = vectFib[lim-1] + vectFib[lim-2];
            //cout << lim << "\n" << vectFib[lim];
        }
    }
}

int main()
{
    int num;
    cin >> num;
    int* vectFib = new int[num+1];
    memset(vectFib, 0, 4*(num+1));

    fibonacci(num, vectFib);
    cout << vectFib[num];
}
