#ifndef TransaccionAbierta_h
#define TransaccionAbierta_h

#include <iostream>
#include "NodoHabitacion.h"
#include "NodoSucursal.h"
using namespace std;

class TransaccionAbierta
{
  public:
    long id;
    NodoH *h;
    NodoS *s;
    int especialidad;
    string fechaIngreso;
    string fechaEgreso;
    float tarifa;
    int diasInternado;
    float total;
    string motivo;

    TransaccionAbierta() {}

    TransaccionAbierta(long id, int especialidad, string fechaIngreso, string fechaEgreso, float tarifa, int internado, float total, string motivo, NodoH* h, NodoS *s) {
        this->id = id;
        this->especialidad = especialidad;
        this->fechaIngreso = fechaIngreso;
        this->fechaEgreso = fechaEgreso;
        this->tarifa = tarifa;
        this->diasInternado = internado;
        this->total = total;
        this->motivo = motivo;
        this->h = h;
        this->s = s;
    }
};

#endif