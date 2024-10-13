#pragma once
#include <iostream>
#include "../Headers/MaterialBibliografico.h"
using namespace std;

class Revista:public MaterialBibliografico{
    private:
    int numeroEdicion;
    string mesPublicacion;

    public:
    Revista(string nombre, string isbn, string autor, string tipo, int numeroEdicion, string mesPublicacion);
    int getNumeroEdicion();
    void setNumeroEdicion(int numeroEdicion);

    string getMesPublicacion();
    void setMesPublicacion(string mesPublicacion);

    void mostrarInformacion();

    ~Revista();
};