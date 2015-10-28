#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

int main()
{
    ifstream flux;
    flux.open("palabras.txt", ios::in);

    stack<char*> minusculas;
    queue<char*> mayusculas;

    while(!flux.eof())
    {
        char* palabra = new char [100];
        flux.getline(palabra, 100);

        if(*(palabra+0) - 'Z' > 0)
        {
            minusculas.push(palabra);
        }
        else
        {
            mayusculas.push(palabra);
        }
    }

    cout << "Palabras en Minusculas:" << endl;
    while(!minusculas.empty())
    {
        cout << "- " << minusculas.top() << endl;
        minusculas.pop();
    }

    cout << endl << "Palabras en Mayusculas:" << endl;
    while(!mayusculas.empty())
    {
        cout << "- " << mayusculas.front() << endl;
        mayusculas.pop();
    }
}
