#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

MaterialBibliografico::MaterialBibliografico(string nombre, string isbn, string autor, string tipo){
    this -> nombre = nombre;
    this -> isbn = isbn;
    this -> autor = autor;
    this -> prestado = false;
    this -> tipo = tipo;
}

string MaterialBibliografico::getNombre(){
    return nombre;
}
void MaterialBibliografico::setNombre(string nombre){
    this -> nombre = nombre;
}

string MaterialBibliografico::getISBN(){
    return isbn;
}
void MaterialBibliografico::setISBN(string isbn){
    this -> isbn = isbn;
}

string MaterialBibliografico::getAutor(){
    return autor;
}
void MaterialBibliografico::setAutor(string autor){
    this -> autor = autor;
}

string MaterialBibliografico::getTipo(){
    return tipo;
}
void MaterialBibliografico::setTipo(string tipo){
    this -> tipo = tipo;
}

bool MaterialBibliografico::getPrestado(){
    return prestado;
}
void MaterialBibliografico::setPrestado(bool prestado){
    this -> prestado = prestado;
}

void MaterialBibliografico::mostrarInformacion(){
    cout<<"Nombre: " + this -> nombre + "\nISBN: " + this -> isbn + "\nAutor:"+ this -> autor<<endl;}

MaterialBibliografico::~MaterialBibliografico(){cout<<"Se destruye Material"<<endl;}