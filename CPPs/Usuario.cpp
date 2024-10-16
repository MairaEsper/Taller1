#include <iostream>
#include "../Headers/Usuario.h"
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

bool Usuario::prestarMaterial(MaterialBibliografico* material){
    for (int i = 0; i < 5; i++){
            if(materialesPrestados[i] == nullptr){
                materialesPrestados[i] = material;
                return true;
            }
    }
    return false;
}
bool Usuario::devolverMaterial(MaterialBibliografico* material){
    for (int i = 0; i < 5; i++){
        if(materialesPrestados[i] != nullptr && material->getNombre() == materialesPrestados[i]->getNombre()){
            materialesPrestados[i] = nullptr;
            return true;    
        }
    }
    return false; 
}

MaterialBibliografico** Usuario::getLista(){
    return materialesPrestados;
}

void Usuario::mostrarMaterialesPrestados(){
    cout<<"Sus materiales prestados son: "<<endl;
    bool hayMateriales = false;
    for (int i = 0; i < 5; i++){
        if(materialesPrestados[i] != nullptr){
            cout<<"\n-"+materialesPrestados[i]->getTipo();
            materialesPrestados[i]->mostrarInformacion();
            hayMateriales = true;
        }
    }
    if (!hayMateriales){
        cout<<"No tiene materiales"<<endl;
    }
    
    
}

Usuario::~Usuario(){}
