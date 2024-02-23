#ifndef Sucursal_h
#define Sucursal_h

#include <iostream>
#include "NodoHabitacion.h"
#include <vector>
#include <algorithm>

using namespace std;

struct Sucursal
{
  public:
    int idSucursal;
    int dineroGenerado;
    vector<NodoH*> habitaciones;
    Sucursal() {}
    
    Sucursal(int idSuc, int dinGen) : idSucursal(idSuc), dineroGenerado(dinGen) {}
    
    Sucursal(int idSuc, vector<NodoH*> hab) : idSucursal(idSuc), habitaciones(hab) {}

    void agregarHabitacion(NodoH *nodo)
    {
      habitaciones.push_back(nodo);
    }
};

#endif