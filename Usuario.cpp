#include <iostream>
#include "Usuario.h"
using namespace std;

Usuario::Usuario(string nombre, string id){
    this -> nombre = nombre;
    this -> id = id;
}

string Usuario::getNombre(){
    return nombre;
}
void Usuario::setNombre(string nombre){
    this -> nombre = nombre;
}

string Usuario::getId(){
    return id;
}
void Usuario::setId(string id){
    this -> id = id;
}

bool Usuario::prestarMaterial(){}
bool Usuario::devolverMaterial(){}
void Usuario::mostrarMaterialesPrestados(){}

Usuario::~Usuario(){}
