#include <iostream>
#include <cstdlib>

using namespace std;

//CONSTANTES
#define ELIM "ZZZZZZZZ"
#define ELIN 99999999

//ESTRUCTURAS
struct fecha
{
    int dd;
    int mm;
    int aa;
};

struct amigo
{
    string nombre;
    string apellido;
    string correo;
    string contrasena;
    bool seguridad;
    fecha fnac;
    int numAmigos;
    int numListas;
};

struct listaAmigo
{
    string nombreLista;
    amigo amigosEnLista[60];
    int tamLista;
};

struct solicitud
{
    string nombre;
    string apellido;
    string correo;
    string contrasena;
    fecha fnac;
    bool seguridad;
    int numAmigos;
    int numListas;
    string amigosEnComun[60];
    int tamAmigosEnComun;
};

struct usuario
{
    string nombre;
    string apellido;
    string correo;
    string contrasena;
    bool perfilActivo;
    bool seguridad;
    fecha fnac;
    solicitud solicitudes[20];
    int numSolicitudes;
    amigo amigos[60];
    int numAmigos;
    listaAmigo listasAmigos[10];
    int numListas;
};

//DECLARACION FUNCIONES
void displayVerUsuariosAssBook(usuario assBook[], int tamAssBook);
int displayMenuInicial();
int displayMenuInscribirse(usuario assBokk[], int tamAssBook);
int displayMenuIngreso(usuario assBook[], int tamAssBook);
int verificarCorreoYContrasena(usuario assBook[], int tamAssBook, string correo, string contrasena);
int displayMenuPerfil(int posPerfil, usuario assBook[]);
int displayMenuEdicionPerfil();
void displayModificarNombre(usuario assBook[], int posPerfil);
void displayModificarFechaNacimiento(usuario assBook[], int posPerfil);
void displayCambiarSeguridad(usuario assBook[], int posPerfil);
void displayDeshabilitarPerfil(usuario assBook[], int posPerfil);
int displayMenuEdicionAmigos();
void displayVerAmigos(usuario assBook[], int posPerfil);
void displayDesicionSolicitud(usuario assBool[], int posPerfil, int tamAssBook);
void ordenarAmigosMenorAMayor(usuario assBook[], int posPerfil);
void ordenarSolicitudesMenorAMayor(usuario assBook[], int posPerfil);
void ordenarListasMenorAMayor(usuario assBook[], int posPerfil);
void displayEliminarAmigos(usuario assBook[], int posPerfil);
void displayAnadirAmigoALista(usuario assBook[], int posPerfil);
int displayMenuManejoListas();
void displayCrearLista(usuario assBook[], int posPerfil);
void displayEliminarLista(usuario assBook[], int posPerfil);
void displayVerAmigosEnLista(usuario assBook[], int posPerfil);
void displayCrearSolicitud(usuario assBook[], int posPerfil, int tamAssBook);

//FUNCIONES
int main()
{
    usuario assBook[50];
    int tamAssBook = 0, opcionMenuInicial;

    do
    {
        system("CLS");
        opcionMenuInicial = displayMenuInicial();
        switch(opcionMenuInicial)
        {
            case 1:
                {
                    system("CLS");
                    tamAssBook = displayMenuInscribirse(assBook, tamAssBook);
                    system("PAUSE");
                }
                break;

            case 2:
                {
                    system("CLS");
                    int posUsuario = displayMenuIngreso(assBook, tamAssBook);
                    if(posUsuario != ELIN)
                    {
                        if(assBook[posUsuario].perfilActivo == true)
                        {

                            int opcionPerfil;
                            do
                            {
                                system("CLS");
                                opcionPerfil = displayMenuPerfil(posUsuario, assBook);
                                switch(opcionPerfil)
                                {
                                    case 1:
                                        {
                                            system("CLS");
                                            int opcionEdicionPerfil = displayMenuEdicionPerfil();
                                            switch(opcionEdicionPerfil)
                                            {
                                                case 1:
                                                    {
                                                        system("CLS");
                                                        displayModificarNombre(assBook, posUsuario);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                case 2:
                                                    {
                                                        system("CLS");
                                                        displayModificarFechaNacimiento(assBook, posUsuario);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                case 3:
                                                    {
                                                        system("CLS");
                                                        displayCambiarSeguridad(assBook, posUsuario);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                case 4:
                                                    {
                                                        system("CLS");
                                                        displayDeshabilitarPerfil(assBook, posUsuario);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                default:
                                                    cout << "Opcion invalida, porfavor vuelva a intentar." << endl;
                                                    break;
                                            }
                                        }

                                    case 2:
                                        {
                                            system("CLS");
                                            int op = displayMenuEdicionAmigos();

                                            switch(op)
                                            {
                                                case 1:
                                                    {
                                                        system("CLS");
                                                        displayVerAmigos(assBook, posUsuario);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                case 2:
                                                    {
                                                        system("CLS");
                                                        displayDesicionSolicitud(assBook, posUsuario, tamAssBook);
                                                        ordenarSolicitudesMenorAMayor(assBook, posUsuario);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                case 3:
                                                    {
                                                        system("CLS");
                                                        displayVerAmigos(assBook, posUsuario);
                                                        displayEliminarAmigos(assBook, posUsuario);
                                                        ordenarAmigosMenorAMayor(assBook, posUsuario);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                case 4:
                                                    {
                                                        system("CLS");
                                                        displayAnadirAmigoALista(assBook, posUsuario);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                case 5:
                                                    {
                                                        system("CLS");
                                                        int op2 = displayMenuManejoListas();

                                                        switch(op2)
                                                        {
                                                            case 1:
                                                                {
                                                                    system("CLS");
                                                                    displayCrearLista(assBook, posUsuario);
                                                                    system("PAUSE");
                                                                }
                                                                break;

                                                            case 2:
                                                                {
                                                                    system("CLS");
                                                                    displayEliminarLista(assBook, posUsuario);
                                                                    ordenarListasMenorAMayor(assBook, posUsuario);
                                                                    system("PAUSE");
                                                                }
                                                                break;

                                                            case 3:
                                                                {
                                                                   system("CLS");
                                                                   displayVerAmigosEnLista(assBook, posUsuario);
                                                                   system("PAUSE");
                                                                }
                                                                break;

                                                            default:
                                                                cout << "Opcion invalida, porfavor vuelva a intentar." << endl;
                                                                break;
                                                        }
                                                    }
                                                    break;

                                                case 6:
                                                    {
                                                        system("CLS");
                                                        displayVerUsuariosAssBook(assBook, tamAssBook);
                                                        displayCrearSolicitud(assBook, posUsuario, tamAssBook);
                                                        system("PAUSE");
                                                    }
                                                    break;

                                                default:
                                                    cout << "Opcion invalida, porfavor vuelva a intentar." << endl;
                                                    break;
                                            }
                                        }
                                        break;

                                    case 3:
                                        {
                                            system("CLS");
                                            cout << "Usted desea salir de la sesion. Vuelva Pronto!" << endl;
                                            system("PAUSE");
                                        }
                                        break;

                                    default:
                                        cout << "Opcion invalida, porfavor vuelva a intentar." << endl;
                                        break;

                                }
                            }while(opcionPerfil != 3);
                        }
                        else
                        {
                            system("CLS");
                            char op;
                            cout << "Su perfil esta deshabilitado, desea re-activarlo? (S/Y)" << endl;
                            cin >> op;
                            if(op == 's' || op == 'S')
                            {
                                assBook[posUsuario].perfilActivo = true;
                                cout << "Su perfil ha sido re-activado, porfavor vuelva a ingresar." << endl;
                            }
                            else
                            {
                                cout << "Usted no ha deseado re-activar su perfil." << endl;
                            }
                            system("PAUSE");
                        }
                    }
                    else
                    {
                        cout << "Su correo o contrasena son incorrectos. Porfavor vuelva a intentar." << endl;
                        system("PAUSE");
                    }
                }

            case 3:
                {
                    cout << "Gracias por usar AssBook! Vuelva Pronto!" << endl;
                }
                break;

            default:
                cout << "Opcion invalida, porfavor vuelva a intentar." << endl;
                break;
        }
    }while(opcionMenuInicial != 3);
}

void displayVerUsuariosAssBook(usuario assBook[], int tamAssBook)
{
    for(int i = 0; i < tamAssBook; i++)
    {
        cout << "Nombre: " << assBook[i].nombre << endl;
        cout << "Apellido: " << assBook[i].apellido << endl;
        cout << "Correo: " << assBook[i].correo << endl;
        if(assBook[i].seguridad == false)
        {
            cout << "Fecha de Nacimiento: " << assBook[i].fnac.dd << "/"
                << assBook[i].fnac.mm << "/"
                << assBook[i].fnac.aa << endl;
        }
        cout << "Numero de amigos: " << assBook[i].numAmigos << endl;
        cout << endl;
    }
}

int displayMenuInicial()
{
    int resp;

    cout << "Bienvenido a AssBook!" << endl << "Que desea hacer?" << endl <<
            "   1: Inscribirse" << endl <<
            "   2: Ingresar" << endl <<
            "   3: Salir del Programa" << endl;
    cin >> resp;
    cout << endl;

    return resp;
}

int displayMenuInscribirse(usuario assBook[], int tamAssBook)
{
    string nombre, apellido, correo, contrasena;
    bool encontro = false;

    cout << "Usted quiere crear un nuevo usuario." << endl << "Ingrese su Nombre" << endl;
    cin >> nombre;
    cout << "Ingrese su Apellido" << endl;
    cin >> apellido;
    cout << "Ingrese su Correo Electronico" << endl;
    cin >> correo;
    cout << "Ingrese su Contrasena" << endl;
    cin >> contrasena;
    cout << endl;

    for(int i = 0; i < tamAssBook && encontro == false; i++)
    {
        if(assBook[i].correo == correo)
        {
            encontro = true;
        }
    }
    if(encontro)
    {
        cout << "No se puede crear el usuario, porque ya hay uno con el mismo correo" << endl;
    }
    else
    {
        assBook[tamAssBook].nombre = nombre;
        assBook[tamAssBook].apellido = apellido;
        assBook[tamAssBook].correo = correo;
        assBook[tamAssBook].contrasena = contrasena;
        assBook[tamAssBook].perfilActivo = true;
        assBook[tamAssBook].seguridad = false;
        assBook[tamAssBook].fnac.dd = 1;
        assBook[tamAssBook].fnac.mm = 3;
        assBook[tamAssBook].fnac.aa = 1993;
        assBook[tamAssBook].numSolicitudes = 0;
        assBook[tamAssBook].numListas = 0;
        assBook[tamAssBook].numAmigos = 0;

        cout << "Bienvenido " << nombre << "! \nAhora puedes Ingresar con el correo " <<
        correo << " y contrasena " << contrasena << " para iniciar sesion." << endl;

        tamAssBook++;
    }

    return tamAssBook;
}

int displayMenuIngreso(usuario assBook[], int tamAssBook)
{
    string correo, contrasena;
    cout << "Usted quiere ingresar a AssBook." << endl << "Ingrese su Correo Electronico" << endl;
    cin >> correo;
    cout << "Ingrese su Contrasena" << endl;
    cin >> contrasena;
    cout << endl;
    int resp = verificarCorreoYContrasena(assBook, tamAssBook, correo, contrasena);

    return resp;
}

int verificarCorreoYContrasena(usuario assBook[], int tamAssBook, string correo, string contrasena)
{
    int resp = ELIN;
    for(int i = 0; i < tamAssBook; i++)
    {
        if(correo == assBook[i].correo && contrasena == assBook[i].contrasena)
        {
            resp = i;
        }
    }

    return resp;
}

int displayMenuPerfil(int posPerfil, usuario assBook[])
{
    int resp;

    cout << "Bienvenido, " << assBook[posPerfil].nombre << "!" << endl << "Que desea hacer?" << endl <<
        "   1: Para editar su informacion." << endl <<
        "   2: Para administrar sus amigos." << endl <<
        "   3: Para salir de la sesion." << endl;

    cin >> resp;
    cout << endl;

    return resp;
}

int displayMenuEdicionPerfil()
{
    int resp;

    cout << "Usted quiere editar su informacion." << endl << "Que desea hacer?" << endl <<
        "   1: Para cambiar su Informacion Basica (Nombre y Apellido)." << endl <<
        "   2: Para cambiar su Cambiar/Ingresar su Fecha de Nacimiento." << endl <<
        "   3: Para Administrar su Seguridad." << endl <<
        "   4: Para Deshabilitar su Perfil." << endl;

    cin >> resp;
    cout << endl;

    return resp;
}

void displayModificarNombre(usuario assBook[], int posPerfil)
{
    string nombre, apellido;
    cout << "Usted quiere cambiar su Informacion Basica (Nombre y Apellido)" << endl << "Porfavor digite su Nuevo Nombre" << endl;
    cin >> nombre;
    cout << "Porfavor digite su Nuevo Apellido" <<endl;
    cin >> apellido;

    assBook[posPerfil].nombre = nombre;
    assBook[posPerfil].apellido = apellido;

    cout << "Su Nombre y Apellido han sido cambiados exitosamente. Para su verificacion son los siguientes " << nombre << " " << apellido << endl << endl;
}

void displayModificarFechaNacimiento(usuario assBook[], int posPerfil)
{
    int dia, mes, anho;
    cout << "Usted desea Cambiar/Ingresar su Fecha de Nacimiento." << endl << "Porfavor digite el dia." << endl;
    cin >> dia;
    cout << "Porfavor digite el mes." << endl;
    cin >> mes;
    cout << "Porfavor digite el anio." << endl;
    cin >> anho;

    assBook[posPerfil].fnac.dd = dia;
    assBook[posPerfil].fnac.mm = mes;
    assBook[posPerfil].fnac.aa = anho;

    cout << "Su Fecha de Nacimiento ha sido cambiada exitosamente. Para su verificacion su Fecha de Nacimiento es " << dia << "/" << mes << "/" << anho << endl << endl;
}

void displayCambiarSeguridad(usuario assBook[], int posPerfil)
{
    char op;

    if(assBook[posPerfil].seguridad)
    {
        cout << "Usted tiene activado el modulo de seguridad, el cual no permite que los demas usuarios vean su fecha de nacimiento." << endl;
    }
    else
    {
        cout << cout << "Usted NO tiene activado el modulo de seguridad, el cual no permite que los demas usuarios vean su fecha de nacimiento." << endl;
    }

    cout << "Usted desea cambiar el valor del modulo de seguridad? (S/N)" << endl;
    cin >> op;

    if(op == 's' || op == 'S')
    {
        if(assBook[posPerfil].seguridad == true)
        {
            assBook[posPerfil].seguridad = false;
            cout << "Su modulo de seguridad ha sido desactivado." << endl;
        }
        else
        {
            assBook[posPerfil].seguridad = true;
            cout << "Su modulo de seguridad ha sido activado." << endl;
        }
    }
}

void displayDeshabilitarPerfil(usuario assBook[], int posPerfil)
{
    int op;

    cout << "Usted desea Deshabilitar su perfil." << endl << " 1: Para Deshabilitar su perfil. \n 2: Para NO Deshabilitar su perfil." << endl;
    cin >> op;

    if(op == 1)
    {
        assBook[posPerfil].perfilActivo = false;
        cout << "Usted ha deshabilitado su perfil, aun puede modificar su perfil y sus amigos pero al momento de cerrar sesion se efectuara la desactivacion." << endl;
    }
    else
    {
        cout << "Su perfil sigue activo." << endl;
    }
}

int displayMenuEdicionAmigos()
{
    int op;

    cout << "Usted quiere administrar a sus amigos." << endl << "Que desea hacer?" << endl <<
    "   1: Para Ver sus Amigos." << endl <<
    "   2: Para Ver las Solicitudes de Amistad." << endl <<
    "   3: Para Eliminar Amigos." << endl <<
    "   4: Para Mover a un Amigo a una Lista Personalizada." << endl <<
    "   5: Para Administrar las Listas Personalizadas de Amigos." << endl <<
    "   6: Para hacer Solicitudes de Amistad." << endl;
    cin >> op;

    return op;
}

void displayVerAmigos(usuario assBook[], int posPerfil)
{
    cout << "Acontinuacion usted vera la lista de sus amigos:" << endl;
    for(int i = 0; i < assBook[posPerfil].numAmigos; i++)
    {
        if(assBook[posPerfil].amigos[i].nombre != ELIM && assBook[posPerfil].amigos[i].apellido != ELIM)
        {
            cout << "Nombre: " << assBook[posPerfil].amigos[i].nombre << endl;
            cout << "Apellido: " << assBook[posPerfil].amigos[i].apellido << endl;
            cout << "Correo: " << assBook[posPerfil].amigos[i].correo << endl;
            if(assBook[posPerfil].amigos[i].seguridad == false)
            {
                cout << "Fecha de Nacimiento: " << assBook[posPerfil].amigos[i].fnac.dd << "/"
                    << assBook[posPerfil].amigos[i].fnac.mm << "/"
                    << assBook[posPerfil].amigos[i].fnac.aa << endl;
            }
            cout << "Numero de amigos: " << assBook[posPerfil].amigos[i].numAmigos << endl;
            cout << endl;
        }
    }
}

void displayDesicionSolicitud(usuario assBook[], int posPerfil, int tamAssBook)
{
    cout << "Usted tiene " << assBook[posPerfil].numSolicitudes << " solicitudes.";
    for(int i = 0; i < assBook[posPerfil].numSolicitudes; i++)
    {
        if(assBook[posPerfil].solicitudes[i].nombre != ELIM && assBook[posPerfil].solicitudes[i].apellido != ELIM)
        {
            char op;
            cout << "El usuario: " << endl
                << "Nombre: " << assBook[posPerfil].solicitudes[i].nombre << endl
                << "Apellido: " << assBook[posPerfil].solicitudes[i].apellido << endl
                << "Correo: " << assBook[posPerfil].solicitudes[i].correo << endl
                << "Amigos en comun: " << endl;
            for(int j = 0; j < assBook[posPerfil].solicitudes[i].tamAmigosEnComun; j++)
            {
                cout << assBook[posPerfil].solicitudes[i].amigosEnComun[j] << endl;
            }
            cout << "Quiere ser tu amigo. Quiere aceptarlo o rechazarlo? (A/R)" << endl;
            cin >> op;

            if(op == 'a' || op == 'A')
            {
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].nombre = assBook[posPerfil].solicitudes[i].nombre;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].apellido = assBook[posPerfil].solicitudes[i].apellido;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].correo = assBook[posPerfil].solicitudes[i].correo;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].contrasena = assBook[posPerfil].solicitudes[i].contrasena;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].seguridad = assBook[posPerfil].solicitudes[i].seguridad;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].fnac.dd = assBook[posPerfil].solicitudes[i].fnac.dd;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].fnac.mm = assBook[posPerfil].solicitudes[i].fnac.mm;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].fnac.aa = assBook[posPerfil].solicitudes[i].fnac.aa;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].numAmigos = assBook[posPerfil].solicitudes[i].numAmigos;
                assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].numListas = assBook[posPerfil].solicitudes[i].numListas;
                assBook[posPerfil].numAmigos++;

                for(int j = 0; j < tamAssBook; j++)
                {
                    if(assBook[j].correo == assBook[posPerfil].solicitudes[i].correo)
                    {
                        assBook[j].amigos[assBook[j].numAmigos].nombre = assBook[posPerfil].nombre;
                        assBook[j].amigos[assBook[j].numAmigos].apellido = assBook[posPerfil].apellido;
                        assBook[j].amigos[assBook[j].numAmigos].correo = assBook[posPerfil].correo;
                        assBook[j].amigos[assBook[j].numAmigos].seguridad = assBook[posPerfil].seguridad;
                        assBook[j].amigos[assBook[j].numAmigos].numAmigos = assBook[posPerfil].numAmigos;
                        assBook[j].amigos[assBook[j].numAmigos].numListas = assBook[posPerfil].numListas;
                        assBook[j].amigos[assBook[j].numAmigos].fnac.dd = assBook[posPerfil].fnac.dd;
                        assBook[j].amigos[assBook[j].numAmigos].fnac.mm = assBook[posPerfil].fnac.mm;
                        assBook[j].amigos[assBook[j].numAmigos].fnac.aa = assBook[posPerfil].fnac.aa;
                        assBook[j].numAmigos++;
                    }
                }

                cout << assBook[posPerfil].solicitudes[i].nombre << " " << assBook[posPerfil].solicitudes[i].apellido << " ha sido agregado a tu lista de amigos." << endl;
            }
            else
            {
                cout << assBook[posPerfil].solicitudes[i].nombre << " " << assBook[posPerfil].solicitudes[i].apellido << " NO ha sido agregado a tu lista de amigos." << endl;
            }

            assBook[posPerfil].solicitudes[i].nombre = ELIM;
            assBook[posPerfil].solicitudes[i].apellido = ELIM;
            assBook[posPerfil].solicitudes[i].fnac.dd = ELIN;
            assBook[posPerfil].solicitudes[i].fnac.aa = ELIN;
            assBook[posPerfil].solicitudes[i].fnac.mm = ELIN;
        }
    }

    assBook[posPerfil].numSolicitudes = 0;
}

void ordenarAmigosMenorAMayor(usuario assBook[], int posPerfil)
{
    for(int i = 0; i < assBook[posPerfil].numAmigos; i++)
    {
        for(int j = i; j < assBook[posPerfil].numAmigos; j++)
        {
            if(assBook[posPerfil].amigos[j].nombre < assBook[posPerfil].amigos[i].nombre && assBook[posPerfil].amigos[j].apellido < assBook[posPerfil].amigos[i].apellido)
            {
                amigo temp = assBook[posPerfil].amigos[j];
                assBook[posPerfil].amigos[j] = assBook[posPerfil].amigos[i];
                assBook[posPerfil].amigos[i] = temp;
            }
        }
    }
}

void ordenarSolicitudesMenorAMayor(usuario assBook[], int posPerfil)
{
    for(int i = 0; i < assBook[posPerfil].numSolicitudes; i++)
    {
        for(int j = i; j < assBook[posPerfil].numSolicitudes; j++)
        {
            if(assBook[posPerfil].solicitudes[j].nombre < assBook[posPerfil].solicitudes[i].nombre && assBook[posPerfil].solicitudes[j].apellido < assBook[posPerfil].solicitudes[i].apellido)
            {
                solicitud temp = assBook[posPerfil].solicitudes[j];
                assBook[posPerfil].solicitudes[j] = assBook[posPerfil].solicitudes[i];
                assBook[posPerfil].solicitudes[i] = temp;
            }
        }
    }
}

void ordenarListasMenorAMayor(usuario assBook[], int posPerfil)
{
    for(int i = 0; i < assBook[posPerfil].numListas; i++)
    {
        for(int j = i; j < assBook[posPerfil].numListas; j++)
        {
            if(assBook[posPerfil].listasAmigos[j].nombreLista < assBook[posPerfil].listasAmigos[i].nombreLista && assBook[posPerfil].listasAmigos[j].tamLista < assBook[posPerfil].listasAmigos[i].tamLista)
            {
                listaAmigo temp = assBook[posPerfil].listasAmigos[j];
                assBook[posPerfil].listasAmigos[j] = assBook[posPerfil].listasAmigos[i];
                assBook[posPerfil].listasAmigos[i] = temp;
            }
        }
    }

}

void displayEliminarAmigos(usuario assBook[], int posPerfil)
{
    string correoT;
    bool elimiando = false;
    cout << "Usted quiere eliminar a un usuario de sus lista de amigos." << endl << "Porfavor digite el correo del usuario que desea eliminar." << endl;
    cin >> correoT;

    for(int i = 0; i < assBook[posPerfil].numAmigos && elimiando == false; i++)
    {
        if(assBook[posPerfil].amigos[i].correo == correoT)
        {
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].nombre = ELIM;
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].apellido = ELIM;
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].correo = ELIM;
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].seguridad = ELIM;
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].fnac.dd = ELIN;
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].fnac.mm = ELIN;
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].fnac.aa = ELIN;
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].numAmigos = ELIN;
            assBook[posPerfil].amigos[assBook[posPerfil].numAmigos].numListas = ELIN;
            elimiando = true;
        }
    }

    if(elimiando)
    {
        cout << "El usuario con correo " << correoT << " ha sido eliminado de su lista de amigos exitosamente." << endl;
    }
    else
    {
        cout << " El usuario con el correo " << correoT << " no ha sido encontrado." << endl;
    }
}

void displayAnadirAmigoALista(usuario assBook[], int posPerfil)
{
    string correoT, nomLista;
    bool estaAmigo = false;
    amigo temp;

    cout << "Usted desea añadir un amigo a una lista. Cual es el correo del amigo?" << endl;
    cin >> correoT;
    cout << "Cual es la lista a la que lo desea agregar?" << endl;
    cin >> nomLista;

    for(int i = 0; i < assBook[posPerfil].numAmigos && estaAmigo == false; i++)
    {
        if(assBook[posPerfil].amigos[i].correo == correoT)
        {
            temp = assBook[posPerfil].amigos[i];
            estaAmigo = true;
        }
    }

    if(estaAmigo)
    {
        for(int i = 0; i < assBook[posPerfil].numListas; i++)
        {
            if(assBook[posPerfil].listasAmigos[i].nombreLista == nomLista)
            {
                assBook[posPerfil].listasAmigos[i].amigosEnLista[assBook[posPerfil].listasAmigos[i].tamLista] = temp;
                assBook[posPerfil].listasAmigos[i].tamLista++;
                cout << "El amigo con correo " << correoT << " ha sido agregado a la lista " << nomLista << endl;
            }
            else
            {
                cout << "La lista con nombre " << nomLista << " no fue encontrada." << endl;
            }
        }
    }
    else
    {
        cout << "El amigo con correo " << correoT << " no fue encontrado." << endl;
    }
}

int displayMenuManejoListas()
{
    int op;

    cout << "Usted quiere Administrar sus Listas Personalizadas de Amigos." << endl << "Que quiere hacer?" << endl <<
    "   1: Para Crear una Lista Personalizada." << endl <<
    "   2: Para Eliminar una Lista Personalizada." << endl <<
    "   3: Para Ver los Amigos que conforman una Lista Personalizada." << endl;
    cin >> op;

    return op;
}

void displayCrearLista(usuario assBook[], int posPerfil)
{
    string nomLista;
    bool sePuede = true;
    cout << "Usted desea crear una lista. Porfavor digite el nombre de la Lista a crear: " << endl;
    cin >> nomLista;

    for(int i = 0; i < assBook[posPerfil].numListas && sePuede; i++)
    {
        if(assBook[posPerfil].listasAmigos[i].nombreLista == nomLista)
        {
            sePuede = false;
        }
    }

    if(sePuede)
    {
        assBook[posPerfil].listasAmigos[assBook[posPerfil].numListas].nombreLista = nomLista;
        assBook[posPerfil].listasAmigos[assBook[posPerfil].numListas].tamLista = 0;
        assBook[posPerfil].numListas++;

        cout << "La lista de nombre " << nomLista << " ha sido creada." << endl;
    }
    else
    {
        cout << "La lista de nombre " << nomLista << " NO ha sido creada, porque ya existe otra lista con ese nombre." << endl;
    }
}

void displayEliminarLista(usuario assBook[], int posPerfil)
{
    string nomLista;
    bool eliminada = false;
    cout << "Usted quiere eliminar una Lista. Porfavor digite el nombre de la lista: " << endl;
    cin >> nomLista;

    for(int i = 0; i < assBook[posPerfil].numListas && eliminada == false; i++)
    {
        if(assBook[posPerfil].listasAmigos[i].nombreLista == nomLista)
        {
            assBook[posPerfil].listasAmigos[i].nombreLista = ELIM;
            assBook[posPerfil].listasAmigos[i].tamLista = ELIN;
            eliminada = true;
        }
    }

    if(eliminada)
    {
        cout << "La lista de nombre " << nomLista << " ha sido eliminada." << endl;
    }
    else
    {
        cout << "La lista de nombre " << nomLista << " NO ha sido eliminada, porque no fue encontrada." << endl;
    }
}

void displayVerAmigosEnLista(usuario assBook[], int posPerfil)
{
    string nomLista;
    bool encontro = false;
    cout << "Usted desea ver a sus amigos en una lista determinada. Porfavor digite el nombre de la lista: " << endl;
    cin >> nomLista;

    for(int i = 0; i < assBook[posPerfil].numListas && encontro == false; i++)
    {
        if(assBook[posPerfil].listasAmigos[i].nombreLista == nomLista)
        {
            cout << "Acontinuacion usted vera los nombres de los amigos en la lista " << nomLista << endl;

            for(int j = 0; j < assBook[posPerfil].listasAmigos[i].tamLista; j++)
            {
                cout << "Nombre: " << assBook[posPerfil].listasAmigos[i].amigosEnLista[j].nombre << endl;
                cout << "Apellido: " << assBook[posPerfil].listasAmigos[i].amigosEnLista[j].apellido << endl;
                cout << "Correo: " << assBook[posPerfil].listasAmigos[i].amigosEnLista[j].correo << endl;
                if(assBook[posPerfil].listasAmigos[i].amigosEnLista[j].seguridad == false)
                {
                    cout << "Fecha de Nacimiento: " << assBook[posPerfil].listasAmigos[i].amigosEnLista[j].fnac.dd << "/"
                        << assBook[posPerfil].listasAmigos[i].amigosEnLista[j].fnac.mm << "/"
                        << assBook[posPerfil].listasAmigos[i].amigosEnLista[j].fnac.aa << endl;
                }
                cout << "Numero de amigos: " << assBook[posPerfil].listasAmigos[i].amigosEnLista[j].numAmigos << endl;
                cout << endl;
            }

            encontro = true;
        }
    }

    if(encontro == false)
    {
        cout << "La lista de nombre " << nomLista << " no fue encontrada." << endl;
    }
}

void displayCrearSolicitud(usuario assBook[], int posPerfil, int tamAssBook)
{
    string correoT;
    bool encontro = false;
    cout << "Usted desea crear una solicitud de amistad. Porfavor digite el correo de la persona a la cual se la desea enviar: " << endl;
    cin >> correoT;

    for(int i = 0; i < tamAssBook && encontro == false; i++)
    {
        if(assBook[i].correo == correoT && assBook[i].correo != assBook[posPerfil].correo)
        {
            assBook[i].solicitudes[assBook[i].numSolicitudes].nombre = assBook[posPerfil].nombre;
            assBook[i].solicitudes[assBook[i].numSolicitudes].apellido = assBook[posPerfil].apellido;
            assBook[i].solicitudes[assBook[i].numSolicitudes].correo = assBook[posPerfil].correo;
            assBook[i].solicitudes[assBook[i].numSolicitudes].fnac.dd = assBook[posPerfil].fnac.dd;
            assBook[i].solicitudes[assBook[i].numSolicitudes].fnac.mm = assBook[posPerfil].fnac.mm;
            assBook[i].solicitudes[assBook[i].numSolicitudes].fnac.aa = assBook[posPerfil].fnac.aa;
            assBook[i].solicitudes[assBook[i].numSolicitudes].numAmigos = assBook[posPerfil].numAmigos;
            assBook[i].solicitudes[assBook[i].numSolicitudes].numListas = assBook[posPerfil].numListas;
            assBook[i].solicitudes[assBook[i].numSolicitudes].seguridad = assBook[posPerfil].seguridad;

            for(int j = 0; j < assBook[posPerfil].numAmigos; j++)
            {
                for(int k = 0; k < assBook[i].numAmigos; k++)
                {
                    if(assBook[i].amigos[k].correo == assBook[posPerfil].amigos[j].correo)
                    {
                        assBook[i].solicitudes[assBook[i].numSolicitudes].amigosEnComun[assBook[i].solicitudes[assBook[i].numSolicitudes].tamAmigosEnComun] = assBook[posPerfil].amigos[j].nombre + " " + assBook[posPerfil].amigos[j].apellido;
                        assBook[i].solicitudes[assBook[i].numSolicitudes].tamAmigosEnComun++;
                    }
                }
            }

            assBook[i].numSolicitudes++;
            encontro = true;
        }
    }

    if(encontro)
    {
        cout << "La solicitud hacia el usuario con correo " << correoT << " ha sido creada." << endl;
    }
    else
    {
        cout << "La solicitud hacia el usuario con correo " << correoT << " NO ha sido creada, porque no fue encontrado o intentaste ser amigo de ti mismo." << endl;
    }
}
