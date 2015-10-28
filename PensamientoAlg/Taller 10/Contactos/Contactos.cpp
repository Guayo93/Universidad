#include <iostream>

using namespace std;

//CONSTANTES
#define CMAX 100
#define ELIM "ELI"
#define ELIN 999

//ESTRUCTURAS
struct fecha
{
    int dd;
    int mm;
    int aa;
};

struct contacto
{
    string nombre;
    string apellido;
    string correo;
    string direccion;
    int telefono;
    fecha fnac;
};

//DECLARACION DE FUNCIONES
void crearContacto(contacto agenda[CMAX], string nom, string ape, string cor, string dir, int tel, fecha fnac, int pos);
void eliminarContacto(contacto agenda[CMAX], int pos);
void verContactos(contacto agenda[CMAX], int tamAgenda);
void ordenarPorApellido(contacto agenda[CMAX], int tamAgenda);
void ordenarPorCorreo(contacto agenda[CMAX], int tamAgenda);
void ordenarPorFechaNacimiento(contacto agenda[CMAX], int tamAgenda);

//MAIN
int main()
{
    contacto agenda[CMAX];
    int tamAgenda = 0, tamTot = 0, op;

    while(op != 5)
    {
        cout << "Que desea hacer?" << endl <<
            "\t1. Crear contacto." << endl <<
            "\t2. Eliminar contacto." << endl <<
            "\t3. Ver contactos." << endl <<
            "\t4. Ordenar contactos." << endl <<
            "\t5. Salir." << endl;
        cin >> op;

        switch(op)
        {
            case 1:
                {
                    string nom, ape, dir, cor;
                    int dd, aa, mm, tel;
                    fecha fnac;
                    cout << "Ingrese el nombre:" << endl;
                    cin >> nom;
                    cout << "Ingrese el apellido:" << endl;
                    cin >> ape;
                    cout << "Ingrese el correo:" << endl;
                    cin >> cor;
                    cout << "Ingrese la direccion:" << endl;
                    cin >> dir;
                    cout << "Ingrese el telefono:" << endl;
                    cin >> tel;
                    cout << "Ingrese el dia de nacimiento:" << endl;
                    cin >> dd;
                    cout << "Ingrese el mes de nacimiento:" << endl;
                    cin >> mm;
                    cout << "Ingrese el año de nacimiento:" << endl;
                    cin >> aa;

                    fnac.dd = dd;
                    fnac.mm = mm;
                    fnac.aa = aa;

                    crearContacto(agenda, nom, ape, cor, dir, tel, fnac, tamTot);
                    tamTot++;
                    tamAgenda++;
                }
                break;
            case 2:
                {
                    string nom, ape;
                    cout << "Ingrese el nombre de la persona que desea eliminar" << endl;
                    cin >> nom;
                    cout << "Ingrese el apellid de la persona que desea eliminar" << endl;
                    cin >> ape;

                    bool esta = false;
                    int pos;
                    for(int i = 0; i < tamAgenda; i++)
                    {
                        if(agenda[i].nombre == nom && agenda[i].apellido == ape)
                        {
                            esta = true;
                            pos = i;
                        }
                    }

                    if(esta)
                    {
                        eliminarContacto(agenda, pos);
                        tamAgenda--;
                        cout << "El contacto ha sido eliminado." << endl;
                    }
                    else
                    {
                        cout << "El contacto no existe para ser eliminado" << endl;
                    }
                }
                break;
            case 3:
                {
                    verContactos(agenda, tamAgenda);
                }
                break;
            case 4:
                {
                    int opc;
                    cout << "De que manera desea ordenar los contactos?" << endl <<
                        "\t1. Por apellido." << endl <<
                        "\t2. Por correo." << endl <<
                        "\t3. Por fecha de nacimiento." << endl;
                    cin >> opc;

                    switch(opc)
                    {
                        case 1:
                            {
                                ordenarPorApellido(agenda, tamAgenda);
                            }
                            break;
                        case 2:
                            {
                                ordenarPorCorreo(agenda, tamAgenda);
                            }
                            break;
                        case 3:
                            {
                                ordenarPorFechaNacimiento(agenda, tamAgenda);
                            }
                            break;
                        default:
                            cout << "BRUTO! Opcion invalida, vuelva a intentar." << endl;
                            break;
                    }
                }
                break;
            case 5:
                {
                    cout << "Gracias por venir!" << endl;
                }
                break;
            default:
                cout << "BRUTO! Opcion invalida, vuelva a intentar." << endl;
                break;
        }
    }
}

//CREAR CONTACTO
void crearContacto(contacto agenda[CMAX], string nom, string ape, string cor, string dir, int tel, fecha fnac, int pos)
{
    agenda[pos].nombre = nom;
    agenda[pos].apellido = ape;
    agenda[pos].correo = cor;
    agenda[pos].direccion = dir;
    agenda[pos].telefono = tel;
    agenda[pos].fnac = fnac;
}

//ELIMINAR CONTACTO
void eliminarContacto(contacto agenda[CMAX], int pos)
{
    agenda[pos].nombre = ELIM;
    agenda[pos].apellido = ELIM;
    agenda[pos].correo = ELIM;
    agenda[pos].direccion = ELIM;
    agenda[pos].telefono = ELIN;
    agenda[pos].fnac.dd = ELIN;
    agenda[pos].fnac.mm = ELIN;
    agenda[pos].fnac.aa = ELIN;
}

//VER CONTACTOS
void verContactos(contacto agenda[CMAX], int tamAgenda)
{
    int i = 0;
    while(i < tamAgenda)
    {
        if(agenda[i].nombre != ELIM)
        {
            cout << "Nombre: " << agenda[i].nombre << endl
                << "Apellido: " << agenda[i].apellido << endl
                << "Correo: " << agenda[i].correo << endl
                << "Direccion: " << agenda[i].direccion << endl
                << "Telefono: " << agenda[i].telefono << endl
                << "Dia de Nacimiento: " << agenda[i].fnac.dd << endl
                << "Mes de Nacimiento: " << agenda[i].fnac.mm << endl
                << "Año de Nacimiento: " << agenda[i].fnac.aa << endl << endl;
            i++;
        }
    }
}

//ORDENAR POR APELLIDO
void ordenarPorApellido(contacto agenda[CMAX], int tamAgenda)
{
    for(int i = 0; i < tamAgenda; i++)
    {
        for(int j = i; j < tamAgenda; j++)
        {
            if(agenda[i].apellido < agenda[j].apellido)
            {
                contacto temp = agenda[i];
                agenda[i]= agenda[j];
                agenda[j] = temp;
            }
        }
    }
}

//ORDENAR POR CORREO
void ordenarPorCorreo(contacto agenda[CMAX], int tamAgenda)
{
    for(int i = 0; i < tamAgenda; i++)
    {
        for(int j = i; j < tamAgenda; j++)
        {
            if(agenda[i].correo < agenda[j].correo)
            {
                contacto temp = agenda[i];
                agenda[i]= agenda[j];
                agenda[j] = temp;
            }
        }
    }
}

//ORDENAR POR FECHA DE NACIMIENTO
void ordenarPorFechaNacimiento(contacto agenda[CMAX], int tamAgenda)
{
    for(int i = 0; i < tamAgenda; i++)
    {
        for(int j = i; j < tamAgenda; j++)
        {
            if(((agenda[i].fnac.aa * 365)+ (agenda[i].fnac.mm * 31) + agenda[i].fnac.dd) > ((agenda[j].fnac.aa * 365)+ (agenda[j].fnac.mm * 31) + agenda[j].fnac.dd))
            {
                contacto temp = agenda[i];
                agenda[i]= agenda[j];
                agenda[j] = temp;
            }
        }
    }
}
