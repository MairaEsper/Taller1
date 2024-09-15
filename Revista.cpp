#include <iostream>
#include "Revista.h"
using namespace std;

Revista::Revista(string nombre, string isbn, string autor, int numeroEdicion, int mesPublicacion):MaterialBibliografico(nombre, isbn, autor){
    this -> numeroEdicion = numeroEdicion;
    this -> mesPublicacion = mesPublicacion;
}

int Revista::getNumeroEdicion(){
    return numeroEdicion;
}
void Revista::setNumeroEdicion(int numeroEdicion){
    this -> numeroEdicion = numeroEdicion;
}

int Revista::getMesPublicacion(){
    return mesPublicacion;
}
void Revista::setMesPublicacion(int mesPublicacion){
    this -> mesPublicacion = mesPublicacion;
}

void Revista::mostrarInformacion(){}

Revista::~Revista(){}