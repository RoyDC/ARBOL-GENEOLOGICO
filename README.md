# ARBOL-GENEOLOGICO
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
