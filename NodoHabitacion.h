#ifndef NodoHabitacion_h
#define NodoHabitacion_h

#include <iostream>
#include "Habitacion.h"

using namespace std;

struct NodoH
{
  NodoH *izq;
  NodoH *der;
  NodoH *padre;
  Habitacion hab;
  int factorEq;
};

NodoH *crearNodoH(Habitacion h)
{
  NodoH *aux = new NodoH();
  aux->hab = h;
  aux->izq = NULL;
  aux->der = NULL;
  aux->padre = NULL;
  aux->factorEq = 0;

  return aux;
}

Habitacion crearH(int id, int tam, NodoP *p, NodoM *m, bool estado)
{
  Habitacion h;
  h.id = id;
  h.tam = tam;
  h.paciente = p;
  h.medico = m;
  h.estado = estado;
  return h;
}

#endif