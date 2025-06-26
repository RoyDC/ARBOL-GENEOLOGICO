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
