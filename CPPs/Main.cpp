#include <iostream>
#include "../Headers/MaterialBibliografico.h"
#include "../Headers/Libro.h"
#include "../Headers/Revista.h"
#include "../Headers/Usuario.h"
#include <fstream>
#include <sstream>

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
// bool validarFecha(string fecha) verifica que el formato de la fecha escrita por pantalla esté en el formato que se pide: dd-mm-aaaa
bool validarFecha(string fecha) {
    if (fecha.length() == 10 && fecha[2] == '-' && fecha[5] == '-') {
        return true;
    } else {
        return false;
    }
}

//---------------------------------------------------------------------------------------------------------------------------
// void agregarALista() recorre con un for() la lista de la biblioteca que contiene los materiales bibliograficos, si la posición en la 
// que se encuentra en el momento es nullptr, se agrega el material bibliográfico mb a la lista de la biblioteca, si logra recorrer todo el for()
// y la posición en la que se encuentra es distinto de nullptr, significa que la lista de la biblioteca está completa (100 materiales disponibles).
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
// void crearLibro() pide los parámetros nombre, isbn y autor, junto con la fecha de publicacion y el resumen por pantalla, para poder crear un 
// libro con esos atributos y luego ese libro creado lo agrega al texto de Materiales.txt que contiene todos los materiales bibliográficos de
// la biblioteca.
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
// void crearRevista() pide los parámetros nombre, isbn y autor, junto con el número de edición y el mes de publicación por pantalla, para poder
// crear una revista con esos atributos y luego esa revista creada la agrega al texto de Materiales.txt que contiene todos los materiales bibliográficos de
// la biblioteca.
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
// void agregarMateriales() pide al usuario igresar por pantalla el material bibliográfico que desea agregar (debe elegir 1 o 2), para luego
// pedirle los datos que comparten en común de la clase padre (nombre, isbn, autor), después se entra a un switch en donde dependiendo de la opción
// que se eligió, se llamará a la función crearLibro() o crearRevista() para crear los respectivos materiales, en caso de que se elija una opción
// diferente a 1 o 2, se mostrará por pantalla "Opcion invalida. Intente nuevamente".
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
// void modificarEstadoEID() abre el archivo de texto "Materiales.txt" y crea un archivo temporal "Materiales_temp", luego va leyendo línea por línea
// el archivo "Materiales.txt" y obtiene los atributos nombre, isbn, autor, tipo, fecha, resumen, estado, id. Si el nombre es igual al nombreMaterial
// pedido en los parámetros de la función, entonces cambia el estado e id por el nuevoEstado y nuevoId pedidos en los parámetros de la función.
// Escribe cada línea en el archivo temporal y si el material que se buscaba fue modificado, se escriben las líneas con los nuevos datos, si no se 
// encuentra, se escriben las líneas originales. Finalmente, cierra ambos archivos de texto, elimina "Materiales.txt" y renombra "Materiales_temp.txt"
// a "Materiales.txt", haciendo así que se cambie el archivo temporal (con los nuevos datos) por el original. Si no se abren los archivos muestra un mensaje de error.
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
// void eliminarUsuarioDelArchivo() al igual que la función modificarEstadoEID(), abre un archivo de texto "Usuarios.txt" y crea un archivo temporal 
// "Usuarios_temp.txt", lee el archivo "Usuarios.txt", obtiene los atributos nombre e id, si el id es distinto al id a eliminar que se pide en
// los parámetros de la función, y si el contador es mayor a 1, entonces agrega un salto de linea, se incrementa el contador y luego se escribe la
// linea en el archivo temporal. Finalmente, cierra ambos archivos de texto, elimina "Usuarios.txt" y renombra "Usuarios_temp.txt"
// a "Usuarios.txt", haciendo así que se cambie el archivo temporal por el original.
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
// bool hayMaterial() recorre con un for() la lista de la biblioteca con los materiales bibliograficos, si la posición en la que se encuentra es
// distinto de nullptr, significa que hay un material en esa posición, de lo contrario, no lo hay.
bool hayMaterial(MaterialBibliografico* biblioteca[],int medida){
    for(int i = 0;i < medida;i++){
        if(biblioteca[i] != nullptr){
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------------------------------------------------------
// void mostrarInfo() llama a la funcion hayMaterial() para saber si existe un material o no, si la posición de la lista de la biblioteca donde 
// se encuentran los materiales bibliográficos es distinto de nullptr, entonces imprime por pantalla los datos del material bibliográfico en esa posición.
// En el caso en el que todas las posiciones de la lista sean igual a nullptr, significa que la lista está vacía y la biblioteca no tiene materiales bibliográficos.
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
// MaterialBibliografico* buscarMaterial() crea un bool hayMateriales que llama a la función hayMaterial(), si hayMateriales es verdadero entra al if()
// pide que se ingrese por pantalla el título o autor del material bibliográfico y luego entra a un for() que recorre toda la lista de la biblioteca, 
// si la posición en la que se encuentra de la lista de biblioteca es distinto de nullptr, entonces buscará las siguientes opciones: 
// 1. si el nombre del material es igual al titulo que se ingresó por pantalla, entonces se encontró el material que se buscaba y se retorna.
// 2. si el autor del material es igual al autor que se ingresó por pantalla, entonces se encontró el material que se buscaba y se retorna.
// En el caso en el que encontrado sea igual a falso, significa que no se encontró el material.
MaterialBibliografico* buscarMaterial(MaterialBibliografico* biblioteca[], int medida){
    string titutloOAutor;
    bool hayMateriales = hayMaterial(biblioteca, medida);
    
    if(hayMateriales){
        bool encontrado = false;
        do{
            cout<<"Ingrese el titulo o autor: ";
            cin>>titutloOAutor;
            
            for (int i = 0; i < medida; i++) {
                if (biblioteca[i] != nullptr) {
                    if (biblioteca[i]->getNombre() == titutloOAutor) {
                        encontrado = true;
                        cin.ignore();
                        return biblioteca[i];
                    }
                    if (biblioteca[i]->getAutor() == titutloOAutor) {
                        encontrado = true;
                        cin.ignore();
                        return biblioteca[i];
                    }
                }
            }
            if (!encontrado) {
                cout<<"No se encontraron resultados para: "<<titutloOAutor<<endl;
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
//buscarUsuario es una funcion que lleva por parametros la lista de usuarios, cantidad de usuarios, el nombre buscado o el id buscado
//con esta informacion busca dentro de la lista de usuarios si el nombre o id de alguno coincide con el nombre o id buscado. Si algun
//usuario coincide, se retornara a dicho usuario y en el caso de no encontrarlo, se retorna false.
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
//prestar es una funcion llamada por prestarYDevolverMaterial, aqui lo que se usa por parametros son la biblioteca, su medida, un usuario
//y un string denominado tituloAutor el cuando contendra el titulo o autor del libro o revista buscado en cuestion. Primero usara la funcion
//hayMaterial para revisar si existe algun material bibliografico en la biblioteca y si es verdadero retornara btrue, siguiendo asi, a buscar
//dentro de la biblioteca si alguno de sus materiales coincide con el titulo o autor, y si coincide alguno, tambien revisara si este se
//encuentra prestado o no(true o false respectivamente).
//1.Si es encontrado, y su estado es false revisara si el usuario a quien se le prestara dicho material posee o no espacio suficiente
//en su lista de materiales prestados y si es un true llamara a modificarEstadoEID para modificar el estado de dicho material en Materiales.txt. 
//2.En el caso de que se encuentre prestado solo escribira por pantalla. 
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
//devolver es una funcion llamada por prestarYDevolverMaterial, aqui lo que se usa por parametros son la biblioteca, su medida, un usuario
//y un string denominado tituloAutor el cuando contendra el titulo o autor del libro o revista buscado en cuestion. Primero usara la funcion
//hayMaterial para revisar si existe algun material bibliografico en la biblioteca y si es verdadero retornara true, siguiendo asi, a buscar
//dentro de la biblioteca si alguno de sus materiales coincide con el titulo o autor, y si coincide alguno, tambien revisara si este se
//encuentra prestado o no(true o false respectivamente). 
//1.Si es encontrado, y su estado es true, modificara el estado del material a false(para indicar que se encuentra prestado) y luego 
//llamara a modificarEstadoEID para modificar el estado de dicho material en Materiales.txt.
//2.En el caso de que no este prestado solo escribira por pantalla que no ha sido prestado dicho material.
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
//prestarYDevolverMaterial da 2 opciones, prestar o devolver un material bibliografico, en cada pregunta pide el nombre o autor y
//el usuario que esta devolviendo dicho material, primero busca si el usuario existe, y en caso de ser true, llamara a los metodos
//prestar o devolver para buscarlo dentro de la biblioteca y hacer la accion correspondiente.
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
//menuBuscarUsuario pide como variables el nombre o id del usuario que se busca. Si se encuentra,se escribira por pantalla su nombre, id y
//en caso de poseer materiales bibliograficos se escribira la informacion de estos.
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
//agregarUsuario lleva por parametros la lista de usuarios, cantidad de usuarios y el usuario entregado. Recorre buscando un espacio
//vacio(nullptr) dentro de la lista, y si lo encuentra pondra en esa posicion al usuario entregado, si no existe espacio disponible
//escribira por pantalla que se encuentra llena.
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
//crearUsuario pide el nombre e id por pantalla, si son respuestas correctas usara esa informacion para crear usuarios y agregarlos
//a la lista de usuarios y tambien abrir el archivo de Usuarios.txt para poder este usuario al archivo.
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
//eliminarUsuario pide nombre o id del usuario buscado, si el nombre o id ingresados corresponden con algun usuario dentro de la
//lista de usuarios, este sera eliminado y reemplazado por un nullptr. Tambien seran devueltos sus materiales en caso de poseer alguno
//y ademas sera todo modificado en los archivos Materiales.txt y Usuarios.txt para que no haya error de informacion y datos guardados
//al borrar dicho usuario del txt y los libros ser devueltos, cambiando su estado.
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
//gestionUsuarios es una funcion que permite crear, buscar o eliminar usuarios, llamando sus metodos correspondientes y facilitando 
//la biblioteca, su medida, la lista de usuarios y cantidad de usuarios disponibles para estos dichos metodos y permitir modificar
//la informacion y datos guardados.
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
//cargarUsuarios lleva por parametros la lista de usuarios y la cantidad de espacios disponibles, luego abrira Usuarios.txt 
//para crear usuarios con la informacion dentro de ese archivo y agregarlos a la lista de usuarios.
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
//cargarMaterialesDesdeArchivo abre Materiales.txt y con la informacion dentro del archivo crea libros o revista segun los parametros
//y los agrega a la biblioteca de materiales bibliograficos. Tambien les agrega el estado, si se encuentra prestado
//usa el id proporcionado para identificar que usuario lo posee y guardar esa informacion en el material y usuario correspondiente.
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
//liberarMmemoria borra la memoria utilizada, es decir, los objetos creados, luego de cerrar el sistema.
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
//main, aqui son creadas 2 listas, la biblioteca que contendra los materiales bibliograficos y la lista de usuarios, ambas con tamaños
//definidos. Cargara 2 archivos predefinidos con algunos materiales y usuarios para ingresarlos a sus listas correspondientes y luego
//llamara a la funcion mostrarMenu para elegir alguna opcion presente y dirigirse a la elegida por pantalla. Cada una llamara a un metodo
//diferente y correspondiente a su funcion. En caso de que la opcion sea cerrar el programa(Salir), este llamara a la funcion
//liberarMemoria para eliminar todo objeto creado y liberar memoria, para despues escribir por pantalla y finalizar. Todo lo creado,
//eliminado o modificado quedara guardados en los archivos de texto Materiales.txt y Usuarios.txt
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
    liberarMemoria(biblioteca,medida,usuarios,cantUsuarios);
    cout<<"\n====Sistema cerrrado===="<<endl;
    return 0;
}