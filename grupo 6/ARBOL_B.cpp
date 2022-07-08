#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct nodo{
     int nro;
     struct nodo *izq, *der;
}*ABB;

int numNodos = 0; 
int numK = 0, k;     

struct nodoCola{
    ABB ptr;
    struct nodoCola *sgte;
};
struct cola{
    struct nodoCola *delante;
    struct nodoCola *atras;
};

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
//crea el nodo del arbol
ABB crearNodo(int x)
{
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
//funcion para insertar un elemento en el arbol
void insertar(ABB &arbol, int x)
{
     if(arbol==NULL)
     {
           arbol = crearNodo(x);
           cout<<"\n\t Elemento Insertado..!"<<endl<<endl;
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
          cout << arbol->nro <<" ";
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}

void enOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          cout << arbol->nro << " ";
          enOrden(arbol->der);
     }
}

void postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          enOrden(arbol->der);
          cout << arbol->nro << " ";
     }
}
//visualizar el arbol 
void verArbol(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->der, n+1);

     for(int i=0; i<n; i++)
         cout<<"   ";

     numNodos++;
     cout<< arbol->nro <<endl;

     verArbol(arbol->izq, n+1);
}
//funcion que busca el elemento
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
//funcion que elimina un elemento del arbol 
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

void menu()
{
     //system("cls");
     cout << "\n        TRABAJO AURTONOMO - GRUPO 6  \n";
     cout << "\n  ************** ARBOL B ****************** \n\n ";
     cout << "\t  0).-  Crear el arbol B                   \n";
     cout << "\t  1).-  Insertar elemento                  \n";
     cout << "\t  2).-  Imprimir el arbol B                \n";
     cout << "\t  3).-  Buscar elemento                    \n";
     cout << "\t  4).-  Eliminar elemento                  \n";
     cout << "\t  5).-  SALIR                              \n";

     cout << "\n\t Ingrese una opcion: ";
}
//funcion principal
int main()
{
    ABB arbol = NULL;
    int x;
    int op, op2;

    system("color 0e");   
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
                    cout << " Ingrese un valor : ";  cin>> x;
                    insertar( arbol, x);
                    break;

               case 2:
                    verArbol(arbol, 0);
                    break;
               case 3:
                    bool band;

                    cout<<" Valor a buscar: "; cin>> x;

                    band = busquedaRec(arbol,x);

                    if(band==1)
                       cout << "\n\tElemento Encontrado...";
                    else
                       cout << "\n\tNo encontrado...";
                    break;

               case 4:
                    cout<<" Valor a eliminar: "; cin>> x;
                    elimina(arbol, x);
                    cout << "\n\tElemento Eliminado..!";
                    break;

               case 5:
                    char respuesta;
            		cout<<"\n DESEA CONTINUAR CON EL ALGORITMO DE LAS OPERACIONES CON ARBOLES B [s/n]: ";
					cin>>respuesta;
					if(respuesta=='s'||respuesta=='S'){
						system("cls");
						main();
					}else{
						system("cls");
						cout<<"EL ALGORITMO DE LAS OPERACIONES CON ARBOLES B HA FINALIZADO !!";
						exit(0);			}
          }

          cout<<"\n\n\n";
            
    }while(op!=11);

}


