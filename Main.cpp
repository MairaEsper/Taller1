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

bool hayMaterial(MaterialBibliografico* biblioteca[],int tamaño){
    for(int i = 0;i < tamaño;i++){
        if(biblioteca[i] !=nullptr){
            return true;
        }
    }
    return false;
}
void mostrarInfo(MaterialBibliografico* biblioteca[], int tamaño){
    bool hayMateriales = hayMaterial(biblioteca, tamaño);
    if(hayMateriales){
        for(int i = 0;i < tamaño;i++){
            if(biblioteca[i] !=nullptr){
                biblioteca[i]->mostrarInformacion();
            }
        }
    } else {
        cout<<"La Biblioteca está vacía."<<endl;
    }
}

void buscarMaterial(MaterialBibliografico* biblioteca[], int tamaño){
    string respuesta;
    bool hayMateriales = hayMaterial(biblioteca, tamaño);
    
    if(hayMateriales){
        bool encontrado = false;
        do{
            cout<<"Ingrese el título o autor: ";
            cin>>respuesta;
            
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
        }while(!encontrado);
    }else{
        cout<<"La Biblioteca está vacía."<<endl;
    }
    
}
//Función para buscar materiales por título o autor utilizando búsquedas lineales en el array.



void prestar(MaterialBibliografico* biblioteca[], int tamaño, string tituloAutor){
    bool hayMateriales = hayMaterial(biblioteca, tamaño);
    if(hayMateriales){
        bool encontrado = false;
        for(int i = 0; i < tamaño; i++){
            if (biblioteca[i] != nullptr) {
                    if (biblioteca[i]->getNombre() == tituloAutor && biblioteca[i]->getPrestado() == false) {
                        biblioteca[i]-> setPrestado(true);
                        encontrado = true;
                        cout<<"El material ha sido prestado con exito"<<endl;
                        return;
                    }else if(biblioteca[i]->getNombre() == tituloAutor && biblioteca[i]->getPrestado() == true){
                        cout<<"Este material ya esta prestado."<<endl;
                        encontrado = true;
                        return;
                    }
            }
        }
        if (!encontrado) {
                cout<<"No se encontraron resultados para: "<<tituloAutor<<endl;
            }
    }else{
        cout<<"La Biblioteca está vacía."<<endl;
    }
}


void devolver(MaterialBibliografico* biblioteca[], int tamaño, string tituloNombre){
    for(int i = 0; i < tamaño; i++){
        
    }
}

void prestarYDevolverMaterial(MaterialBibliografico* biblioteca[], int tamaño){
    int opcion;
    cout<<"1.Prestar"<<endl;
    cout<<"2.Devolver"<<endl;
    cout<<"Ingrese una opcion: ";
    cin>>opcion;
    string tituloAutor;
    cout<<"Ingrese titulo o nombre: ";
    cin>>tituloAutor;
    switch(opcion){
        case 1:
        prestar(biblioteca,tamaño,tituloAutor);
        break;

        case 2:
        devolver(biblioteca,tamaño,tituloAutor);
        break;

        default:
        cout<<"la opción no es válida"<<endl;
        break;
    }
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
        buscarMaterial(biblioteca,tamaño);
        break;

        case 4:
        break;

        default:
        cout<<"la opción no es válida"<<endl;
        break;
    }
    return 0;
}