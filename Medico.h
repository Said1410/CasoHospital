#ifndef Medico_h
#define Medico_h

#include <iostream>

using namespace std;

struct Medico
{
  public:
    int dni;
    string nombre;
    string apellido;
    int edad;
    int especialidad;
    int pacienteAtendidos;
    float dineroGenerado;

    Medico() {};
  
    Medico(int dni, string nombre, string apellido, int edad, int especialidad, int pacienteAtendidos, float generado)
    {
      this->dni = dni;
      this->nombre = nombre;
      this->apellido = apellido;
      this->edad = edad;
      this->especialidad = especialidad;
      this->pacienteAtendidos = pacienteAtendidos;
      this->dineroGenerado = generado;
    }
};

#endif