#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#include "display.h"
#include "data.h"

//Funcion inicial en la que se introducen datos.
int p_init(struct Contacto **lista) {

//**lista -> La cabecera se pasa por referencia (Lo que se modifica es la variable a la que apunta lista que es la direccion donde esta el puntero a la cabeza de la lista).

  //Definicion de punteros.
  struct Contacto *nodo, *ult;
  
  char cadena[256];
  char nombre[256];
  int edad;
  
  FILE *fichero_entrada;

  fichero_entrada = fopen("contacts.txt", "r");

  //Inicialmente la lista de contactos esta a 0 por eso se inicializa a NULL.
  *lista = NULL;
  
  //Si el fichero esta vacio salimos de la funcion.
  if(fichero_entrada == NULL) {

    return 0;
  }

  //Leemos linea a linea el contenido del fichero.
  while((fgets(cadena, sizeof(cadena), fichero_entrada)) != NULL) {

    //Analizamos la linea (que esta en cadena), sscanf sabe que primero hay un array con nombre, despues un espacio y despues un entero.
    sscanf(cadena,"%s %d", nombre, &edad);

    //Reservamos memoria para los diferentes nodos a utilizar.
    nodo = (struct Contacto *)malloc(sizeof(struct Contacto));

    //Asignamos a edad la edad que lee el sscanf.
    nodo-> edad = edad;

    //Asignamos el nombre al nombre que lee sscanf (al ser cadena se usa strcpy).
    strcpy(nodo -> nombre, nombre);

    //Hacemos que apunte a sig ya que puede que sea el final de la lista.
    nodo -> sig = NULL;

    //Comprobamos si estamos al final de la lista.
    if(*lista == NULL) {

      //Hacemos que *lista apunte a nodo -> El nuevo nodo que metemos pasa a ser el primero.
      *lista = nodo;
    } else  {

      //ult es un puntero auxiliar que nos dice que elemento va detras del ultimo al que apunta nodo.
      ult -> sig = nodo;
    }

    //El ultimo nodo que se ingresa es el ultimo de la lista.
    ult = nodo;   
  }

  fclose(fichero_entrada);

  //free(nodo);
  
  return 0;
}

//Funcion que añade un contacto a la agenda.
int p_add(struct Contacto **lista) {

  printf("\nAdd\n");

  //Definicion de punteros.
  struct Contacto *nodo, *ult;

  nodo = malloc(sizeof (struct Contacto));

  int salida = 0;
  int edad_retornada; //Entero que devuelve la funcion read_integer.
  char palabra_apuntada[100]; //variable a a la que apunta *palabra.
  read_string("Name", palabra_apuntada); //read_string no devuelve nada, pero el nombre se guarda en palabra_apuntada (ver strcpy en la definicion de la funcion).
  edad_retornada = read_integer("Age");
  
  printf("New contact\n");

  //Asignamos al campo nombre (apuntada por nodo) el valor que tiene palabra_apuntada.
  strcpy(nodo -> nombre, palabra_apuntada);

  //Asignamos el valor de edad_retornada al campo edad.
  nodo -> edad = edad_retornada;

  //Apuntamos el nodo a sig y lo inicializamos a null por si estamos al final de la cadena.
  nodo -> sig = NULL;

  //Comprobamos si estamos al final de la lista.
  if(*lista == NULL) {

    //Hacemos que *lista apunte a nodo -> El nuevo nodo que metemos pasa a ser el primero.
    *lista = nodo;
  } else  {

    //Hacemos que ult apunte al primer elemento de la lista.
    ult = *lista;

    //Ahora movemos ult hasta que lleguemos al ultimo nodo (que este a null).
    while(ult -> sig != NULL) {

      ult = ult -> sig;
    }

    //Finalmente hacemos que ult apunte al siguiente nodo que tiene algo, es decir, al ultimo (el que esta a null).
    ult -> sig = nodo;
  }

  //free(nodo);
  
  return salida;
}

//Funcion que elimina un contacto de la agenda.
int p_delete(struct Contacto **lista) {

  printf("\nDelete\n");
  
  int salida = 0;

  struct Contacto *pos, *ant;
  
  char palabra_apuntada[100];
 

  read_string("Name", palabra_apuntada);

  /*
  if(*lista == NULL) {
    printf("\nUnknow contact\n");

    salida = -1;
    return salida;
  }
  */

  pos = *lista;

  ant = NULL;

  //EL while hace de forma implicita lo que esta comentado
  while(pos != NULL && (strcmp(palabra_apuntada, pos -> nombre))) {


    //OJO CON EL ORDEN!
    ant = pos;

    pos = pos -> sig;
    
  }

  if(pos == NULL) {
    printf("\nUnknown contact\n");

    salida = -1;
    return salida;
  }

  
  if(pos == *lista) {
    *lista = pos -> sig;
  } else {

    ant -> sig = pos -> sig;
    
  }

  free(pos);

  printf("\nDeleted contact\n");
   
  return salida;
}

//Funcion que saca por pantalla los datos almacenados en la tabla.
int p_list(struct Contacto *lista) {

  printf("\nList\n");
  
  struct Contacto *pos;
  int salida = 0;
  
  printf("\nContacts table:\n");

  pos = lista;

  while(pos != NULL) {

    printf("%s:%d\n", pos -> nombre, pos -> edad);
    
    pos = pos -> sig;    
  }

  return salida;
}

//Funcion que actualiza el fichero de salida antes de terminar la ejecucion del programa.
int p_fin(struct Contacto *lista) {

  struct Contacto *pos;
  FILE *fichero_salida;

  fichero_salida = fopen("contacts.txt", "w");

  //Primero hacemos que el puntero apunte al primer elemento de la lista.
  pos = lista;

  //El bucle se ejecuta siempre que pos apunte a algun nodo de la lista.
  while(pos != NULL) {

    fprintf(fichero_salida, "%s %d\n", pos -> nombre, pos -> edad);

    //Hacemos que pos apunte al siguiente elemento de la lista.
    pos = pos -> sig;
    
  }
  
  /* ESTO ES CON STRUCT
     fputs((tabla[i].nombre), fichero_salida);
     fputc(' ', fichero_salida);
     char edadComoCadena[256];
     sprintf(edadComoCadena, "%d", (tabla[i].edad)); //Combertimos edad a int para poder copiarlo en el fichero.
     fputs(edadComoCadena, fichero_salida);
     fputc('\n', fichero_salida); 
  */
  
  fclose(fichero_salida);

  return 0;
}


