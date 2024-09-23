#include <iostream>
#include "MaterialBibliografico.h"
#include "Libro.h"
#include "Revista.h"
#include "Usuario.h"
using namespace std;

void mostrarMenu(){
    cout<<"1. Agregar material a la biblioteca"<<endl;
    cout<<"2. Mostrar información de los materiales"<<endl;
    cout<<"3. Buscar material"<<endl;
    cout<<"4. Prestar y devolver material"<<endl;
    cout<<"5. Gestión de usuarios"<<endl;
    cout<<"Elija una opción: ";
}

bool validarFecha(const string& fecha) {
    if (fecha.length() == 10 && fecha[2] == '-' && fecha[5] == '-') {
        return true;
    } else {
        return false;
    }
}

void crearLibro(string nombre, string isbn, string autor, MaterialBibliografico* biblioteca[], int tamaño){
    string fechaPublicacion;
    do{
        cout<<"Ingrese la fecha de publicación(dd-mm-yyyy): "; 
        cin>>fechaPublicacion;
        if(!validarFecha(fechaPublicacion)){
            cout<<"Formato incorrecto. Porfavor ingrese la fecha en el formato dd-mm-yyyy"<<endl;
        }
    }while(!validarFecha(fechaPublicacion));
    cout<<"Ingrese el resumen: "; 
    string resumen;
    getline(cin, resumen); 

    Libro* libro = new Libro(nombre, isbn, autor, "libro", fechaPublicacion, resumen);
    agregarALista(biblioteca, tamaño, libro);
    
}

void crearRevista(string nombre, string isbn, string autor, MaterialBibliografico* biblioteca[], int tamaño){
    cout<<"Ingrese el número de edición: "; 
    int numeroEdicion;
    cin>>numeroEdicion;

    cout<<"Ingrese el mes de publicación: ";
    string mesPublicacion;
    cin>>mesPublicacion;

    Revista* revista = new Revista(nombre, isbn, autor, "revista", numeroEdicion, mesPublicacion);
    agregarALista(biblioteca, tamaño, revista);

}

void agregarALista(MaterialBibliografico* biblioteca[], int tamaño, MaterialBibliografico* mb){
    for(int i = 0; i > tamaño; i++){
        if(biblioteca[i] == nullptr){
            biblioteca[i] = mb;
            return;  
        }
    }
    cout<<"La biblioteca está llena";
}


void agregarMateriales(MaterialBibliografico* biblioteca[], int tamaño){
    int material;
    string nombre;
    string isbn;
    string autor;

    cout<<"Ingrese el material bibliográfico que desea agregar (1. Libro / 2. Revista): ";
    cin>>material;

    cout<<"Ingrese el nombre del material: "; 
    getline(cin, nombre);

    cout<<"Ingrese el ISBN:";
    cin>>isbn;

    cout<<"Ingrese el autor:";
    cin>>autor;

    switch(material){
        case 1:
            crearLibro(nombre, isbn, autor, biblioteca, tamaño);
            break;

        case 2:
            crearRevista(nombre, isbn, autor, biblioteca, tamaño);
            break;

        default:
            cout<<"La opción que eligió es incorrecta/no existe"<<endl;
            break;
    }

}

void mostrarInfo(MaterialBibliografico* biblioteca[], int tamaño){
    bool hayMateriales = false;
    for(int i = 0;i < tamaño;i++){
        if(biblioteca[i] !=nullptr){
            biblioteca[i]->mostrarInformacion();
            cout<<endl;
            hayMateriales = true;
        }
    }
    if(!hayMateriales){cout<<"La Biblioteca está vacía."<<endl;}
}

void buscarMaterial(MaterialBibliografico* biblioteca[], int tamaño){
    string respuesta;
    cout<<"Ingrese el título o autor: ";
    cin>>respuesta;
    bool encontrado = false;
     for (int i = 0; i < tamaño; i++) {
        if (biblioteca[i] != nullptr) {
            if (biblioteca[i]->getNombre() == respuesta) {
                biblioteca[i]->mostrarInformacion();
                encontrado = true;
            }
            if (biblioteca[i]->getAutor() == respuesta) {
                biblioteca[i]->mostrarInformacion();
                encontrado = true;
            }
        }
    }
    if (!encontrado) {
        cout<<"No se encontraron resultados para: "<<respuesta<<endl;
    }
}

    for(int i = 0; i > tamaño, i++){
        if(respuesta == biblioteca[i]->getNombre() or respuesta == biblioteca[i]->getAutor()){
            cout<<"Título: " + biblioteca[i]->getNombre() + "\nISBN: " + biblioteca[i]->getISBN() + "\nAutor: " + biblioteca[i]->getAutor();
        }
    }
} //Función para buscar materiales por título o autor utilizando búsquedas lineales en el array. 

void prestarYDevolverMaterial(biblioteca){
    
}
void gestionUsuarios(){} //Implementar la funcionalidad para crear, buscar y eliminar usuarios. Asociar materiales prestados a usuarios específicos. 


int Main(){
    int tamaño = 100;
    MaterialBibliografico* biblioteca[tamaño];
    mostrarMenu();
    int opcion;
    cin>>opcion;
    
    switch(opcion){
        case 1:
        agregarMateriales(biblioteca,tamaño);
        break;

        case 2:
        mostrarInfo(biblioteca,tamaño);
        break;

        case 3:
        break;

        case 4:
        break;

        default:
        cout<<"la opción no es válida"<<endl;
        break;
    }
    return 0;
}