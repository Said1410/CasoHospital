#ifndef Hospitals_h
#define Hospitals_h

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class HospitalUtils 
{
  public:
    bool login(unordered_map<string, string>& credenciales, const string& username, const string& password) 
    {
      if (credenciales.find(username) != credenciales.end() && 
          credenciales[username] == password) 
      {
        return true;// Credenciales válidas
      }
      return false;// Credenciales inválidas
    }

    void registrarUsuario(unordered_map<string, string>& credenciales, const string& username, const string& password) 
    {
      // Verificar si el usuario ya existe
      if (credenciales.find(username) == credenciales.end()) 
      {
      // Usuario no encontrado, se puede registrar
        credenciales[username] = password;
        cout << "Usuario registrado exitosamente." << endl;
      } 
      else
      {
        // Usuario ya existe
        cout << "El usuario ya existe. Por favor, elija otro nombre de usuario." << endl;
      }
    }
};



#endif
