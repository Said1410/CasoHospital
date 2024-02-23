#include <iostream>
#include <limits>
#include <queue>
#include <map>
#include <algorithm>
#include "sala.h"

using namespace std;

class SalaDeEmergencia {
  public:
    map<string, Sala*> salas;

    void agregarSala(string nombre) 
    {
      Sala* nuevaSala = new Sala(nombre);
      salas[nombre] = nuevaSala;
    }

    void agregarConexion(string sala1, string sala2, int peso) 
    {
      Sala* s1 = salas[sala1];
      Sala* s2 = salas[sala2];
      if(s1 != NULL && s2 != NULL)
      {
        s1->agregarVecino(s2, peso);
        s2->agregarVecino(s1, peso);
      }
      else
      {
        cout << "Error: Alguna de las salas no existe.\n" << endl;
      }
    }

    void eliminarSala(string nombre) 
    {
      auto it = salas.find(nombre);
      if (it != salas.end()) 
      {
        Sala* salaEliminar = it->second;

        for (auto& par : salas) 
        {
          Sala* sala = par.second;
          auto itVecino = find_if(sala->vecinos.begin(), sala->vecinos.end(), [salaEliminar](const pair<Sala*, int>& vecino) 
          {
            return vecino.first == salaEliminar;
          });

          if (itVecino != sala->vecinos.end()) 
          {
            sala->vecinos.erase(itVecino);
          }
        }

        delete salaEliminar;
        salas.erase(it);
        cout << "Sala eliminada con exito!\n" << endl;
      }
      else
      {
        cout << "Error: La sala no existe.\n" << endl;
      }
    }

    void eliminarConexion(string sala1, string sala2) 
    {
      Sala* s1 = salas[sala1];
      Sala* s2 = salas[sala2];

      if(s1 != NULL && s2 != NULL)
      {
        auto itVecinoS1 = find_if(s1->vecinos.begin(), s1->vecinos.end(),
              [s2](const pair<Sala*, int>& vecino) 
        {
          return vecino.first == s2;
        });

        auto itVecinoS2 = find_if(s2->vecinos.begin(), s2->vecinos.end(),
              [s1](const pair<Sala*, int>& vecino) 
        {
          return vecino.first == s1;
        });

        if (itVecinoS1 != s1->vecinos.end() && itVecinoS2 != s2->vecinos.end()) 
        {
          s1->vecinos.erase(itVecinoS1);
          s2->vecinos.erase(itVecinoS2);
        }
      }
      else
      {
        cout << "Error: Alguna de las salas no existe.\n" << endl;  
      }
    }

    void modificarSala(string nombre, string nuevoNombre) 
    {
      auto it = salas.find(nombre);
      if (it != salas.end()) 
      {
        Sala* salaModificar = it->second;
        salaModificar->nombre = nuevoNombre;
        salas.erase(it);
        salas[nuevoNombre] = salaModificar;
        cout << "Sala modificada con exito!\n" << endl;
      }
      else
      {
        cout << "Error: La sala no existe.\n" << endl;
      }
    }

    void modificarPesoConexion(string sala1, string sala2, int nuevoPeso) 
    {
      Sala* s1 = salas[sala1];
      Sala* s2 = salas[sala2];

      if(s1 != NULL && s2 != NULL)
      {
        auto itVecinoS1 = find_if(s1->vecinos.begin(), s1->vecinos.end(),
              [s2](const pair<Sala*, int>& vecino) 
        {
          return vecino.first == s2;
        });

        auto itVecinoS2 = find_if(s2->vecinos.begin(), s2->vecinos.end(),
              [s1](const pair<Sala*, int>& vecino) 
        {
          return vecino.first == s1;
        });

        if (itVecinoS1 != s1->vecinos.end() && itVecinoS2 != s2->vecinos.end()) {
          itVecinoS1->second = nuevoPeso;
          itVecinoS2->second = nuevoPeso;
        }

        cout << "Peso de la conexion modificado con exito!\n" << endl;
      }
      else
      {
        cout << "Error: Alguna de las salas no existe.\n" << endl; 
      }
    }

    void dijkstra(string inicio) 
    {
      priority_queue<pair<int, Sala*>, vector<pair<int, Sala*>>, greater<pair<int, Sala*>>> pq;
      map<Sala*, int> distancias;

      for (auto& par : salas) 
      {
        Sala* sala = par.second;
        distancias[sala] = numeric_limits<int>::max();
      }

      Sala* salaInicio = salas[inicio];
      if(salaInicio != NULL)
      {
        distancias[salaInicio] = 0;
        pq.push(make_pair(0, salaInicio));

        while (!pq.empty()) 
        {
          Sala* actual = pq.top().second;
          pq.pop();

          for (auto& vecino : actual->vecinos) 
          {
            Sala* salaVecino = vecino.first;
            int peso = vecino.second;

            if (distancias[actual] + peso < distancias[salaVecino]) 
            {
              distancias[salaVecino] = distancias[actual] + peso;
              pq.push(make_pair(distancias[salaVecino], salaVecino));
            }
          }
        }

        cout << "Camino más corto desde la sala " << inicio << " a todas las demás salas:" << endl;
        for (auto& par : distancias) 
        {
          Sala* sala = par.first;
          int distancia = par.second;

          cout << "Sala: " << sala->nombre << ", Distancia: " << distancia << endl;
        }
      }
      else
      {
        cout << "Error: La sala de inicio no existe.\n" << endl;
      }
    }

    void mostrarNodosAdyacentes() 
    {
      cout << "Nodos adyacentes para cada sala:\n" << endl;
      for (auto& par : salas) 
      {
        Sala* sala = par.second;
        cout  << sala->nombre << " :" << endl << endl;

        for (auto& vecino : sala->vecinos) 
        {
          Sala* salaVecino = vecino.first;
          cout << salaVecino->nombre << " -> ";
        }

        cout << endl << endl;;
      }
    }

    void mostrarRecorridoDijkstra(string inicio) 
    {
      map<Sala*, Sala*> padres;

      priority_queue<pair<int, Sala*>, vector<pair<int, Sala*>>, greater<pair<int, Sala*>>> pq;
      map<Sala*, int> distancias;

      for (auto& par : salas) 
      {
        Sala* sala = par.second;
        distancias[sala] = numeric_limits<int>::max();
      }

      Sala* salaInicio = salas[inicio];
      distancias[salaInicio] = 0;
      pq.push(make_pair(0, salaInicio));

      while (!pq.empty()) 
      {
        Sala* actual = pq.top().second;
        pq.pop();

        for (auto& vecino : actual->vecinos) 
        {
          Sala* salaVecino = vecino.first;
          int peso = vecino.second;

          if (distancias[actual] + peso < distancias[salaVecino]) 
          {
            distancias[salaVecino] = distancias[actual] + peso;
            padres[salaVecino] = actual; // Actualizamos el padre del vecino en el camino más corto
            pq.push(make_pair(distancias[salaVecino], salaVecino));
          }
        }
      }

      cout << "Recorrido desde la sala " << inicio << " a todas las demás salas:" << endl;
      for (auto& par : salas) 
      {
        Sala* salaDestino = par.second;
        cout << "Hacia Sala " << salaDestino->nombre << ": ";

        Sala* salaActual = salaDestino;
        while (salaActual != nullptr) 
        {
          cout << salaActual->nombre;
          salaActual = padres[salaActual];

          if (salaActual != nullptr) 
          {
            cout << " <- ";
          }
        }

        cout << ", Distancia: " << distancias[salaDestino] << endl;
      }
    }
};
