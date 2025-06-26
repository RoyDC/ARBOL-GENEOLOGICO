
#include <iostream>
using namespace std; 

// Definicion de la estructura Persona
// Cada nodo del arbol representa una persona con sus datos genealogicos
struct Persona {
    int id;                // Identificador unico de la persona
    string nombre;         // Nombre del miembro
    string posicion;       // Rol o cargo dentro de la civilizacion (ejemplo: lider, guerrero)
    Persona* izquierda;    // Puntero al hijo izquierdo (ID menor)
    Persona* derecha;      // Puntero al hijo derecho (ID mayor)
};

// Funcion para crear un nuevo nodo Persona
// Inicializa los datos y los punteros en NULL
Persona* crearPersona(int id, string nombre, string posicion) {
    Persona* nueva = new Persona(); // Se reserva memoria para una nueva persona
    nueva->id = id;                 // Se asigna el ID ingresado
    nueva->nombre = nombre;         // Se asigna el nombre ingresado
    nueva->posicion = posicion;     // Se asigna la posicion o rol
    nueva->izquierda = nueva->derecha = NULL; // Ambos hijos se inicializan como vacios
    return nueva; // Se devuelve el puntero al nuevo nodo creado
}

// Funcion para insertar una persona en el arbol binario de busqueda (ABB)
Persona* insertar(Persona* raiz, int id, string nombre, string posicion) {
    if (raiz == NULL) {
        // Si el arbol esta vacio o se llego a una hoja, se inserta una nueva persona
        return crearPersona(id, nombre, posicion);
    }
    if (id < raiz->id) {
        // Si el ID es menor, se inserta en el subarbol izquierdo
        raiz->izquierda = insertar(raiz->izquierda, id, nombre, posicion);
    } else if (id > raiz->id) {
        // Si el ID es mayor, se inserta en el subarbol derecho
        raiz->derecha = insertar(raiz->derecha, id, nombre, posicion);
    } else {
        // Si el ID ya existe, se evita insertar duplicados
        cout << "ID duplicado. No se inserto.\n";
    }
    return raiz; // Se retorna la raiz actualizada
}

// Recorrido INORDEN: izquierda -> raiz -> derecha
// Se usa para mostrar el arbol en orden creciente de ID
void inorden(Persona* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda); // Primero recorre el subarbol izquierdo
        cout << "ID: " << raiz->id 
             << "  Nombre: " << raiz->nombre 
             << "  Posicion: " << raiz->posicion << endl;
        inorden(raiz->derecha); // Luego recorre el subarbol derecho
    }
}

// Recorrido PREORDEN: raiz -> izquierda -> derecha
// Se usa para representar jerarquias o niveles de genealogia
void preorden(Persona* raiz) {
    if (raiz != NULL) {
        cout << "ID: " << raiz->id 
             << "  Nombre: " << raiz->nombre 
             << "  Posicion: " << raiz->posicion << endl;
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

// Recorrido POSTORDEN: izquierda -> derecha -> raiz
// Se usa en eliminaciones o evaluaciones por ramas completas
void postorden(Persona* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        cout << "ID: " << raiz->id 
             << "  Nombre: " << raiz->nombre 
             << "  Posicion: " << raiz->posicion << endl;
    }
}

// Funcion para buscar una persona en el arbol por su ID
// Retorna la informacion si se encuentra o un mensaje si no
void buscar(Persona* raiz, int idBuscado) {
    if (raiz == NULL) {
        cout << "Persona no encontrada.\n"; // Caso base: no existe
        return;
    }
    if (idBuscado == raiz->id) {
        // Coincidencia encontrada: muestra la informacion
        cout << "\nPersona encontrada:\n";
        cout << "ID: " << raiz->id << "\nNombre: " << raiz->nombre << "\nPosicion: " << raiz->posicion << "\n";
    } else if (idBuscado < raiz->id) {
        // Si es menor, busca en el subarbol izquierdo
        buscar(raiz->izquierda, idBuscado);
    } else {
        // Si es mayor, busca en el subarbol derecho
        buscar(raiz->derecha, idBuscado);
    }
}

// Funcion auxiliar para encontrar el nodo con menor ID
// Se usa en el proceso de eliminacion cuando hay dos hijos
Persona* encontrarMinimo(Persona* nodo) {
    while (nodo->izquierda != NULL) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

// Funcion para eliminar una persona del arbol por su ID
Persona* eliminar(Persona* raiz, int id) {
    if (raiz == NULL) {
        return NULL; // El nodo no existe
    }
    if (id < raiz->id) {
        raiz->izquierda = eliminar(raiz->izquierda, id);
    } else if (id > raiz->id) {
        raiz->derecha = eliminar(raiz->derecha, id);
    } else {
        // Nodo encontrado: se evalua el caso correspondiente

        // Caso 1: nodo sin hijos
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            delete raiz;
            return NULL;
        }
        // Caso 2: solo tiene hijo derecho
        else if (raiz->izquierda == NULL) {
            Persona* temp = raiz->derecha;
            delete raiz;
            return temp;
        }
        // Caso 3: solo tiene hijo izquierdo
        else if (raiz->derecha == NULL) {
            Persona* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        // Caso 4: tiene dos hijos
        else {
            Persona* temp = encontrarMinimo(raiz->derecha); // Se busca el sucesor
            // Se copian los datos del sucesor
            raiz->id = temp->id;
            raiz->nombre = temp->nombre;
            raiz->posicion = temp->posicion;
            // Se elimina el sucesor duplicado
            raiz->derecha = eliminar(raiz->derecha, temp->id);
        }
    }
    return raiz; // Se retorna la raiz actualizada
}

// Funcion principal: administra el menu del programa
int main() {
    Persona* raiz = NULL; // Arbol inicialmente vacio
    int opcion; // Variable para controlar las opciones del menu

    do {
      
        cout << "\n--- MENU ARBOL GENEALOGICO ---\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Mostrar recorrido inorden\n";
        cout << "3. Mostrar recorrido preorden\n";
        cout << "4. Mostrar recorrido postorden\n";
        cout << "5. Buscar miembro por ID\n";
        cout << "6. Eliminar miembro por ID\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        
        switch (opcion) {
            case 1: {
                // Inserta un nuevo miembro
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
                inorden(raiz);
                break;
            case 3:
                
                cout << "\n--- RECORRIDO PREORDEN ---\n";
                preorden(raiz);
                break;
            case 4:

                cout << "\n--- RECORRIDO POSTORDEN ---\n";
                postorden(raiz);
                break;
            case 5: {
                // Busca un miembro por su ID
                int idBuscar;
                cout << "Ingrese ID a buscar: ";
                cin >> idBuscar;
                buscar(raiz, idBuscar);
                break;
            }
            case 6: {
                // Elimina un miembro por su ID
                int idEliminar;
                cout << "Ingrese ID a eliminar: ";
                cin >> idEliminar;
                raiz = eliminar(raiz, idEliminar);
                break;
            }
            case 7:
                // Finaliza el programa
                cout << "Saliendo del programa.\n";
                break;
            default:
                // Opcion no valida
                cout << "Opcion no valida. Intente nuevamente.\n";
        }
    } while (opcion != 7); // El programa se repite hasta que se elija salir

    return 0; // Fin del programa
}
