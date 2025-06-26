#include <iostream> 
using namespace std; 

// Estructura que representa a cada persona del arbol genealogico
struct Persona {
    int id;                // Identificador unico de la persona
    string nombre;         // Nombre de la persona
    string posicion;       // Posicion o rol en la civilizacion
    Persona* izquierda;    // Puntero al hijo izquierdo (menor ID)
    Persona* derecha;      // Puntero al hijo derecho (mayor ID)
};

// Funcion que crea un nuevo nodo (miembro) en el arbol
Persona* crearPersona(int id, string nombre, string posicion) {
    Persona* nueva = new Persona(); // Reserva memoria para una nueva persona
    nueva->id = id;                 // Asigna el ID
    nueva->nombre = nombre;         // Asigna el nombre
    nueva->posicion = posicion;     // Asigna la posicion
    nueva->izquierda = nueva->derecha = NULL; // Inicializa sus hijos como nulos
    return nueva; // Devuelve el puntero al nuevo nodo
}

// Funcion que inserta un nodo en el arbol binario de busqueda (ABB)
Persona* insertar(Persona* raiz, int id, string nombre, string posicion) {
    if (raiz == NULL) {
        return crearPersona(id, nombre, posicion); // Si el arbol esta vacio, crea nuevo nodo
    }
    if (id < raiz->id) {
        raiz->izquierda = insertar(raiz->izquierda, id, nombre, posicion); // Inserta a la izquierda si el ID es menor
    } else if (id > raiz->id) {
        raiz->derecha = insertar(raiz->derecha, id, nombre, posicion); // Inserta a la derecha si el ID es mayor
    } else {
        cout << "ID duplicado. No se inserto.\n"; // Evita duplicados
    }
    return raiz; // Retorna la raiz del arbol
}

// Recorrido inorden (izquierda, raiz, derecha)
void inorden(Persona* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda); // Recorre subarbol izquierdo
        cout << "ID: " << raiz->id 
             << "  Nombre: " << raiz->nombre 
             << "  Posicion: " << raiz->posicion << endl; // Muestra datos del nodo
        inorden(raiz->derecha); // Recorre subarbol derecho
    }
}

// Funcion que busca una persona por su ID en el arbol
void buscar(Persona* raiz, int idBuscado) {
    if (raiz == NULL) {
        cout << "Persona no encontrada.\n"; // Si llega a un nodo nulo, no existe
        return;
    }
    if (idBuscado == raiz->id) {
        // Si el ID coincide, muestra los datos
        cout << "\nPersona encontrada:\n";
        cout << "ID: " << raiz->id << "\nNombre: " << raiz->nombre << "\nPosicion: " << raiz->posicion << "\n";
    } else if (idBuscado < raiz->id) {
        buscar(raiz->izquierda, idBuscado); // Busca en subarbol izquierdo
    } else {
        buscar(raiz->derecha, idBuscado); // Busca en subarbol derecho
    }
}

// Funcion que encuentra el nodo con menor ID (el mas a la izquierda)
Persona* encontrarMinimo(Persona* nodo) {
    while (nodo->izquierda != NULL) {
        nodo = nodo->izquierda; // Sigue avanzando hacia la izquierda
    }
    return nodo; // Retorna el nodo minimo
}

// Funcion que elimina un nodo dado su ID del arbol
Persona* eliminar(Persona* raiz, int id) {
    if (raiz == NULL) {
        return NULL; // Arbol vacio
    }
    if (id < raiz->id) {
        raiz->izquierda = eliminar(raiz->izquierda, id); // Busca en subarbol izquierdo
    } else if (id > raiz->id) {
        raiz->derecha = eliminar(raiz->derecha, id); // Busca en subarbol derecho
    } else {
        // Caso 1: nodo sin hijos
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            delete raiz;
            return NULL;
        }
        // Caso 2: solo hijo derecho
        else if (raiz->izquierda == NULL) {
            Persona* temp = raiz->derecha;
            delete raiz;
            return temp;
        }
        // Caso 3: solo hijo izquierdo
        else if (raiz->derecha == NULL) {
            Persona* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        // Caso 4: tiene dos hijos
        else {
            Persona* temp = encontrarMinimo(raiz->derecha); // Encuentra el sucesor
            // Copia los datos del sucesor al nodo actual
            raiz->id = temp->id;
            raiz->nombre = temp->nombre;
            raiz->posicion = temp->posicion;
            // Elimina el sucesor
            raiz->derecha = eliminar(raiz->derecha, temp->id);
        }
    }
    return raiz; // Retorna la raiz modificada
}

// Funcion principal (punto de entrada del programa)
int main() {
    Persona* raiz = NULL; // Inicializa el arbol vacio
    int opcion; // Variable para guardar la opcion del menu

    // Menu interactivo
    do {
        cout << "\n--- MENU ARBOL GENEALOGICO ---\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Mostrar arbol inorden\n";
        cout << "3. Buscar miembro por ID\n";
        cout << "4. Eliminar miembro por ID\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Procesamiento de opciones
        switch (opcion) {
            case 1: {
                int id;
                string nombre, posicion;
                cout << "ID: ";
                cin >> id;
                cout << "Nombre: ";
                cin >> nombre;
                cout << "Posicion: ";
                cin >> posicion;
                raiz = insertar(raiz, id, nombre, posicion);
                break;
            }
            case 2:
                cout << "\n--- RECORRIDO INORDEN ---\n";
                inorden(raiz); // Muestra arbol en orden
                break;
            case 3: {
                int idBuscar;
                cout << "Ingrese ID a buscar: ";
                cin >> idBuscar;
                buscar(raiz, idBuscar); // Llama a busqueda
                break;
            }
            case 4: {
                int idEliminar;
                cout << "Ingrese ID a eliminar: ";
                cin >> idEliminar;
                raiz = eliminar(raiz, idEliminar); // Llama a eliminacion
                break;
            }
            case 5:
                cout << "Saliendo del programa.\n"; 
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente.\n"; 
        }
    } while (opcion != 5); 

    return 0; 
}
