/* PROYECTO SEGUNDO PARCIAL ESTRUCTURA DE DATOS:
CARRERA: SW 3/1
ASIGNATURA: ESTRUCTURA DE DATOS
DOCENTE: ING. JAIME OROZCO
DESARROLLADORES: HERNANDEZ ROCA WASHINGTON FABRICIO - RODRIGUEZ BORBOR NICK MAURICIO - POVEDA BAIDAL VICTOR ANDRES*/


#include <iostream>
#include <string>
#include <locale>
#include <windows.h>
#include <limits.h>

using namespace std;

struct nodo;
struct arista;

typedef nodo* Tnodo;
typedef arista* Tarista;

struct arista {
    Tnodo destino;
    int distancia;
    Tarista sgte;
};

struct nodo {
    string nombre;
    string tipo;
    string prioridad;
    int prioridadNum;
    Tnodo sgte;
    Tarista ady;
};

Tnodo cabecera = NULL;

// Estructura para jerarquía administrativa (árbol binario)
struct admin {
    string nombre;
    string zonaEncargada;
    int prioridad; // prioridad numérica
    admin* hijoIzq;
    admin* hijoDer;
};

typedef admin* Tadmin;
Tadmin raizAdmin = NULL;

int menu();
void gotoxy(int x, int y);
void registrarZona(string nombreZona, string tipoZona, string prioridadTexto);
void registrarAdministrador(string nombreAdmin, string zona, string prioridadTexto);
void establecerRuta(string origen, string destino, int distancia);
void mostrarZonas(Tnodo cab);
void mostrarConexiones(Tnodo cab);
void dijkstra(string nombreOrigen);
void rutaMasCorta();
void clasificarPorTipo(Tnodo inicio);
void listarZonasPorPrioridad(Tnodo inicio);
void mostrarJerarquia(Tadmin admin, int nivel);
Tnodo buscarZona(string nombre);
void buscarPorTipo(Tnodo cab, const string& tipoBuscado);
bool buscarAdministrador(Tadmin admin, const string& nombreAdmin);
void buscarZonaMenu();

// Función para eliminar espacios al inicio y final de un string (sin librerías externas)
string trim(string s) {
    int start = 0;
    while (start < (int)s.length() && s[start] == ' ') {
        start++;
    }
    int end = (int)s.length() - 1;
    while (end >= 0 && s[end] == ' ') {
        end--;
    }
    if (end >= start) {
        return s.substr(start, end - start + 1);
    }
    return "";  // Si solo eran espacios, retorna cadena vacía
}


int main() {
    setlocale(LC_CTYPE, "Spanish");
    int op;
    do {
        system("cls");  // Se limpia antes del menú
        op = menu();    // Mostrar menú y obtener opción

        switch (op) {
            case 1: {
                string nombreZona, tipoZona, prioridadTexto;
                cin.ignore();
                gotoxy(30, 21); cout << "Nombre de la zona: ";
                getline(cin, nombreZona);
                gotoxy(30, 22); cout << "Tipo de zona (Reserva, Bosque, Lago, etc.): ";
                getline(cin, tipoZona);
                gotoxy(30, 23); cout << "Prioridad (Alta - Media - Baja): ";
                getline(cin, prioridadTexto);
                registrarZona(nombreZona, tipoZona, prioridadTexto);
                break;
            }
            case 2: {
                string nombreAdmin, zona, prioridadTexto;
                cin.ignore();
                gotoxy(30, 21); cout << "Nombre del administrador: ";
                getline(cin, nombreAdmin);
                gotoxy(30, 22); cout << "Zona encargada: ";
                getline(cin, zona);
                gotoxy(30, 23); cout << "Prioridad (Alta - Media - Baja): ";
                getline(cin, prioridadTexto);
                registrarAdministrador(nombreAdmin, zona, prioridadTexto);
                break;
            }
            case 3: {
                string origen, destino;
                int distancia;
                cin.ignore();
                gotoxy(30, 21); cout << "Zona origen: ";
                getline(cin, origen);
                gotoxy(30, 22); cout << "Zona destino: ";
                getline(cin, destino);
                gotoxy(30, 23); cout << "Distancia entre zonas (Km): ";
                cin >> distancia;
                cin.ignore(); // Limpiar el buffer
                establecerRuta(origen, destino, distancia);
                break;
            }
            case 4:
                mostrarZonas(cabecera);
                break;
            case 5:
                mostrarConexiones(cabecera);
                break;
            case 6:
                rutaMasCorta();
                break;
            case 7:
                clasificarPorTipo(cabecera);
                break;
            case 8:
                listarZonasPorPrioridad(cabecera);
                break;
            case 9:
                if (raizAdmin == NULL) {
                    gotoxy(30, 21); cout << "No hay administradores registrados.\n";
                } else {
                    gotoxy(30, 21); cout << "Jerarquia administrativa:\n";
                    // Cambiar impresión para que no pise el menú: imprimiremos en pantalla limpia, incluyendo avance línea manual
                    system("cls");
                    int y = 5; // línea inicial para imprimir sin pisar menú
                    // Función auxiliar recursiva modificada para control de línea
                    void mostrarJerarquiaAvanzado(Tadmin admin, int nivel, int& y);
                    mostrarJerarquiaAvanzado(raizAdmin, 0, y);
                }
                break;
            case 10:
                buscarZonaMenu();
                break;
            case 11:
                gotoxy(30, 21); cout << "Saliendo del programa \n";
                break;
            default:
                gotoxy(30, 21); cout << "Opcion no valida. Intente nuevamente.\n";
        }

        if (op != 11) {
            gotoxy(30, 30); cout << "\nPresione Enter para continuar...";
            
            cin.get();     // Esperar a que el usuario presione Enter
        }

    } while (op != 11);

    return 0;
}

int menu() {
    int op;
    do {
        system("cls"); // Limpia la consola al inicio del menú
        gotoxy(30, 5);	cout << "----------------------------------------------------------";
        gotoxy(30, 6);	cout << "           MENU PRINCIPAL - ECOSISTEMA NATURAL            ";
        gotoxy(30, 7);	cout << "----------------------------------------------------------";
        gotoxy(30, 8);	cout << "1. Registrar nueva zona natural\n";
        gotoxy(30, 9);	cout << "2. Registrar administrador de zona\n";
        gotoxy(30, 10);	cout << "3. Establecer rutas entre zonas\n";
        gotoxy(30, 11);	cout << "4. Mostrar todas las zonas registradas\n";
        gotoxy(30, 12);	cout << "5. Mostrar conexiones entre zonas\n";
        gotoxy(30, 13);	cout << "6. Calcular ruta mas corta entre dos zonas\n";
        gotoxy(30, 14);	cout << "7. Clasificar zonas jerarquicamente por tipo\n";
        gotoxy(30, 15);	cout << "8. Listar zonas por prioridad\n";
        gotoxy(30, 16);	cout << "9. Mostrar jerarquia administrativa\n";
        gotoxy(30, 17);	cout << "10. Buscar zona especifica\n";
        gotoxy(30, 18);	cout << "11. Salir\n";
        gotoxy(30, 19); cout << "----------------------------------------------------------";
        gotoxy(30, 20);	cout << "Seleccione una opcion: ";
        
        cin >> op;

        // Validar entrada
        if (cin.fail() || op < 1 || op > 11) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(1000, '\n'); // Limpiar el buffer
            gotoxy(30, 23); cout << "Error: Ingrese opcion correcta (1 - 11)" << endl;
            gotoxy(30, 24);
            gotoxy(30, 30);
            system("pause"); // Esperar a que el usuario presione una tecla
            continue; // Volver a mostrar el menú
        }

        cin.ignore(1000, '\n'); // Limpiar el buffer después de leer la opción

    } while (op < 1 || op > 11);  // Repetir hasta que se ingrese una opción válida

    return op; 
}


// Función para mover el cursor en consola
void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

// Funcion Opcion #1
void registrarZona(string nombreZona, string tipoZona, string prioridadTexto) {
    // Limpiar espacios en blanco
    nombreZona = trim(nombreZona);
    tipoZona = trim(tipoZona);
    prioridadTexto = trim(prioridadTexto);

    Tnodo nuevo = new nodo;
    nuevo->nombre = nombreZona;

    // Removida la verificación de nombres únicos para permitir nombres duplicados
    nuevo->tipo = tipoZona;

    // Validar prioridad
    if (prioridadTexto == "Alta" || prioridadTexto == "alta") {
        nuevo->prioridad = "Alta";
        nuevo->prioridadNum = 1;
    } else if (prioridadTexto == "Media" || prioridadTexto == "media") {
        nuevo->prioridad = "Media";
        nuevo->prioridadNum = 2;
    } else if (prioridadTexto == "Baja" || prioridadTexto == "baja") {
        nuevo->prioridad = "Baja";
        nuevo->prioridadNum = 3;
    } else {
        gotoxy(30, 23); cout << "Prioridad invalida. Zona no registrada.\n";
        delete nuevo;
        return;
    }

    nuevo->sgte = NULL;
    nuevo->ady = NULL;

    // Insertar al final de la lista
    if (cabecera == NULL) {
        cabecera = nuevo;
    } else {
        Tnodo aux = cabecera;
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
    }

    gotoxy(30, 24); cout << "Zona '" << nuevo->nombre << "' registrada correctamente.\n";
}


// Funcion Opcion #2
Tadmin crearAdmin(string nombre, string zona, int prioridad) {
    Tadmin nuevo = new admin;
    nuevo->nombre = nombre;
    nuevo->zonaEncargada = zona;
    nuevo->prioridad = prioridad;
    nuevo->hijoIzq = NULL;
    nuevo->hijoDer = NULL;
    return nuevo;
}

void insertarAdmin(Tadmin& raiz, string nombre, string zona, int prioridad) {
    if (raiz == NULL) {
        raiz = crearAdmin(nombre, zona, prioridad);
    } else if (prioridad < raiz->prioridad) {
        insertarAdmin(raiz->hijoIzq, nombre, zona, prioridad);
    } else {
        insertarAdmin(raiz->hijoDer, nombre, zona, prioridad);
    }
}

void registrarAdministrador(string nombreAdmin, string zona, string prioridadTexto) {
    int prioridadNum;

    if (prioridadTexto == "Alta" || prioridadTexto == "alta") {
        prioridadNum = 1;
    } else if (prioridadTexto == "Media" || prioridadTexto == "media") {
        prioridadNum = 2;
    } else if (prioridadTexto == "Baja" || prioridadTexto == "baja") {
        prioridadNum = 3;
    } else {
        gotoxy(30, 23); cout << "Prioridad invalida. Administrador no registrado.\n";
        return;
    }

    insertarAdmin(raizAdmin, nombreAdmin, zona, prioridadNum);
    gotoxy(30, 24); cout << "Administrador registrado correctamente.\n";
}

int prioridadNumerica(string prioridad) {
    if (prioridad == "alta") return 1;
    if (prioridad == "media") return 2;
    if (prioridad == "baja") return 3;
    return 4; // valor por defecto si no coincide
}

string textoPrioridad(int prioridad) {
    if (prioridad == 1) return "Alta";
    else if (prioridad == 2) return "Media";
    else if (prioridad == 3) return "Baja";
    else return "Desconocida";
}

// Funcion Opcion #3
void establecerRuta(string origen, string destino, int distancia) {
    Tnodo nodoOrigen = buscarZona(origen);
    Tnodo nodoDestino = buscarZona(destino);

    if (nodoOrigen == NULL || nodoDestino == NULL) {
        gotoxy(30, 23); cout << "Alguna de las zonas no esta registrada.\n";
        return;
    }

    // Crear arista para origen
    Tarista nuevaArista = new arista;
    nuevaArista->destino = nodoDestino;
    nuevaArista->distancia = distancia;
    nuevaArista->sgte = nodoOrigen->ady;
    nodoOrigen->ady = nuevaArista;

    // Crear arista para destino (grafo no dirigido)
    Tarista aristaReversa = new arista;
    aristaReversa->destino = nodoOrigen;
    aristaReversa->distancia = distancia;
    aristaReversa->sgte = nodoDestino->ady;
    nodoDestino->ady = aristaReversa;

    gotoxy(30, 23); cout << "Ruta establecida correctamente.\n";
}

// Funcion Opcion #4
void mostrarZonas(Tnodo cab) {
    system("cls");
    if (cab == NULL) {
        gotoxy(30, 5);
        cout << "No hay zonas registradas.\n";
        return;
    }
    gotoxy(30, 3);
    cout << "Zonas registradas:\n";
    int y = 5;
    int contador = 1;
    Tnodo temp = cab;
    while (temp != NULL) {
        gotoxy(30, y++);
        cout << contador++ << ". " << temp->nombre << " | Tipo: " << temp->tipo << " | Prioridad: " << temp->prioridad << "    ";
        temp = temp->sgte;
    }
}


// Funcion Opcion #5
void mostrarConexiones(Tnodo cab) {
    system("cls");
	if (cab == NULL) {
        gotoxy(30, 5);
        cout << "No hay zonas registradas.\n";
        return;
    }
    int y = 5;
    Tnodo temp = cab;
    while (temp != NULL) {
        gotoxy(30, y++);
        cout << "Zona " << temp->nombre << " conecta con:";
        y++;
        Tarista aristaTemp = temp->ady;
        while (aristaTemp != NULL) {
            gotoxy(32, y++);
            cout << "- " << aristaTemp->destino->nombre << " (Distancia: " << aristaTemp->distancia << ")    ";
            aristaTemp = aristaTemp->sgte;
        }
        y++;
        temp = temp->sgte;
    }
}

// Funcion Opcion #6
void dijkstra(string nombreOrigen) {
    // Contar número de nodos para arreglos
    int n = 0;
    Tnodo temp = cabecera;
    while (temp != NULL) {
        n++;
        temp = temp->sgte;
    }
    if (n == 0) {
        gotoxy(30, 23); cout << "No hay zonas registradas.\n";
        return;
    }

    // Guardar nodos en arreglo para índice
    Tnodo* nodos = new Tnodo[n];
    temp = cabecera;
    for (int i = 0; i < n; i++) {
        nodos[i] = temp;
        temp = temp->sgte;
    }

    // Encontrar índice origen
    int origenIdx = -1;
    for (int i = 0; i < n; i++) {
        if (nodos[i]->nombre == nombreOrigen) {
            origenIdx = i;
            break;
        }
    }
    if (origenIdx == -1) {
        gotoxy(30, 23); cout << "Zona origen no encontrada.\n";
        delete[] nodos;
        return;
    }

    // Inicializar distancias e incluido
    int* dist = new int[n];
    bool* incluido = new bool[n];
    int* prev = new int[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        incluido[i] = false;
        prev[i] = -1;
    }
    dist[origenIdx] = 0;

    for (int count = 0; count < n - 1; count++) {
        // Elegir nodo con distancia mínima no incluido
        int minDist = INT_MAX, u = -1;
        for (int i = 0; i < n; i++) {
            if (!incluido[i] && dist[i] <= minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        incluido[u] = true;

        // Actualizar distancias de adyacentes
        Tarista aristaTemp = nodos[u]->ady;
        while (aristaTemp != NULL) {
            // Buscar índice destino
            int v = -1;
            for (int i = 0; i < n; i++) {
                if (nodos[i] == aristaTemp->destino) {
                    v = i;
                    break;
                }
            }
            if (v != -1 && !incluido[v] && dist[u] != INT_MAX &&
                dist[u] + aristaTemp->distancia < dist[v]) {
                dist[v] = dist[u] + aristaTemp->distancia;
                prev[v] = u;
            }
            aristaTemp = aristaTemp->sgte;
        }
    }

    // Mostrar resultados
    system("cls");
	gotoxy(30, 5); cout << "Distancias desde " << nombreOrigen << ":\n";
    for (int i = 0; i < n; i++) {
        gotoxy(30, 6 + i);
        cout << nodos[i]->nombre << ": ";
        if (dist[i] == INT_MAX)
            cout << "Inalcanzable\n";
        else {
            cout << dist[i] << " | Ruta: ";
            // Mostrar ruta inversa
            int ruta[100];
            int contador = 0;
            int actual = i;
            while (actual != -1) {
                ruta[contador++] = actual;
                actual = prev[actual];
            }
            for (int j = contador - 1; j >= 0; j--) {
                cout << nodos[ruta[j]]->nombre;
                if (j > 0) cout << " -> ";
            }
            cout << "\n";
        }
    }

    delete[] dist;
    delete[] incluido;
    delete[] prev;
    delete[] nodos;
}

void rutaMasCorta() {
    if (cabecera == NULL) {
        gotoxy(30, 23); cout << "No hay zonas registradas.\n";
        return;
    }
    string origen;
    cin.ignore();
    gotoxy(30, 23); cout << "Ingrese la zona origen para calcular rutas mas cortas: ";
    getline(cin, origen);
    dijkstra(origen);
}

// Funcion Opcion #7
void clasificarPorTipo(Tnodo inicio) {
    system("cls");
    if (inicio == NULL) {
        gotoxy(30, 23);
        cout << "No hay zonas registradas.\n";
        return;
    }

    // Arreglo para almacenar tipos únicos encontrados
    const int MAX_TIPOS = 100;
    string tiposUnicos[MAX_TIPOS];
    int numTipos = 0;

    Tnodo temp = inicio;
    while (temp != NULL) {
        // Verificar si tipo ya está en tiposUnicos
        bool encontrado = false;
        for (int i = 0; i < numTipos; i++) {
            if (tiposUnicos[i] == temp->tipo) {
                encontrado = true;
                break;
            }
        }
        // Si no está, agregarlo
        if (!encontrado && numTipos < MAX_TIPOS) {
            tiposUnicos[numTipos++] = temp->tipo;
        }
        temp = temp->sgte;
    }

    int y = 5;
    // Para cada tipo único, mostrar las zonas que pertenecen a ese tipo
    for (int t = 0; t < numTipos; t++) {
        gotoxy(30, y++);
        cout << "Zonas tipo " << tiposUnicos[t] << ":\n";

        temp = inicio;
        bool hay = false;
        while (temp != NULL) {
            if (temp->tipo == tiposUnicos[t]) {
                gotoxy(30, y++);
                cout << "- " << temp->nombre << " | Prioridad: " << temp->prioridad << "    ";
                hay = true;
            }
            temp = temp->sgte;
        }
        if (!hay) {
            gotoxy(30, y++);
            cout << "  (Ninguna)\n";
        }
        y++; // espacio entre tipos
    }
}

// Funcion Opcion #8
void listarZonasPorPrioridad(Tnodo inicio) {
    if (inicio == NULL) {
        gotoxy(30, 23);
        cout << "No hay zonas registradas.\n";
        return;
    }

    int n = 0;
    Tnodo temp = inicio;
    while (temp != NULL) {
        n++;
        temp = temp->sgte;
    }

    Tnodo* nodos = new Tnodo[n];
    temp = inicio;
    for (int i = 0; i < n; i++) {
        nodos[i] = temp;
        temp = temp->sgte;
    }

    // Ordenar por prioridadNum (menor = mayor prioridad)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (nodos[j]->prioridadNum > nodos[j + 1]->prioridadNum) {
                Tnodo aux = nodos[j];
                nodos[j] = nodos[j + 1];
                nodos[j + 1] = aux;
            }
        }
    }
	system("cls");
    gotoxy(30, 5);
    cout << "Zonas ordenadas por prioridad:\n";
    int y = 5;
    for (int i = 0; i < n; i++) {
        gotoxy(30, y++);
        cout << "- " << nodos[i]->nombre << " | Prioridad: " << nodos[i]->prioridad << "    ";
    }

    delete[] nodos;
}



// opcion # 9

void mostrarJerarquia(Tadmin admin, int nivel) {
    if (admin != NULL) {
        mostrarJerarquia(admin->hijoIzq, nivel + 1);

        gotoxy(30 + nivel * 4, 17 + nivel);
        cout << "+ " << admin->nombre << " (" << admin->zonaEncargada << ") [Prioridad: " << textoPrioridad(admin->prioridad) << "]" << endl;

        mostrarJerarquia(admin->hijoDer, nivel + 1);
    }
}

// Nueva función auxiliar para imprimir jerarquia sin pisar menú controlando línea Y
void mostrarJerarquiaAvanzado(Tadmin admin, int nivel, int& y) {
    if (admin != NULL) {
        mostrarJerarquiaAvanzado(admin->hijoIzq, nivel + 1, y);

        gotoxy(30 + nivel * 4, y++);
        cout << "+ " << admin->nombre << " (" << admin->zonaEncargada << ") [Prioridad: " << textoPrioridad(admin->prioridad) << "]" << endl;

        mostrarJerarquiaAvanzado(admin->hijoDer, nivel + 1, y);
    }
}// Las demás funciones permanecen igual que en el código original...










// Funcion auxiliar buscarZona
Tnodo buscarZona(string nombre) {
    Tnodo temp = cabecera;
    while (temp != NULL) {
        if (temp->nombre == nombre) {
            return temp; // Retorna la primera coincidencia encontrada
        }
        temp = temp->sgte;
    }
    return NULL;
}

// Funcion auxiliar buscarPorTipo
void buscarPorTipo(Tnodo cab, const string& tipoBuscado) {
    if (cab == NULL) {
        gotoxy(30, 23);
        cout << "No hay zonas registradas.\n";
        return;
    }
    bool encontrado = false;
    int y = 17;
    Tnodo temp = cab;
    gotoxy(30, y++);
    cout << "Zonas de tipo '" << tipoBuscado << "':\n";
    while (temp != NULL) {
        if (temp->tipo == tipoBuscado) {
            gotoxy(30, y++);
            cout << "- " << temp->nombre << " | Prioridad: " << temp->prioridad << endl;
            encontrado = true;
        }
        temp = temp->sgte;
    }
    if (!encontrado) {
        gotoxy(30, y++);
        cout << "(Ninguna zona de este tipo encontrada)\n";
    }
}

// Funcion auxiliar buscarAdministrador
bool buscarAdministrador(Tadmin admin, const string& nombreAdmin) {
    if (admin == NULL) {
        return false;
    }
    if (admin->nombre == nombreAdmin) {
        gotoxy(30, 17);
        cout << "Administrador encontrado:\n";
        gotoxy(30, 18);
        cout << "- Nombre: " << admin->nombre << "\n";
        gotoxy(30, 19);
        cout << "- Zona encargada: " << admin->zonaEncargada << "\n";
        gotoxy(30, 20);
        cout << "- Prioridad: " << textoPrioridad(admin->prioridad) << endl;
        return true;
    }
    if (buscarAdministrador(admin->hijoIzq, nombreAdmin)) {
        return true;
    }
    if (buscarAdministrador(admin->hijoDer, nombreAdmin)) {
        return true;
    }
    return false;
}

// Funcion Opcion #10
void buscarZonaMenu() {
    int opcionBusqueda;
    do {
        system("cls");
        
		gotoxy(30, 5);	cout << "-----------------------------------------------";
		gotoxy(30, 6);	cout << "           SUBMENU DE BUSQUEDA                 ";
        gotoxy(30, 7);	cout << "-----------------------------------------------";
		gotoxy(30, 8); cout << "1. Buscar por nombre de zona";
        gotoxy(30, 9); cout << "2. Buscar por tipo de zona";
        gotoxy(30, 10);	cout << "3. Buscar por administrador o jerarquia";
        gotoxy(30, 11);	cout << "4. Volver al menu principal";
        gotoxy(30, 12);	cout << "-----------------------------------------------";
		gotoxy(30, 13); cout << "Seleccione una opcion: ";

        if (!(cin >> opcionBusqueda)) {
            cin.clear();
            cin.ignore(10000, '\n');
            gotoxy(30, 24);
            cout << "Entrada no valida. Intente nuevamente...";
            cin.get();
            continue; // reinicia el bucle para mostrar menú limpio
        }
        cin.ignore(10000, '\n'); // Limpia buffer para getline siguiente

        switch (opcionBusqueda) {
            case 1: {
                gotoxy(30, 17);
                cout << "Ingrese el nombre de la zona a buscar: ";
                string nombreBuscado;
                getline(cin, nombreBuscado);
                Tnodo zona = buscarZona(nombreBuscado);
                if (zona != NULL) {
                    gotoxy(30, 18);
                    cout << "Zona encontrada:\n";
                    gotoxy(30, 19);
                    cout << "- Nombre: " << zona->nombre << "\n";
                    gotoxy(30, 20);
                    cout << "- Tipo: " << zona->tipo << "\n";
                    gotoxy(30, 21);
                    cout << "- Prioridad: " << zona->prioridad;
                } else {
                    gotoxy(30, 18);
                    cout << "No se encontro la zona con ese nombre.";
                }
                gotoxy(30, 23);
                cout << "Presione Enter para continuar...";
                cin.get();
                break;
            }
            case 2: {
                gotoxy(30, 17);
                cout << "Ingrese el tipo de zona a buscar: ";
                string tipoBuscado;
                getline(cin, tipoBuscado);
                buscarPorTipo(cabecera, tipoBuscado);
                gotoxy(30, 23);
                cout << "Presione Enter para continuar...";
                cin.get();
                break;
            }
            case 3: {
                gotoxy(30, 17);
                cout << "Ingrese el nombre del administrador a buscar: ";
                string nombreAdmin;
                getline(cin, nombreAdmin);
                bool encontrado = buscarAdministrador(raizAdmin, nombreAdmin);
                if (!encontrado) {
                    gotoxy(30, 18);
                    cout << "Administrador no encontrado en la jerarquia.";
                }
                gotoxy(30, 23);
                cout << "Presione Enter para continuar...";
                cin.get();
                break;
            }
            case 4:
                gotoxy(30, 23);
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                gotoxy(30, 18);
                cout << "Opción no valida. Intente nuevamente.";
                gotoxy(30, 20);
                cout << "Presione Enter para continuar...";
                cin.get();
                break;
        }
    } while (opcionBusqueda != 4);
}