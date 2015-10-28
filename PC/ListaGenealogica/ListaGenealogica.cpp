#include <iostream>
#include "MultiLista.cpp"

using namespace std;

struct SInfoNieto
{
    char* nombre;
};

struct SInfoHijo
{
    char* nombre;
    Slista<SInfoNieto>* nietos;
};

struct SInfoPadre
{
    char* nombre;
    char* cargo;
    Slista<SInfoHijo>* hijos;
};

SInfoPadre* crearInfoPadre(char* nombre, char* cargo)
{
    SInfoPadre* infoPadre = new SInfoPadre;

    infoPadre->nombre = nombre;
    infoPadre->cargo = cargo;
    infoPadre->hijos = crearLista<SInfoHijo>();

    return infoPadre;
}

SInfoHijo* crearInfoHijo(char* nombre)
{
    SInfoHijo* infoHijo = new SInfoHijo;

    infoHijo->nombre = nombre;
    infoHijo->nietos = crearLista<SInfoNieto>();

    return infoHijo;
}

SInfoNieto* crearInfoNieto(char* nombre)
{
    SInfoNieto* infoNieto = new SInfoNieto;

    infoNieto->nombre = nombre;

    return infoNieto;
}

void imprimirLista(Slista<SInfoPadre>* lista)
{
    ///INICIA PADRE
    if(listaEstaVacia(lista) == true)
    {
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        Snodo<SInfoPadre>* nodo = lista->cabeza;

        while(esCola(nodo) == false)
        {
            ///INICIAN HIJOS
            cout << nodo->info->nombre << endl;
            cout << nodo->info->cargo << endl;

            Slista<SInfoHijo>* hijos = nodo->info->hijos;

            cout << "\tHijos: " << endl;
            if(listaEstaVacia(hijos) == true)
            {
                cout << "\tLa lista esta vacia" << endl;
            }
            else
            {
                Snodo<SInfoHijo>* nodoH = hijos->cabeza;

                while(esCola(nodoH) == false)
                {
                    ///INICIAN NIETOS
                    cout << "\t" << nodoH->info->nombre << endl;

                    Slista<SInfoNieto>* nietos = nodoH->info->nietos;
                    cout << "\t\tNietos: " << endl;
                    if(listaEstaVacia(nietos) == true)
                    {
                        cout << "\t\tLa lista esta vacia" << endl;
                    }
                    else
                    {
                        Snodo<SInfoNieto>* nodoN = nietos->cabeza;

                        while(esCola(nodoN) == false)
                        {
                            cout << "\t\t" << nodoN->info->nombre << endl;

                            nodoN = nodoN->sig;
                        }

                        ///ULTIMO NIETO
                        cout << "\t\t" << nietos->cola->info->nombre << endl;
                    }

                    nodoH = nodoH->sig;
                }

                ///ULTIMO HIJO
                cout << "\t" << hijos->cola->info->nombre << endl;

                Slista<SInfoNieto>* nietos = hijos->cola->info->nietos;
                cout << "\t\tNietos: " << endl;
                if(listaEstaVacia(nietos) == true)
                {
                    cout << "\t\tLa lista esta vacia" << endl;
                }
                else
                {
                    Snodo<SInfoNieto>* nodoN = nietos->cabeza;

                    while(esCola(nodoN) == false)
                    {
                        cout << "\t\t" << nodoN->info->nombre << endl;

                        nodoN = nodoN->sig;
                    }

                    cout << "\t\t" << nietos->cola->info->nombre << endl;
                }
            }

            nodo = nodo->sig;
        }

        ///ULTIMO PADRE
        cout << lista->cola->info->nombre << endl;
        cout << lista->cola->info->cargo << endl;

        Slista<SInfoHijo>* hijos = lista->cola->info->hijos;

        cout << "\tHijos: " << endl;
        if(listaEstaVacia(hijos) == true)
        {
            cout << "\tLa lista esta vacia" << endl;
        }
        else
        {
            ///HIJOS-ULTIMO PADRE
            Snodo<SInfoHijo>* nodoH = hijos->cabeza;

            while(esCola(nodoH) == false)
            {
                cout << "\t" << nodoH->info->nombre << endl;

                Slista<SInfoNieto>* nietos = nodoH->info->nietos;
                cout << "\t\tNietos: " << endl;
                if(listaEstaVacia(nietos) == true)
                {
                    cout << "\t\tLa lista esta vacia" << endl;
                }
                else
                {
                    ///NIETOS-ULTIMO PADRE
                    Snodo<SInfoNieto>* nodoN = nietos->cabeza;

                    while(esCola(nodoN) == false)
                    {
                        cout << "\t\t" << nodoN->info->nombre << endl;

                        nodoN = nodoN->sig;
                    }

                    ///ULTIMO NIETO-ULTIMO PADRE
                    cout << "\t\t" << nietos->cola->info->nombre << endl;
                }

                nodoH = nodoH->sig;
            }

            cout << "\t" << hijos->cola->info->nombre << endl;

            ///ULTIMO HIJO-ULTIMO PADRE
            Slista<SInfoNieto>* nietos = hijos->cola->info->nietos;
            cout << "\t\tNietos: " << endl;
            if(listaEstaVacia(nietos) == true)
            {
                cout << "\t\tLa lista esta vacia" << endl;
            }
            else
            {
                ///NIETOS-ULTIMO HIJO-ULTIMO PADRE
                Snodo<SInfoNieto>* nodoN = nietos->cabeza;

                while(esCola(nodoN) == false)
                {
                    cout << "\t\t" << nodoN->info->nombre << endl;

                    nodoN = nodoN->sig;
                }

                ///ULTIMO NIETO-ULTIMO HIJO-ULTIMO PADRE
                cout << "\t\t" << nietos->cola->info->nombre << endl;
            }
        }
    }
}

int main()
{
    Slista<SInfoPadre>* lista = crearLista<SInfoPadre>();

    ///PADRE
    SInfoPadre* infoPadre = crearInfoPadre("Alejo", "Fundador");
    agregarNodo(lista, infoPadre);
    ///HIJO 1
    SInfoHijo* infoHijo = crearInfoHijo("Carlos");
    agregarNodo(infoPadre->hijos, infoHijo);
    ///NIETO 1
    SInfoNieto* infoNieto = crearInfoNieto("Juliana");
    agregarNodo(infoHijo->nietos, infoNieto);
    ///NIETO 2
    infoNieto = crearInfoNieto("Carolina");
    agregarNodo(infoHijo->nietos, infoNieto);
    ///NIETO 3
    infoNieto = crearInfoNieto("Manuel");
    agregarNodo(infoHijo->nietos, infoNieto);
    ///HIJO 2
    infoHijo = crearInfoHijo("Pedro");
    agregarNodo(infoPadre->hijos, infoHijo);
    ///NIETO 1
    infoNieto = crearInfoNieto("Ricardo");
    agregarNodo(infoHijo->nietos, infoNieto);

    ///PADRE
    infoPadre = crearInfoPadre("Sandra", "Fundadora");
    agregarNodo(lista, infoPadre);
    ///HIJO
    infoHijo = crearInfoHijo("Manuel");
    agregarNodo(infoPadre->hijos, infoHijo);

    ///PADRE
    infoPadre = crearInfoPadre("David", "Presidente");
    agregarNodo(lista, infoPadre);

    imprimirLista(lista);
}
