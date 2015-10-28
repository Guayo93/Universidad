#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>

using namespace std;

struct Candidato
{
    int codigo;
    char nombre[10];
    int numVotos;
};

bool estaPorId(Candidato* cs, int tam, int id)
{
    bool esta = false;

    for(int i = 0; i < tam && esta == false; i++)
    {
        if((cs+i)->codigo == id)
        {
            esta = true;
        }
    }

    return esta;
}

void agregarVotoPorId(Candidato* cs, int tam, int id)
{
    bool esta = false;

    for(int i = 0; i < tam && esta == false; i++)
    {
        if((cs+i)->codigo == id)
        {
            (cs+i)->numVotos += 1;
            esta = true;
        }
    }
}

int main()
{
    ifstream candidatos;
    ifstream votos;
    ofstream resultado;
    ofstream errores;

    candidatos.open("candidatos.bin", ios::in|ios::binary|ios::ate);
    votos.open("votos.txt", ios::in);
    resultado.open("resultado.txt", ios::out);
    errores.open("errores.txt", ios::out);

    Candidato* cands;
    int tamCands = 0;
    Candidato* errs;
    int tamErrs = 0;

    if(candidatos.is_open())
    {
        int tam = candidatos.tellg();
        tamCands = tam/14;
        cands = new Candidato [tamCands];
        candidatos.seekg(0, ios::beg);

        for(int i = 0; i < tamCands; i++)
        {
            Candidato c;
            candidatos.read((char*)&(c), 14);
            c.numVotos = 0;
            *(cands + i) = c;
        }

        if(votos.is_open())
        {
            char* voto = new char [10];

            while(!votos.eof())
            {
                votos.getline(voto, 10);
                int id = atoi(voto);

                if(!estaPorId(cands, tamCands, id))
                {
                    if(!estaPorId(errs, tamErrs, id))
                    {
                        Candidato c;
                        c.codigo = id;
                        strcpy(c.nombre, "Error");
                        c.numVotos = 1;

                        *(errs + tamErrs) = c;
                        tamErrs++;
                    }
                    else
                    {
                        agregarVotoPorId(errs, tamErrs, id);
                    }
                }
                else
                {
                    agregarVotoPorId(cands, tamCands, id);
                }
            }
        }
        else
        {
            cout << "El archivo votos.txt no pudo ser leido." << endl;
        }
    }
    else
    {
        cout << "El archivo candidatos.bin no pudo ser leido." << endl;
    }

    for(int i = 0; i < tamCands; i++)
    {
        resultado << cands->codigo << "," << cands->nombre << "," << cands->numVotos << endl;
    }

    for(int i = 0; i < tamErrs; i++)
    {
        resultado << errs->codigo << "," << errs->nombre << "," << errs->numVotos << endl;
    }
}
