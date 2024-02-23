#ifndef ListaDoblePaciente_h
#define ListaDoblePaciente_h

#include <iostream>
#include <fstream>
#include "NodoPaciente.h"

using namespace std;

class listaDoblePaciente{

  public:
    listaDoblePaciente();
    void agregarPaciente(NodoP *&inicio, NodoP *&fin, NodoP *nuevo);
    void modificarPaciente(NodoP *&inicio, NodoP *&fin, int dni);
    void eliminarPaciente(NodoP *&inicio, NodoP *&fin, int dni);
    void mostrarPaciente(NodoP *inicio, NodoP *fin);
    void buscarPaciente(NodoP *inicio, NodoP *fin, int dni);
    bool pacienteExiste(NodoP *inicio, NodoP *fin, int dni);
    NodoP* encontrarPaciente(NodoP *inicio, NodoP *fin, int dni);
    void guardarPacientes(NodoP *inicio);
    void leerPacientes(NodoP *&inicio, NodoP *&fin);
};

listaDoblePaciente::listaDoblePaciente() {}

bool listaDoblePaciente::pacienteExiste(NodoP *inicio, NodoP *fin, int dni)
{
  bool existe = false;

  if(inicio == NULL)
  {
    return existe;
  }
  else
  {
    NodoP *aux = inicio;

    while(aux != NULL)
    {
      if(aux->paciente.dni == dni)
      {
        existe = true;
        return existe;
      }
      aux = aux->der;
    }
  }
  return existe;
}

void listaDoblePaciente::agregarPaciente(NodoP *&inicio, NodoP *&fin, NodoP *nuevo)
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

void listaDoblePaciente::modificarPaciente(NodoP *&inicio, NodoP *&fin, int dni)
{
  int opc = 0;

  if(listaDoblePaciente::pacienteExiste(inicio, fin, dni))
  {
    if(inicio == NULL)
    {
      cout << "\nNo hay pacientes registrados" << endl;
    }
    else
    {
      NodoP* aux = inicio;
      while(aux != NULL)
      {
        if(aux->paciente.dni == dni)
        {
          do
          {
            cout << "***** MODIFICAR *****" << endl;
            cout << "1. DNI" << endl;
            cout << "2. Nombre" << endl;
            cout << "3. Apellido" << endl;
            cout << "4. Edad" << endl;
            cout << "5. Sexo" << endl;
            cout << "6. Peso" << endl;
            cout << "7. Altura" << endl;
            cout << "8. Salir" << endl;
            cout << "Ingrese una opcion: "; cin >> opc;
            cout << "\033[2J\033[1;1H";
            switch(opc)
            {
              case 1:
                cout << "Ingrese el dni: ";
                cin >> aux->paciente.dni;
                break;
              case 2:
                cout << "Ingrese el nombre: ";
                cin >> aux->paciente.nombre;
                break;
              case 3:
                cout << "Ingrese el apellido: ";
                cin >> aux->paciente.apellido;
                break;
              case 4:
                cout << "Ingrese la edad: ";
                cin >> aux->paciente.edad;
                break;
              case 5:
                cout << "Ingrese el sexo: ";
                cin >> aux->paciente.sexo;
                break;
              case 6:
                cout << "Ingrese el peso: ";
                cin >> aux->paciente.peso;
                break;
              case 7:
                cout << "Ingrese la altura: ";
                cin >> aux->paciente.altura;
                break;
              case 8:
                cout << "\033[2J\033[1;1H";
                break;
              default:
                cout << "\nOpcion invalida" << endl;
                break;
            }
            cout << "\n";
          }while(opc != 8);
          cout << "\033[2J\033[1;1H";
          cout << "Paciente modificado exitosamente!" << endl;
          break;
        }
        aux = aux->der;
      }
    }
  }
  else
  {
    cout << "\nNo existe el paciente" << endl;
  }
}

void listaDoblePaciente::eliminarPaciente(NodoP *&inicio, NodoP *&fin, int dni)
{
  if(inicio == NULL)
  {
    cout << "No hay pacientes registrados" << endl;
    return;
  }

  if (!pacienteExiste(inicio, fin, dni))
  {
    cout << "\nNo existe el paciente" << endl;
    return;
  }

  if (inicio->paciente.dni == dni)
  {
      NodoP *auxI = inicio;
      inicio = inicio->der;

      if (inicio != NULL)
          inicio->izq = NULL;

      delete auxI;
  }
  else if (fin->paciente.dni == dni)
  {
      NodoP *auxF = fin;
      fin = fin->izq;

      if (fin != NULL)
          fin->der = NULL;

      delete auxF;
  }
  else
  {
      NodoP *aux = inicio;

      while (aux != NULL && aux->paciente.dni != dni)
      {
          aux = aux->der;
      }

      if (aux != NULL)
      {
          NodoP *auxI = aux->izq;
          NodoP *auxD = aux->der;

          auxI->der = auxD;

          if (auxD != NULL)
              auxD->izq = auxI;

          delete aux;
          cout << "\033[2J\033[1;1H";
          cout << "Paciente eliminado exitosamente!" << endl;
      }
  }
}

void listaDoblePaciente::mostrarPaciente(NodoP *inicio, NodoP *fin)
{
  if(inicio == NULL)
  {
    cout << "\nNo hay pacientes registrados" << endl;
  }
  else
  {
    NodoP *aux = inicio;
    
    while(aux != NULL)
    {
      cout << "DNI: " << aux->paciente.dni << endl;
      cout << "Nombre: " << aux->paciente.nombre << endl;
      cout << "Apellido: " << aux->paciente.apellido << endl;
      cout << "Sexo: " << aux->paciente.sexo << endl;
      cout << "Edad: " << aux->paciente.edad << endl;
      cout << "Peso: " << aux->paciente.peso << endl;
      cout << "\n";
      aux = aux->der;
    }
  }
}

void listaDoblePaciente::buscarPaciente(NodoP *inicio, NodoP *fin, int dni)
{
  bool existe = false;
  NodoP *aux = inicio;

  if(inicio == NULL)
  {
    cout << "\nNo hay pacientes registrados" << endl;
  }
  else
  {
    while(aux != NULL)
    {
      if(aux->paciente.dni == dni)
      {
        existe = true;
        break;
      }
      aux = aux->der;
    }

    if(existe)
    {
      cout << "Paciente: \n" << endl;
      cout << "DNI: " << aux->paciente.dni << endl;
      cout << "Nombre: " << aux->paciente.nombre << endl;
      cout << "Apellido: " << aux->paciente.apellido << endl;
      cout << "Sexo: " << aux->paciente.sexo << endl;
      cout << "Edad: " << aux->paciente.edad << endl;
      cout << "Peso: " << aux->paciente.peso << endl;
      cout << "Altura: " << aux->paciente.altura << endl;
    }
    else
    {
      cout << "\nNo se encontro al paciente" << endl;
    }
  }
}

void listaDoblePaciente::guardarPacientes(NodoP *inicio) 
{

  if (inicio == NULL) 
  {
    cout << endl
         << "\nNo se han registrado datos, no se guardaran datos en archivos"
         << endl;
  } 
  else 
  {
    ofstream archivo;
    NodoP *aux = inicio;

    archivo.open("pacientes.txt", ios::out);

    if (archivo.fail()) 
    {
      cout << "No se puede abrir el archivo" << endl;
    } 
    else 
    {
      while (aux != NULL) 
      {
        archivo << aux->paciente.dni << endl;
        archivo << aux->paciente.nombre << endl;
        archivo << aux->paciente.apellido << endl;
        archivo << aux->paciente.sexo << endl;
        archivo << aux->paciente.edad << endl;
        archivo << aux->paciente.peso << endl;
        archivo << aux->paciente.altura << endl;
        archivo << aux->paciente.gastoTotal << endl;
        archivo << "*_*" << endl;
        // Pasamos al siguiente nodo
        aux = aux->der;
      }
      archivo.close();
    }
  }
}

void listaDoblePaciente::leerPacientes(NodoP *&inicio, NodoP *&fin) 
{
  ifstream archivo;
  string linea;
  int numLinea = 0;

  // Datos del nodo
  int dni = 0;
  string nombre = "";
  string apellido = "";
  string sexo = "";
  int edad = 0;
  float peso = 0;
  float altura = 0;
  NodoP *aux;
  double gastoTotal = 0;

  archivo.open("pacientes.txt", ios::in);

  if (archivo.fail()) 
  {
    cout << "No se puede abrir el archivo" << endl << endl;
  } 
  else 
  {
    while (!archivo.eof()) 
    {
      Paciente p;

      numLinea++;
      getline(archivo, linea);
      p = Paciente(dni,nombre,apellido,sexo,edad,peso,altura,gastoTotal);
      aux = crearNodoP(p);
      if (linea == "*_*") 
      {
        numLinea = 0;
        agregarPaciente(inicio, fin, aux);
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
          sexo = linea;
          break;
        case 5:
          edad = stoi(linea);
          break;
        case 6:
          peso = stof(linea);
          break;
        case 7:
          altura = stof(linea);
          break;
        case 8:
          gastoTotal = stod(linea);
          break;
        }
      }
    }
    archivo.close();
  }
}

NodoP* listaDoblePaciente::encontrarPaciente(NodoP *inicio, NodoP *fin,                                                  int dni)
{
  if(inicio == NULL)
  {
    return NULL;
  }
  else
  {
    NodoP *aux = inicio;
    while(aux != NULL)
    {
      if(aux->paciente.dni == dni)
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