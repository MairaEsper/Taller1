#include <iostream>
#include "Libro.h"
using namespace std;

Libro::Libro(string nombre, string isbn, string autor, string tipo, string fechaPublicacion, string resumen):MaterialBibliografico(nombre, isbn, autor, tipo){
    this -> fechaPublicacion = fechaPublicacion;
    this -> resumen = resumen;
}

string Libro::getFechaPublicacion(){
    return fechaPublicacion;
}
void Libro::setFechaPublicacion(string fechaPublicacion){
    this -> fechaPublicacion = fechaPublicacion;
}

string Libro::getResumen(){
    return resumen;
}
void Libro::setResumen(string resumen){
    this -> resumen = resumen;
}

void Libro::mostrarInformacion(){
    cout<<"Nombre: " + this -> nombre + "\nFecha de publicación: " + fechaPublicacion + "\nResumen: " + resumen;
}

Libro::~Libro(){}

