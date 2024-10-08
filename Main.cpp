#include <iostream>
#include "MaterialBibliografico.h"
#include "Libro.h"
#include "Revista.h"
#include "Usuario.h"
#include <fstream>
using namespace std;

void mostrarMenu(){
    cout<<"\n==================MENU================"<<endl;
    cout<<"1. Agregar material a la biblioteca"<<endl;
    cout<<"2. Mostrar informacion de los materiales"<<endl;
    cout<<"3. Buscar material"<<endl;
    cout<<"4. Prestar y devolver material"<<endl;
    cout<<"5. Prestar y devolver material"<<endl;
    cout<<"6. Gestion de usuarios"<<endl;
    cout<<"7. Salir"<<endl;
    cout<<"Elija una opcion: ";
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
    cout<<"La biblioteca esta llena";
}
void crearLibro(string nombre, string isbn, string autor, MaterialBibliografico* biblioteca[], int medida){
    string fechaPublicacion;
    do{
        cout<<"Ingrese la fecha de publicacion(dd-mm-yyyy): "; 
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
    cout<<"Libro creado con exito"<<endl;
    
}

void crearRevista(string nombre, string isbn, string autor, MaterialBibliografico* biblioteca[], int medida){
    cout<<"Ingrese el numero de edicion: "; 
    int numeroEdicion;
    cin>>numeroEdicion;

    cout<<"Ingrese el mes de publicacion(enero/febrero/etc): ";
    string mesPublicacion;
    cin>>mesPublicacion;

    Revista* revista = new Revista(nombre, isbn, autor, "revista", numeroEdicion, mesPublicacion);
    agregarALista(biblioteca, medida, revista);
    cin.ignore();
    cout<<"Revista creada con exito"<<endl;
}

void agregarMateriales(MaterialBibliografico* biblioteca[], int medida){
    int material;
    string nombre;
    string isbn;
    string autor;

    cout<<"Ingrese el material bibliografico que desea agregar (1. Libro / 2. Revista): ";
    cin>>material;
    if(material == 1 ||material == 2){
        cin.ignore();
        cout<<"Ingrese el nombre del material: "; 
        getline(cin, nombre);

        cout<<"Ingrese el ISBN: ";
        getline(cin,isbn);

        cout<<"Ingrese el autor: ";
        getline(cin, autor);
        

        switch(material){
            case 1:
                crearLibro(nombre, isbn, autor, biblioteca, medida);
                break;

            case 2:
                crearRevista(nombre, isbn, autor, biblioteca, medida);
                break;
        }
    }else{
        cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
        cin.ignore();
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
    cout<<"\n_____Material Bibliografico_____";
    if(hayMateriales){
        for(int i = 0;i < medida;i++){
            if(biblioteca[i] != nullptr){
                biblioteca[i]->mostrarInformacion();
            }
        }
    }else{
        cout<<"\nLa Biblioteca esta vacia."<<endl;
    }
    cout<<"__________________________________"<<endl;
}

MaterialBibliografico* buscarMaterial(MaterialBibliografico* biblioteca[], int medida){
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
                        encontrado = true;
                        return biblioteca[i];
                    }
                    if (biblioteca[i]->getAutor() == respuesta) {
                        encontrado = true;
                        return biblioteca[i];
                    }
                }
            }
            if (!encontrado) {
                cout<<"No se encontraron resultados para: "<<respuesta<<endl;
                break;
            }
        }while(!encontrado);
    }else{
        cout<<"\nLa Biblioteca esta vacia."<<endl;
    }
    cin.ignore();
    
}
Usuario* buscarUsuario(Usuario* usuarios[],int cantUsuarios,string nombreUsuario,int idUsuario){
    for(int i = 0; i < cantUsuarios; i++){

        if(usuarios[i]!= nullptr){
            if(usuarios[i]->getNombre() == nombreUsuario || usuarios[i]->getId() == idUsuario){
                return usuarios[i];
            }
        }
        
    }
    return nullptr;
}
void prestar(MaterialBibliografico* biblioteca[], int medida, string tituloAutor,Usuario* usuario){
    bool hayMateriales = hayMaterial(biblioteca, medida);
    if(hayMateriales){
        bool encontrado = false;
        for(int i = 0; i < medida; i++){
            if (biblioteca[i] != nullptr) {
                    if ((biblioteca[i]->getNombre() == tituloAutor || biblioteca[i]->getAutor() == tituloAutor) && biblioteca[i]->getPrestado() == false) {
                        biblioteca[i]-> setPrestado(true);
                        bool espacioSuf = usuario->prestarMaterial(biblioteca[i]);
                        if(espacioSuf == true){
                            encontrado = true;
                            cout<<"El material ha sido prestado con exito"<<endl;
                            return;
                        }else{
                            cout<<"No hay espacio suficiente"<<endl;
                            return;
                        }
                    }else if((biblioteca[i]->getNombre() == tituloAutor || biblioteca[i]->getAutor() == tituloAutor) && biblioteca[i]->getPrestado() == true){
                        cout<<"Este material ya esta prestado."<<endl;
                        encontrado = true;
                        return;
                    }
            }
        }
        if (!encontrado) {
                cout<<"\nNo se encontraron resultados para: "<<tituloAutor<<endl;
                return;
            }
    }else{
        cout<<"\nLa Biblioteca esta vacia."<<endl;
    }
}


void devolver(MaterialBibliografico* biblioteca[], int medida,string tituloAutor, Usuario* usuario){
    bool hayMateriales = hayMaterial(biblioteca, medida);
    if(hayMateriales){
        bool encontrado = false;
        for(int i = 0; i < medida; i++){
            if (biblioteca[i] != nullptr) {
                    if ((biblioteca[i]->getNombre() == tituloAutor || biblioteca[i]->getAutor() == tituloAutor) && biblioteca[i]->getPrestado() == true) {
                        biblioteca[i]-> setPrestado(false);
                        bool devolverExito = usuario->devolverMaterial(biblioteca[i]);
                        if(devolverExito == true){
                            encontrado = true;
                            cout<<"El material ha sido devuelto con exito"<<endl;
                            return;
                        }else{
                            cout<<"El material no ha sido devuelto"<<endl;
                            return;
                        }
                    }else if((biblioteca[i]->getNombre() == tituloAutor || biblioteca[i]->getAutor() == tituloAutor) && biblioteca[i]->getPrestado() == false){
                        cout<<"Este material no ha sido prestado."<<endl;
                        encontrado = true;
                        return;
                    }
            }
        }
        if (!encontrado) {
                cout<<"\nNo se encontraron resultados para: "<<tituloAutor<<endl;
                return;
            }
    }else{
        cout<<"\nLa Biblioteca esta vacia."<<endl;
    }
}

void prestarYDevolverMaterial(MaterialBibliografico* biblioteca[], int medida,Usuario* usuarios[]){
    int opcionPyD;
    string input;
    do{
        cout<<"\n==========="<<endl;
        cout<<"1.Prestar"<<endl;
        cout<<"2.Devolver"<<endl;
        cout<<"3.Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        getline(cin,input);
        try{
            opcionPyD = stoi(input);
            
            }catch (invalid_argument&){
                cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
                continue;
            }
        if (opcionPyD == 1 || opcionPyD == 2){
            string tituloAutor;
            cout<<"Ingrese titulo o nombre: ";
            cin>>tituloAutor;
            string nombreUsuarioPresDevol;
            int idUsuarioPresDevol = -1;
            if(opcionPyD == 1){
                cout<<"Prestar a Usuario(nombre): ";
                cin>>nombreUsuarioPresDevol;
            }else{
                cout<<"Devolucion por parte de Usuario(nombre): ";
                cin>>nombreUsuarioPresDevol;
            }
            
            Usuario* usuario = buscarUsuario(usuarios,medida,nombreUsuarioPresDevol,idUsuarioPresDevol);
            if(usuario != nullptr){
                switch(opcionPyD){
                    case 1:
                    prestar(biblioteca,medida,tituloAutor,usuario);
                    cin.ignore();
                    break;

                    case 2:
                    devolver(biblioteca,medida,tituloAutor,usuario);
                    cin.ignore();
                    break;

                }    
            }
            continue;
        }
        
    }while(opcionPyD !=3);
}

void menuBuscarUsuario(Usuario* usuarios[],int cantUsuarios){
    Usuario* usuario = nullptr;
    int opcionMusuario;
    string input;
    string nombre;
    int id;
    do{
        cout<<"\n========="<<endl;
        cout<<"1.Nombre"<<endl;
        cout<<"2.Id"<<endl;
        cout<<"3.Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        getline(cin,input);
        try{
            opcionMusuario = stoi(input);
            
            }catch (invalid_argument&){
                cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
                continue;
            }
        if(opcionMusuario == 1 || opcionMusuario == 2){
            switch (opcionMusuario){

                case 1:
                cout<<"Ingrese el nombre: ";
                cin>>nombre;
                id = -1;
                usuario = buscarUsuario(usuarios,cantUsuarios,nombre,id);
                break;

                case 2:
                cout<<"Ingresa el id: ";
                cin>>id;
                nombre = "";
                usuario = buscarUsuario(usuarios,cantUsuarios,nombre,id);
                break;

            }
            if(usuario != nullptr){
                cout<<"El usuario buscado: "+usuario->getNombre()+" Id: "<<usuario->getId()<<endl;
                usuario->mostrarMaterialesPrestados();
                cin.ignore();
                continue;
            }else if(usuario == nullptr){
                cout<<"El usuario no existe";
                cin.ignore();
                continue;
            }
        }
        
        
    }while(opcionMusuario != 3);
}

void agregarUsuario(Usuario* usuarios[],int cantUsuarios,Usuario* usuario){
    for(int i = 0; i < cantUsuarios; i++){
        if(usuarios[i] == nullptr){
            usuarios[i] = usuario;
            return;  
        }
    }
    cout<<"\nLa lista de usuarios esta llena"<<endl;
}
void crearUsuario(Usuario* usuarios[],int cantUsuarios){
    string nombreUsuario;
    int idUsuario;
    cout<<"Ingrese el nombre del usuario: ";
    getline(cin,nombreUsuario);
    cout<<"Ingrese la id del usuario: ";
    cin>>idUsuario;
    Usuario* usuarioBuscado= buscarUsuario(usuarios,cantUsuarios,nombreUsuario,idUsuario);
    
    if(usuarioBuscado != nullptr){
        cout<<"Este usuario, nombre o id ya existe"<<endl;
        cin.ignore();
        return;
    }else{
        Usuario* usuario = new Usuario(nombreUsuario, idUsuario);
        cout<<"El usuario fue creado con exito"<<endl;
        agregarUsuario(usuarios,cantUsuarios,usuario);
        cin.ignore();
        return;
    }
    
}


void eliminarUsuario(Usuario* usuarios[],int cantUsuarios){
    Usuario* usuario = nullptr;
    int opcionEliminar;
    string input;
    string nombre;
    int id;
    int idOnombre;
    do{
        cout<<"\n========="<<endl;
        cout<<"1.Nombre"<<endl;
        cout<<"2.Id"<<endl;
        cout<<"3.Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        getline(cin,input);
        try{
            opcionEliminar = stoi(input);
            
            }catch (invalid_argument&){
                cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
                continue;
            }
        if(opcionEliminar == 1 || opcionEliminar == 2){
            switch (opcionEliminar){

                case 1:
                cout<<"Ingrese el nombre: ";
                cin>>nombre;
                id = -1;
                usuario = buscarUsuario(usuarios,cantUsuarios,nombre,id);
                idOnombre = 1;
                break;

                case 2:
                cout<<"Ingrese el id: ";
                cin>>id;
                nombre = "";
                usuario = buscarUsuario(usuarios,cantUsuarios,nombre,id);
                idOnombre = 2;
                break;
            }
            for(int i = 0;i <cantUsuarios;i++){
                if(usuarios[i] != nullptr){
                    if(idOnombre==1){
                        if (usuarios[i]->getNombre() == usuario->getNombre()){
                            delete usuarios[i];
                            usuarios[i] = nullptr;
                            cout<<"Usuario eliminado con exito";
                            cin.ignore();
                            break;    
                        }
                    }else if(idOnombre==2){
                        if(usuarios[i]->getId() == usuario->getId()){
                            delete usuarios[i];
                            usuarios[i] = nullptr;
                            cout<<"Usuario eliminado con exito";
                            cin.ignore();
                            break;
                        }
                    }else{
                        cout<<"Error";
                        cin.ignore();
                        break;
                    }
                }    
            }        
        }
        
    }while(opcionEliminar != 3);
}
void gestionUsuarios(Usuario* usuarios[],int cantUsuarios){
    string nombreUsuario;
    int id;
    string input;
    int opcionUsuario;
    do{
        cout<<"\n================="<<endl;
        cout<<"1. Crear usuario"<<endl;
        cout<<"2. Buscar usuario"<<endl;
        cout<<"3. Eliminar usuario"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        getline(cin,input);
        try{
            opcionUsuario = stoi(input);
        
        }catch (invalid_argument&){
            cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
            continue;
        }
        
        if(opcionUsuario == 1 || opcionUsuario == 2 || opcionUsuario == 3){
            switch(opcionUsuario){
                case 1:
                crearUsuario(usuarios,cantUsuarios);
                break;

                case 2:
                menuBuscarUsuario(usuarios,cantUsuarios);
                break;

                case 3:
                eliminarUsuario(usuarios,cantUsuarios);
                break;
            }
        }
        

    }while(opcionUsuario != 4);
} //Implementar la funcionalidad para crear, buscar y eliminar usuarios. Asociar materiales prestados a usuarios específicos. 


void guardarLibroRevista(MaterialBibliografico* biblioteca[],int medida){
        int opcion;
        ofstream archivo("materiales.txt", ios::app);
        do{
            cout<<"========="<<endl;
            cout<<"1.Libro"<<endl;
            cout<<"2.Revista"<<endl;
            cout<<"3.Salir"<<endl;
            if(opcion>=1 || opcion <=2){
                switch (opcion)
                {
                case 1:
                    MaterialBibliografico* material = buscarMaterial(biblioteca,medida);
                    if (archivo.is_open()) {
                        archivo<<material->getNombre()<<","<<material->getISBN()<<","<<material->getAutor()<<","<<material->getFechaPublicacion() << "," << resumen << endl;
                        archivo.close();
                        cout << "Libro guardado exitosamente en el archivo." << endl;
                    } else {
                        cout << "No se pudo abrir el archivo." << endl;
                    }
                    break;
                
                default:
                    break;
                }
            }



        }while(opcion!= 3);
}

void guardarOCargarArchivos(MaterialBibliografico* biblioteca[],int medida,Usuario* usuarios[]){
    int opcionGuardarCargar;
    string input;
    string nombreBiblioteca;
    string nombreUsuarios;
    do{
        cout<<"========"<<endl;
        cout<<"1.Guardar libro o revista"<<endl;
        cout<<"2.Guardar usuario"<<endl;
        cout<<"3.Cargar Biblioteca"<<endl;
        cout<<"4.Cargar Usuarios"<<endl;
        cout<<"5.Salir"<<endl;
        try{
            opcionGuardarCargar = stoi(input);
        
        }catch (invalid_argument&){
            cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
            continue;
        }
        if(opcionGuardarCargar>=1 || opcionGuardarCargar <=4){
            
            switch (opcionGuardarCargar)
            {
                case 1:
                
                
                
                break;
            
                case 2:

                break;
            }
        }



    }while(opcionGuardarCargar != 3);






}

int main(){
    int medida = 100;
    int cantUsuarios = 50;
    MaterialBibliografico* biblioteca[medida] = {nullptr};
    Usuario* usuarios[cantUsuarios] = {nullptr};
    string input;
    int opcion;
    bool blanquito = false;

    do{
        mostrarMenu();


        getline(cin,input);
        try{
            opcion = stoi(input);
        
        }catch (invalid_argument&){
            cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
            continue;
        }
        if(opcion >= 1 || opcion <=6){
            switch(opcion){
                case 1:
                agregarMateriales(biblioteca,medida);
                break;

                case 2:
                mostrarInfo(biblioteca,medida);
                break;

                case 3:
                MaterialBibliografico* material = buscarMaterial(biblioteca,medida);
                material->mostrarInformacion();
                break;

                case 4:
                prestarYDevolverMaterial(biblioteca,medida,usuarios);
                break;

                case 5:
                guardarOCargarArchivos(biblioteca,medida,usuarios);
                break;

                case 6:
                gestionUsuarios(usuarios,cantUsuarios);
                break;
                
            }
        }else{
            cout<<"\n====Sistema cerrrado===="<<endl;
        }
        
    }while(opcion != 7);
    return 0;
}