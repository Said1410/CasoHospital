#ifndef NodoPaciente_h
#define NodoPaciente_h

#include <string>
#include "Paciente.h"

using namespace std;

struct NodoP
{
  public:
    NodoP *izq;
    NodoP *der;
    Paciente paciente;
};

NodoP *crearNodoP(Paciente p)
{
  NodoP *nuevoNodo = new NodoP();
  nuevoNodo->paciente = p;
  nuevoNodo->izq = NULL;
  nuevoNodo->der = NULL;

  return nuevoNodo;
}

#endif