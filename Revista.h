#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Revista:public MaterialBibliografico{
    private:
    int numeroEdicion;
    int mesPublicacion;

    public:
    Revista(string nombre, string isbn, string autor, int numeroEdicion, int mesPublicacion);
    int getNumeroEdicion();
    void setNumeroEdicion(int numeroEdicion);

    int getMesPublicacion();
    void setMesPublicacion(int mesPublicacion);

    void mostrarInformacion();

    ~Revista();
};