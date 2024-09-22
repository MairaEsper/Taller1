#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Revista:public MaterialBibliografico{
    private:
    int numeroEdicion;
    string mesPublicacion;

    public:
    Revista(string nombre, string isbn, string autor, int numeroEdicion, string mesPublicacion);
    int getNumeroEdicion();
    void setNumeroEdicion(int numeroEdicion);

    string getMesPublicacion();
    void setMesPublicacion(string mesPublicacion);

    void mostrarInformacion();

    ~Revista();
};