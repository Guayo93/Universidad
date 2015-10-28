#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

struct Alumno
{
    int id;
    double definitiva;
};

struct Estudiante
{
    char* info;
};

struct Carrera
{
    char* nombre;
    int numEstudiantes;
    Estudiante* estudiantes;
};

struct Clase
{
    char* nomClase;
    char* nomProfesor;
    int numAlumnos;
    Alumno* alumnos;
};

struct Curso
{
    char* id;
    char* nomCurso;
    int numClases;
    Clase* clases;
};

struct Periodo
{
    char* nomPeriodo;
    int numCursos;
    Curso* cursos;
};

struct Departamento
{
    char* nomDept;
    int numPeriodos;
    Periodo* periodos;
};

char* buscarNombreEstudiante(int idEstudiante, int tamEstudiantes, Estudiante* estudiantes)
{
    char* resp = new char [50];

    for(int i = 0; i < tamEstudiantes; i++)
    {
        Estudiante est = *(estudiantes+i);
        int id = atoi(strtok(est.info, ","));

        if(idEstudiante == id)
        {
            char* nomTemp = strtok(NULL, ",");
            char* apeTemp = strtok(NULL, ",");
            strcpy(resp, apeTemp);
            strcat(resp, " ");
            strcat(resp, nomTemp);
        }
    }
    
    return resp;
}

int estudiantesDeProfesor(char* nomProfesor, char* nomPeriodo, double notaMin, Departamento dept, char** &nomEstudiantes, Carrera carrera)
{
    nomEstudiantes = new char* [100];
    int tamResp = 0;
    bool flag = false;

    for(int i = 0; i < dept.numPeriodos && flag == false; i++)
    {
        Periodo p = *(dept.periodos+i);
        for(int j = 0; j < p.numCursos && flag == false; j++)
        {
            Curso cur = *(p.cursos+j);
            for(int k = 0; k < cur.numClases && flag == false; k++)
            {
                Clase cl = *(cur.clases+k);
                if(strcmp(cl.nomProfesor, nomProfesor) == 0)
                {
                    for(int l = 0; l < cl.numAlumnos; l++)
                    {
                        Alumno al = *(cl.alumnos+l);
                        if(al.definitiva > notaMin)
                        {
                            *(nomEstudiantes+tamResp) = buscarNombreEstudiante(al.id, carrera.numEstudiantes, carrera.estudiantes);
                            tamResp++;
                        }
                    }

                    flag = true;
                }
            }
        }
    }

    return tamResp;
}

void modificarPeriodo(char* nomPeriodo, Curso* cursos, Departamento &dept)
{
    bool flag = false;

    for(int i = 0; i < dept.numPeriodos && flag == false; i++)
    {
        if(strcmp((dept.periodos+i)->nomPeriodo, nomPeriodo) == 0)
        {
            (dept.periodos+i)->cursos = cursos;
            flag = true;
        }
    }
}

int main()
{

}
