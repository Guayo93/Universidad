#include <iostream>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include <fstream>

using namespace std;

struct Vehiculo
{
    char* placa;
    char tipoVehiculo;
    struct tm* entrada;
    struct tm* salida;
};

struct Lugar
{
    Lugar* sig;
    Lugar* ant;
    Vehiculo* vehiculo;
    char tipoVehiculo;
    int numeroLugar;
};

struct Piso
{
    Piso* sig;
    Piso* ant;
    ///Lista 3 Cabezas
    Lugar* cabA;
    Lugar* colA;
    int numLugsA;
    Lugar* cabB;
    Lugar* colB;
    int numLugsB;
    Lugar* cabC;
    Lugar* colC;
    int numLugsC;
    int numLugaresTotal;
};

struct Parqueadero
{
    char* nombre;
    Piso* cabeza;
    Piso* cola;
    int numPisos;
    Vehiculo** vehiculosIngresados;
    int tamVehis;
};

/**
    Muestra el menu principal de la aplicacion
*/
int mostrarMenuPrincipal()
{
    int opcion;

    cout << endl << "Que desea hacer?" << endl
        << endl << "1. Iniciar un nuevo sistema." << endl
        << "2. Administrar sistema actual." << endl
        << "3. Cargar sistema." << endl
        << "4. Salir." << endl << endl;

    cin >> opcion;

    return opcion;
}

/**
    Muestra menu de administracion
*/
int mostrarMenuAdministrativo(Parqueadero* parqueadero)
{
    int opcion;

    cout << endl << "Bienvenido " << parqueadero->nombre << endl
        << endl << "Actualmente hay: "
        << endl << parqueadero->numPisos << " pisos disponibles."

        << endl << "Que desea hacer?" << endl
        << endl << "1. Agregar Piso."
        << endl << "2. Agregar Lugar a Piso."
        << endl << "3. Cambiar Tipo a Lugar en Piso."
        << endl << "4. Eliminar Piso."
        << endl << "5. Eliminar Lugar."
        << endl << "6. Ingresar Vehiculo."
        << endl << "7. Sacar Vehiculo."
        << endl << "8. Reporte de Vehiculos ingresados segun rango de Fechas."
        << endl << "9. Reporte Lugares Vacios."
        << endl << "10. Reporte Lugares Ocupados."
        << endl << "11. Guardar Sistema."
        << endl << "12. Salir." << endl << endl;

    cin >> opcion;

    return opcion;
}

Parqueadero* crearParqueadero(char* nombre)
{
    Parqueadero* p = new Parqueadero;

    p->cabeza = NULL;
    p->cola = NULL;

    p->nombre = nombre;
    p->numPisos = 0;

    p->vehiculosIngresados = new Vehiculo* [100];
    p->tamVehis = 0;

    return p;
}

Piso* crearPiso()
{
    Piso* p = new Piso;

    p->ant = NULL;
    p->sig = NULL;

    p->cabA = NULL;
    p->colA = NULL;
    p->numLugsA = 0;

    p->cabB = NULL;
    p->colB = NULL;
    p->numLugsB = 0;

    p->cabC = NULL;
    p->colC = NULL;
    p->numLugsC = 0;

    p->numLugaresTotal = 0;

    return p;
}

Lugar* crearLugar(char tipoVehiculo)
{
    Lugar* l = new Lugar;

    l->sig = NULL;
    l->ant = NULL;

    l->numeroLugar = 0;
    l->tipoVehiculo = tipoVehiculo;
    l->vehiculo = NULL;

    return l;
}

Vehiculo* crearVehiculo(char* placa, char tipoVehiculo, struct tm * entrada)
{
    Vehiculo* v = new Vehiculo;

    v->entrada = entrada;
    v->salida = NULL;
    v->placa = placa;
    v->tipoVehiculo = tipoVehiculo;

    return v;
}

Piso* buscarPiso(Parqueadero* parqueadero, int numPiso)
{
    Piso* p = NULL;

    if(numPiso <= parqueadero->numPisos)
    {
        Piso* tmp = parqueadero->cabeza;

        for(int i = 0; i < numPiso-1; i++)
        {
            tmp = tmp->sig;
        }

        p = tmp;
    }

    return p;
}

bool agregarPiso(Parqueadero* parqueadero)
{
    bool entra = false;

    if(parqueadero->cabeza == NULL)
    {
        Piso* p = crearPiso();
        parqueadero->cabeza = p;
        parqueadero->cola = p;
        parqueadero->numPisos++;

        entra = true;
    }
    else
    {
        Piso* p = crearPiso();

        parqueadero->cola->sig = p;
        p->ant = parqueadero->cola;
        parqueadero->cola = p;
        parqueadero->numPisos++;

        entra = true;
    }

    return entra;
}

bool eliminarPiso(Parqueadero* parqueadero, int numPiso)
{
    bool elimino = false;

    if(numPiso > 1)
    {
        Piso* p = buscarPiso(parqueadero, numPiso);

        if(p != NULL)
        {
            p->ant->sig = p->sig;
            if(p->sig != NULL)
            {
                p->sig->ant = p->ant;
            }
            p->sig = NULL;
            p->ant = NULL;

            delete p;

            parqueadero->numPisos -= 1;

            elimino = true;
        }
    }
    else
    {
        if(parqueadero->cabeza != NULL)
        {
            Piso* p = parqueadero->cabeza;

            if(p->sig != NULL)
            {
                parqueadero->cabeza = p->sig;
                p->sig->ant = NULL;

                p->sig = NULL;

                delete p;

                parqueadero->numPisos -= 1;

                elimino = true;
            }
            else
            {
                parqueadero->cabeza = NULL;

                delete p;

                parqueadero->numPisos -= 1;

                elimino = true;
            }
        }
    }

    return elimino;
}

Lugar* buscarLugar(Parqueadero* parqueadero, int numPiso, int numLugar)
{
    Piso* p = buscarPiso(parqueadero, numPiso);
    Lugar* l = NULL;

    if(numLugar <= p->numLugaresTotal)
    {
        bool esta = false;
        int pos = 0;

        Lugar* la = p->cabA;
        Lugar* lb = p->cabB;
        Lugar* lc = p->cabC;

        while(esta == false && la != NULL)
        {
            if(la->numeroLugar == numLugar)
            {
                l = la;
                esta = true;
            }
            else
            {
                la = la->sig;
            }
        }

        while(esta == false && lb != NULL)
        {
            if(lb->numeroLugar == numLugar)
            {
                l = lb;
                esta = true;
            }
            else
            {
                lb = lb->sig;
            }
        }

        while(esta == false && lc != NULL)
        {
            if(lc->numeroLugar == numLugar)
            {
                l = lc;
                esta = true;
            }
            else
            {
                lc = lc->sig;
            }
        }
    }

    return l;
}

Lugar* buscarLugarDesocupado(Piso* p, char tipoVehiculo)
{
    Lugar* l = NULL;

    if(tipoVehiculo == 'A' || tipoVehiculo == 'a')
    {
        l = p->cabA;
        bool sent = false;

        while(l != NULL && sent == false)
        {
            if(l->vehiculo == NULL)
            {
                sent = true;
            }
            else
            {
                l = l->sig;
            }
        }
    }

    if(tipoVehiculo == 'B' || tipoVehiculo == 'b')
    {
        l = p->cabB;
        bool sent = false;

        while(l != NULL && sent == false)
        {
            if(l->vehiculo == NULL)
            {
                sent = true;
            }
            else
            {
                l = l->sig;
            }
        }
    }

    if(tipoVehiculo == 'C' || tipoVehiculo == 'c')
    {
        l = p->cabC;
        bool sent = false;

        while(l != NULL && sent == false)
        {
            if(l->vehiculo == NULL)
            {
                sent = true;
            }
            else
            {
                l = l->sig;
            }
        }
    }

    return l;
}

bool agregarLugar(Parqueadero* parqueadero, int numPiso, char tipoVehiculo)
{
    bool entra = false;

    if(numPiso <= parqueadero->numPisos)
    {
        Piso* p = buscarPiso(parqueadero, numPiso);
        Lugar* l = crearLugar(tipoVehiculo);
        l->numeroLugar = p->numLugaresTotal + 1;

        if(tipoVehiculo == 'A' || tipoVehiculo == 'a')
        {
            if(p->numLugsA == 0)
            {
                p->cabA = l;
                p->colA = l;
                p->numLugsA += 1;
                p->numLugaresTotal += 1;

                cout << "El numero asignado para este lugar es: " << l->numeroLugar << "." << endl;

                entra = true;
            }
            else
            {
                p->colA->sig = l;
                p->colA = l;
                p->numLugsA += 1;
                p->numLugaresTotal += 1;

                cout << "El numero asignado para este lugar es: " << l->numeroLugar << "." << endl;

                entra = true;
            }
        }
        else if(tipoVehiculo == 'B' || tipoVehiculo == 'b')
        {
            if(p->numLugsB == 0)
            {
                p->cabB = l;
                p->colB = l;
                p->numLugsB += 1;
                p->numLugaresTotal += 1;

                cout << "El numero asignado para este lugar es: " << l->numeroLugar << "." << endl;

                entra = true;
            }
            else
            {
                p->colB->sig = l;
                p->colB = l;
                p->numLugsB += 1;
                p->numLugaresTotal += 1;

                cout << "El numero asignado para este lugar es: " << l->numeroLugar << "." << endl;

                entra = true;
            }
        }
        else if(tipoVehiculo == 'C' || tipoVehiculo == 'c')
        {
            if(p->numLugsC == 0)
            {
                p->cabC = l;
                p->colC = l;
                p->numLugsC += 1;
                p->numLugaresTotal += 1;

                cout << "El numero asignado para este lugar es: " << l->numeroLugar << "." << endl;

                entra = true;
            }
            else
            {
                p->colC->sig = l;
                p->colC = l;
                p->numLugsC += 1;
                p->numLugaresTotal += 1;

                cout << "El numero asignado para este lugar es: " << l->numeroLugar << "." << endl;

                entra = true;
            }
        }
    }

    return entra;
}

bool eliminarLugar(Parqueadero* parqueadero, int numPiso, int numLugar)
{
    bool elimino = false;

    if(numLugar > 1)
    {
        Lugar* l = buscarLugar(parqueadero, numPiso, numLugar);

        if(l != NULL)
        {
            l->ant->sig = l->sig;
            if(l->sig != NULL)
            {
                l->sig->ant = l->ant;
            }
            l->sig = NULL;
            l->ant = NULL;

            delete l;

            elimino = true;
        }
    }
    else
    {
        Piso* p = buscarPiso(parqueadero, numPiso);

        if(p->numLugaresTotal != 0)
        {
            Lugar* l = buscarLugar(parqueadero, numPiso, numLugar);

            if(l->tipoVehiculo == 'A' || l->tipoVehiculo == 'a')
            {
                if(l->sig != NULL)
                {
                    p->cabA = l->sig;
                    l->sig->ant = NULL;

                    l->sig = NULL;

                    delete l;

                    p->numLugsA -= 1;
                    p->numLugaresTotal -= 1;

                    elimino = true;
                }
                else
                {
                    p->cabA = NULL;
                    p->colA = NULL;

                    delete l;

                    p->numLugsA -= 1;
                    p->numLugaresTotal -= 1;

                    elimino = true;
                }
            }

            if(l->tipoVehiculo == 'B' || l->tipoVehiculo == 'b')
            {
                if(l->sig != NULL)
                {
                    p->cabB = l->sig;
                    l->sig->ant = NULL;

                    l->sig = NULL;

                    delete l;

                    p->numLugsB -= 1;
                    p->numLugaresTotal -= 1;

                    elimino = true;
                }
                else
                {
                    p->cabB = NULL;
                    p->colB = NULL;

                    delete l;

                    p->numLugsB -= 1;
                    p->numLugaresTotal -= 1;

                    elimino = true;
                }
            }

            if(l->tipoVehiculo == 'C' || l->tipoVehiculo == 'c')
            {
                if(l->sig != NULL)
                {
                    p->cabC = l->sig;
                    l->sig->ant = NULL;

                    l->sig = NULL;

                    delete l;

                    p->numLugsC -= 1;
                    p->numLugaresTotal -= 1;

                    elimino = true;
                }
                else
                {
                    p->cabC = NULL;
                    p->colC = NULL;

                    delete l;

                    p->numLugsC -= 1;
                    p->numLugaresTotal -= 1;

                    elimino = true;
                }
            }
        }
    }

    return elimino;
}

bool cambiarTipoLugar(Parqueadero* parqueadero, int numPiso, int numLugar, char nuevoTipo)
{
    Lugar* l = buscarLugar(parqueadero, numPiso, numLugar);

    if(l != NULL)
    {
        l->tipoVehiculo = nuevoTipo;

        return true;
    }
    else
    {
        return false;
    }
}

Vehiculo* buscarVehiculo(char* placa, Parqueadero* parqueadero)
{
    Vehiculo* v = NULL;
    if(parqueadero->numPisos != 0)
    {
        Piso* p = parqueadero->cabeza;
        bool esta = false;

        for(int i = 0; i < parqueadero->numPisos && esta == false; i++)
        {
            Lugar* l = p->cabA;

            for(int j = 0; j < p->numLugsA && esta == false; j++)
            {
                if(strcmp(l->vehiculo->placa, placa) == 0)
                {
                    v = l->vehiculo;
                    esta = true;
                }

                l = l->sig;
            }

            l = p->cabB;

            for(int j = 0; j < p->numLugsB && esta == false; j++)
            {
                if(strcmp(l->vehiculo->placa, placa) == 0)
                {
                    v = l->vehiculo;
                    esta = true;
                }

                l = l->sig;
            }

            l = p->cabC;

            for(int j = 0; j < p->numLugsC && esta == false; j++)
            {
                if(strcmp(l->vehiculo->placa, placa) == 0)
                {
                    v = l->vehiculo;
                    esta = true;
                }

                l = l->sig;
            }

            p = p->sig;
        }
    }

    return v;
}

bool ingresoVehiculo(char* placa, char tipoVehiculo, struct tm * entrada, Parqueadero* parqueadero, int numPiso)
{
    Piso* p = buscarPiso(parqueadero, numPiso);

    if(p != NULL)
    {
        Vehiculo* v = crearVehiculo(placa, tipoVehiculo, entrada);

        Lugar* l = buscarLugarDesocupado(p, tipoVehiculo);

        if(l != NULL)
        {
            l->vehiculo = v;

            cout << "El vehiculo ingreso en el piso " << numPiso << " y en el lugar numero " << l->numeroLugar << "." << endl;
            return true;
        }
        else
        {
            delete v;
            cout << "No hay lugares disponibles en este piso para ese tipo de vehiculo." << endl;
        }
    }

    return false;
}

bool salidaVehiculo(char* placa, Parqueadero* parqueadero, int numLugar, int numPiso)
{
    bool sale = false;

    Vehiculo* v = buscarVehiculo(placa, parqueadero);

    if(v != NULL)
    {
        Lugar* l = buscarLugar(parqueadero, numPiso, numLugar);

        if(l != NULL)
        {
            time_t rawT;
            struct tm * salida;

            time(&rawT);
            salida = localtime(&rawT);

            v->salida = salida;

            l->vehiculo = NULL;
            *(parqueadero->vehiculosIngresados + parqueadero->tamVehis) = v;
            parqueadero->tamVehis += 1;
            sale = true;

            cout << "La fecha y hora de salida es " << asctime(salida) << endl;
        }
    }

    return sale;
}

void reporteVehiculosPorFecha(Parqueadero* parqueadero, struct tm * fechaInicio, struct tm * fechaFin)
{
    system("CLS");

    //cout << "Vehiculos que ingresaron entre las fechas " << asctime(fechaInicio) << " y " << asctime(fechaFin) << ":" << endl;

    for(int i = 0; i < parqueadero->tamVehis; i++)
    {
        Vehiculo* v = *(parqueadero->vehiculosIngresados + i);

        if(difftime(mktime(fechaFin), mktime(v->entrada)) > 0 )
        {
            cout << "Placa: " << v->placa << endl << "Tipo de Vehiculo: " << v->tipoVehiculo << endl;
        }
    }
}

void reporteLugaresVaciosPantalla(Parqueadero* parqueadero)
{
    Piso* p = parqueadero->cabeza;
    int suma = 0;

    for(int i = 0; i < parqueadero->numPisos; i++)
    {
        Lugar* l = p->cabA;

        while(l != NULL)
        {
            if(l->vehiculo == NULL)
            {
                suma++;
                cout << "El lugar numero " << l->numeroLugar << " del piso " << i+1 << " esta vacio. El lugar es de tipo " << l->tipoVehiculo << "." << endl;
            }

            l = l->sig;
        }

        l = p->cabB;

        while(l != NULL)
        {
            if(l->vehiculo == NULL)
            {
                suma++;
                cout << "El lugar numero " << l->numeroLugar << " del piso " << i+1 << " esta vacio. El lugar es de tipo " << l->tipoVehiculo << "." << endl;
            }

            l = l->sig;
        }

        l = p->cabC;

        while(l != NULL)
        {
            if(l->vehiculo == NULL)
            {
                suma++;
                cout << "El lugar numero " << l->numeroLugar << " del piso " << i+1 << " esta vacio. El lugar es de tipo " << l->tipoVehiculo << "." << endl;
            }

            l = l->sig;
        }

        p = p->sig;
    }

    cout << "Dentro del parqueadero se tienen " << suma << " lugares vacios." << endl;
}

void reporteLugaresVaciosArchivo(Parqueadero* parqueadero, ofstream &repVac)
{
    Piso* p = parqueadero->cabeza;

    for(int i = 0; i < parqueadero->numPisos; i++)
    {
        Lugar* l = p->cabA;

        while(l != NULL)
        {
            if(l->vehiculo == NULL)
            {
                repVac << endl << "<tr>"
                    << endl << "<td>" << i+1 << "</td>"
                    << endl << "<td>" << l->numeroLugar << "</td>"
                    << endl << "<td>" << l->tipoVehiculo << "</td"
                    << endl << "</tr>" << endl;
            }

            l = l->sig;
        }

        l = p->cabB;

        while(l != NULL)
        {
            if(l->vehiculo == NULL)
            {
                repVac << endl << "<tr>"
                    << endl << "<td>" << i+1 << "</td>"
                    << endl << "<td>" << l->numeroLugar << "</td>"
                    << endl << "<td>" << l->tipoVehiculo << "</td"
                    << endl << "</tr>" << endl;
            }

            l = l->sig;
        }

        l = p->cabC;

        while(l != NULL)
        {
            if(l->vehiculo == NULL)
            {
                repVac << endl << "<tr>"
                    << endl << "<td>" << i+1 << "</td>"
                    << endl << "<td>" << l->numeroLugar << "</td>"
                    << endl << "<td>" << l->tipoVehiculo << "</td"
                    << endl << "</tr>" << endl;
            }

            l = l->sig;
        }

        p = p->sig;
    }

    repVac << "</table>" << endl << "</body>" << endl << "</html>" << endl;
}

void reporteLugaresOcupadosPantalla(Parqueadero* parqueadero)
{
    Piso* p = parqueadero->cabeza;
    int suma = 0;

    for(int i = 0; i < parqueadero->numPisos; i++)
    {
        Lugar* l = p->cabA;

        while(l != NULL)
        {
            if(l->vehiculo != NULL)
            {
                suma++;
                cout << "El lugar numero " << l->numeroLugar << " del piso " << i+1 << " esta ocupado por el vehiculo de placa " << l->vehiculo->placa << "." << endl;
            }

            l = l->sig;
        }

        l = p->cabB;

        while(l != NULL)
        {
            if(l->vehiculo != NULL)
            {
                suma++;
                cout << "El lugar numero " << l->numeroLugar << " del piso " << i+1 << " esta ocupado por el vehiculo de placa " << l->vehiculo->placa << "." << endl;
            }

            l = l->sig;
        }

        l = p->cabC;

        while(l != NULL)
        {
            if(l->vehiculo != NULL)
            {
                suma++;
                cout << "El lugar numero " << l->numeroLugar << " del piso " << i+1 << " esta ocupado por el vehiculo de placa " << l->vehiculo->placa << "." << endl;
            }

            l = l->sig;
        }

        p = p->sig;
    }

    cout << "Dentro del parqueadero se tienen " << suma << " lugares ocupados." << endl;
}

void reporteLugaresOcupadosArchivo(Parqueadero* parqueadero, ofstream &repOcu)
{
    Piso* p = parqueadero->cabeza;

    for(int i = 0; i < parqueadero->numPisos; i++)
    {
        Lugar* l = p->cabA;

        while(l != NULL)
        {
            if(l->vehiculo != NULL)
            {
                repOcu << endl << "<tr>"
                    << endl << "<td>" << i+1 << "</td>"
                    << endl << "<td>" << l->numeroLugar << "</td>"
                    << endl << "<td>" << l->vehiculo->placa << "</td>"
                    << endl << "<td>" << l->tipoVehiculo << "</td"
                    << endl << "</tr>" << endl;
            }

            l = l->sig;
        }

        l = p->cabB;

        while(l != NULL)
        {
            if(l->vehiculo != NULL)
            {
                repOcu << endl << "<tr>"
                    << endl << "<td>" << i+1 << "</td>"
                    << endl << "<td>" << l->numeroLugar << "</td>"
                    << endl << "<td>" << l->vehiculo->placa << "</td>"
                    << endl << "<td>" << l->tipoVehiculo << "</td"
                    << endl << "</tr>" << endl;
            }

            l = l->sig;
        }

        l = p->cabC;

        while(l != NULL)
        {
            if(l->vehiculo != NULL)
            {
                repOcu << endl << "<tr>"
                    << endl << "<td>" << i+1 << "</td>"
                    << endl << "<td>" << l->numeroLugar << "</td>"
                    << endl << "<td>" << l->vehiculo->placa << "</td>"
                    << endl << "<td>" << l->tipoVehiculo << "</td"
                    << endl << "</tr>" << endl;
            }

            l = l->sig;
        }

        p = p->sig;
    }

    repOcu << "</table>" << endl << "</body>" << endl << "</html>" << endl;
}

void guardarSistema(Parqueadero* parqueadero, fstream &sistema)
{
    sistema.write((char*) parqueadero, sizeof(parqueadero));
}

void cargarSistema(Parqueadero* parqueadero, fstream &sistema)
{
    int tam = 0;
    sistema.seekg(0, ios::end);
    tam = sistema.tellg();
    sistema.seekg(0, ios::beg);

    if(tam != 0)
    {
        sistema.read((char*) parqueadero, tam);
    }
    else
    {
        cout << "El archivo sistema esta vacio." << endl;
    }
}

int main()
{
    fstream sistema;
    sistema.open("sistema.bin", fstream::in | fstream::out | fstream::binary);

    ofstream repVac;
    repVac.open("reporteVacios.txt", ios::out | ios::app);

    ofstream repOcu;
    repOcu.open("reporteOcupados.txt", ios::out | ios::app);

    Parqueadero* parqueadero = NULL;
    int opcion;

    while(opcion != 4)
    {
        system("CLS");

        cout << "Bienvenido a Severa Flor Parking Software ( Nombre Tentativo :3 )" << endl;

        opcion = mostrarMenuPrincipal();

        switch(opcion)
        {
            case 1:
                {
                    delete parqueadero;

                    int numPisos;

                    system("CLS");

                    cout << "Cual sera el nombre del parqueadero?" << endl;
                    char* nombre = new char [100];
                    cin >> nombre;

                    parqueadero = crearParqueadero(nombre);

                    system("CLS");

                    cout << "Cuantos pisos habra inicialmente?" << endl;
                    cin >> numPisos;

                    system("CLS");

                    for(int i = 0; i < numPisos; i++)
                    {
                        bool agrego = agregarPiso(parqueadero);

                        if(agrego == true)
                        {
                            cout << "Se ha añadido el piso numero " << i+1 << endl;
                        }
                        else
                        {
                            cout << "El piso numero " << i+1 << " ha fallado en ser agregado" << endl;
                        }
                    }

                    system("PAUSE");

                    system("CLS");

                    cout << "Creo que eso seria todo :3" << endl;

                    system("PAUSE");

                }
            break;

            case 2:
                {
                    system("CLS");

                    if(parqueadero != NULL)
                    {
                        int opAd;

                        while(opAd != 12)
                        {
                            system("CLS");

                            opAd = mostrarMenuAdministrativo(parqueadero);

                            switch(opAd)
                            {
                                case 1:
                                    {
                                        system("CLS");

                                        bool entro = agregarPiso(parqueadero);

                                        if(entro)
                                        {
                                            cout << "Se ha agregado un piso al sistema." << endl;
                                        }
                                        else
                                        {
                                            cout << "Hubo error al ingresar el piso." << endl;
                                        }

                                        system("PAUSE");
                                    }
                                    break;

                                case 2:
                                    {
                                        system("CLS");

                                        int numPiso;
                                        char tipoVehiculo;

                                        cout << "A que piso desea agregar el lugar?" << endl;
                                        cin >> numPiso;

                                        cout << "Que tipo de vehiculo almacenara el lugar?" << endl;
                                        cin >> tipoVehiculo;

                                        bool entro = agregarLugar(parqueadero, numPiso, tipoVehiculo);

                                        if(entro)
                                        {
                                            cout << "Se ha agregado un lugar al piso " << numPiso << " de tipo " << tipoVehiculo << " satisfactoriamente." << endl;
                                        }
                                        else
                                        {
                                            cout << "Hubo un error al ingresar el lugar." << endl;
                                        }

                                        system("PAUSE");
                                    }
                                    break;

                                case 3:
                                    {
                                        system("CLS");

                                        char nuevoTipo;
                                        int numPiso, numLugar;

                                        cout << "De cual piso es el lugar?" << endl;
                                        cin >> numPiso;

                                        cout << "Cual es el numero del lugar?" << endl;
                                        cin >> numLugar;

                                        cout << "Cual nuevo tipo sera asignado?" << endl;
                                        cin >> nuevoTipo;

                                        bool cambio = cambiarTipoLugar(parqueadero, numPiso, numLugar, nuevoTipo);

                                        if(cambio)
                                        {
                                            cout << "El tipo del lugar numero " << numLugar << " del piso " << numPiso  << " ha sido cambiado a " << nuevoTipo << "." << endl;
                                        }
                                        else
                                        {
                                            cout << "Hubo un error al cambiar el tipo del lugar." << endl;
                                        }

                                        system("PAUSE");
                                    }
                                    break;

                                case 4:
                                    {
                                        system("CLS");

                                        int numPiso;

                                        cout << "Que piso desea eliminar?" << endl;
                                        cin >> numPiso;

                                        bool elimino = eliminarPiso(parqueadero, numPiso);

                                        if(elimino)
                                        {
                                            cout << "El piso se ha eliminado satisfactoriamente." << endl;
                                        }
                                        else
                                        {
                                            cout << "Hubo un error al eliminar el piso." << endl;
                                        }

                                        system("PAUSE");
                                    }
                                    break;

                                case 5:
                                    {
                                        system("CLS");

                                        int numPiso, numLugar;

                                        cout << "En que piso se encuentra el lugar?" << endl;
                                        cin >> numPiso;

                                        cout << "Cual es el numero del lugar a eliminar?" << endl;
                                        cin >> numLugar;

                                        bool elimino = eliminarLugar(parqueadero, numPiso, numLugar);

                                        if(elimino)
                                        {
                                            cout << "El lugar numero " << numLugar << " del piso " << numPiso << " ha sido eliminado." << endl;
                                        }
                                        else
                                        {
                                            cout << "Hubo un error al eliminar el lugar." << endl;
                                        }

                                        system("PAUSE");
                                    }
                                    break;

                                case 6:
                                    {
                                        system("CLS");

                                        time_t rawT;
                                        struct tm * entrada;
                                        char* placa = new char [100];
                                        char tipoVehiculo;
                                        int numPiso;

                                        cout << "Cual es la placa del vehiculo?" << endl;
                                        cin >> placa;

                                        cout << "Cual es el tipo del vehiculo?" << endl;
                                        cin >> tipoVehiculo;

                                        cout << "En que piso desea guardar el vehiculo?" << endl;
                                        cin >> numPiso;

                                        time(&rawT);
                                        entrada = localtime(&rawT);

                                        bool entra = ingresoVehiculo(placa, tipoVehiculo, entrada, parqueadero, numPiso);

                                        if(entra)
                                        {
                                            cout << "La fecha y hora de ingreso es " << asctime(entrada) << endl;
                                            cout << "El vehiculo de placa " << placa << " ha ingresado correctamente." << endl;
                                        }
                                        else
                                        {
                                            cout << "Hubo un error al ingresar el vehiculo." << endl;
                                        }

                                        system("PAUSE");
                                    }
                                    break;

                                case 7:
                                    {
                                        int numPiso;
                                        int numLugar;
                                        char* placa = new char [100];

                                        cout << "Cual es la placa del vehiculo que desea sacar?" << endl;
                                        cin >> placa;

                                        cout << "En que piso se encuentra el vehiculo?" << endl;
                                        cin >> numPiso;

                                        cout << "En que lugar se encuentra el vehiculo?" << endl;
                                        cin >> numLugar;

                                        bool salio = salidaVehiculo(placa, parqueadero, numLugar, numPiso);

                                        if(salio)
                                        {
                                            cout << "El vehiculo salio satisfactoriamente y el lugar vuelve a estar disnible." << endl;
                                        }
                                        else
                                        {
                                            cout << "Hubo un error al sacar el vehiculo." << endl;
                                        }
                                    }
                                    break;

                                case 8:
                                    {
                                        system("CLS");

                                        int anio1, mes1, dia1, anio2, mes2, dia2;
                                        struct tm * fecha1;
                                        struct tm * fecha2;
                                        fecha1 = new tm;
                                        fecha2 = new tm;

                                        cout << "Cual es el año de la fecha de inicio?" << endl;
                                        cin >> anio1;

                                        cout << "Cual es el mes de la fecha de inicio?" << endl;
                                        cin >> mes1;

                                        cout << "Cual es el dia de la fecha de inicio?" << endl;
                                        cin >> dia1;

                                        cout << "Cual es el año de la fecha de fin?" << endl;
                                        cin >> anio2;

                                        cout << "Cual es el mes de la fecha de fin?" << endl;
                                        cin >> mes2;

                                        cout << "Cual es el dia de la fecha de fin?" << endl;
                                        cin >> dia2;

                                        fecha1->tm_year = (anio1 - 1900);
                                        fecha1->tm_mon = mes1 - 1;
                                        fecha1->tm_mday = dia1;
                                        fecha1->tm_hour = 0;
                                        fecha1->tm_min = 0;
                                        fecha1->tm_sec = 0;

                                        fecha2->tm_year = (anio2 - 1900);
                                        fecha2->tm_mon = mes2 - 1;
                                        fecha2->tm_mday = dia2;
                                        fecha2->tm_hour = 0;
                                        fecha2->tm_min = 0;
                                        fecha2->tm_sec = 0;

                                        reporteVehiculosPorFecha(parqueadero, fecha1, fecha2);

                                        system("PAUSE");
                                    }
                                    break;

                                case 9:
                                    {
                                        system("CLS");

                                        int op;

                                        cout << "De que manera desea saber los lugares vacios? (1. Pantalla, 2. Archivo)" << endl;
                                        cin >> op;

                                        if(op == 1)
                                        {
                                            reporteLugaresVaciosPantalla(parqueadero);
                                        }
                                        else if(op == 2)
                                        {
                                            reporteLugaresVaciosArchivo(parqueadero, repVac);
                                            cout << "El archivo de reporte ha sido generado." << endl;
                                        }
                                        else
                                        {
                                            cout << "Error de pedido. Vuelva a intentar." << endl;
                                        }

                                        system("PAUSE");
                                    }
                                    break;

                                case 10:
                                    {
                                        system("CLS");

                                        int op;

                                        cout << "De que manera desea saber los lugares ocupados? (1. Pantalla, 2. Archivo)" << endl;
                                        cin >> op;

                                        if(op == 1)
                                        {
                                            reporteLugaresOcupadosPantalla(parqueadero);
                                        }
                                        else if(op == 2)
                                        {
                                            reporteLugaresOcupadosArchivo(parqueadero, repOcu);
                                        }
                                        else
                                        {
                                            cout << "Error de pedido. Vuelva a intentar." << endl;
                                        }

                                        system("PAUSE");
                                    }
                                    break;

                                case 11:
                                    {
                                        guardarSistema(parqueadero, sistema);
                                    }
                                    break;

                                case 12:
                                    break;

                                default:
                                    {
                                        cout << "Error de seleccion. Por favor vuelva a intentarlo." << endl;
                                    }
                                    break;
                            }
                        }
                    }
                    else
                    {
                        cout << "El Sistema no ha sido inicializado. Intentelo denuevo despues de haberlo hecho." << endl;
                    }


                    system("PAUSE");
                }
            break;

            case 3:
                {
                    system("CLS");

                    cargarSistema(parqueadero, sistema);

                    system("PAUSE");
                }
            break;

            case 4:
                break;

            default:
                {
                    cout << "Error de seleccion. Por favor vuelva a intentarlo." << endl;
                }
                break;
        }
    }
}
