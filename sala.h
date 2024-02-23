#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Sala {
  public:
    string nombre;
    vector<pair<Sala*, int>> vecinos;

    Sala(string _nombre) : nombre(_nombre) {}

    void agregarVecino(Sala* vecino, int peso) 
    {
          vecinos.push_back(make_pair(vecino, peso));
    }
};