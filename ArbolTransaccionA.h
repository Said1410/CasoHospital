#ifndef ArbolTransaccionA_h
#define ArbolTransaccionA_h

#include <iostream>
#include "NodoTransaccionAbierta.h"
#include "ArbolHabitacion.h"
#include "ListaDobleSucursal.h"

using namespace std;

struct ArbolTA
{
  NodoTA *raiz;
};

//Prototipos
void balancearArbol(ArbolTA *arbol, NodoTA *nodo);

//Funcion para crear un arbol vacio
ArbolTA *crearArbolTA()
{
  ArbolTA *aux = new ArbolTA();
  aux->raiz = NULL;

  return aux;
}

//Funcion para validar si el arbol esta vacio
bool arbolVacioTA(ArbolTA *arbol) 
{
  if(arbol->raiz == NULL)//La raiz del arbol apunta a NULL
  {
    return true;
  }

  return false;
}
//Disponibilidad
string disponibilidadHab(bool disp)
{
  if(!disp)
  {
    return "Disponible";
  }
  return "No disponible";
}
//Funcion para insertar un nodo en el arbol
void insertarNodoTA(ArbolTA *arbol, NodoTA *nodo)
{
  if(arbolVacioTA(arbol))//Validamos si el arbol esta vacio
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
    balancearArbol(arbol, padre);
  }
}
//Funcion de busqueda del nodo por habitacion 
NodoTA *buscarNodoHabTA(ArbolTA *arbol, int id)
{
  NodoTA *aux = NULL;

  if(!arbolVacioTA(arbol))//Validamos si el arbol esta vacio
  {
    aux = arbol->raiz;//Guardamos la raiz del arbol
    while(aux != NULL && aux->trana.h->hab.id != id)//Busqueda del nodo
    {
      //Direccionamos al nodo por la izquierda o derecha segun el valor del dato
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
//Recorrido del arbol inOrden paciente
void inOrdenTAPac(NodoTA *nodo)
{
  if(nodo != NULL)
  {
    inOrdenTAPac(nodo->izq);
    cout << "Transaccion ID: " << nodo->trana.id << endl;
    cout << "Paciente: " << nodo->trana.h->hab.paciente->paciente.nombre << " " << nodo->trana.h->hab.paciente->paciente.apellido << endl;
    cout << "Sucursal: " << nodo->trana.s->sucursal.idSucursal << endl;
    cout << "Habitacion: " << nodo->trana.h->hab.id << endl;
    switch(nodo->trana.especialidad)
    {
      case 1:
        cout << "Especialidad: Cardiologia" << endl;
        break;
      case 2:
        cout << "Especialidad: Oncologia" << endl;
        break;
      case 3:
        cout << "Espeialidad: Neurologia" << endl;
        break;
      case 4:
        cout << "Especialidad: Traumatologia" << endl;
        break;
    }
    cout << "Fecha de ingreso: " << nodo->trana.fechaIngreso << endl;
    cout << "Tarifa por dia: " << nodo->trana.tarifa << endl;
    cout << "\n";
    inOrdenTAPac(nodo->der);
  }
}
//Recorrido del arbol inOrden medico
void inOrdenTAMed(NodoTA *nodo)
{
  if(nodo != NULL)
  {
    inOrdenTAPac(nodo->izq);
    cout << "Transaccion ID: " << nodo->trana.id << endl;
    cout << "DNI: " << nodo->trana.h->hab.medico->medico.dni << endl;
    cout << "Doctor: Dr. " << nodo->trana.h->hab.medico->medico.nombre << " " << nodo->trana.h->hab.medico->medico.apellido << endl;
    switch(nodo->trana.especialidad)
    {
      case 1:
        cout << "Especialidad: Cardiologia" << endl;
        break;
      case 2:
        cout << "Especialidad: Oncologia" << endl;
        break;
      case 3:
        cout << "Espeialidad: Neurologia" << endl;
        break;
      case 4:
        cout << "Especialidad: Traumatologia" << endl;
        break;
    }
    cout << "Sucursal: " << nodo->trana.s->sucursal.idSucursal << endl;
    cout << "Habitacion: " << nodo->trana.h->hab.id << endl;
    cout << "\n";
    inOrdenTAPac(nodo->der);
  }
}
//Recorrido del arbol inOrden habitacion
void inOrdenTAHab(NodoTA *nodo)
{
  if(nodo != NULL)
  {
    inOrdenTAPac(nodo->izq);
    cout << "Transaccion ID: " << nodo->trana.id << endl;
    cout << "Sucursal: " << nodo->trana.s->sucursal.idSucursal << endl;
    cout << "Habitacion: " << nodo->trana.h->hab.id << endl;
    cout << "Estado: " << disponibilidadHab(nodo->trana.h->hab.estado) << endl;
    cout << "Paciente: " << nodo->trana.h->hab.paciente->paciente.nombre << " " << nodo->trana.h->hab.paciente->paciente.apellido << endl;
    cout << "Medico: " << nodo->trana.h->hab.medico->medico.nombre << " " << nodo->trana.h->hab.medico->medico.apellido << endl;
    cout << "\n";
    inOrdenTAPac(nodo->der);
  }
}
//Recorrido del arbol inOrden sucursal
void inOrdenTASuc(ArbolTA *arbol)
{
  if(!arbolVacioTA(arbol))
  {
    NodoTA *nodo = arbol->raiz;
    
    if(nodo != NULL)
    {
      inOrdenTAPac(nodo->izq);
      cout << "Sucursal: " << nodo->trana.s->sucursal.idSucursal << endl;
      if(!nodo->trana.s->sucursal.habitaciones.empty())
      {
        for (const auto& habitacion : nodo->trana.s->sucursal.habitaciones)
        {
          cout << "\nHabitacion: " << habitacion->hab.id << endl;
          cout << "Estado: " << disponibilidadHab(habitacion->hab.estado) << endl;
          NodoTA *aux2 = buscarNodoHabTA(arbol, habitacion->hab.id);
          if(aux2 != NULL)
          {
            cout << "Transaccion ID: " << aux2->trana.id << endl;
          }
          else
          {
            cout << "Transaccion ID: No registrado"  << endl;
          }
        }
      }
      cout << "\n";
      inOrdenTAPac(nodo->der);
    }
  }
  else
  {
    cout << "El arbol esta vacio\n" << endl;
  }
}
//Funcion de busqueda del nodo 
NodoTA *buscarNodoPacienteTA(ArbolTA *arbol, int dni)
{
  NodoTA *aux = NULL;

  if(!arbolVacioTA(arbol))//Validamos si el arbol esta vacio
  {
    aux = arbol->raiz;//Guardamos la raiz del arbol
    while(aux != NULL && aux->trana.h->hab.paciente->paciente.dni != dni)//Busqueda del nodo
    {
      //Direccionamos al nodo por la izquierda o derecha segun el valor del dato
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

NodoTA *hijoNoNull(NodoTA *nodo)
{
  if(nodo->izq != NULL)
  {
    return nodo->izq;
  }
  return nodo->der;
}
//Funcion para modificar un nodo
void modificarTransaccionAbierta(ArbolTA *arbol, int dni)
{
  NodoTA *aux = buscarNodoPacienteTA(arbol, dni);//Buscamos el nodo a eliminar
  int opc = 0;

  if(aux != NULL)//Validamos si el nodo existe
  {
    do
    {
      cout << "1. Modificar especialidad" << endl;
      cout << "2. Modificar fecha de ingreso" << endl;
      cout << "3. Modificar tarifa" << endl;
      cout << "4. Salir" << endl;
      cout << "Ingrese una opcion: ";
      cin >> opc;
      cout << "\033[2J\033[1;1H";
      switch(opc)
      {
        case 1:
          cout << "Ingrese la nueva especialidad: ";
          cin >> aux->trana.especialidad;
          cout << "\n";
          break;        
        case 2:
          cout << "Ingrese la nueva fecha de ingreso: ";
          cin >> aux->trana.fechaIngreso;
          cout << "\n";
          break;
        case 3:
          cout << "Ingrese la nueva tarifa: ";
          cin >> aux->trana.tarifa;
          cout << "\n";
          break;
        case 4:
          break;
        default:
          cout << "Opcion invalida\n" << endl;
          break;
      }
    }while(opc != 4);
    cout << "\033[2J\033[1;1H";
    cout << "Transaccion abierta modificada con exito" << endl << endl;
  }
  else
  {
    cout << "El paciente no tiene transacciones abiertas\n" << endl;
  }
}
//Funcion para eliminar un nodo
void eliminarNodoTA(ArbolTA *arbol, int dni)
{
  NodoTA *aux = buscarNodoPacienteTA(arbol,dni);//Buscamos el nodo a eliminar
  NodoTA *aux2;
  NodoTA *padre;
  if (aux != NULL) 
  {
    cout << "\033[2J\033[1;1H";
    padre = aux->padre;
    if (aux->izq == NULL && aux->der == NULL) 
    { 
      if (padre != NULL) 
      {               
        if (aux->trana.id < padre->trana.id) 
        {
          padre->izq = NULL;
        } 
        else 
        {
          padre->der = NULL;
        }
      } 
      else 
      {
        arbol->raiz = NULL;
      }
      delete aux;
    } 
    else if (aux->der == NULL || aux->izq == NULL) 
    { 
      if (padre != NULL) 
      {       
        if (aux->trana.id < padre->trana.id) 
        {
          padre->izq = hijoNoNull(aux);
          padre->izq->padre = padre;
        } 
        else 
        {
          padre->der = hijoNoNull(aux);
          padre->der->padre = padre;
        }
      } 
      else 
      {
        arbol->raiz = hijoNoNull(aux);
        arbol->raiz->padre = NULL;
      }
      delete aux;
    } 
    else 
    { // Si el nodo tiene dos hijos
      aux2 = aux->izq;
      while (aux2->der != NULL) 
      {
        aux2 = aux2->der;
      }
      padre = aux2->padre;
      if (aux2->trana.id < padre->trana.id) 
      {
        padre->izq = aux2->izq;
      } 
      else 
      {
        padre->der = aux2->izq;
      }
      aux->trana.id = aux2->trana.id;
      delete aux2;
    }
    cout << "Transaccion abierta eliminada con exito\n" << endl;
    balancearArbol(arbol, padre);
  }
  else
  {
    cout << "El paciente no tiene una transaccion abierta\n" << endl;
  }
}

//Funcion para eliminar un nodo habitacion
void eliminarNodoHabTA(ArbolTA *arbol, int id)
{
  NodoTA *aux = buscarNodoHabTA(arbol,id);//Buscamos el nodo a eliminar
  NodoTA *aux2;
  NodoTA *padre;

  if (aux != NULL) 
  {
    padre = aux->padre;
    if (aux->izq == NULL && aux->der == NULL) 
    { 
      if (padre != NULL) 
      {               
        if (aux->trana.id < padre->trana.id) 
        {
          padre->izq = NULL;
        } 
        else 
        {
          padre->der = NULL;
        }
      } 
      else 
      {
        arbol->raiz = NULL;
      }
      delete aux;
    } 
    else if (aux->der == NULL || aux->izq == NULL) 
    { 
      if (padre != NULL) 
      {       
        if (aux->trana.id < padre->trana.id) 
        {
          padre->izq = hijoNoNull(aux);
          padre->izq->padre = padre;
        } 
        else 
        {
          padre->der = hijoNoNull(aux);
          padre->der->padre = padre;
        }
      } 
      else 
      {
        arbol->raiz = hijoNoNull(aux);
        arbol->raiz->padre = NULL;
      }
      delete aux;
    } 
    else 
    { // Si el nodo tiene dos hijos
      aux2 = aux->izq;
      while (aux2->der != NULL) 
      {
        aux2 = aux2->der;
      }
      padre = aux2->padre;
      if (aux2->trana.id < padre->trana.id) 
      {
        padre->izq = aux2->izq;
      } 
      else 
      {
        padre->der = aux2->izq;
      }
      aux->trana.id = aux2->trana.id;
      delete aux2;
    }
    balancearArbol(arbol, padre);
  }
  else
  {
    cout << "No se encontro la habitacion\n" << endl;
  }
}
//Funcion para calcular la altura de un arbol
int alturaArbol(NodoTA *nodo)
{
  if(nodo != NULL)
  {
    int hizq = alturaArbol(nodo->izq);
    int hder = alturaArbol(nodo->der);
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
int factorEquilibrio(NodoTA *nodo)
{
  return alturaArbol(nodo->der) - alturaArbol(nodo->izq);
}

//Funcion de la rotacion simple a la izquierda
void rotacionIzquierda(ArbolTA *arbol, NodoTA *nodo)
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

  aux->factorEq = factorEquilibrio(aux);
  nodo->factorEq = factorEquilibrio(nodo);
}

//Funcion de la rotacion simple a la derecah
void rotacionDerecha(ArbolTA *arbol, NodoTA *nodo)
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

  aux->factorEq = factorEquilibrio(aux);
  nodo->factorEq = factorEquilibrio(nodo);
}

//Funcion para la rotacion doble izquierda
void rotacionDobleIzquierda(ArbolTA *arbol, NodoTA *nodo)
{
  rotacionDerecha(arbol, nodo->der);
  rotacionIzquierda(arbol, nodo);
}

//Funcion para la rotacion doble derecha
void rotacionDobleDerecha(ArbolTA *arbol, NodoTA *nodo)
{
  rotacionIzquierda(arbol, nodo->izq);
  rotacionDerecha(arbol, nodo);
}

//Funcion para balancear un arbol
void balancearArbol(ArbolTA *arbol, NodoTA *nodo)
{
  NodoTA *padre;

  if(nodo != NULL)
  {
    padre = nodo->padre;
    nodo->factorEq = factorEquilibrio(nodo);
    if(nodo->factorEq > 1)
    {
      if(factorEquilibrio(nodo->der) < 0)
      {
        rotacionDobleIzquierda(arbol, nodo);
      }
      else
      {
        rotacionIzquierda(arbol, nodo);
      }
    }
    else if(nodo->factorEq < -1)
    {
      if(factorEquilibrio(nodo->izq) > 0)
      {
        rotacionDobleDerecha(arbol, nodo);
      }
      else
      {
        rotacionDerecha(arbol, nodo);
      }
    }
    balancearArbol(arbol, padre);
  }
}

#endif