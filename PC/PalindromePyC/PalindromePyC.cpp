#include <iostream>
#include <stack>
#include <queue>
#include <string.h>

using namespace std;

bool esPalindrome(char* palabra)
{
    stack<char> pila;
    queue<char> cola;

    for(int i = 0; i < strlen(palabra); i++)
    {
        pila.push(*(palabra+i));
        cola.push(*(palabra+i));
    }

    bool resp = true;

    while(!pila.empty() && !cola.empty() && resp)
    {
        if(pila.top() != cola.front())
        {
            resp = false;
        }
        pila.pop();
        cola.pop();
    }

    return resp;
}

int main()
{
    char* palabra = new char [100];
    cout << "Palabra?" << endl;
    cin >> palabra;

    if(esPalindrome(palabra))
    {
        cout << "Es palindrome!!" << endl;
    }
    else
    {
        cout << "NO es palindrome!!" << endl;
    }
}
