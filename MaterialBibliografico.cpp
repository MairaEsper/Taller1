#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

MaterialBibliografico::MaterialBibliografico(string nombre, string isbn, string autor){
    this -> nombre = nombre;
    this -> isbn = isbn;
    this -> autor = autor;
    this -> prestado = false;
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

bool MaterialBibliografico::getPrestado(){
    return prestado;
}
void MaterialBibliografico::setPrestado(bool prestado){
    this -> prestado = false;
}

void MaterialBibliografico::mostrarInformacion(){}

MaterialBibliografico::~MaterialBibliografico(){}