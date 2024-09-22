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

void crearLibro(){
    cout<<"Ingrese la fecha de publicación (11-22-3333): "; //problema menor revisar despues
    string fechaPublicacion;
    cin>>fechaPublicacion;

    cout<<"Ingrese el resumen: "; 
    string resumen;
    getline(cin, resumen); 

}

void crearRevista(){
    cout<<"Ingrese el número de edición: "; 
    int numeroEdicion;
    cin>>numeroEdicion;

    cout<<"Ingrese el mes de publicación: ";
    string mesPublicacion;
    cin>>mesPublicacion;

}

void agregarMateriales(MaterialBibliografico* biblioteca[]){
    cout<<"Ingrese el material bibliográfico que desea agregar (1. Libro / 2. Revista): ";
    int material;
    cin>>material;

    cout<<"Ingrese el nombre del material: "; 
    string nombre;
    getline(cin, nombre);

    cout<<"Ingrese el ISBN:";
    string isbn;
    cin>>isbn;

    cout<<"Ingrese el autor:";
    string autor;
    cin>>autor;

    string fechaPublicacion;
    string resumen;
    int numeroEdicion;
    string mesPublicacion;

    switch(material){
        case 1:
            cout<<"Ingrese la fecha de publicación (11-22-3333): "; 
            cin>>fechaPublicacion;

            cout<<"Ingrese el resumen: "; 
            cin>>resumen;
            break;

        case 2:
            cout<<"Ingrese el número de edición: "; 
            cin>>numeroEdicion;

            cout<<"Ingrese el mes de publicación (11-22-3333): "; 
            cin>>mesPublicacion;
            break;

        default:
            cout<<"La opción que eligió es incorrecta/no existe"<<endl;
            break;
    }

}
void mostrarInfo(){}
void buscarMaterial(){}
void prestarYDevolverMaterial(){}
void gestionUsuarios(){}

int Main(){
    MaterialBibliografico* biblioteca[100];
    mostrarMenu();
    int opcion;
    cin>>opcion;
    
    switch(opcion){
        case 1:
        break;

        case 2:
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