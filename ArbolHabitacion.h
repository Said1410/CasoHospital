#ifndef ArbolHabitacion_h
#define ArbolHabitacion_h

#include <iostream>
#include "NodoHabitacion.h"
#include "ArbolTransaccionA.h"
#include "ArbolTransaccionC.h"

using namespace std;

struct ArbolH
{
  NodoH *raiz;
};

//Prototipos
void balancearArbol(ArbolH *arbol, NodoH *nodo);

//Funcion para crear un arbol vacio
ArbolH *crearArbolH()
{
  ArbolH *aux = new ArbolH();
  aux->raiz = NULL;

  return aux;
}

//Funcion para validar si el arbol esta vacio
bool arbolVacio(ArbolH *arbol) 
{
  if(arbol->raiz == NULL)//La raiz del arbol apunta a NULL
  {
    return true;
  }

  return false;
}

//Funcion para insertar un nodo en el arbol
void insertarNodoH(ArbolH *arbol, NodoH *nodo)
{
  if(arbolVacio(arbol))//Validamos si el arbol esta vacio
  {
    arbol->raiz = nodo;//Cumplida la condicion, la raiz del arbol apunta al nodo
  }
  else// De no estar vacio
  {
    NodoH *aux = arbol->raiz; //Creamos un auxiliar que almacena la raiz del arbol
    NodoH *padre; // Variable para almacenar el padre del nodo actual

    while(aux != NULL)//Recorrido del arbol hasta el ultimo nodo
    {
      padre = aux; // Guardamos el nodo actual en la variable padre

      if(nodo->hab.id < aux->hab.id)//Si el dato es menor, vamos a la izquierda
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
    if(nodo->hab.id < padre->hab.id)
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

string disponibilidad(bool disp)
{
  if(!disp)
  {
    return "Disponible";
  }
  return "No disponible";
}

//Recorrido del arbol inOrden habitaciones 
void mostrarHabitaciones(NodoH *nodo)
{
  if(nodo != NULL)
  {
    mostrarHabitaciones(nodo->izq);
    cout << "ID: " << nodo->hab.id << endl;
    cout << "Disponibilidad: " << disponibilidad(nodo->hab.estado) << endl;
    mostrarHabitaciones(nodo->der);
  }
}

//Funcion de busqueda de habitacion por id
NodoH *buscarNodoHabitacion(ArbolH *arbol, int id)
{
  NodoH *aux = NULL;

  if(!arbolVacio(arbol))//Validamos si el arbol esta vacio
  {
    aux = arbol->raiz;//Guardamos la raiz del arbol
    while(aux != NULL && aux->hab.id != id)//Busqueda del nodo
    {
      //Direccionamos al nodo por la izquierda o derecha segun el valor del dato
      if(id < aux->hab.id)
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
//Asignar habitacion
void asignarHabitacion(NodoH *habitacion, NodoP *paciente, NodoM *medico)
{
  if(habitacion != NULL)
  {
    if(habitacion->hab.estado == false)
    {
      habitacion->hab.estado = true;
      habitacion->hab.paciente = paciente;
      habitacion->hab.medico = medico;
      cout << "\033[2J\033[1;1H";
      cout << "Habitacion asignada exitosamente!\n" << endl;
    }
    else
    {
      cout << "Habitacion ocupada\n" << endl;
    }
  }
}
//Quitar asignacion de habitacion
void quitarAsignarHabitacion(NodoH *habitacion)
{
  if(habitacion != NULL)
  {
    if(habitacion->hab.estado == true)
    {
      habitacion->hab.estado = false;
      habitacion->hab.paciente = NULL;
      habitacion->hab.medico = NULL;
      cout << "\033[2J\033[1;1H";
      cout << "La Habitacion ha sido desocupada exitosamente!\n" << endl;
    }
    else
    {
      cout << "Habitacion ocupada\n" << endl;
    }
  }
}

//Atender paciente
void atenderPaciente(NodoTA *auxta, ArbolTC *arboltc, ArbolTA *arbolta, int dni)
{
  vector<NodoH*> habitaciones;
  TransaccionAbierta ta;
  Habitacion h;
  Sucursal s;
  NodoH *auxh = auxta->trana.h;
  //Habitacion
  NodoH *auxh2;
  int id = auxh->hab.id;
  int tam = auxh->hab.tam;
  NodoP *auxp = auxh->hab.paciente;
  NodoM *auxm = auxh->hab.medico;
  bool estado = auxh->hab.estado;
  float dineroG = auxh->hab.dineroGenerado;
  //Sucural
  NodoS *auxs = auxta->trana.s;
  //NodoS *auxs2;
  //int ids = auxs->sucursal.idSucursal;
  //habitaciones = auxs->sucursal.habitaciones;
  //Transaccion abierta
  NodoTA *aux2;
  float tarifa = auxta->trana.tarifa;
  float total;
  string fechaIngreso = auxta->trana.fechaIngreso;
  string fechaEgreso;
  string motivo;
  int dias;
  int especialidad = auxta->trana.especialidad;
  long idT = auxta->trana.id;
  
  cout << "Ingrese la fecha de egreso: ";
  cin >> fechaEgreso;
  cout << "Ingrese el motivo: ";
  cin >> motivo;
  cout << "Ingrese la cantidad de dias de internado: ";
  cin >> dias;

  
  total = dias * tarifa;
  cout << total << endl;
  auxp->paciente.gastoTotal += total;
  auxm->medico.pacienteAtendidos++;
  auxm->medico.dineroGenerado += total;
  auxh->hab.dineroGenerado += auxp->paciente.gastoTotal;
  auxs->sucursal.dineroGenerado += total;

  dineroG = auxh->hab.dineroGenerado;
  
  h = Habitacion(id, tam, auxp, auxm, estado, dineroG);
  auxh2 = crearNodoH(h);
  
  //s = Sucursal(ids, habitaciones);
  //auxs2 = crearNodoS(s);

  ta = TransaccionAbierta(idT, especialidad, fechaIngreso, fechaEgreso, tarifa, dias, total, motivo, auxh2, auxs);
  
  aux2 = crearNodoTA(ta);
  insertarNodoTC(arboltc, aux2);
  eliminarNodoHabTA(arbolta, auxh->hab.id);
  quitarAsignarHabitacion(auxh);

  cout << "\033[2J\033[1;1H";
  cout << "El paciente ha sido atendido\n" << endl;
}

//Funcion para reasignar una habitacion
void reasignarHabitacion(NodoH* auxh, NodoTA* auxta, ArbolTA *arbol, NodoS *auxs)
{
  NodoTA *aux2 = auxta;
  NodoH *aux = auxta->trana.h;
  NodoP *auxp = aux->hab.paciente;
  NodoM *auxm = aux->hab.medico;
  
  eliminarNodoHabTA(arbol, aux->hab.id);
  quitarAsignarHabitacion(aux);
  asignarHabitacion(auxh, auxp, auxm);

  aux2->trana.s = auxs;
  aux2->trana.h = auxh;
  insertarNodoTA(arbol, aux2);
}

//Funcion de busqueda del paciente en la habitacion 
NodoH *buscarNodoHabitacionPac(ArbolH *arbol, int dni)
{
  NodoH *aux = NULL;

  if(!arbolVacio(arbol))//Validamos si el arbol esta vacio
  {
    aux = arbol->raiz;//Guardamos la raiz del arbol
    while(aux != NULL && aux->hab.paciente->paciente.dni != dni)//Busqueda del nodo
    {
      //Direccionamos al nodo por la izquierda o derecha segun el valor del dato
      if(dni < aux->hab.paciente->paciente.dni)
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

//Funcion de busqueda del paciente en la habitacion 
void mostrarNodoHabitacionPac(ArbolH *arbol, int id)
{
  NodoH *aux = NULL;

  if(!arbolVacio(arbol))//Validamos si el arbol esta vacio
  {
    aux = arbol->raiz;//Guardamos la raiz del arbol
    while(aux != NULL && aux->hab.id != id)//Busqueda del nodo
    {
      //Direccionamos al nodo por la izquierda o derecha segun el valor del dato
      if(id < aux->hab.id)
      {
        aux = aux->izq;
      }
      else
      {
        aux = aux->der;  
      }
    }
  }
  
  if(aux != NULL)
  {
    cout << "Habitacion: " << aux->hab.id << endl;
    cout << "Tamaño: " << aux->hab.tam << endl;
    if(aux->hab.paciente != NULL)
    {
      cout << "DNI: " << aux->hab.paciente->paciente.dni << endl;
      cout << "Paciente: " << aux->hab.paciente->paciente.nombre << " " << aux->hab.paciente->paciente.apellido <<endl;
    }
    else
    {
      cout << "Paciente: No asigando" << endl;
    }
    if(aux->hab.medico != NULL)
    {
      cout << "Medico: " << aux->hab.medico->medico.nombre << " " << aux->hab.medico->medico.apellido << endl;
    }
    else
    {
      cout << "Medico: No asignado" << endl;
    }
    cout << endl << endl;
  }
  else
  {
    cout << "No se encontro la habitacion\n" << endl;
  }
}

void asignarSucursalHab(int ids, int idh, NodoS *inicio, NodoS *fin, ArbolH *arbol)
{
  listaDobleSucursal ls;
  NodoS *auxs = ls.encontrarSucursal(inicio, fin, ids);
  if(auxs != NULL)
  {
    NodoH *auxh = buscarNodoHabitacion(arbol, idh);
    if(auxh != NULL)
    {
      
      auxs->sucursal.agregarHabitacion(auxh);
      cout << "Habitacion asiganada con exito!\n" << endl;
    }
    else
    {
      cout << "No se encontro la habitacion\n" << endl;
    }
  }
  else
  {
    cout << "No se encontro la sucursal\n" << endl;
  }
}

NodoH *hijoNoNull(NodoH *nodo)
{
  if(nodo->izq != NULL)
  {
    return nodo->izq;
  }
  return nodo->der;
}


void eliminarNodoH(ArbolH *arbol, int id)
{
  NodoH *aux = buscarNodoHabitacion(arbol,id);//Buscamos el nodo a eliminar
  NodoH *aux2;
  NodoH *padre;

  if(aux != NULL)//Validamos si el nodo existe
  {
    if(aux->hab.medico == NULL)
    {
      if(aux->hab.paciente == NULL)
      {
        padre = aux->padre;
        if (aux->izq == NULL && aux->der == NULL) 
        { 
          if (padre != NULL) 
          {                     
            if (aux->hab.id < padre->hab.id) 
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
            if (aux->hab.id < padre->hab.id) 
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
          if (aux2->hab.id < padre->hab.id)
          {
            padre->izq = aux2->izq;
          } 
          else 
          {
            padre->der = aux2->izq;
          }
          aux->hab.id = aux2->hab.id;
          delete aux2;
        }
        cout << "Habitacion eliminada exitosamente\n" << endl;
        balancearArbol(arbol, padre);
      }
      else
      {
        cout << "Hay un paciente asignado a la habitacion\n" << endl;
      }
    }
    else
    {
      cout << "Hay un medico asignado a la habitacion\n" << endl;
    }
  }
  else
  {
    cout << "La habitacion no existe\n" << endl;
  }
}


void modificarNodoH(ArbolH *arbol, int id)
{
  Habitacion h;
  NodoH *aux = buscarNodoHabitacion(arbol,id);
  NodoH *aux2;
  bool estado = aux->hab.estado;
  int tam = aux->hab.tam;
  NodoP *p = aux->hab.paciente;
  NodoM *m = aux->hab.medico;
  float dineroG = 0;

  if(aux->hab.medico == NULL && aux->hab.paciente == NULL)
  {
    int opc = 0;
    int disp;
    do
    {
      cout << "***** MODIFICAR *****" << endl;
      cout << "1. Modificar ID" << endl;
      cout << "2. Modificar Tamaño" << endl;
      cout << "3. Modificar Disponibilidad" << endl;
      cout << "4. Salir" << endl;
      cout << "Opcion: "; cin >> opc;
      cout << "\033[2J\033[1;1H";
      switch(opc)
      {
        case 1:
          int id2;
          eliminarNodoH(arbol, id);
          cout << "Ingrese el nuevo ID: "; 
          cin >> id2;
          h = Habitacion(id2, tam, p, m, estado, dineroG);
          aux2 = crearNodoH(h);
          insertarNodoH(arbol, aux2);
          break;
        case 2:
          cout << "Ingrese el nuevo tamaño: ";
          cin >> aux->hab.tam;
         break;
        case 3:
          do
          {
            cout << "Ingrese la nueva disponibilidad: " << endl;
            cout << "1. Disponible" << endl;
            cout << "2. No disponible" << endl;
            cout << "3. Salir" << endl;
            cout << "Opcion: "; cin >> disp;
            cout << "\033[2J\033[1;1H";
            switch(disp)
            {
              case 1:
                aux->hab.estado = false;
                break;
              case 2:
                aux->hab.estado = true;
                break;
              case 3:
                cout << "\033[2J\033[1;1H";
                break;
              default:
                cout << "Opcion invalida\n" << endl;
            }
          }while(disp < 1 || disp > 3);
          break;
        case 4:
          cout << "\033[2J\033[1;1H";
         break;
        default:
          cout << "Opcion invalida\n" << endl;
      }
      cout << "\033[2J\033[1;1H";
      cout << "Habitacion modificada exitosamente\n" << endl;
    }while(opc != 4);
  }
  else
  {
     cout << "La habitacion tiene un medico o un paciente asignado\n" << endl; 
  }
}
//Balanceo del arbol
//Funcion para calcular la altura de un arbol
int alturaArbol(NodoH *nodo)
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
int factorEquilibrio(NodoH *nodo)
{
  return alturaArbol(nodo->der) - alturaArbol(nodo->izq);
}
//Funcion de la rotacion simple a la izquierda
void rotacionIzquierda(ArbolH *arbol, NodoH *nodo)
{
  NodoH *aux, *p, *q;
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
    if(aux->hab.id < p->hab.id)
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
void rotacionDerecha(ArbolH *arbol, NodoH *nodo)
{
  NodoH *aux, *p, *q;
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
    if(aux->hab.id < p->hab.id)
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
void rotacionDobleIzquierda(ArbolH *arbol, NodoH *nodo)
{
  rotacionDerecha(arbol, nodo->der);
  rotacionIzquierda(arbol, nodo);
}
//Funcion para la rotacion doble derecha
void rotacionDobleDerecha(ArbolH *arbol, NodoH *nodo)
{
  rotacionIzquierda(arbol, nodo->izq);
  rotacionDerecha(arbol, nodo);
}
//Funcion para balancear un arbol
void balancearArbol(ArbolH *arbol, NodoH *nodo)
{
  NodoH *padre;

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