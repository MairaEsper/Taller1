#pragma once
#include <iostream>
#include "MaterialBibliografico.h"
using namespace std;

class Usuario{
    private:
    string nombre;
    string id;
    MaterialBibliografico* materialesPrestados[5];

    public:
    Usuario(string nombre, string id);
    string getNombre();
    void setNombre(string nombre);

    string getId();
    void setId(string id);

    void prestarMaterial();
    void devolverMaterial();
    void mostrarMaterialesPrestados();
    ~Usuario();
};