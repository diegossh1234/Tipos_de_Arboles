#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Nodo {
    int dato;
    int altura;
    Nodo* der;
    Nodo* izq;
    Nodo* padre;
};

void menu();
Nodo crearNodo(int,Nodo);
void insertarNodo(Nodo*&, int,Nodo*);
void mostrarArbol(Nodo*, int);
bool busqueda(Nodo*, int);
void preOrden(Nodo*);
void inOrden(Nodo*);
void postOrden(Nodo*);
void eliminar(Nodo*, int);
void eliminarNodo(Nodo*);
Nodo* minimo(Nodo*);
void reemplazar(Nodo*, Nodo*);
void destruirNodo(Nodo*);
Nodo* arbol = NULL;
int nroNodos(Nodo*);
int altura(Nodo*);
int contar(Nodo *);


int main()
{
    menu();
}
//FunciÃ³n del menu
void menu() {
	system("color B");
    int dato, opcion,contador= 0;
    int opcion2;
    string op;
    op="si";
	while(op =="si"){

    do {
    	cout << "=======ARBOL AVL======="<<endl;
		cout << "        GRUPO 3     "<<endl;
        cout << "========>MENU<========" << endl;
        cout << "1.Insertar un nuevo nodo" << endl;
        cout << "2.Mostrar el arbol avl" << endl;
        cout << "3.Buscar un elemento en el arbol avl" << endl;
        cout << "4.Tipos de orden" << endl;
        cout << "5.Todos los Tipos de orden" << endl;
        cout << "6.Eliminar un nodo del arbol avl" << endl;
        cout << "7.La altura del arbol avl" << endl;
        cout << "8.Numero de nodos" << endl;
        cout << "9.Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
            switch (opcion) {
            	
            	case 1:
            cout << "Digite un numero: ";
            cin >> dato;
            insertarNodo(arbol, dato,NULL);
            cout << "\n";
            system("cls");
            break;
            
             case 2:
            cout << " Arbol impreso de forma recursiva: " << endl;
            mostrarArbol(arbol, contador);
            cout << "\n";
            system("pause");
            break;
            
            case 3:
            cout <<"\n" <<"Introduce el dato a buscar en el arbol ";
            cin >> dato;
            if (busqueda(arbol, dato) == true) {
                cout << "\n" << "El elemento " << dato << " si se encuentra en el arbol avl" << endl;
            }
            else {
                cout << "\n" << "El elemento " << dato << " no se encuentra en el arbol avl" << endl;
            }
            system("pause");
            break;
            
            case 4:
            		 int opcion2;
                          	do{
                             cout << endl;
                             cout << " 1. En inOrden     \n";
                             cout << " 2. Pre Orden    \n";
                             cout << " 3. Post Orden   \n";
                             cout << "\n  Opcion :  ";
                                  cin >> opcion2;
                                     switch (opcion2) {
                                     	case 1:
                                          inOrden(arbol);
                                          system("pause");
                                        	 break;                     
                                    	 case 2:
                                          preOrden(arbol); 
                                          system("pause");
                                           	break;
                                         case 3:
                                         postOrden(arbol); 
                                        	system("pause");
											break;
	                                         }		
                                      	}while (opcion2 != 4);
                   
                                           break;
            case 5:
            cout << "\nTodos los tipos de orden AVL:";
             cout << "\nIn Orden\n";
            inOrden(arbol);
            cout << "\nPre Orden\n";
            preOrden(arbol);
            cout << "\nPost Orden\n";
            postOrden(arbol); 
            cout << "\n";
            system("pause");
            break;
            
                    
           case 6:
            cout << "\nDigite el numero que desea eliminar del arbol avl:";
            cin >> dato;
            eliminar(arbol, dato);
            cout << "\n";
            system("pause");
            break;
            
            case 7:
        	int h;
            h = altura(arbol);
            cout << "La altura es : "<< h << endl;
            break;
            
            case 8:
            cout<<"Numero de nodos"<<endl;
        	cout<<contar(arbol);
            break;
            
            default:
			cout << "Opcion incorecta";
			
            }
            
          } while (opcion != 9);
    
    system("cls");
	cout<<"\n\nDESEA CONTINUAR CON EL ALGORITMO DEL ARBOL AVL: SI/NO "<< endl;
		cin>>op;
		
	}
	cout <<"................EL ALGORITMO SOBRE DEL ARBOL AVL HA TERMINADO.................."<<endl;
}  
            	
//FunciÃ³n para crear un nuevo nodo
Nodo* crearNodo(int n,Nodo* padre) {
    Nodo* nuevo_nodo = new Nodo();

    nuevo_nodo->dato = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->padre = padre;

    return nuevo_nodo;
}
//FunciÃ³n para insertar nodos en el Ã¡rbol
void insertarNodo(Nodo *&arbol, int n,Nodo*padre) {
    if (arbol == NULL) { //Si el arbol estÃ¡ vacÃ­o
        Nodo *nuevo_nodo = crearNodo(n,padre);
        arbol = nuevo_nodo;
    }
    else { // Si el arbol tiene un nodo o mÃ¡s
        int valorRaiz = arbol->dato; // Obtener valor de la raÃ­z
        if (n < valorRaiz) {
            insertarNodo(arbol->izq, n,arbol);
        }
        else {
            insertarNodo(arbol->der, n,arbol);
        }
    }
}
//FunciÃ³n para mostrar el arbol
void mostrarArbol(Nodo* arbol, int cont) {
    if (arbol == NULL) {
        return;
    }
    else {
        mostrarArbol(arbol->der, cont + 1);
        for (int i = 0; i < cont; i++) {
            cout <<"    ";
        }
        cout << arbol->dato << endl;
        mostrarArbol(arbol->izq, cont + 1);
    }
}
// FunciÃ³n para buscar un dato en el arbol
bool busqueda(Nodo* arbol, int n) {
    if (arbol == NULL) {
        return false;
    }
    else if (arbol->dato == n){
        return true;
    }
    else if (n <arbol->dato) {
        return busqueda(arbol->izq, n);
    }
    else {
        return busqueda(arbol->der, n);
    }
}
// Funcion para recorrido en profundidad - PreOrden
void preOrden(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    }
    else {
        cout << arbol->dato << " - ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}
// Funcion para recorrido en profundidad - InOrden
void inOrden(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    }
    else {
        inOrden(arbol->izq);
        cout << arbol->dato << " - ";
        inOrden(arbol->der);
    }
}
// Funcion para recorrido en profundidad - PostOrden
void postOrden(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    }
    else {
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout << arbol->dato << " - ";
    }
}
// Funcion para eliminar un nodo del arbol
void eliminar(Nodo* arbol, int n) {
    if (arbol == NULL) {
        return;
    }
    else if (n < arbol->dato) { //Si el valor es menor
        eliminar(arbol->izq, n); // Busca por la izquierda
    }
    else if (n > arbol->dato) { // Si el valor es mayor
        eliminar(arbol->der, n); //Busca por la derecha
    }
    else {
        eliminarNodo(arbol);
    }
}
// Funcion para eliminar el nodo encontrado
void eliminarNodo(Nodo* nodoEliminar) {
    if (nodoEliminar->izq && nodoEliminar->der) {
        Nodo* menor = minimo(nodoEliminar->der); // Primero te vas hacia la derecha
        nodoEliminar->dato = menor->dato;
        eliminarNodo(menor);
    }
    else if (nodoEliminar->izq) {
        reemplazar(nodoEliminar, nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }
    else if (nodoEliminar->der) {
        reemplazar(nodoEliminar, nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }
    else { // No tiene hijos
        reemplazar(nodoEliminar, NULL);
        destruirNodo(nodoEliminar);
    }
}
// FunciÃ³n para determinar el nodo mÃ¡s izquierdo posible
Nodo* minimo(Nodo* arbol) {
    if (arbol == NULL) {
        return NULL;
    }
    if (arbol->izq) { // Si tiene hijo izquierdo
        return minimo(arbol->izq); // retorna el hijo izquierdo
    }
    else { // Si no tiene hijo izquierdo (significa que Ã©l es el mÃ¡s izquierdo)
        return arbol; // se retorna a sÃ­ mismo
    }
}
// FunciÃ³n para reemplazar dos nodos
void reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
    if (arbol->padre) {
        //arbol->padre hay que asignarle su nuevo hijo
        if (arbol->dato == arbol->padre->izq->dato) {
            arbol->padre->izq = nuevoNodo;
        }
        else if (arbol->dato == arbol->padre->der->dato) {
            arbol->padre->der = nuevoNodo;
        }
    }
    if (nuevoNodo) {
        // Procedemos a asignarle su nuevo padre
        nuevoNodo->padre = arbol->padre;
    }
}
// FunciÃ³n para destruir un nodo
void destruirNodo(Nodo* nodo) {
    nodo->izq = NULL;
    nodo->der = NULL;
    delete nodo;
}

int alturaRec_v1(Nodo* v){
	if(v->izq==NULL && v->der==NULL)return 0;
	int altIzq=-1, altDer=-1;
	if(v->izq!=NULL) altIzq=alturaRec_v1(v->izq);
	if(v->der!=NULL) altDer=alturaRec_v1(v->der);
	//Elegimos el mayor valor y le sumamos 1..
	if(altIzq>altDer)return altIzq+1;
	else return altDer+1;	
}

int altura(Nodo* arbol){
    int AltIzq, AltDer;
 
    if(arbol==NULL)
        return -1;
    else
    {
        AltIzq = altura(arbol->izq);
        AltDer = altura(arbol->der);
 
        if(AltIzq>AltDer)
            return AltIzq+1;
        else
            return AltDer+1;
    }
}
int contar(Nodo *arbol)
{
	if(arbol ==NULL)
	{
		return 0 ;
	}
	else
	{
		int izquierda = contar(arbol->izq);
		int derecha = contar(arbol->der);
		int medio=1;
		return izquierda+derecha+medio;
		
	}
	
}