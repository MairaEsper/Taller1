#pragma once 
#include <iostream>
using namespace std;

class MaterialBibliografico{
    private:
    string nombre;
    string isbn;
    string autor;
    bool prestado;
    string tipo;

    public:
    MaterialBibliografico(string nombre, string isbn, string autor, string tipo);
    string getNombre();
    void setNombre(string nombre);

    string getISBN();
    void setISBN(string isbn);

    string getAutor();
    void setAutor(string autor);

    string getTipo();
    void setTipo(string tipo);

    bool getPrestado();
    void setPrestado(bool prestado);

    virtual void mostrarInformacion();

    ~MaterialBibliografico();
};