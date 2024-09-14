#pragma once 
#include <iostream>
using namespace std;

class MaterialBibliografico{
    private:
    string nombre;
    string isbn;
    string autor;
    bool prestado;

    public:
    MaterialBibliografico(string nombre, string isbn, string autor);
    string getNombre();
    void setNombre(string nombre);

    string getISBN();
    void setISBN(string isbn);

    string getAutor();
    void setAutor(string autor);

    bool getPrestado();
    void setPrestado(bool prestado);

    virtual void mostrarInformacion();

    ~MaterialBibliografico();
};