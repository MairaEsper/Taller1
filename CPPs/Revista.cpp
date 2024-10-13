#include <iostream>
#include "../Headers/Revista.h"
using namespace std;

Revista::Revista(string nombre, string isbn, string autor,string tipo,int numeroEdicion, string mesPublicacion):MaterialBibliografico(nombre, isbn, autor, tipo){
    this -> numeroEdicion = numeroEdicion;
    this -> mesPublicacion = mesPublicacion;
}

int Revista::getNumeroEdicion(){
    return numeroEdicion;
}
void Revista::setNumeroEdicion(int numeroEdicion){
    this -> numeroEdicion = numeroEdicion;
}

string Revista::getMesPublicacion(){
    return mesPublicacion;
}
void Revista::setMesPublicacion(string mesPublicacion){
    this -> mesPublicacion = mesPublicacion;
}

void Revista::mostrarInformacion(){
    cout<<"\nNombre: " + this -> nombre + "\nISBN: " + this -> isbn + "\nAutor: " + this -> autor + "\nNumero edicion: "<< this -> numeroEdicion << "\nMes publicacion: " + mesPublicacion<<endl;
}

Revista::~Revista(){cout<<"Se destruye Revista"<<endl;}