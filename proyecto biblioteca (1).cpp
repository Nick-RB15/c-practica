#include <iostream>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h> // Para _getch()
#include <sstream> 
using namespace std;

// Función para posicionar el cursor
void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

// Estructuras de Datos
struct Libro {
    string codigo;
    string nombre;
    string editorial;
    string autor;
    string genero;
    string pais_autor;
    int num_paginas;
    int anio_edicion;
    float precio;
    bool estado; // true = disponible, false = prestado
    Libro* sigt;
    Libro* ant;
};

struct Usuario {
    string codigo;
    string nombres;
    string apellidos;
    string DNI;
    string domicilio;
    string fecha_nacimiento;
    bool estado; // true = activo, false = inactivo
    Usuario* sigt;
    Usuario* ant;
};

struct Prestamo {
    string num_pedido;
    string cod_libro;
    string cod_usuario;
    string fecha_salida;
    string fecha_max_devolucion;
    string fecha_devolucion;
    string estado; // "Prestado" / "Entregado"
    Prestamo* sigt;
    Prestamo* ant;
};

// Prototipos de funciones
char menuPrincipal();
void gestionarLibros(Libro*&, Libro*&);
void registrarLibro(Libro*&, Libro*&);
void modificarLibro(Libro*);
void listarLibros(Libro*);
Libro* buscarLibro(Libro*, string);
void eliminarLibro(Libro*&, Libro*&, Prestamo*);
void ordenarLibrosAnio(Libro*&);
void registrarUsuario(Usuario*&, Usuario*&);
Usuario* buscarUsuario(Usuario*, string);
void listarUsuarios(Usuario*);
void registrarPrestamo(Prestamo*&, Prestamo*&, Libro*, Usuario*);
void registrarDevolucion(Prestamo*, Libro*&);
void listarPrestamosFecha(Prestamo*, string);
void contarPrestamosLibros(Prestamo*, Libro*);

// Función principal
int main() {
    setlocale(LC_CTYPE, "Spanish");
    Libro* inicioLibros = NULL, * finLibros = NULL;
    Usuario* inicioUsuarios = NULL, * finUsuarios = NULL;
    Prestamo* inicioPrestamos = NULL, * finPrestamos = NULL;
    char opcion;

    do {
        system("cls");
        opcion = menuPrincipal();
        switch (opcion) {
        case 'A': gestionarLibros(inicioLibros, finLibros); break;
        case 'B': registrarUsuario(inicioUsuarios, finUsuarios); break;
        case 'C': {
            string nombre;
            cout << "Nombre del libro: ";
            cin.ignore();
            getline(cin, nombre);
            Libro* encontrado = buscarLibro(inicioLibros, nombre);
            if (encontrado) {
                cout << "Libro encontrado:\n";
                cout << "Código: " << encontrado->codigo << "\nAutor: " << encontrado->autor << endl;
            }
            else {
                cout << "Libro no encontrado!\n";
            }
            system("pause");
            break;
        }
        case 'D': registrarPrestamo(inicioPrestamos, finPrestamos, inicioLibros, inicioUsuarios); break;
        case 'E': registrarDevolucion(inicioPrestamos, inicioLibros); break;
        case 'F': {
			int dia, mes, anio;
			string fecha;
			
			cout << "Día: ";
			cin >> dia;
			cout << "Mes: ";
			cin >> mes;
			cout << "Año: ";
			cin >> anio;
			
			stringstream ss;
			if (dia < 10) ss << "0";
			ss << dia << "/";
			
			if (mes < 10) ss << "0";
			ss << mes << "/";
			
			ss << anio;
			
			fecha = ss.str();
			
			cout << "Fecha completa: " << fecha << endl;
			
		listarPrestamosFecha(inicioPrestamos, fecha);
		system("pause");
		break;

        }
        case 'G': contarPrestamosLibros(inicioPrestamos, inicioLibros); break;
        case 'H': eliminarLibro(inicioLibros, finLibros, inicioPrestamos); break;
        case 'I': ordenarLibrosAnio(inicioLibros); break;
        case 'J': listarLibros(inicioLibros); break;
        case 'S': cout << "Saliendo...\n"; break;
        default: cout << "Opción inválida!\n";
        }
    } while (opcion != 'S');

    return 0;
}

// Implementación de funciones

char menuPrincipal() {
    char op;
    cout << "*** BIBLIOTECA PENINSULA ***\n";
    cout << "A. Gestionar Libros\n";
    cout << "B. Registrar Usuario\n";
    cout << "C. Buscar Libro\n";
    cout << "D. Registrar Préstamo\n";
    cout << "E. Registrar Devolución\n";
    cout << "F. Listar préstamos por fecha\n";
    cout << "G. Conteo de préstamos por libro\n";
    cout << "H. Eliminar libro\n";
    cout << "I. Ordenar libros por año\n";
    cout << "J. Listar todos los libros\n";
    cout << "S. Salir\n";
    cout << "Opción: ";
    cin >> op;
    return toupper(op);
}

void gestionarLibros(Libro*& inicio, Libro*& fin) {
    int op;
    do {
        system("cls");
        cout << "*** GESTIÓN DE LIBROS ***\n";
        cout << "1. Registrar Libro\n";
        cout << "2. Modificar Libro\n";
        cout << "3. Volver\n";
        cout << "Opción: ";
        cin >> op;

        switch (op) {
        case 1: registrarLibro(inicio, fin); break;
        case 2: modificarLibro(inicio); break;
        }
    } while (op != 3);
}

void registrarLibro(Libro*& inicio, Libro*& fin) {
    system("cls");
    Libro* nuevo = new Libro();

    gotoxy(5, 2); cout << "*** REGISTRO DE LIBRO ***";

    gotoxy(5, 4); cout << "Código: ";
    gotoxy(14, 4); cin >> nuevo->codigo;

    gotoxy(5, 5); cout << "Nombre: ";
    gotoxy(14, 5); cin.ignore();
    getline(cin, nuevo->nombre);

    gotoxy(5, 6); cout << "Editorial: ";
    gotoxy(16, 6); getline(cin, nuevo->editorial);

    gotoxy(5, 7); cout << "Autor: ";
    gotoxy(13, 7); getline(cin, nuevo->autor);

    gotoxy(5, 8); cout << "Género: ";
    gotoxy(14, 8); getline(cin, nuevo->genero);

    gotoxy(5, 9); cout << "País autor: ";
    gotoxy(17, 9); getline(cin, nuevo->pais_autor);

    gotoxy(5, 10); cout << "Páginas: ";
    gotoxy(15, 10); cin >> nuevo->num_paginas;

    gotoxy(5, 11); cout << "Año edición: ";
    gotoxy(18, 11); cin >> nuevo->anio_edicion;

    gotoxy(5, 12); cout << "Precio: $";
    gotoxy(14, 12); cin >> nuevo->precio;

    nuevo->estado = true;
    nuevo->sigt = NULL;	
	nuevo->ant = fin;  // El anterior del nuevo nodo es el actual fin

	if (fin != NULL) {  // Si hay nodos en la lista
	    fin->sigt = nuevo;
	} else {  // Lista vacía
	    inicio = nuevo;
	}
	fin = nuevo;
    gotoxy(5, 14); cout << "¡Libro registrado exitosamente!";
    gotoxy(5, 16); system("pause");
}

Libro* buscarLibro(Libro* inicio, string dato) {
    Libro* actual = inicio;
    while (actual) {
        if (actual->codigo == dato || actual->nombre == dato) {
            return actual;
        }
        actual = actual->sigt;
    }
    return NULL;
}

void modificarLibro(Libro* inicio) {
    system("cls");
    string codigo;

    gotoxy(5, 2); cout << "*** MODIFICAR LIBRO ***";
    gotoxy(5, 4); cout << "Ingrese el código del libro: ";
    gotoxy(32, 4); cin >> codigo;

    Libro* libro = buscarLibro(inicio, codigo);
    if (!libro) {
        gotoxy(5, 6); cout << "Libro no encontrado!";
        gotoxy(5, 8); system("pause");
        return;
    }

int opcion;
char continuar;

do {
	system("cls"); // Limpia pantalla si quieres que sea más limpio
	gotoxy(5, 6); cout << "1. Nombre: " << libro->nombre;
    gotoxy(5, 7); cout << "2. Editorial: " << libro->editorial;
    gotoxy(5, 8); cout << "3. Autor: " << libro->autor;
    gotoxy(5, 9); cout << "4. Género: " << libro->genero;
    gotoxy(5, 10); cout << "5. País autor: " << libro->pais_autor;
    gotoxy(5, 11); cout << "6. Páginas: " << libro->num_paginas;
    gotoxy(5, 12); cout << "7. Año edición: " << libro->anio_edicion;
    gotoxy(5, 13); cout << "8. Precio: " << libro->precio;
	
    gotoxy(5, 15); cout << "Seleccione el campo a modificar (1-8): ";
    gotoxy(45, 15); cin >> opcion;
    cin.ignore();

    switch (opcion) {
    case 1:
        gotoxy(5, 17); cout << "Nuevo nombre: ";
        gotoxy(18, 17); getline(cin, libro->nombre);
        break;
    case 2:
        gotoxy(5, 17); cout << "Nueva editorial: ";
        gotoxy(22, 17); getline(cin, libro->editorial);
        break;
    case 3:
        gotoxy(5, 17); cout << "Nuevo autor: ";
        gotoxy(18, 17); getline(cin, libro->autor);
        break;
    case 4:
        gotoxy(5, 17); cout << "Nuevo género: ";
        gotoxy(18, 17); getline(cin, libro->genero);
        break;
    case 5:
        gotoxy(5, 17); cout << "Nuevo país autor: ";
        gotoxy(22, 17); getline(cin, libro->pais_autor);
        break;
    case 6:
        gotoxy(5, 17); cout << "Nuevas páginas: ";
        gotoxy(21, 17); cin >> libro->num_paginas;
        cin.ignore();
        break;
    case 7:
        gotoxy(5, 17); cout << "Nuevo año edición: ";
        gotoxy(23, 17); cin >> libro->anio_edicion;
        cin.ignore();
        break;
    case 8:
        gotoxy(5, 17); cout << "Nuevo precio: $";
        gotoxy(20, 17); cin >> libro->precio;
        cin.ignore();
        break;
    default:
        gotoxy(5, 17); cout << "¡Opción no válida!";
    }

    gotoxy(5, 19); cout << "¿Desea modificar otro campo? (s/n): ";
    gotoxy(38, 19); cin >> continuar;
    cin.ignore();

} while (continuar == 's' || continuar == 'S');

gotoxy(5, 21); cout << "¡Modificación finalizada!";
gotoxy(5, 23); system("pause");
}

void listarLibros(Libro* inicio) {
    system("cls");
    int x = 5, y = 2;

    gotoxy(x, y); cout << "*** LISTADO DE LIBROS ***";
    y += 2;

    if (!inicio) {
        gotoxy(x, y); cout << "No hay libros registrados.";
    }
    else {
        gotoxy(x, y); cout << "CODIGO";
        gotoxy(x + 10, y); cout << "NOMBRE";
        gotoxy(x + 40, y); cout << "AUTOR";
        gotoxy(x + 70, y); cout << "AÑO";
        gotoxy(x + 80, y); cout << "ESTADO";
        y++;

        Libro* actual = inicio;
        while (actual) {
            gotoxy(x, y); cout << actual->codigo;
            gotoxy(x + 10, y); cout << (actual->nombre.length() > 30 ? actual->nombre.substr(0, 27) + "..." : actual->nombre);
            gotoxy(x + 40, y); cout << (actual->autor.length() > 25 ? actual->autor.substr(0, 22) + "..." : actual->autor);
            gotoxy(x + 70, y); cout << actual->anio_edicion;
            gotoxy(x + 80, y); cout << (actual->estado ? "Disponible" : "Prestado");
            y++;

            if (y > 25 && actual->sigt) {
                gotoxy(x, y); cout << "Presione una tecla para continuar...";
                _getch();
                system("cls");
                y = 2;
                gotoxy(x, y); cout << "*** LISTADO DE LIBROS (CONT.) ***";
                y += 2;
                gotoxy(x, y); cout << "CODIGO";
                gotoxy(x + 10, y); cout << "NOMBRE";
                gotoxy(x + 40, y); cout << "AUTOR";
                gotoxy(x + 70, y); cout << "AÑO";
                gotoxy(x + 80, y); cout << "ESTADO";
                y++;
            }

            actual = actual->sigt;
        }
    }

    gotoxy(x, y + 2); cout << "Presione una tecla para continuar...";
    _getch();
}

void eliminarLibro(Libro*& inicio, Libro*& fin, Prestamo* prestamos) {
    system("cls");
    string codigo;

    gotoxy(5, 2); cout << "*** ELIMINAR LIBRO ***";
    gotoxy(5, 4); cout << "Ingrese el código del libro: ";
    gotoxy(32, 4); cin >> codigo;

    Libro* libro = buscarLibro(inicio, codigo);
    if (!libro) {
        gotoxy(5, 6); cout << "Libro no encontrado!";
        gotoxy(5, 8); system("pause");
        return;
    }

    // Verificar si el libro tiene préstamos registrados (actuales o históricos)
    Prestamo* actual = prestamos;
    while (actual) {
        if (actual->cod_libro == codigo) {  // Eliminamos la validación del estado
            gotoxy(5, 6); cout << "No se puede eliminar. El libro tiene préstamos registrados.";
            gotoxy(5, 8); system("pause");
            return;
        }
        actual = actual->sigt;
    }

    // Eliminar de la lista
    if (libro->ant != NULL) {  
        libro->ant->sigt = libro->sigt;  
    } else {  
        inicio = libro->sigt;  
    }

    if (libro->sigt != NULL) {  
        libro->sigt->ant = libro->ant;  
    } else {  
        fin = libro->ant;  
    }
    delete libro;
    gotoxy(5, 6); cout << "¡Libro eliminado exitosamente!";
    gotoxy(5, 8); system("pause");
}

void ordenarLibrosAnio(Libro*& inicio) {
    if (!inicio || !inicio->sigt) {
        cout << "No hay suficientes libros para ordenar.\n";
        system("pause");
        return;
    }

    bool intercambio;
    Libro* actual;
    Libro* ultimo = NULL;

    do {
        intercambio = false;
        actual = inicio;

        while (actual->sigt != ultimo) {
            if (actual->anio_edicion > actual->sigt->anio_edicion) {
                // Intercambiar nodos (actual y actual->sigt)
                
                // 1. Preparar nodos temporales
                Libro* anterior = actual->ant;
                Libro* siguiente = actual->sigt;
                Libro* sigDelSig = siguiente->sigt;

                // 2. Reconfigurar enlaces
                if (anterior) {
                    anterior->sigt = siguiente;
                } else {
                    inicio = siguiente; // Actualizar inicio si es el primer nodo
                }

                siguiente->ant = anterior;
                siguiente->sigt = actual;
                actual->ant = siguiente;
                actual->sigt = sigDelSig;

                if (sigDelSig) {
                    sigDelSig->ant = actual;
                }

                intercambio = true;
            } else {
                actual = actual->sigt;
            }
        }
        ultimo = actual; // Optimización: el último ya está ordenado
    } while (intercambio);

    cout << "\n¡Libros ordenados por año de edición!\n";
    system("pause");
}

void registrarUsuario(Usuario*& inicio, Usuario*& fin) {
    system("cls");
    Usuario* nuevo = new Usuario();

    gotoxy(5, 2); cout << "*** REGISTRO DE USUARIO ***";

    gotoxy(5, 4); cout << "Código: ";
    gotoxy(14, 4); cin >> nuevo->codigo;

    gotoxy(5, 5); cout << "Nombres: ";
    gotoxy(14, 5); cin.ignore();
    getline(cin, nuevo->nombres);

    gotoxy(5, 6); cout << "Apellidos: ";
    gotoxy(16, 6); getline(cin, nuevo->apellidos);

    gotoxy(5, 7); cout << "DNI: ";
    gotoxy(10, 7); getline(cin, nuevo->DNI);

    gotoxy(5, 8); cout << "Domicilio: ";
    gotoxy(16, 8); getline(cin, nuevo->domicilio);

    gotoxy(5, 9); cout << "Fecha nacimiento: ";
    gotoxy(23, 9); getline(cin, nuevo->fecha_nacimiento);

    nuevo->estado = true;
    nuevo->sigt = NULL;	
	nuevo->ant = fin;  // El anterior del nuevo nodo es el actual fin

	if (fin != NULL) {  // Si hay nodos en la lista
	    fin->sigt = nuevo;
	} else {  // Lista vacía
	    inicio = nuevo;
	}
	fin = nuevo;

    gotoxy(5, 11); cout << "¡Usuario registrado exitosamente!";
    gotoxy(5, 13); system("pause");
}

Usuario* buscarUsuario(Usuario* inicio, string codigo) {
    Usuario* actual = inicio;
    while (actual) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->sigt;
    }
    return NULL;
}

void listarUsuarios(Usuario* inicio) {
    system("cls");
    int x = 5, y = 2;

    gotoxy(x, y); cout << "*** LISTADO DE USUARIOS ***";
    y += 2;

    if (!inicio) {
        gotoxy(x, y); cout << "No hay usuarios registrados.";
    }
    else {
        gotoxy(x, y); cout << "CODIGO";
        gotoxy(x + 10, y); cout << "NOMBRES";
        gotoxy(x + 40, y); cout << "APELLIDOS";
        gotoxy(x + 70, y); cout << "DNI";
        y++;

        Usuario* actual = inicio;
        while (actual) {
            gotoxy(x, y); cout << actual->codigo;
            gotoxy(x + 10, y); cout << (actual->nombres.length() > 30 ? actual->nombres.substr(0, 27) + "..." : actual->nombres);
            gotoxy(x + 40, y); cout << (actual->apellidos.length() > 25 ? actual->apellidos.substr(0, 22) + "..." : actual->apellidos);
            gotoxy(x + 70, y); cout << actual->DNI;
            y++;

            if (y > 25 && actual->sigt) {
                gotoxy(x, y); cout << "Presione una tecla para continuar...";
                _getch();
                system("cls");
                y = 2;
                gotoxy(x, y); cout << "*** LISTADO DE USUARIOS (CONT.) ***";
                y += 2;
                gotoxy(x, y); cout << "CODIGO";
                gotoxy(x + 10, y); cout << "NOMBRES";
                gotoxy(x + 40, y); cout << "APELLIDOS";
                gotoxy(x + 70, y); cout << "DNI";
                y++;
            }

            actual = actual->sigt;
        }
    }

    gotoxy(x, y + 2); cout << "Presione una tecla para continuar...";
    _getch();
}

void registrarPrestamo(Prestamo*& inicio, Prestamo*& fin, Libro* libros, Usuario* usuarios) {
    system("cls");
    string codLibro, codUsuario;

    gotoxy(5, 2); cout << "*** REGISTRO DE PRÉSTAMO ***";

    gotoxy(5, 4); cout << "Código del libro: ";
    gotoxy(24, 4); cin >> codLibro;
    Libro* libro = buscarLibro(libros, codLibro);
    if (!libro || !libro->estado) {
        gotoxy(5, 6); cout << "Libro no disponible!";
        gotoxy(5, 8); system("pause");
        return;
    }

    gotoxy(5, 6); cout << "Código del usuario: ";
    gotoxy(26, 6); cin >> codUsuario;
    Usuario* usuario = buscarUsuario(usuarios, codUsuario);
    if (!usuario || !usuario->estado) {
        gotoxy(5, 8); cout << "Usuario no válido!";
        gotoxy(5, 10); system("pause");
        return;
    }

    Prestamo* nuevo = new Prestamo();
    gotoxy(5, 8); cout << "Número de pedido: ";
    gotoxy(24, 8); cin >> nuevo->num_pedido;

    nuevo->cod_libro = codLibro;
    nuevo->cod_usuario = codUsuario;

		int dia, mes, anio;
		stringstream ss; // Reutilizable
		string fecha_formateada;
		
		// === Fecha de salida ===
		gotoxy(5, 10); cout << "Fecha de salida:";
		gotoxy(5, 11); cout << "Día: ";
		gotoxy(12, 11); cin >> dia;
		gotoxy(20, 11); cout << "Mes: ";
		gotoxy(26, 11); cin >> mes;
		gotoxy(34, 11); cout << "Año: ";
		gotoxy(40, 11); cin >> anio;
		
		// Formatear fecha salida
		ss.str(""); ss.clear(); // Limpiar el stringstream antes de usarlo
		if (dia < 10) ss << "0";
		ss << dia << "/";
		if (mes < 10) ss << "0";
		ss << mes << "/";
		ss << anio;
		
		nuevo->fecha_salida = ss.str();
		
		// === Fecha máxima de devolución ===
		gotoxy(5, 13); cout << "Fecha máxima devolución:";
		gotoxy(5, 14); cout << "Día: ";
		gotoxy(12, 14); cin >> dia;
		gotoxy(20, 14); cout << "Mes: ";
		gotoxy(26, 14); cin >> mes;
		gotoxy(34, 14); cout << "Año: ";
		gotoxy(40, 14); cin >> anio;
		
		// Formatear fecha devolución
		ss.str(""); ss.clear(); // Limpiar el stringstream otra vez
		if (dia < 10) ss << "0";
		ss << dia << "/";
		if (mes < 10) ss << "0";
		ss << mes << "/";
		ss << anio;
		
		nuevo->fecha_max_devolucion = ss.str();

    nuevo->estado = "Prestado";
    nuevo->sigt = NULL;
	nuevo->ant = fin;  // El anterior del nuevo nodo es el actual fin

	if (fin != NULL) {  // Si hay nodos en la lista
	    fin->sigt = nuevo;
	} else {  // Lista vacía
	    inicio = nuevo;
	}
	fin = nuevo;
    libro->estado = false; // Marcar libro como prestado

    gotoxy(5, 15); cout << "¡Préstamo registrado exitosamente!";
    gotoxy(5, 16); system("pause");
}

void registrarDevolucion(Prestamo* inicio, Libro*& libros) {
    system("cls");
    string numPedido;

    gotoxy(5, 2); cout << "*** REGISTRO DE DEVOLUCIÓN ***";
    gotoxy(5, 4); cout << "Número de pedido: ";
    gotoxy(24, 4); cin >> numPedido;

    Prestamo* prestamo = NULL;
    Prestamo* actual = inicio;
    while (actual) {
        if (actual->num_pedido == numPedido && actual->estado == "Prestado") {
            prestamo = actual;
            break;
        }
        actual = actual->sigt;
    }

    if (!prestamo) {
        gotoxy(5, 6); cout << "Préstamo no encontrado o ya devuelto!";
        gotoxy(5, 8); system("pause");
        return;
    }

   int dia, mes, anio;
		stringstream ss; // Reutilizable
		string fecha_formateada;
		
		// === Fecha de devolucion ===
		gotoxy(5, 5); cout << "Fecha de devolucion:";
		gotoxy(5, 6); cout << "Día: ";
		gotoxy(12, 6); cin >> dia;
		gotoxy(20, 6); cout << "Mes: ";
		gotoxy(26, 6); cin >> mes;
		gotoxy(34, 6); cout << "Año: ";
		gotoxy(40, 6); cin >> anio;
		
		// Formatear fecha devolucion 
		ss.str(""); ss.clear(); // Limpiar el stringstream antes de usarlo
		if (dia < 10) ss << "0";
		ss << dia << "/";
		if (mes < 10) ss << "0";
		ss << mes << "/";
		ss << anio;
		
	prestamo->fecha_devolucion = ss.str();
    	
    prestamo->estado = "Entregado";

    // Marcar libro como disponible
    Libro* libro = buscarLibro(libros, prestamo->cod_libro);
    if (libro) {
        libro->estado = true;
    }

    gotoxy(5, 8); cout << "¡Devolución registrada exitosamente!";
    gotoxy(5, 10); system("pause");
}

void listarPrestamosFecha(Prestamo* inicio, string fecha) {
    system("cls");
    int x = 5, y = 2;

    gotoxy(x, y); cout << "*** PRÉSTAMOS DEL " << fecha << " ***";
    y += 2;

    if (!inicio) {
        gotoxy(x, y); cout << "No hay préstamos registrados.";
    }
    else {
        gotoxy(x, y); cout << "N° PEDIDO";
        gotoxy(x + 15, y); cout << "LIBRO";
        gotoxy(x + 45, y); cout << "USUARIO";
        gotoxy(x + 75, y); cout << "ESTADO";
        y++;

        bool encontrados = false;
        Prestamo* actual = inicio;
        while (actual) {
            if (actual->fecha_salida == fecha) {
                encontrados = true;
                gotoxy(x, y); cout << actual->num_pedido;
                gotoxy(x + 15, y); cout << actual->cod_libro;
                gotoxy(x + 45, y); cout << actual->cod_usuario;
                gotoxy(x + 75, y); cout << actual->estado;
                y++;

                if (y > 25 && actual->sigt) {
                    gotoxy(x, y); cout << "Presione una tecla para continuar...";
                    _getch();
                    system("cls");
                    y = 2;
                    gotoxy(x, y); cout << "*** PRÉSTAMOS DEL " << fecha << " (CONT.) ***";
                    y += 2;
                    gotoxy(x, y); cout << "N° PEDIDO";
                    gotoxy(x + 15, y); cout << "LIBRO";
                    gotoxy(x + 45, y); cout << "USUARIO";
                    gotoxy(x + 75, y); cout << "ESTADO";
                    y++;
                }
            }
            actual = actual->sigt;
        }

        if (!encontrados) {
            gotoxy(x, y); cout << "No hay préstamos en esta fecha.";
        }
    }

    gotoxy(x, y + 2); cout << "Presione una tecla para continuar...";
    _getch();
}

void contarPrestamosLibros(Prestamo* inicio, Libro* libros) {
    system("cls");
    int x = 5, y = 2;

    gotoxy(x, y); cout << "*** CONTEO DE PRÉSTAMOS POR LIBRO ***";
    y += 2;

    if (!libros) {
        gotoxy(x, y); cout << "No hay libros registrados.";
    }
    else {
        gotoxy(x, y); cout << "LIBRO";
        gotoxy(x + 40, y); cout << "CÓDIGO";
        gotoxy(x + 60, y); cout << "PRÉSTAMOS";
        y++;

        Libro* actualLibro = libros;
        while (actualLibro) {
            int contador = 0;
            Prestamo* actualPrestamo = inicio;
            while (actualPrestamo) {
                if (actualPrestamo->cod_libro == actualLibro->codigo) {
                    contador++;
                }
                actualPrestamo = actualPrestamo->sigt;
            }

            gotoxy(x, y); cout << (actualLibro->nombre.length() > 35 ? actualLibro->nombre.substr(0, 32) + "..." : actualLibro->nombre);
            gotoxy(x + 40, y); cout << actualLibro->codigo;
            gotoxy(x + 60, y); cout << contador;
            y++;

            if (y > 25 && actualLibro->sigt) {
                gotoxy(x, y); cout << "Presione una tecla para continuar...";
                _getch();
                system("cls");
                y = 2;
                gotoxy(x, y); cout << "*** CONTEO DE PRÉSTAMOS POR LIBRO (CONT.) ***";
                y += 2;
                gotoxy(x, y); cout << "LIBRO";
                gotoxy(x + 40, y); cout << "CÓDIGO";
                gotoxy(x + 60, y); cout << "PRÉSTAMOS";
                y++;
            }

            actualLibro = actualLibro->sigt;
        }
    }

    gotoxy(x, y + 2); cout << "Presione una tecla para continuar...";
    _getch();
}
