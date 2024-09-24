#include <iostream>
#include "Usuario.h"
using namespace std;

Usuario::Usuario(string nombre, int id){
    this -> nombre = nombre;
    this -> id = id;
    for(int i= 0; i < 5; i++){
        this -> materialesPrestados[i] = nullptr;    
    }
}

string Usuario::getNombre(){
    return nombre;
}
void Usuario::setNombre(string nombre){
    this -> nombre = nombre;
}

int Usuario::getId(){
    return id;
}
void Usuario::setId(int id){
    this -> id = id;
}

void Usuario::prestarMaterial(){}
void Usuario::devolverMaterial(){}
void Usuario::mostrarMaterialesPrestados(){}

Usuario::~Usuario(){}
