#pragma once
#include <iostream>
#include "../Headers/MaterialBibliografico.h"
using namespace std;

class Libro:public MaterialBibliografico{
    private:
    string fechaPublicacion;
    string resumen;

    public: 
    Libro(string nombre, string isbn, string autor, string tipo, string fechaPublicacion, string resumen);
    string getFechaPublicacion();
    void setFechaPublicacion(string getFechaPublicacion);

    string getResumen();
    void setResumen(string resumen);

    void mostrarInformacion();

    ~Libro();
};