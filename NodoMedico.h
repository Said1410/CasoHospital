#ifndef NodoMedico_h
#define NodoMedico_h

#include <iostream>
#include "Medico.h"

using namespace std;

struct NodoM
{
  NodoM *izq;
  NodoM *der;
  Medico medico;
};

NodoM *crearNodoM(Medico m)
{
  NodoM *nuevoNodo = new NodoM();
  nuevoNodo->medico = m;
  nuevoNodo->izq = NULL;
  nuevoNodo->der = NULL;
  
  return nuevoNodo;
}

#endif