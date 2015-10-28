#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

void rellenoInicial(stack<int> &torre, int num)
{
	for(int i = num; i > 0; i--)
	{
		torre.push(i);
	}
}

void imprimirTorre(stack<int> torre)
{
	while(!torre.empty())
	{
		cout << torre.top() << endl;
		torre.pop();
	}
}

void estadoActual(stack<int> torre1, stack<int> torre2, stack<int> torre3)
{
	cout << "Torre 1" << endl;
	imprimirTorre(torre1);

	cout << "Torre 2" << endl;
	imprimirTorre(torre2);

	cout << "Torre 3" << endl;
	imprimirTorre(torre3);
}

int torreAMover(stack<int> torre1, stack<int> torre2, stack<int> torre3, int ultimaTorre)
{
	if(ultimaTorre == 1)
	{
		int temp1 = 0;
		if(!torre2.empty())
		{
			temp1 = torre2.top();
		}
		int temp2 = 0;
		if(!torre3.empty())
		{
			temp2 = torre3.top();
		}

		if(temp1 < temp2)
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}
	else if(ultimaTorre == 2)
	{
		int temp1 = 0;
		if(!torre1.empty())
		{
			temp1 = torre1.top();
		}
		int temp2 = 0;
		if(!torre3.empty())
		{
			temp2 = torre3.top();
		}

		if(temp1 < temp2)
		{
			return 1;
		}
		else
		{
			return 3;
		}
	}
	else if(ultimaTorre == 3)
	{
		int temp1 = 0;
		if(torre1.empty() == false)
		{
			temp1 = torre1.top();
		}
		int temp2 = 0;
		if(torre2.empty() == false)
		{
			temp2 = torre2.top();
		}

		if(temp1 < temp2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else
    {
        return 1;
    }
}

int mover(stack<int> &torre1, stack<int> &torre2, stack<int> &torre3, int tAMover, int nDiscos)
{
	if(tAMover == 1)
	{
		int discoActual = torre1.top();
		torre1.pop();

		int disco1 = nDiscos;
		if(!torre2.empty())
		{
			disco1 = torre2.top();
		}

		int disco2 = nDiscos;
		if(!torre3.empty())
		{
			disco2 = torre3.top();
		}

		if(disco1 > discoActual && disco2 > discoActual)
		{
			torre2.push(discoActual);
			return 2;
		}
		else if(disco1 > discoActual && disco2 < discoActual)
		{
			torre2.push(discoActual);
			return 2;
		}
		else if(disco1 < discoActual && disco2 > discoActual)
		{
			torre3.push(discoActual);
			return 3;
		}
	}

	else if(tAMover == 2)
	{
		int discoActual = torre2.top();
		torre2.pop();

		int disco1 = nDiscos;
		if(!torre1.empty())
		{
			disco1 = torre1.top();
		}

		int disco2 = nDiscos;
		if(!torre3.empty())
		{
			disco2 = torre3.top();
		}

		if(disco1 > discoActual && disco2 > discoActual)
		{
			torre3.push(discoActual);
			return 3;
		}
		else if(disco1 > discoActual && disco2 < discoActual)
		{
			torre1.push(discoActual);
			return 1;
		}
		else if(disco1 < discoActual && disco2 > discoActual)
		{
			torre3.push(discoActual);
			return 3;
		}
	}

	else if(tAMover == 3)
	{
		int discoActual = torre3.top();
		torre3.pop();

		int disco1 = nDiscos;
		if(!torre1.empty())
		{
			disco1 = torre1.top();
		}

		int disco2 = nDiscos;
		if(!torre2.empty())
		{
			disco2 = torre2.top();
		}

		if(disco1 > discoActual && disco2 > discoActual)
		{
			torre1.push(discoActual);
			return 1;
		}
		else if(disco1 > discoActual && disco2 < discoActual)
		{
			torre1.push(discoActual);
			return 1;
		}
		else if(disco1 < discoActual && disco2 > discoActual)
		{
			torre2.push(discoActual);
			return 2;
		}
	}
}

int main()
{
	int numDiscos, ultimaTorre = 4;
	bool termino = false;

	stack<int> torre1;
	stack<int> torre2;
	stack<int> torre3;

	cout << "Cuantos discos se van a utilizar?" << endl;
	cin >> numDiscos;

	//system("CLS");

	rellenoInicial(torre1, numDiscos);

	estadoActual(torre1, torre2, torre3);
	cout << endl;

    int cont = 1;
	while(torre1.empty() == false || torre2.empty() == false)
	{
	    cout << "Paso #" << cont << endl;
		int tAMover = torreAMover(torre1, torre2, torre3, ultimaTorre);
		ultimaTorre = mover(torre1, torre2, torre3, tAMover, numDiscos + 1);
		estadoActual(torre1, torre2, torre3);
		cont++;
		cout << endl;
	}

	cout << "FIN! :D" << endl;
}
