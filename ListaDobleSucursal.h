#ifndef ListaDobleSucursal_h
#define ListaDobleSucursal_h

#include <iostream>
#include <fstream>
#include "NodoSucursal.h"
#include <algorithm>

using namespace std;

class listaDobleSucursal{

  public:
    listaDobleSucursal();
    void agregarSucursal(NodoS *&inicio, NodoS *&fin, NodoS *nuevo);
    void modificarSucursal(NodoS *&inicio, NodoS *&fin, int id);
    void eliminarSucursal(NodoS *&inicio, NodoS *&fin, int id);
    void mostrarSucursal(NodoS *inicio, NodoS *fin);
    void buscarSucursal(NodoS *inicio, NodoS *fin, int id);
    bool sucursalExiste(NodoS *inicio, NodoS *fin, int id);
    bool habitacionExisteSuc(NodoS *inicio, NodoS *fin, NodoH *hab);
    NodoS* encontrarSucursal(NodoS *inicio, NodoS *fin, int id);
};

listaDobleSucursal::listaDobleSucursal() {}

void listaDobleSucursal::agregarSucursal(NodoS *&inicio, NodoS *&fin, NodoS *nuevo)
{
  if(inicio == NULL)
  {
    inicio = nuevo;
    fin = nuevo;
    nuevo->izq = NULL;
    nuevo->der = NULL;
  }
  else
  {
    nuevo->izq = fin;
    fin->der = nuevo;
    fin = nuevo;
    fin->der = NULL;
  }
}

void listaDobleSucursal::modificarSucursal(NodoS *&inicio, NodoS *&fin, int id)
{
  if(listaDobleSucursal::sucursalExiste(inicio, fin, id))
  {
    int opc = 0;
    if(inicio == NULL)
    {
      cout << "No hay sucursales registradas\n" << endl;
    }
    else
    {
      NodoS* aux = inicio;
      while(aux != NULL)
      {
        if(aux->sucursal.idSucursal == id)
        {
          do
          {
            cout << "***** MODIFICAR *****" << endl;
            cout << "1. id" << endl;
            cout << "2. Salir" << endl;
            cout << "Opcion: "; cin >> opc;
            cout << "\033[2J\033[1;1H";
            switch(opc)
            {
              case 1:
                cout << "Ingrese la nueva id: ";
                cin >> aux->sucursal.idSucursal;
                break;
              case 2:
                cout << "\033[2J\033[1;1H";
                break;
              default:
                cout << "Opcion invalida" << endl;
            }
            cout << "\n";
          }while(opc != 2);
          cout << "\033[2J\033[1;1H";
          cout << "Sucursal modificada existosamente!\n" << endl;
        }
        aux = aux->der;
      }
    }
  }
  else
  {
    cout << "No existe la sucursal\n" << endl;
  }
}

void listaDobleSucursal::eliminarSucursal(NodoS *&inicio, NodoS *&fin, int id)
{
  if(listaDobleSucursal::sucursalExiste(inicio, fin, id))
  {
    if(inicio == NULL)
    {
      cout << "No hay sucursales registradas\n" << endl;
    }
    
    NodoS *aux = encontrarSucursal(inicio, fin, id);

    if(aux->sucursal.habitaciones.empty())
    {
      if(inicio->sucursal.idSucursal == id)
      {
        NodoS *auxI = inicio;
        inicio = inicio->der;
        inicio->izq = NULL;
        delete auxI;
      }

      if(fin->sucursal.idSucursal == id)
      {
        NodoS *auxF = fin;
        fin = fin->izq;
        fin->der = NULL;
        delete auxF;
      }
      else
      {
        NodoS* aux = inicio->der;
        NodoS* auxI;
        NodoS* auxD;
        NodoS* eliminar;

        while(aux->der != NULL)
        {
          if(aux->sucursal.idSucursal == id)
          {
            auxI = aux->izq;
            auxD = aux->der;
            eliminar = aux;
            auxI->der = auxD;
            auxD->izq = auxI;
            delete eliminar;
            break;
          }
          aux = aux->der;
        }
        cout << "\033[2J\033[1;1H";
        cout << "Sucursal eliminada exitosamente!\n" << endl;
      }
    }
    else
    {
      cout << "La sucursal tiene habitaciones\n" << endl;
    }
  }
  else
  {
    cout << "No existe la sucursal\n" << endl;
  }
}

void listaDobleSucursal::mostrarSucursal(NodoS *inicio, NodoS *fin)
{
  if(inicio == NULL)
  {
    cout << "No hay sucursales registradas\n" << endl;
  }
  else
  {
    NodoS *aux = inicio;

    while(aux != NULL)
    {
      cout << "Sucursal: " << aux->sucursal.idSucursal << endl << endl;
      if(!aux->sucursal.habitaciones.empty())
      {
        for (const auto& habitacion : aux->sucursal.habitaciones) 
        {
          cout << "Habitación " << habitacion->hab.id << endl;
        }
      }
      else
      {
        cout << "No hay habitaciones registradas" << endl;
      }
      cout << "\n";
      aux = aux->der;
    }
  }
}

void listaDobleSucursal::buscarSucursal(NodoS *inicio, NodoS *fin, int id)
{
  bool existe = false;
  NodoS *aux = inicio;

  if(inicio == NULL)
  {
    cout << "\nNo hay sucursales registradas" << endl;
  }
  else
  {
    while(aux != NULL)
    {
      if(aux->sucursal.idSucursal == id)
      {
        existe = true;
        break;
      }
      aux = aux->der;
    }

    if(existe)
    {
      cout << "Sucursal: " << aux->sucursal.idSucursal << endl << endl;
      if(!aux->sucursal.habitaciones.empty())
      {
        for (const auto& habitacion : aux->sucursal.habitaciones) 
        {
          cout << "Habitación " << habitacion->hab.id << endl;
        }
        cout << "\n";
      }
      else
      {
        cout << "No hay habitaciones registradas\n" << endl;
      }
    }
    else
    {
      cout << "No se encontro la sucursal\n" << endl;
    }
  }
}

bool listaDobleSucursal::sucursalExiste(NodoS *inicio, NodoS *fin, int id)
{
  bool existe = false;

  if(inicio == NULL)
  {
    return existe;
  }
  else
  {
    NodoS *aux = inicio;

    while(aux != NULL)
    {
      if(aux->sucursal.idSucursal == id)
      {
        existe = true;
        return existe;
      }
      aux = aux->der;
    }
  }
  return existe;
}

bool listaDobleSucursal::habitacionExisteSuc(NodoS *inicio, NodoS *fin, NodoH *hab)
{
  if(inicio == NULL)
  {
    return false;
  }
  else
  {
    NodoS *aux = inicio;

    auto iterator = find(aux->sucursal.habitaciones.begin(), aux->sucursal.habitaciones.end(), hab);

    if(iterator != aux->sucursal.habitaciones.end())
    {
      return true;
    }
    return false;
    
  }
  return false;
}

NodoS* listaDobleSucursal::encontrarSucursal(NodoS *inicio, NodoS *fin, int id)
{
  if(inicio == NULL)
  {
    return NULL;
  }
  else
  {
    NodoS *aux = inicio;
    while(aux != NULL)
    {
      if(aux->sucursal.idSucursal == id)
      {
        return aux;
        break;
      }
      aux = aux->der;
    }
  }

  return NULL;
}

#endif