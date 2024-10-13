#include <iostream>
#include "MaterialBibliografico.h"
#include "Libro.h"
#include "Revista.h"
#include "Usuario.h"
#include <fstream>
#include <sstream>
using namespace std;

//---------------------------------------------------------------------------------------------------------------------------
// void mostrarMenu() muestra por pantalla el menú con las opciones que el usuario puede elegir.
void mostrarMenu(){
    cout<<"\n==================MENU================"<<endl;
    cout<<"1. Agregar material a la biblioteca"<<endl;
    cout<<"2. Mostrar informacion de los materiales"<<endl;
    cout<<"3. Buscar material"<<endl;
    cout<<"4. Prestar y devolver material"<<endl;
    cout<<"5. Gestion de usuarios"<<endl;
    cout<<"6. Salir"<<endl;
    cout<<"Elija una opcion: ";
}

//---------------------------------------------------------------------------------------------------------------------------
// bool validarFecha(string& fecha) verifica que el formato de la fecha escrita por pantalla esté 
bool validarFecha(string fecha) {
    if (fecha.length() == 10 && fecha[2] == '-' && fecha[5] == '-') {
        return true;
    } else {
        return false;
    }
}

//---------------------------------------------------------------------------------------------------------------------------
void agregarALista(MaterialBibliografico* biblioteca[], int medida, MaterialBibliografico* mb){
    for(int i = 0; i < medida; i++){
        if(biblioteca[i] == nullptr){
            biblioteca[i] = mb;
            return;  
        }
    }
    cout<<"La biblioteca esta llena";
}

//---------------------------------------------------------------------------------------------------------------------------
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
    ofstream archivo("Materiales.txt",ios::app);
    if(archivo.is_open()){
        archivo<<endl;
        archivo<<nombre<<","<<isbn<<","<<autor<<","<<"libro"<<","<<fechaPublicacion<<","<<resumen<<","<<"no prestado"<<","<<"0";
    }else{
        cout << "Error al abrir el archivo para guardar." << endl;
    }
    agregarALista(biblioteca, medida, libro);
    cout<<"Libro creado con exito"<<endl;
    
}

//---------------------------------------------------------------------------------------------------------------------------
void crearRevista(string nombre, string isbn, string autor, MaterialBibliografico* biblioteca[], int medida){
    cout<<"Ingrese el numero de edicion: "; 
    int numeroEdicion;
    cin>>numeroEdicion;

    cout<<"Ingrese el mes de publicacion(enero/febrero/etc): ";
    string mesPublicacion;
    cin>>mesPublicacion;

    Revista* revista = new Revista(nombre, isbn, autor, "revista", numeroEdicion, mesPublicacion);
    ofstream archivo("Materiales.txt",ios::app);
    if(archivo.is_open()){
        archivo<<endl;
        archivo<<nombre<<","<<isbn<<","<<autor<<","<<"revista"<<","<<numeroEdicion<<","<<mesPublicacion<<","<<"no prestado"<<","<<"0";
    }else{
        cout << "Error al abrir el archivo para guardar." << endl;
    }

    agregarALista(biblioteca, medida, revista);
    cin.ignore();
    cout<<"Revista creada con exito"<<endl;
}

//---------------------------------------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------------------------------------
void modificarEstadoEID(string nombreMaterial,string nuevoEstado,int nuevoID) {
    ifstream archivoLectura("Materiales.txt");
    ofstream archivoTemporal("Materiales_temp.txt");

    string linea;
    bool encontrado = false;
    int contador = 1;

    if (archivoLectura.is_open() && archivoTemporal.is_open()) {
        while (getline(archivoLectura, linea)) {
            stringstream ss(linea);
            string nombre, isbn, autor, tipo, fecha, resumen, estado, id;

            getline(ss, nombre, ',');
            getline(ss, isbn, ',');
            getline(ss, autor, ',');
            getline(ss, tipo, ',');
            getline(ss, fecha, ',');
            getline(ss, resumen, ',');
            getline(ss, estado, ',');
            getline(ss, id, ',');

            if (nombre == nombreMaterial) {
                estado = nuevoEstado;
                id = to_string(nuevoID);      
                encontrado = true;
            }
            if(contador > 1){
                archivoTemporal<<endl;

            }
            archivoTemporal << nombre << "," << isbn << "," << autor << "," << tipo << "," << fecha << "," << resumen << "," << estado << "," << id;
            contador++;
        }
        archivoLectura.close();
        archivoTemporal.close();

        remove("Materiales.txt");
        rename("Materiales_temp.txt", "Materiales.txt");
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

//---------------------------------------------------------------------------------------------------------------------------
void eliminarUsuarioDelArchivo(int IDaEliminar) {
    ifstream archivoEntrada("Usuarios.txt");
    ofstream archivoTemporal("Usuarios_temp.txt");

    string linea;
    bool usuarioEncontrado = false;
    int contador = 1;

    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string nombre, id;
        getline(ss, nombre, ',');
        getline(ss, id, ',');

        if (id != to_string(IDaEliminar)) {
            if(contador > 1){
                archivoTemporal<<endl;
            }
            contador++;
            archivoTemporal << nombre << "," << id;
        } else {
            usuarioEncontrado = true;
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();
    remove("Usuarios.txt");
    rename("Usuarios_temp.txt", "Usuarios.txt");
}

//---------------------------------------------------------------------------------------------------------------------------
bool hayMaterial(MaterialBibliografico* biblioteca[],int medida){
    for(int i = 0;i < medida;i++){
        if(biblioteca[i] != nullptr){
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------------------------------------
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
                        cin.ignore();
                        return biblioteca[i];
                    }
                    if (biblioteca[i]->getAutor() == respuesta) {
                        encontrado = true;
                        cin.ignore();
                        return biblioteca[i];
                    }
                }
            }
            if (!encontrado) {
                cout<<"No se encontraron resultados para: "<<respuesta<<endl;
            }
            cin.ignore();
        }while(!encontrado);
    }else{
        cout<<"\nLa Biblioteca esta vacia."<<endl;
    }
    cin.ignore();
    return nullptr;
}

//---------------------------------------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------------------------------------
void prestar(MaterialBibliografico* biblioteca[], int medida, string tituloAutor,Usuario* usuario){
    bool hayMateriales = hayMaterial(biblioteca, medida);
    if(hayMateriales){
        bool encontrado = false;
        for(int i = 0; i < medida; i++){
            if (biblioteca[i] != nullptr) {
                    if ((biblioteca[i]->getNombre() == tituloAutor || biblioteca[i]->getAutor() == tituloAutor) && biblioteca[i]->getPrestado() == false) {
                        encontrado = true;
                        bool espacioSuf = usuario->prestarMaterial(biblioteca[i]);
                        if(espacioSuf == true){
                            biblioteca[i]-> setPrestado(true);
                            modificarEstadoEID(biblioteca[i]->getNombre(),"prestado",usuario->getId());
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

//---------------------------------------------------------------------------------------------------------------------------
void devolver(MaterialBibliografico* biblioteca[], int medida,string tituloAutor, Usuario* usuario){
    bool hayMateriales = hayMaterial(biblioteca, medida);
    if(hayMateriales){
        bool encontrado = false;
        for(int i = 0; i < medida; i++){
            if (biblioteca[i] != nullptr) {
                    if ((biblioteca[i]->getNombre() == tituloAutor || biblioteca[i]->getAutor() == tituloAutor) && biblioteca[i]->getPrestado() == true) {
                        biblioteca[i]-> setPrestado(false);
                        modificarEstadoEID(biblioteca[i]->getNombre(),"no prestado",0);
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

//---------------------------------------------------------------------------------------------------------------------------
void prestarYDevolverMaterial(MaterialBibliografico* biblioteca[], int medida,Usuario* usuarios[],int cantUsuarios){
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
            getline(cin,tituloAutor);
            string nombreUsuarioPresDevol;
            int idUsuarioPresDevol = -1;
            if(opcionPyD == 1){
                cout<<"Prestar a Usuario(nombre): ";
                cin>>nombreUsuarioPresDevol;
            }else{
                cout<<"Devolucion por parte de Usuario(nombre): ";
                cin>>nombreUsuarioPresDevol;
            }
            
            Usuario* usuario = buscarUsuario(usuarios,cantUsuarios,nombreUsuarioPresDevol,idUsuarioPresDevol);
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
            }else{
                cin.ignore();
                cout<<"El usuario no existe"<<endl;
            }
            continue;
        }
        
    }while(opcionPyD !=3);
}

//---------------------------------------------------------------------------------------------------------------------------
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
                string inputID;
                cout<<"Ingresa el id: ";
                cin>>inputID;
                try{
                    id = stoi(inputID);
            
                    }catch (invalid_argument&){
                        cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
                        cin.ignore();
                        continue;
                }       
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

//---------------------------------------------------------------------------------------------------------------------------
void agregarUsuario(Usuario* usuarios[],int cantUsuarios,Usuario* usuario){
    for(int i = 0; i < cantUsuarios; i++){
        if(usuarios[i] == nullptr){
            usuarios[i] = usuario;
            return;  
        }
    }
    cout<<"\nLa lista de usuarios esta llena"<<endl;
}

//---------------------------------------------------------------------------------------------------------------------------
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
        ofstream archivo("Usuarios.txt",ios::app);
        if(archivo.is_open()){
            archivo<<endl;
            archivo<<nombreUsuario<<","<<idUsuario;
        }else{
            cout<<"Error al abrir el archivo para guardar."<<endl;
        }
        cin.ignore();
        return;
    }
}

//---------------------------------------------------------------------------------------------------------------------------
void eliminarUsuario(MaterialBibliografico* biblioteca[],int medida,Usuario* usuarios[],int cantUsuarios){
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
                break;

                case 2:
                string inputID;
                cout<<"Ingresa el id: ";
                cin>>inputID;
                try{
                    id = stoi(inputID);
            
                    }catch (invalid_argument&){
                        cout<<"\nOpcion invalida. Intente nuevamente"<<endl;
                        cin.ignore();
                        continue;
                }       
                nombre = " ";
                usuario = buscarUsuario(usuarios,cantUsuarios,nombre,id);
                break;
            }
            if(usuario != nullptr){
                for(int i = 0;i <cantUsuarios;i++){
                    if(usuarios[i] != nullptr){
                        if(opcionEliminar==1){
                            if (usuarios[i]->getNombre() == usuario->getNombre()){
                                MaterialBibliografico** materialesPrestados = usuarios[i]->getLista();
                                for (int j = 0; j < 5; j++){
                                    if(materialesPrestados[j] != nullptr){
                                        devolver(biblioteca,medida,materialesPrestados[j]->getNombre(),usuarios[i]);
                                    }
                                }
                                eliminarUsuarioDelArchivo(usuario->getId());
                                delete usuarios[i];
                                usuarios[i] = nullptr;

                                cout<<"Usuario eliminado con exito";
                                cin.ignore();
                                break;    
                            }
                        }else if(opcionEliminar==2){
                            if(usuarios[i]->getId() == usuario->getId()){
                            MaterialBibliografico** materialesPrestados = usuarios[i]->getLista();
                                for (int j = 0; j < 5; j++){
                                    if(materialesPrestados[j] != nullptr){
                                        devolver(biblioteca,medida,materialesPrestados[j]->getNombre(),usuarios[i]);
                                    }
                                }
                                eliminarUsuarioDelArchivo(usuario->getId());
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
            }else{
                cout<<"Usuario no encontrado"<<endl;
                cin.ignore();
            }        
        }
        
    }while(opcionEliminar != 3);
}

//---------------------------------------------------------------------------------------------------------------------------
void gestionUsuarios(MaterialBibliografico* biblioteca[],int medida,Usuario* usuarios[],int cantUsuarios){
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
                eliminarUsuario(biblioteca,medida,usuarios,cantUsuarios);
                break;
            }
        }
        

    }while(opcionUsuario != 4);
} 

//---------------------------------------------------------------------------------------------------------------------------
void cargarUsuarios(Usuario* usuarios[], int cantUsuarios){
    ifstream archivo("Usuarios.txt");
    string linea;
    string parte;
    
    while(getline(archivo, linea)){
        
        int iterador = 0;
        stringstream input_stringstream(linea);
        string nombre, id;
        while(getline(input_stringstream, parte, ',')){
            iterador++;
            if (iterador == 1){
                nombre = parte;
            }else if(iterador == 2){
                id = parte;
            }
        }
        Usuario* usuario = new Usuario(nombre,stoi(id));
        agregarUsuario(usuarios,cantUsuarios,usuario);
    }
}

//---------------------------------------------------------------------------------------------------------------------------
void cargarMaterialesDesdeArchivo(MaterialBibliografico* biblioteca[], int medida, Usuario* usuarios[], int cantUsuarios) {
    ifstream archivo("Materiales.txt");
    string linea, nombre, ISBN, autor, tipo, par1, par2, estado, id;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, nombre, ',');
        getline(ss, ISBN, ',');
        getline(ss, autor, ',');
        getline(ss, tipo, ',');
        getline(ss, par1, ',');
        getline(ss, par2, ',');
        getline(ss, estado, ',');
        getline(ss, id, ',');

        Usuario* usuario = buscarUsuario(usuarios, cantUsuarios, "__", stoi(id));

        MaterialBibliografico* material = nullptr;
        if (tipo == "libro") {
            material = new Libro(nombre, ISBN, autor, tipo, par1, par2);
        } else if (tipo == "revista") {
            material = new Revista(nombre, ISBN, autor, tipo, stoi(par1), par2);
        }

        if (material != nullptr) {
            agregarALista(biblioteca, medida, material);

            if (estado == "prestado" && usuario != nullptr) {
                usuario->prestarMaterial(material);
                material->setPrestado(true);
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------
void liberarMemoria(MaterialBibliografico* biblioteca[], int medida, Usuario* usuarios[], int cantUsuarios){
    for(int i = 0; i < medida; i++){
        if(biblioteca[i]!= nullptr){
            delete biblioteca[i];
        }
    }
    for(int i = 0; i < cantUsuarios; i++){
        if(usuarios[i]!= nullptr){
            delete usuarios[i];
        }
    }   
}

//---------------------------------------------------------------------------------------------------------------------------
int main(){
    int medida = 100;
    int cantUsuarios = 50;
    MaterialBibliografico* biblioteca[medida] = {nullptr};
    Usuario* usuarios[cantUsuarios] = {nullptr};
    string input;
    int opcion;
    cargarUsuarios(usuarios,cantUsuarios);
    cargarMaterialesDesdeArchivo(biblioteca,medida,usuarios,cantUsuarios);
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
                case 1:{
                agregarMateriales(biblioteca,medida);
                break;}

                case 2:{
                mostrarInfo(biblioteca,medida);
                break;}

                case 3:{
                MaterialBibliografico* material = buscarMaterial(biblioteca,medida);
                material->mostrarInformacion();
                break;}

                case 4:{
                prestarYDevolverMaterial(biblioteca,medida,usuarios,cantUsuarios);
                break;}

                case 5:{
                gestionUsuarios(biblioteca,medida,usuarios,cantUsuarios);
                break;}
            }
        }
        
    }while(opcion != 6);
    cout<<"\n====Sistema cerrrado===="<<endl;
    return 0;
}