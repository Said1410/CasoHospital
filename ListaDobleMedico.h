#ifndef ListaDobleMedico_h
#define ListaDobleMedico_h

#include <iostream>
#include <fstream>
#include "NodoMedico.h"
#include "ListaDoblePaciente.h"

using namespace std;

class listaDobleMedico{

  public:
    listaDobleMedico();
    void agregarMedico(NodoM *&inicio, NodoM *&fin, NodoM *nuevo);
    void modificarMedico(NodoM *&inicio, NodoM *&fin, int dni);
    void eliminarMedico(NodoM *&inicio, NodoM *&fin, int dni);
    void mostrarMedico(NodoM *inicio, NodoM *fin);
    void buscarMedico(NodoM *inicio, NodoM *fin, int dni);
    bool medicoExiste(NodoM *inicio, NodoM *fin, int dni);
    NodoM* encontrarMedico(NodoM *inicio, NodoM *fin, int dni);
    void guardarMedicos(NodoM *inicio);
    void leerMedicos(NodoM *&inicio, NodoM *&fin, int esp);
};

listaDobleMedico::listaDobleMedico() {}

bool listaDobleMedico::medicoExiste(NodoM *inicio, NodoM *fin, int dni)
{
  bool existe = false;

  if(inicio == NULL)
  {
    return existe;
  }
  else
  {
    NodoM *aux = inicio;

    while(aux != NULL)
    {
      if(aux->medico.dni == dni)
      {
        existe = true;
        return existe;
      }
      aux = aux->der;
    }
  }
  return existe;
}

NodoM* listaDobleMedico::encontrarMedico(NodoM *inicio, NodoM *fin, int dni)
{
  if(inicio == NULL)
  {
    return NULL;
  }
  else
  {
    NodoM *aux = inicio;
    while(aux != NULL)
    {
      if(aux->medico.dni == dni)
      {
        return aux;
        break;
      }
      aux = aux->der;
    }
  }

  return NULL;
}

void listaDobleMedico::agregarMedico(NodoM *&inicio, NodoM *&fin,                                               NodoM *nuevo)
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

void listaDobleMedico::modificarMedico(NodoM *&inicio, NodoM *&fin, int dni)
{
  int opc = 0;

  if(listaDobleMedico::medicoExiste(inicio, fin, dni))
  {
    if(inicio == NULL)
    {
      cout << "\nNo hay medicos registrados" << endl;
    }
    else
    {
      NodoM* aux = inicio;
      
      while(aux != NULL)
      {
        if(aux->medico.dni == dni)
        {
          do
          {
            cout << "***** MODIFICAR *****" << endl;
            cout << "1. DNI" << endl;
            cout << "2. Nombre" << endl;
            cout << "3. Apellido" << endl;
            cout << "4. Edad" << endl;
            cout << "5. Especialidad" << endl;
            cout << "6. Salir" << endl;
            cout << "Ingrese una opcion: "; cin >> opc;
            cout << "\033[2J\033[1;1H";
            switch(opc)
            {
              case 1:
                cout << "Ingrese el nuevo DNI: ";
                cin >> aux->medico.dni;
                break;
              case 2:
                cout << "Ingrese el nombre: ";
                cin >> aux->medico.nombre;
                break;
              case 3:
                cout << "Ingrese el apellido: ";
                cin >> aux->medico.apellido;
                break;
              case 4:
                cout << "Ingrese la edad: ";
                cin >> aux->medico.edad;
                break;
              case 5:
                cout << "Ingrese la especialidad: ";
                cin >> aux->medico.especialidad;
                break;
              case 6:
                cout << "\033[2J\033[1;1H";
                break;
              default:
                cout << "\nOpcion invalida" << endl;
                break;
            }
          }while(opc != 6);
          cout << "\033[2J\033[1;1H";
          cout << "Medico modificado exitosamente!" << endl;
          break;
        }
        aux = aux->der;
      }
    }
  }
  else
  {
    cout << "\nNo existe el medico" << endl;
  }
}

void listaDobleMedico::eliminarMedico(NodoM *&inicio, NodoM *&fin, int dni)
{
  if(inicio == NULL)
  {
    cout << "No hay medicos registrados" << endl;
  }
  
  if(medicoExiste(inicio, fin, dni))
  {
    cout << "\nEl medico no existe" << endl;
  }
  
  if(inicio->medico.dni == dni)
  {
    NodoM *auxI = inicio;
    inicio = inicio->der;

    if (inicio != NULL)
        inicio->izq = NULL;

    delete auxI;
  }
  else if(fin->medico.dni == dni)
  {
    NodoM *auxF = fin;
    fin = fin->izq;

    if (fin != NULL)
      fin->der = NULL;

    delete auxF;
  }
  else
  {
    NodoM *aux = inicio;

    while (aux != NULL && aux->medico.dni != dni)
    {
      aux = aux->der;
    }

    if (aux != NULL)
    {
      NodoM *auxI = aux->izq;
      NodoM *auxD = aux->der;

      auxI->der = auxD;

      if (auxD != NULL)
        auxD->izq = auxI;

      delete aux;
      cout << "\033[2J\033[1;1H";
      cout << "Medico eliminado exitosamente!" << endl;
    }
  }
}

void listaDobleMedico::mostrarMedico(NodoM *inicio, NodoM *fin)
{
  if(inicio == NULL)
  {
    cout << "No hay medicos registrados\n" << endl;
  }
  else
  {
    NodoM *aux = inicio;
    while(aux != NULL)
    {
      cout << "DNI: " << aux->medico.dni << endl;
      cout << "Nombre: " << aux->medico.nombre << endl;
      cout << "Apellido: " << aux->medico.apellido << endl;
      cout << "Edad: " << aux->medico.edad << endl;
      cout << "Especialidad: " << aux->medico.especialidad << endl;
      cout << "\n";
      aux = aux->der;
    }
  }
}

void listaDobleMedico::buscarMedico(NodoM *inicio, NodoM *fin, int dni)
{
  bool existe = false;
  NodoM *aux = inicio;
  
  if(inicio == NULL)
  {
    cout << "No hay medicos registrados\n" << endl;
  }
  else
  {
    while(aux != NULL)
    {
      if(aux->medico.dni == dni)
      {
        existe = true;
        break;
      }
      aux = aux->der;
    }

    if(existe)
    {
      cout << "\nDNI: " << aux->medico.dni << endl;
      cout << "Nombre: " << aux->medico.nombre << endl;
      cout << "Apellido: " << aux->medico.apellido << endl;
      cout << "Edad: " << aux->medico.edad << endl;
      cout << "Especialidad: " << aux->medico.especialidad << endl;
    }
    else
    {
      cout << "No se encontro al medico\n" << endl;
    }
  }
}

void listaDobleMedico::guardarMedicos(NodoM *inicio) 
{

  if (inicio == NULL) 
  {
    cout << endl
         << "No se han registrado datos, no se guardaran datos en archivos"
         << endl;
  } 
  else 
  {
    ofstream archivo;
    NodoM *aux = inicio;

    switch(aux->medico.especialidad)
    {
      case 1:
        archivo.open("medicos_cardiologia.txt", ios::out);
        break;
      case 2:
        archivo.open("medicos_oncologia.txt", ios::out);
        break;
      case 3:
        archivo.open("medicos_neurologia.txt", ios::out);
        break;
      case 4:
        archivo.open("medicos_traumatologia.txt", ios::out);
        break;
    }

    if (archivo.fail()) 
    {
      cout << endl << "No se puede abrir el archivo" << endl;
    } 
    else 
    {
      while (aux != NULL) 
      {
        archivo << aux->medico.dni << endl;
        archivo << aux->medico.nombre << endl;
        archivo << aux->medico.apellido << endl;
        archivo << aux->medico.edad << endl;
        archivo << aux->medico.especialidad << endl;
        archivo << aux->medico.pacienteAtendidos << endl;
        archivo << aux->medico.dineroGenerado << endl;
        archivo << "*_*" << endl;
        // Pasamos al siguiente nodo
        aux = aux->der;
      }
      archivo.close();
    }
  }
}

void listaDobleMedico::leerMedicos(NodoM *&inicio, NodoM *&fin, int esp) 
{
  ifstream archivo;
  string linea;
  int numLinea = 0;
  
  // Datos del nodo
  int dni = 0;
  string nombre = "";
  string apellido = "";
  int edad = 0;
  int especialidad = 0;
  int pacAtendidos = 0;
  float generado = 0;
  NodoM *aux;

  switch(esp)
  {
    case 1:
      archivo.open("medicos_cardiologia.txt", ios::in);
      break;
    case 2:
      archivo.open("medicos_oncologia.txt", ios::in);
      break;
    case 3:
      archivo.open("medicos_neurologia.txt", ios::in);
      break;
    case 4:
      archivo.open("medicos_traumatologia.txt", ios::in);
      break;
  }

  if (archivo.fail()) 
  {
    cout << endl << "No se puede abrir el archivo" << endl;
  } 
  else 
  {
    while (!archivo.eof()) 
    {
      Medico m;

      numLinea++;
      getline(archivo, linea);
      m = Medico(dni,nombre,apellido,edad,especialidad,pacAtendidos,generado);
      aux = crearNodoM(m);
      if (linea == "*_*") 
      {
        numLinea = 0;
        agregarMedico(inicio, fin, aux);
      } 
      else if (linea != "")
      {
        switch(numLinea) 
        {
        case 1:
          dni = stoi(linea);
          break;
        case 2:
          nombre = linea;
          break;
        case 3:
          apellido = linea;
          break;
        case 4:
          edad = stoi(linea);
          break;
        case 5:
          especialidad = stoi(linea);
          break;
        case 6:
          pacAtendidos = stoi(linea);
          break;
        case 7:
          generado = stof(linea);
          break;
        }
      }
    }
    archivo.close();
  }
}

#endif