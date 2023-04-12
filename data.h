#ifndef DATA_H
#define DATA_H

//Definicion del struct.
struct Contacto {
  char nombre[25];
  int edad;
  struct Contacto *sig; //Info de enlace al siguiente nodo.
}; //OJO AL ;


int p_add(struct Contacto **lista);
int p_delete(struct Contacto **lista);
int p_list(struct Contacto *lista);
int p_init(struct Contacto **lista);
int p_fin(struct Contacto *lista);

#endif
