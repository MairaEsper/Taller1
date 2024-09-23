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
    cout<<"6. Salir"<<endl;
    cout<<"Elija una opción: ";
}

bool validarFecha(const string& fecha) {
    if (fecha.length() == 10 && fecha[2] == '-' && fecha[5] == '-') {
        return true;
    } else {
        return false;
    }
}
void agregarALista(MaterialBibliografico* biblioteca[], int medida, MaterialBibliografico* mb){
    for(int i = 0; i < medida; i++){
        if(biblioteca[i] == nullptr){
            biblioteca[i] = mb;
            return;  
        }
    }
    cout<<"La biblioteca está llena";
}
void crearLibro(string nombre, string isbn, string autor, MaterialBibliografico* biblioteca[], int medida){
    string fechaPublicacion;
    do{
        cout<<"Ingrese la fecha de publicación(dd-mm-yyyy): "; 
        cin>>fechaPublicacion;
        if(!validarFecha(fechaPublicacion)){
            cout<<"Formato incorrecto. Porfavor ingrese la fecha en el formato dd-mm-yyyy"<<endl;
        }
    }while(!validarFecha(fechaPublicacion));
    cin.ignore();
    cout<<"Ingrese el resumen: "; 
    string resumen;
    getline(cin, resumen); 

    Libro* libro = new Libro(nombre, isbn, autor, "libro", fechaPublicacion, resumen);
    agregarALista(biblioteca, medida, libro);
    
}

void crearRevista(string nombre, string isbn, string autor, MaterialBibliografico* biblioteca[], int medida){
    cout<<"Ingrese el número de edición: "; 
    int numeroEdicion;
    cin>>numeroEdicion;

    cout<<"Ingrese el mes de publicación: ";
    string mesPublicacion;
    cin>>mesPublicacion;

    Revista* revista = new Revista(nombre, isbn, autor, "revista", numeroEdicion, mesPublicacion);
    agregarALista(biblioteca, medida, revista);

}

void agregarMateriales(MaterialBibliografico* biblioteca[], int medida){
    int material;
    string nombre;
    string isbn;
    string autor;

    cout<<"Ingrese el material bibliográfico que desea agregar (1. Libro / 2. Revista): ";
    cin>>material;

    cin.ignore();
    cout<<"Ingrese el nombre del material: "; 
    getline(cin, nombre);

    cout<<"Ingrese el ISBN:";
    cin>>isbn;

    cin.ignore();
    cout<<"Ingrese el autor:";
    getline(cin, autor);
    

    switch(material){
        case 1:
            crearLibro(nombre, isbn, autor, biblioteca, medida);
            break;

        case 2:
            crearRevista(nombre, isbn, autor, biblioteca, medida);
            break;

        default:
            cout<<"La opción que eligió es incorrecta/no existe"<<endl;
            break;
    }

}
bool hayMaterial(MaterialBibliografico* biblioteca[],int medida){
    for(int i = 0;i < medida;i++){
        if(biblioteca[i] != nullptr){
            return true;
        }
    }
    return false;
}
void mostrarInfo(MaterialBibliografico* biblioteca[], int medida){
    bool hayMateriales = hayMaterial(biblioteca, medida);
    if(hayMateriales){
        for(int i = 0;i < medida;i++){
            if(biblioteca[i] != nullptr){
                biblioteca[i]->mostrarInformacion();
            }
        }
    }else{
        cout<<"La Biblioteca esta vacia."<<endl;
    }
}

void buscarMaterial(MaterialBibliografico* biblioteca[], int medida){
    string respuesta;
    bool hayMateriales = hayMaterial(biblioteca, medida);
    
    if(hayMateriales){
        bool encontrado = false;
        do{
            cout<<"Ingrese el titulo o autor: ";
            cin>>respuesta;
            
            for (int i = 0; i < medida; i++) {
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
        cout<<"La Biblioteca esta vacia."<<endl;
    }
    
}
void prestar(MaterialBibliografico* biblioteca[], int medida, string tituloAutor){
    bool hayMateriales = hayMaterial(biblioteca, medida);
    if(hayMateriales){
        bool encontrado = false;
        for(int i = 0; i < medida; i++){
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
        cout<<"La Biblioteca esta vacia."<<endl;
    }
}


void devolver(MaterialBibliografico* biblioteca[], int medida,string tituloAutor){
    bool hayMateriales = hayMaterial(biblioteca, medida);
    if(hayMateriales){
        bool encontrado = false;
        for(int i = 0; i < medida; i++){
            if (biblioteca[i] != nullptr) {
                    if (biblioteca[i]->getNombre() == tituloAutor && biblioteca[i]->getPrestado() == false) {
                        biblioteca[i]-> setPrestado(true);
                        encontrado = true;
                        cout<<"El material ha sido devuelto con exito"<<endl;
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
        cout<<"La Biblioteca esta vacia."<<endl;
    }
}

void prestarYDevolverMaterial(MaterialBibliografico* biblioteca[], int medida){
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
        prestar(biblioteca,medida,tituloAutor);
        break;

        case 2:
        devolver(biblioteca,medida,tituloAutor);
        break;

        default:
        cout<<"la opcion no es valida"<<endl;
        break;
    }
}
void gestionUsuarios(){
    cout<<"1. Crear usuario";
    cout<<"2. Buscar usuario";
    cout<<"3. Eliminar usuario";
    cout<<"Ingrese una opción: ";
    int opcionUsuario;
    cin>>opcionUsuario;

    switch(opcionUsuario){
        case 1:
        break;

        case 2:
        break;

        case 3:
        break;

        default:
        cout<<"la opcion no es valida"<<endl;
        break;
    }
} //Implementar la funcionalidad para crear, buscar y eliminar usuarios. Asociar materiales prestados a usuarios específicos. 
    

int main(){
    int medida = 100;
    MaterialBibliografico* biblioteca[medida] = {nullptr};
    int opcion;
    do{
        mostrarMenu();
        cin>>opcion;
        
        switch(opcion){
            case 1:
            agregarMateriales(biblioteca,medida);
            break;

            case 2:
            mostrarInfo(biblioteca,medida);
            break;

            case 3:
            buscarMaterial(biblioteca,medida);
            break;

            case 4:
            break;

            case 5:
            break;

            case 6:
            cout<<"Sistema Cerrado";
            break;

            default:
            cout<<"la opcion no es valida"<<endl;
            break;
        }
    }while(opcion !=6);
    return 0;
}