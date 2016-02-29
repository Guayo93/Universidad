/* Ejemplo: matriz.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
main(int argc, char *argv[])

{

  int status, i,nprocesos,cuantos;
  int matriz[6][6]={{1,1,1,1,1,1},{2,2,2,2,2,2},{3,3,3,3,3,3},{4,4,4,4,4,4},{5,5,5,5,5,5},{6,6,6,6,6,6}};
  pid_t childpid;

  if(argc != 2)
  {
    printf("Error de Argumentos\n");
    exit(0);
  }

  nprocesos = atoi(argv[1]);

  if(6 % nprocesos != 0)
  {
    printf("Debe ser un numero divisor de 6\n");
    exit(0);
  }

  cuantos = 6/nprocesos;

  for (i = 0; i < nprocesos; ++i)
  { // Creaci�n de los procesos.

    if ((childpid = fork()) < 0)
    {
      perror("fork:");
      exit(1);
    }
    // colocar aqui el c�digo de los hijos







  }
  // El padre espera por todos los hijos que creo.
  for (i = 0; i < nprocesos; ++i)
  wait(&status);
  printf("El padre termina\n");

}
