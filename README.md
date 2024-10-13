# Taller1
Para compilar se utiliza:
- g++ -o main.exe CPPs/MaterialBibliografico.cpp CPPs/Libro.cpp CPPs/Revista.cpp CPPs/Usuario.cpp CPPs/main.cpp -I Headers
- .\main

Integrantes:
- Felipe Jeremias Blanco Pizarro, rut: 21.301.314-9, correo institucional: felipe.blanco@alumnos.ucn.cl, paralelo: C1
- Maira Esperanza Cortés Araya, rut: 21.324.438-8, correo institucional: maira.cortes@alumnos.ucn.cl, paralelo: C1

Información sobre los objetos que se crean en el main durante el inicio del programa:

MaterialesBibliograficos:
- {Nombre: ”Caperucita",ISBN:"455-22-0",ablo Neruda",Tipo: "libro",FechaPublicacion: "11-12-2003",Resumen: "Nina perdida es encontrada por un lobo y deciden viajar juntos para volver a casa",Prestado:"false"}
- {Nombre: "Vogue Chile",ISBN: "356-86-9",Autor: "Feliruis JOnne",Tipo: "revista", N°Edicion: "34",MesPublicacion: "Mayo",Prestado: "false"}
- {Nombre: "Recetas de la Abuela",ISBN: "344-65-234",Autor: "Rosa Castillo",Tipo: "revista", N°Edicion: "23",MesPublicacion: "Febrero",Prestado: "false"}

Usuarios:
- {nombre: Francisco,id: 278, ListaMaterialBibliografico: ["Caperucita"]}
- {nombre: Felipe,id: 918, ListaMaterialBibliografico: []}
- {nombre: Guille,id: 444, ListaMaterialBibliografico: []}
- {nombre: Maira,id: 456, ListaMaterialBibliografico: []}