#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <queue>

using namespace std;

int main()
{
    srand (time(NULL));

    ifstream eTxt;
    ifstream eDic;
    ofstream sVar;

    eTxt.open("texto.txt", ios::in);
    eDic.open("diccionario.txt", ios::in);
    sVar.open("variante.txt", ios::out);

    while(!eTxt.eof())
    {
        char* linea = new char [100];
        eTxt.getline(linea, 100);

        queue<char*> arrTxt;
        char* tmp;

        tmp = strtok(linea, " ,.-");

        while(tmp != NULL)
        {
            arrTxt.push(tmp);
            tmp = strtok(NULL, " ,.-");
        }

        while(!arrTxt.empty())
        {
            bool esta = false;

            char* palAct = arrTxt.front();

            queue<char*> arrDic;

            while(!eDic.eof() && esta == false)
            {
                queue<char*> arrTmp;

                char* lineaDic = new char [100];
                eDic.getline(lineaDic, 100);


                char* tmp2;
                tmp2 = strtok(lineaDic, ",");

                while(tmp2 != NULL)
                {
                    arrTmp.push(tmp2);
                    tmp2 = strtok(NULL, ",");
                }

                arrDic = arrTmp;

                while(!arrTmp.empty() && esta == false)
                {
                    if( strcmp(arrTmp.front(), palAct) == 0)
                    {
                        esta = true;
                    }

                    arrTmp.pop();
                }
            }

            if(esta == true)
            {
                int n = rand()%arrDic.size();
                for(int i = 0; i < n; i++)
                {
                    arrDic.pop();
                }

                sVar.write(arrDic.front(), strlen(arrDic.front()) + 1);
            }
            else
            {
                sVar.write(palAct, strlen(palAct) + 1);
            }

            arrTxt.pop();
            eDic.seekg(0, eDic.beg);
        }

        sVar << endl;
    }
}
