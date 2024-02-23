#ifndef NodoSucursal_h
#define NodoSucursal_h

#include <string>
#include "Sucursal.h"

using namespace std;

struct NodoS
{
  public:
    NodoS *izq;
    NodoS *der;
    Sucursal sucursal;
};

NodoS *crearNodoS(Sucursal s)
{
  NodoS *nuevoNodo = new NodoS();
  nuevoNodo->sucursal = s;
  nuevoNodo->izq = NULL;
  nuevoNodo->der = NULL;

  return nuevoNodo;
}

void agregarhabitacion(NodoS *nodo, NodoH *nodoH)
{
  nodo->sucursal.agregarHabitacion(nodoH);
}

Sucursal crearS(int id)
{
  Sucursal s;
  s.idSucursal = id;
  return s;
}

#endif