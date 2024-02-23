#ifndef Habitacion_h
#define Habitacion_h

#include <iostream>
#include "NodoPaciente.h"
#include "NodoMedico.h"
#include <vector>

using namespace std;

class Habitacion
{
  public:
    int id;
    int tam;
    NodoP *paciente;
    NodoM *medico;
    bool estado;
    float dineroGenerado;

    Habitacion() {}

    Habitacion(int id, int tam, NodoP *p, NodoM *m, bool estado, float dineroGenerado)
    {
      this->id = id;
      this->tam = tam;
      this->paciente = p;
      this->medico = m;
      this->estado = estado;
      this->dineroGenerado = dineroGenerado;
    }
};

#endif