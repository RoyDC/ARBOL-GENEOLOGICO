// MENU DEL ARBOL - DE LA CRUZ

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
