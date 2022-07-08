#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct Nodo {
    string dato;
    Nodo* der;
    Nodo* izq;
    Nodo* padre;
    int altura;
};

void menu();
Nodo *crearNodo(string,Nodo*);
void insertarNodo(Nodo*&, string,Nodo*);
void mostrarArbol(Nodo*, int);
void eliminar(Nodo*, string);
void eliminarNodo(Nodo*);
bool busqueda(Nodo *, string);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);

Nodo* arbol = NULL;
Nodo* minimo(Nodo*);
void reemplazar(Nodo*, Nodo*);
void destruirNodo(Nodo*);
int altura(Nodo*);
void general(Nodo *);
int contar(Nodo*);
string salida();

int main()
{
    menu();
    cout << "EL ALGORITMO DE LAS OPERACIONES CON ARBOLES BINARIO HA FINALIZADO.";
}

void menu() {
    int  opcion, numero, contador= 0;
    string dato;
	string respuesta = "si";
    do {
        cout << "\t===============MENU==================" << endl;
        cout << "======Analisis de sentimientos mediante Machine Learning=======" << endl;
        cout << "1.Crear Arbol Binario" << endl;
        cout << "2.Insertar un nuevo nodo" << endl;
        cout << "3.Mostrar el arbol" << endl;
        cout << "4.Eliminar Nodo" << endl;
        cout << "5.Buscar Nodo"<<endl;
        cout << "6.PreOrden"<<endl;
        cout << "7.InOrden"<<endl;
        cout << "8.PostOrden"<<endl;
        cout << "9.Recorrido general"<<endl; 
        cout << "10.Altura del arbol" << endl;
        cout << "11.Numero de nodos "<<endl;
        cout << "12.Salir"<<endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
        	cout << "Cuantos datos desea ingresar: ";
        	cin >> numero;
        	for(int i = 0; i < numero; i++){
        		cout << "Digite el elemento: ";
	            cin >> dato;
	            insertarNodo(arbol, dato,NULL);
			}
			cout << "\n";
            respuesta = salida();
            break;
        case 2: 
            cout << "Digite un elemento: ";
            cin >> dato;
            insertarNodo(arbol, dato,NULL);
            cout << "\n";
            respuesta = salida();
            break;
        case 3:
            cout << "ARBOL BINARIO " << endl;
            mostrarArbol(arbol, contador);
            cout << "\n";
            respuesta = salida();
            break;
        case 4:
            cout << "\nDigite el elemento que desea eliminar:"<<endl;
            cin >> dato;
            eliminar(arbol, dato);
            cout << "\n";
            respuesta = salida();
            break;
        case 5:
            cout << "\nDigite el elemento que desea buscar:"<<endl;
            cin >> dato;
            if(busqueda(arbol, dato)==true)
            {
            	cout<<"\n El elemento "<<dato<<" ha sido encontrado "<<endl;
			}
			else
			{
				cout<<"\nEl elemento no ha sido encontrado "<<endl;
			}
            cout << "\n";
            respuesta = salida();
            break;
        case 6:
        	cout<<"\n Recorrido en preOrden: "<<endl;
        	preOrden(arbol); 
        	cout<<"\n\n";
        	system("pause");
        	break;
        case 7:
        	cout<<"\n Recorrido en InOrden: "<<endl;
        	inOrden(arbol); 
        	cout<<"\n\n";
        	system("pause");
        	break;
        case 8:
        	cout<<"\n Recorrido en PostOrden: "<<endl;
        	postOrden(arbol); 
        	cout<<"\n\n";
        	system("pause");
        	break;
        case 9:
        	cout<<"\n Recorrido en General: "<<endl;
        	general(arbol);
            cout<<"\n\n";
            system("pause");       	
            break;
         case 10:
        	int h;
            h = altura(arbol);
            cout << "La altura es : "<< h << endl;
            respuesta = salida();
            break;
        case 11:
        	int nodos;
        	nodos=contar(arbol);
        	cout << "El numero de nodos es : "<< nodos << endl;
        	respuesta = salida();
            break;
        default:
        	respuesta = "NO";
        	break;
        }
        system("cls");
    } while(respuesta == "SI" || respuesta == "Si" || respuesta == "si");
}

Nodo* crearNodo(string n,Nodo* padre) {
    Nodo* nuevo_nodo = new Nodo();

    nuevo_nodo->dato = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->padre = padre;

    return nuevo_nodo;
}

void insertarNodo(Nodo *&arbol, string n,Nodo*padre) {
    if (arbol == NULL) { 
        Nodo *nuevo_nodo = crearNodo(n,padre);
        arbol = nuevo_nodo;
    }
    else {
        string valorRaiz = arbol->dato; 
        if (n < valorRaiz) {
            insertarNodo(arbol->izq, n,arbol);
        }
        else {
            insertarNodo(arbol->der, n,arbol);
        }
    }
}


void mostrarArbol(Nodo* arbol, int cont) {
    if (arbol == NULL) {
        return;
    }
    else {
        mostrarArbol(arbol->der, cont + 1);
        for (int i = 0; i < cont; i++) {
            cout <<"               ";
        }
        cout << arbol->dato << endl;
        cout<<"\n"<<endl;
        mostrarArbol(arbol->izq, cont + 1);
    }
}

bool busqueda(Nodo *arbol,string n)
{
	if(arbol==NULL)
	{
		return false;
	}
	else if(arbol->dato==n)
	{
		return true;
	}
	else if (n<arbol->dato)
	{
		return busqueda(arbol->izq,n);
	}
	else
	{
		return busqueda(arbol->der,n);
	}
}



void eliminar(Nodo* arbol, string n) {
    if (arbol == NULL) {
        return;
    }
    else if (n < arbol->dato) { 
        eliminar(arbol->izq, n); 
    }
    else if (n > arbol->dato) { 
        eliminar(arbol->der, n);
    }
    else {
        eliminarNodo(arbol);
	}
}

void eliminarNodo(Nodo* nodoEliminar) {
    if (nodoEliminar->izq && nodoEliminar->der) {
        Nodo* menor = minimo(nodoEliminar->der); 
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

Nodo* minimo(Nodo* arbol) {
    if (arbol == NULL) {
        return NULL;
    }
    if (arbol->izq) { 
        return minimo(arbol->izq); 
    }
    else { 
        return arbol; 
    }
}


void reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
    if (arbol->padre) {

        if (arbol->dato == arbol->padre->izq->dato) {
            arbol->padre->izq = nuevoNodo;
        }
        else if (arbol->dato == arbol->padre->der->dato) {
            arbol->padre->der = nuevoNodo;
        }
    }
    if (nuevoNodo) {

        nuevoNodo->padre = arbol->padre;
    }
}


void destruirNodo(Nodo* nodo) {
    nodo->izq = NULL;
    nodo->der = NULL;
    delete nodo;
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

void preOrden(Nodo *arbol)
{
	if(arbol==NULL)
	{
		return ;
	}
	else
	{
		cout<<arbol->dato<<" - ";
		preOrden(arbol->izq);
		preOrden(arbol->der);
		
	}
	
	 
}
void inOrden(Nodo *arbol)
{
		if(arbol==NULL)
	{
		return ;
	}
	else
	{
		inOrden(arbol->izq);
		cout<<arbol->dato<<" - ";
		inOrden(arbol->der);
	}
	
}
void postOrden(Nodo *arbol)
{
		if(arbol==NULL)
	{
		return ;
	}
	else
	{
		
		postOrden(arbol->izq);
	    postOrden(arbol->der);
		cout<<arbol->dato<<" - ";

	}
	
}
void general(Nodo *arbol)
{
	     if(arbol==NULL)
    {
        return ;
    }
    else
    {   cout<<"Preorden"<<endl;
       cout<<arbol->dato<<" - ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
        cout<<"\n\n";
        cout<<"Inorden"<<endl;
        inOrden(arbol->izq);
        cout<<arbol->dato<<" - ";
        inOrden(arbol->der);
        cout<<"\n\n";
        cout<<"Postorden"<<endl;
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout<<arbol->dato<<" - ";
        cout<<"\n\n";
        
        
 
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

string salida(){
	string respuesta = "si";
	cout << "\nDESEA CONTINUAR CON EL ALGORITMO DE LAS OPERACIONES CON ARBOLES BINARIOS: SI/NO? ";
	cin.ignore();
	getline(cin, respuesta);
	return respuesta;
} 
