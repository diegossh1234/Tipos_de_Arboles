#include <iostream>
#include <stdlib.h>
using namespace std;

/* Estructura del arbol  -------*/
typedef struct nodo{
     int nro;
     struct nodo *izq, *der;
}*ABB;

int numNodos = 0; // nummero de nodos del arbol AB
int numK = 0, k;     //  nodos menores que un numero k ingresado
/*  Estructura de la cola ---------*/
struct nodoCola{
    ABB ptr;
    struct nodoCola *sgte;
};
struct cola{
    struct nodoCola *delante;
    struct nodoCola *atras;
};
//Lllamadas de funciones
void inicializaCola(struct cola &q);
void encola(struct cola &q, ABB n);
ABB desencola(struct cola &q);
ABB crearNodo(int x);
void insertar(ABB &arbol, int x);
void preOrden(ABB arbol);
void enOrden(ABB arbol);
void postOrden(ABB arbol);
void verArbol(ABB arbol, int n);
bool busquedaRec(ABB arbol, int dato);
ABB unirABB(ABB izq, ABB der);
void elimina(ABB &arbol, int x);
int alturaAB(ABB arbol);
void menu();
void menu2();

//funcion principal
int main()
{
    ABB arbol = NULL;
    int x;
    int op, op2;


    system("color 0a");   // poner color a la consola
    do
    {
          menu();  cin>> op;
          cout << endl;

          switch(op)
          {
          		case 0:
					cout <<"\n Inicializacion del arbol B:\n\n";
				 	cout <<"\t ARBOL VACIO";
				 	break;
          		
               case 1:
                    cout << " Ingrese un valor: ";  cin>> x;
                    insertar( arbol, x);
                    break;

               case 2:
               	cout << "El arbol es: "<<endl;
                    verArbol(arbol, 0);
                    break;

               case 3:
                    
                    char opc;
					do{
						menu2();  cin>> op2;
						if(arbol!=NULL){
                         switch(op2)
                            {
                             	case 1:
                                	 enOrden(arbol); break;
                             	case 2:
                                 	preOrden(arbol); break;
                             	case 3:
                                 	postOrden(arbol); break;
                            	case 4: 
                            		cout<<"\nEN ORDEN  ";
                            		enOrden(arbol);
                            		cout<<"\nPRE ORDEN  ";
                            		preOrden(arbol);
                            		cout<<"\nPOST ORDEN  ";
                            		postOrden(arbol);
                            		
                           }
                        	
						}else{
                           		cout << "\n\t Arbol vacio..!";
						   }
						
                        cout<<"  Desea continuar?(S/N): ";
                        cin>>opc;
                    }while(opc!='N');
                	cout<<"\n\tSaliendo del menu...";
            
                    break;

               case 4:
                    bool band;

                    cout<<" Valor a buscar: "; cin>> x;

                    band = busquedaRec(arbol,x);

                    if(band==1)
                       cout << "\n\tValor Encontrado...";
                    else
                       cout << "\n\tEl valor no se encuentra...";
                    break;

               case 5:
                    cout<<" ingrese el valor a eliminar: "; cin>> x;
                    elimina(arbol, x);
                    cout << "\n\tValor Eliminado..!";
                    break;

               case 6:
                    int h;
                    h = alturaAB(arbol);
                    cout << " La altura del arbol B es : "<< h << endl;
                    break;

               case 7:
                    verArbol(arbol, 0);
                    cout << "\n\n El numero de nodos del arbol B es : ";
                    cout << numNodos;
                    break;

               case 8:
               		cout << "EL ALGORITMO SOBRE LAS OPERACIONES CON ARBOLES B HA FINALIZADO!!";
                    exit(0);
          }

          cout<<"\n\n\n";
          //system("pause");  // hacer pausa y presionar una tecla para continuar
    }while(op!=10);

}
void inicializaCola(struct cola &q)
{
    q.delante = NULL;
    q.atras = NULL;
}

void encola(struct cola &q, ABB n)
{
     struct nodoCola *p;
     p = new(struct nodoCola);
     p->ptr = n;
     p->sgte = NULL;
     if(q.delante==NULL)
         q.delante = p;
     else
         (q.atras)->sgte = p;
     q.atras = p;
}

ABB desencola(struct cola &q)
{
    struct nodoCola *p;
    p = q.delante;
    ABB n = p->ptr;
    q.delante = (q.delante)->sgte;
    delete(p);
    return n;
}

ABB crearNodo(int x)
{
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
void insertar(ABB &arbol, int x)
{
     if(arbol==NULL)
     {
           arbol = crearNodo(x);
           cout<<"\n\t Valor Insertado..!"<<endl<<endl;
     }
     else if(x < arbol->nro)
          insertar(arbol->izq, x);
     else if(x > arbol->nro)
          insertar(arbol->der, x);
}

void preOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          cout << arbol->nro <<" - ";
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}

void enOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          cout << arbol->nro << " - ";
          enOrden(arbol->der);
     }
}

void postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          enOrden(arbol->der);
          cout << arbol->nro << " - ";
     }
}

void verArbol(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->der, n+1);

     for(int i=0; i<n; i++)
         cout<<"  ";

     numNodos++;
     cout<< arbol->nro <<endl;
     verArbol(arbol->izq, n+1);
}

bool busquedaRec(ABB arbol, int dato)
{
     int r=0;   // 0 indica que lo encontre

     if(arbol==NULL)
        return r;

     if(dato<arbol->nro)
         r = busquedaRec(arbol->izq, dato);

     else if(dato> arbol->nro)
         r = busquedaRec(arbol->der, dato);

     else
        r = 1;   // son iguales, lo encontre

     return r;
}

ABB unirABB(ABB izq, ABB der)
{
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    ABB centro = unirABB(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;
    return der;
}

void elimina(ABB &arbol, int x)
{
     if(arbol==NULL) return;

     if(x<arbol->nro)
         elimina(arbol->izq, x);
     else if(x>arbol->nro)
         elimina(arbol->der, x);

     else
     {
         ABB p = arbol;
         arbol = unirABB(arbol->izq, arbol->der);
         delete p;
     }
}

int alturaAB(ABB arbol)
{
    int AltIzq, AltDer;

    if(arbol==NULL)
        return -1;
    else
    {
        AltIzq = alturaAB(arbol->izq);
        AltDer = alturaAB(arbol->der);

        if(AltIzq>AltDer)
            return AltIzq+1;
        else
            return AltDer+1;
    }
}



void menu()
{
     //system("cls");
     cout << "\n\t    TRABAJO AUTONOMO  -  GRUPO 6\n";
     cout << "\n\t    SISTEMA DE BASE DE DATOS DE BANCOS CON RECOLECCION NUMEROS PARA TRANSCRIPCION A LETRAS\n";
     cout << "\n\t***** ARBOL B ******\n\n";
     cout << "\t [0]  Crear arbol B                 \n ";
     cout << "\t [1]  Insertar elemento a cifrar                 \n";
     cout << "\t [2]  Mostrar arbol B                     \n";
     cout << "\t [3]  Recorridos de profundidad           \n";
     cout << "\t [4]  Buscar elemento cifrado                   \n";
     cout << "\t [5]  Eliminar elemento  cifrado               \n";
     cout << "\t [6]  Altura del arbol                   \n";
     cout << "\t [7]  Numeros de nodos a mandar                     \n";
     cout << "\t [8] SALIR                              \n";

     cout << "\n\t escoja una opcion : ";
}

void menu2()
{
     //system("cls");   // para limpiar pantalla
     cout << endl;
     cout << "\t [1] En Orden     \n";
     cout << "\t [2] Pre Orden    \n";
     cout << "\t [3] Post Orden   \n";
     cout << "\t [4] Orden General   \n";
     cout << "\n\t     Opcion :  ";
}