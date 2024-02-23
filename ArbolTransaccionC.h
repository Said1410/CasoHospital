#ifndef ArbolTransaccionC_h
#define ArbolTransaccionC_h

#include <iostream>
#include "NodoTransaccionAbierta.h"
#include "ListaDobleSucursal.h"
#include "ListaDoblePaciente.h"
#include <vector>
#include <queue>

using namespace std;

struct ArbolTC
{
  NodoTA *raiz;
};

//Prototipos
void balancearArbolTC(ArbolTC *arbol, NodoTA *nodo);

//Funcion para crear un arbol vacio
ArbolTC *crearArbolTC()
{
  ArbolTC *aux = new ArbolTC();
  aux->raiz = NULL;

  return aux;
}

//Funcion para validar si el arbol esta vacio
bool arbolVacioTC(ArbolTC *arbol) 
{
  if(arbol->raiz == NULL)//La raiz del arbol apunta a NULL
  {
    return true;
  }

  return false;
}

//Funcion para insertar un nodo en el arbol
void insertarNodoTC(ArbolTC *arbol, NodoTA *nodo)
{
  if(arbolVacioTC(arbol))//Validamos si el arbol esta vacio
  {
    arbol->raiz = nodo;//Cumplida la condicion, la raiz del arbol apunta al nodo
  }
  else// De no estar vacio
  {
    NodoTA *aux = arbol->raiz; //Creamos un auxiliar que almacena la raiz del arbol
    NodoTA *padre; // Variable para almacenar el padre del nodo actual

    while(aux != NULL)//Recorrido del arbol hasta el ultimo nodo
    {
      padre = aux; // Guardamos el nodo actual en la variable padre

      if(nodo->trana.id < aux->trana.id)//Si el dato es menor, vamos a la izquierda
      {
        aux = aux->izq;
      }
      else//Si el dato es mayor, vamos a la derecha
      {
        aux = aux->der;
      }
    }
    //Cuando salimos del ciclo, almacenamos el nodo anterior de la posicion actual
    nodo->padre = padre;

    //Ubicamos por la derecha o izquierda al nodo, segun e valor del dato
    if(nodo->trana.id < padre->trana.id)
    {
      padre->izq = nodo;
    }
    else
    {
      padre->der = nodo;
    }
    balancearArbolTC(arbol, padre);
  }
}

//Funcion de busqueda del nodo 
NodoTA *buscarNodoTC(ArbolTC *arbol, int dni)
{
  NodoTA *aux = NULL;

  if(!arbolVacioTC(arbol))
  {
    aux = arbol->raiz;
    
    while(aux != NULL && aux->trana.h->hab.paciente->paciente.dni != dni)
    {
      if(dni < aux->trana.h->hab.paciente->paciente.dni)
      {
        aux = aux->izq;
      }
      else
      {
        aux = aux->der;  
      }
    }
  }

  //Retorno del nodo
  return aux;
}

string disponibilidadTC(bool disp)
{
  if(!disp)
  {
    return "Disponible";
  }
  return "No disponible";
}

//Funcion de busqueda del nodo 
NodoTA *buscarNodoHabTC(ArbolTC *arbol, int id)
{
  NodoTA *aux = NULL;

  if(!arbolVacioTC(arbol))
  {
    aux = arbol->raiz;

    while(aux != NULL && aux->trana.h->hab.id != id)
    {
      if(id < aux->trana.h->hab.id)
      {
        aux = aux->izq;
      }
      else
      {
        aux = aux->der;  
      }
    }
  }

  //Retorno del nodo
  return aux;
}

// Funcion de retorno de suma total de tarifas
int tarifaHabTC(ArbolTC *arbol, int id) {
  NodoTA *aux = NULL;
  int suma = 0;

  if (!arbolVacioTC(arbol)) // Validamos si el arbol esta vacio
  {
    aux = arbol->raiz; // Guardamos la raiz del arbol
    while (aux != NULL) 
    {
      if (id < aux->trana.h->hab.id)
      {
        aux = aux->izq;
      }
      else if(id > aux->trana.h->hab.id)
      {
        aux = aux->der;
      }
      else
      {
        suma += aux->trana.h->hab.dineroGenerado;
      }
    }

    return suma;
  }

  return suma;
}

void mostrarTransaccionesAgrupadasSucursal(NodoTA* nodo, ArbolTC *arbol, NodoS*& sucActual) 
{
  if (nodo != NULL) 
  {
    mostrarTransaccionesAgrupadasSucursal(nodo->izq, arbol, sucActual);

    if(sucActual == NULL || nodo->trana.s->sucursal.idSucursal != sucActual->sucursal.idSucursal) 
    {
      sucActual = nodo->trana.s;
      // Si cambió el paciente, mostrar información del paciente anterior
      if(sucActual != NULL) 
      {
        cout << "ID Sucursal: " << nodo->trana.s->sucursal.idSucursal << endl;
        cout << "Total generado: " << sucActual->sucursal.dineroGenerado << endl;
        cout << "-----------------------" << endl;
      }

      // Actualizar la información del paciente actual
      if(nodo->trana.h != NULL) 
      {
        sucActual = nodo->trana.s;
      }
      else 
      {
        sucActual = new NodoS; // Crea un nuevo NodoP para almacenar el paciente si no existe
        sucActual->sucursal.idSucursal = -1;
      }
    }

     // Mostrar la transacción actual

    cout << "ID Transaccion: " << nodo->trana.id << endl;
    cout << "Total: " << nodo->trana.total << endl;
    cout << "\n";
    mostrarTransaccionesAgrupadasSucursal(nodo->der, arbol, sucActual);
  }
}

void mostrarTransaccionesAgrupadasHabitaciones(NodoTA* nodo, ArbolTC *arbol, NodoH*& habActual) 
{
  if (nodo != NULL) 
  {
    mostrarTransaccionesAgrupadasHabitaciones(nodo->izq, arbol, habActual);

    if(habActual == NULL || nodo->trana.h->hab.id != habActual->hab.id) 
    {
      habActual = nodo->trana.h;
      // Si cambió el paciente, mostrar información del paciente anterior
      if(habActual != NULL) 
      {
        cout << "ID Habitacion: " << habActual->hab.id << endl;
        cout << "Sucursal: " << nodo->trana.s->sucursal.idSucursal << endl;
        cout << "Total: " << habActual->hab.dineroGenerado << endl;
        cout << "-----------------------" << endl;
      }

      // Actualizar la información del paciente actual
      if(nodo->trana.h != NULL) 
      {
        habActual = nodo->trana.h;
      }
      else 
      {
        habActual = new NodoH; // Crea un nuevo NodoP para almacenar el paciente si no existe
        habActual->hab.id = -1;
      }
    }

     // Mostrar la transacción actual

    cout << "ID Transaccion: " << nodo->trana.id << endl;
    cout << "Total: " << nodo->trana.total << endl;
    cout << "\n";
    mostrarTransaccionesAgrupadasHabitaciones(nodo->der, arbol, habActual);
  }
}

void mostrarTransaccionesAgrupadasDoctores(NodoTA* nodo, ArbolTC *arbol, NodoM*& docActual) 
{
  if (nodo != NULL) 
  {
    mostrarTransaccionesAgrupadasDoctores(nodo->izq, arbol, docActual);

    if(docActual == NULL || nodo->trana.h->hab.medico->medico.dni != docActual->medico.dni) 
    {
      docActual = nodo->trana.h->hab.medico;
      // Si cambió el paciente, mostrar información del paciente anterior
      if(docActual != NULL) 
      {
        cout << "DNI Doctor: " << docActual->medico.dni << endl;
        cout << "Nombre: " << docActual->medico.nombre << " " << docActual->medico.apellido << endl;
        cout << "Pacientes atendidos: " << docActual->medico.pacienteAtendidos << endl;
        cout << "Dinero generado: " << docActual->medico.dineroGenerado << endl;
        cout << "-----------------------" << endl;
      }

      // Actualizar la información del paciente actual
      if(nodo->trana.h != NULL) 
      {
        docActual = nodo->trana.h->hab.medico;
      }
      else 
      {
        docActual = new NodoM; // Crea un nuevo NodoP para almacenar el paciente si no existe
        docActual->medico.dni = -1;
      }
    }

     // Mostrar la transacción actual

    cout << "ID Transaccion: " << nodo->trana.id << endl;
    cout << "Paciente: " << nodo->trana.h->hab.paciente->paciente.nombre << " " << nodo->trana.h->hab.paciente->paciente.apellido << endl;
    cout << "\n";
    mostrarTransaccionesAgrupadasDoctores(nodo->der, arbol, docActual);
  }
}

void mostrarTransaccionesAgrupadasPacientes(NodoTA* nodo, ArbolTC *arbol, NodoP*& pacActual) 
{
  if (nodo != NULL) 
  {
    mostrarTransaccionesAgrupadasPacientes(nodo->izq, arbol, pacActual);
    
    if (pacActual == NULL || nodo->trana.h->hab.paciente->paciente.dni != pacActual->paciente.dni) 
    {
      pacActual = nodo->trana.h->hab.paciente;
      // Si cambió el paciente, mostrar información del paciente anterior
      if (pacActual != NULL) 
      {
        cout << "DNI Paciente: " << pacActual->paciente.dni << endl;
        cout << "Nombre: " << pacActual->paciente.nombre << " " << pacActual->paciente.apellido << endl;
        cout << "Total pagado: " << pacActual->paciente.gastoTotal << endl;
        cout << "-----------------------" << endl;
      }

      // Actualizar la información del paciente actual
      if (nodo->trana.h->hab.paciente != NULL) 
      {
        pacActual = nodo->trana.h->hab.paciente;
      }
      else 
      {
        pacActual = new NodoP; // Crea un nuevo NodoP para almacenar el paciente si no existe
        pacActual->paciente.dni = -1;
      }
    }
    // Mostrar la transacción actual
    cout << "ID Transaccion: " << nodo->trana.id << endl;
    cout << "Fecha de egreso: " << nodo->trana.fechaIngreso << endl;
    cout << "Fecha de egreso: " << nodo->trana.fechaEgreso << endl;
    cout << "Internado: " << nodo->trana.diasInternado << endl;
    cout << "Motivo: " << nodo->trana.motivo << endl;
    cout << "Total: " << nodo->trana.total << endl;
    cout << "\n";
    mostrarTransaccionesAgrupadasPacientes(nodo->der, arbol, pacActual);
  }
}

void mostrarTCPaciente(NodoTA *nodo, int dni, NodoP *i, NodoP *f)
{
  listaDoblePaciente lp;
  NodoP *auxp = lp.encontrarPaciente(i, f, dni);
  
  if(nodo != NULL && auxp != NULL)
  {
    if(dni < nodo->trana.h->hab.paciente->paciente.dni)
    {
      mostrarTCPaciente(nodo->izq, dni, i, f);
    }
    else if(dni > nodo->trana.h->hab.paciente->paciente.dni)
    {
      mostrarTCPaciente(nodo->der, dni, i, f);
    }
    else
    {
      cout << "Paciente: " << nodo->trana.h->hab.paciente->paciente.nombre << " " << nodo->trana.h->hab.paciente->paciente.apellido << endl;
      cout << "Medico: Dr. " << nodo->trana.h->hab.medico->medico.nombre << " " << nodo->trana.h->hab.medico->medico.apellido << endl;
      cout << "Sucursal: " << nodo->trana.s->sucursal.idSucursal << endl;
      cout << "Habitacion: " << nodo->trana.h->hab.id << endl;
      cout << "Fecha entrada: " << nodo->trana.fechaIngreso << endl;
      cout << "Fecha salida: " << nodo->trana.fechaEgreso << endl;
      switch(nodo->trana.especialidad)
      {  
        case 1:
          cout << "Especialidad: Cardiologia" << endl;
          break;
        case 2:
          cout << "Especialidad: Oncologia" << endl;
          break;
        case 3:
          cout << "Especialidad: Neurologia" << endl;
          break;
        case 4:
          cout << "Especialidad: Traumatologia" << endl;
          break;
      }
      cout << "Motivo: " << nodo->trana.motivo << endl;
      cout << "Tarifa: " << nodo->trana.tarifa << endl;
      cout << "Dias internado: " << nodo->trana.diasInternado << endl;
      cout << "Total a pagar: " << nodo->trana.total << endl;
      cout << "\n"; 
      mostrarTCPaciente(nodo->izq, dni, i, f);
      mostrarTCPaciente(nodo->der, dni, i, f);
    }
  }
}

NodoTA *hijoNoNullTC(NodoTA *nodo)
{
  if(nodo->izq != NULL)
  {
    return nodo->izq;
  }
  return nodo->der;
}


//Funcion para calcular la altura de un arbol
int alturaArbolTC(NodoTA *nodo)
{
  if(nodo != NULL)
  {
    int hizq = alturaArbolTC(nodo->izq);
    int hder = alturaArbolTC(nodo->der);
    if(hizq > hder)
    {
      return hizq + 1;
    }
    else
    {
      return hder + 1;
    }
  }
  else
  {
    return 0;
  }
}

//Funcion para calcular el factor de equilibrio de un nodo
int factorEquilibrioTC(NodoTA *nodo)
{
  return alturaArbolTC(nodo->der) - alturaArbolTC(nodo->izq);
}

//Funcion de la rotacion simple a la izquierda
void rotacionIzquierdaTC(ArbolTC *arbol, NodoTA *nodo)
{
  NodoTA *aux, *p, *q;
  aux = nodo->der;
  q = aux->izq;
  p = nodo->padre;

  nodo->der = q;
  aux->izq = nodo;

  if(q != NULL)
  {
    q->padre = nodo;
  }
  nodo->padre = aux;

  if(p == NULL)
  {
    arbol->raiz = aux;
    aux->padre = NULL;
  }
  else
  {
    aux->padre = p;
    if(aux->trana.id < p->trana.id)
    {
      p->izq = aux;
    }
    else
    {
      p->der = aux;
    }
  }

  aux->factorEq = factorEquilibrioTC(aux);
  nodo->factorEq = factorEquilibrioTC(nodo);
}

//Funcion de la rotacion simple a la derecah
void rotacionDerechaTC(ArbolTC *arbol, NodoTA *nodo)
{
  NodoTA *aux, *p, *q;
  aux = nodo->izq;
  q = aux->der;
  p = nodo->padre;

  nodo->izq = q;
  aux->der = nodo;

  if(q != NULL)
  {
    q->padre = nodo;
  }
  nodo->padre = aux;

  if(p == NULL)
  {
    arbol->raiz = aux;
    aux->padre = NULL;
  }
  else
  {
    aux->padre = p;
    if(aux->trana.id < p->trana.id)
    {
      p->izq = aux;
    }
    else
    {
      p->der = aux;
    }
  }

  aux->factorEq = factorEquilibrioTC(aux);
  nodo->factorEq = factorEquilibrioTC(nodo);
}

//Funcion para la rotacion doble izquierda
void rotacionDobleIzquierdaTC(ArbolTC *arbol, NodoTA *nodo)
{
  rotacionDerechaTC(arbol, nodo->der);
  rotacionIzquierdaTC(arbol, nodo);
}

//Funcion para la rotacion doble derecha
void rotacionDobleDerechaTC(ArbolTC *arbol, NodoTA *nodo)
{
  rotacionIzquierdaTC(arbol, nodo->izq);
  rotacionDerechaTC(arbol, nodo);
}

//Funcion para balancear un arbol
void balancearArbolTC(ArbolTC *arbol, NodoTA *nodo)
{
  NodoTA *padre;

  if(nodo != NULL)
  {
    padre = nodo->padre;
    nodo->factorEq = factorEquilibrioTC(nodo);
    if(nodo->factorEq > 1)
    {
      if(factorEquilibrioTC(nodo->der) < 0)
      {
        rotacionDobleIzquierdaTC(arbol, nodo);
      }
      else
      {
        rotacionIzquierdaTC(arbol, nodo);
      }
    }
    else if(nodo->factorEq < -1)
    {
      if(factorEquilibrioTC(nodo->izq) > 0)
      {
        rotacionDobleDerechaTC(arbol, nodo);
      }
      else
      {
        rotacionDerechaTC(arbol, nodo);
      }
    }
    balancearArbolTC(arbol, padre);
  }
}

#endif