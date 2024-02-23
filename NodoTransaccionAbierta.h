#ifndef NodoTransaccionAbierta_h
#define NodoTransaccionAbierta_h

#include <iostream>
#include "TransaccionAbierta.h"

using namespace std;

struct NodoTA
{
  NodoTA *izq;
  NodoTA *der;
  NodoTA *padre;
  TransaccionAbierta trana;
  int factorEq;

};

NodoTA *crearNodoTA(TransaccionAbierta ta)
{
  NodoTA *aux = new NodoTA();

  aux->izq = NULL;
  aux->der = NULL;
  aux->padre = NULL;
  aux->trana = ta;
  aux->factorEq = 0;

  return aux;
}

#endif