#pragma once
#include <iostream>
#include "../Headers/MaterialBibliografico.h"
using namespace std;

class Usuario{
    private:
    string nombre;
    int id;
    MaterialBibliografico* materialesPrestados[5];

    public:
    Usuario(string nombre, int id);
    string getNombre();
    void setNombre(string nombre);

    int getId();
    void setId(int id);

    bool prestarMaterial(MaterialBibliografico* material);
    bool devolverMaterial(MaterialBibliografico* material);
    MaterialBibliografico** getLista();
    void mostrarMaterialesPrestados();
    ~Usuario();
};