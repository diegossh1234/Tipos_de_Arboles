#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct nodo{
     string nro;
     struct nodo *Izquierda, *Derecha;
}*Arbol;

int numNodos = 0; 
int raices = 0, k;   


struct nodoCola{
    Arbol ptr;
    struct nodoCola *sgte;
};
struct cola{
    struct nodoCola *delante;
    struct nodoCola *atras;
};

void InicioCola(struct cola &dato)
{
    dato.delante = NULL;
    dato.atras = NULL;
}

void Datos_cola(struct cola &dato, Arbol n)
{
     struct nodoCola *dat2;
     dat2 = new(struct nodoCola);
     dat2->ptr = n;
     dat2->sgte = NULL;
     if(dato.delante==NULL)
         dato.delante = dat2;
     else
         (dato.atras)->sgte = dat2;
     dato.atras = dat2;
}

Arbol Datos_cola2(struct cola &dato)
{
    struct nodoCola *dat2;
    dat2 = dato.delante;
    Arbol n = dat2->ptr;
    dato.delante = (dato.delante)->sgte;
    delete(dat2);
    return n;
}

Arbol crearNodo(string numero_ingresado)
{
     Arbol nuevoNodo = new(struct nodo);
     nuevoNodo->nro = numero_ingresado;
     nuevoNodo->Izquierda = NULL;
     nuevoNodo->Derecha = NULL;
     return nuevoNodo;
}
void insertar(Arbol &arbol, string numero_ingresado)
{
     if(arbol==NULL)
     {
           arbol = crearNodo(numero_ingresado);
           cout<<"\n Se ha ingresado un nuevo elemento"<<endl<<endl;
     }
     else if(numero_ingresado < arbol->nro)
          insertar(arbol->Izquierda, numero_ingresado);
     else if(numero_ingresado > arbol->nro)
          insertar(arbol->Derecha, numero_ingresado);
}

void preOrden(Arbol arbol)
{
     if(arbol!=NULL)
     {
          cout << arbol->nro <<" ";
          preOrden(arbol->Izquierda);
          preOrden(arbol->Derecha);
     }
}

void enOrden(Arbol arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->Izquierda);
          cout << arbol->nro << " ";
          enOrden(arbol->Derecha);
     }
}

void postOrden(Arbol arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->Izquierda);
          enOrden(arbol->Derecha);
          cout << arbol->nro << " ";
     }
}

void verArbol(Arbol arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->Derecha, n+1);

     for(int i=0; i<n; i++)
         cout<<"   ";

     numNodos++;
     cout<< arbol->nro <<endl;

     verArbol(arbol->Izquierda, n+1);
}

bool busquedaRec(Arbol arbol, string dato)
{
     int r=0;   

     if(arbol==NULL)
        return r;

     if(dato<arbol->nro)
         r = busquedaRec(arbol->Izquierda, dato);

     else if(dato> arbol->nro)
         r = busquedaRec(arbol->Derecha, dato);

     else
        r = 1;   

     return r;
}

Arbol UnionArbol(Arbol Izquierda, Arbol Derecha)
{
    if(Izquierda==NULL) return Derecha;
    if(Derecha==NULL) return Izquierda;

    Arbol centro = UnionArbol(Izquierda->Derecha, Derecha->Izquierda);
    Izquierda->Derecha = centro;
    Derecha->Izquierda = Izquierda;
    return Derecha;
}

void elimina(Arbol &arbol, string numero_ingresado)
{
     if(arbol==NULL) return;

     if(numero_ingresado<arbol->nro)
         elimina(arbol->Izquierda, numero_ingresado);
     else if(numero_ingresado>arbol->nro)
         elimina(arbol->Derecha, numero_ingresado);

     else
     {
         Arbol dat2 = arbol;
         arbol = UnionArbol(arbol->Izquierda, arbol->Derecha);
         delete dat2;
     }
}
int alturaAB(Arbol arbol)
{
    int AltIzq, AltDer;

    if(arbol==NULL)
        return -1;
    else
    {
        AltIzq = alturaAB(arbol->Izquierda);
        AltDer = alturaAB(arbol->Derecha);

        if(AltIzq>AltDer)
            return AltIzq+1;
        else
            return AltDer+1;
    }
}


void menu()
{
     system("cls");
     	cout<<"	/////OPERACIONES CON ARBOLES BINARIOS////\n"<<endl;
		cout<<"1. Ingrese nuevos nodos"<<endl;
		cout<<"2. Mostrar Arbol (completo)"<<endl;
		cout<<"3. Buscar elemento en el Arbol"<<endl;
		cout<<"4. Recorridos en fundidad (Preorden,PostOrden, InOrden)"<<endl;
		cout<<"5. Eliminar elemento del arbol"<<endl;
		cout<<"6. Altura del arbol"<<endl;
		cout<<"7. Salir"<<endl;
		cout<<"\n ingrese la opcion: ";
}

void menu2()
{
     system("cls");   
     cout << endl;
	cout<<"\n		RECORRIDOS EN PROFUNDIDAD\n"<<endl;
	cout<<"1. Recorrido en profundidad Pre Orden"<<endl;
	cout<<"2. Recorrido en profundidad InOrden"<<endl;
	cout<<"3. Recorrido en profundidad PostOrden"<<endl;
	cout<<"4. Mostrar todos los recorridos	"<<endl;
	cout<<" ingresar la opcion: ";
}


void continuar() {
	int dec;
	cout << "\nDesea continuar con EL ALGORITMO DE LAS OPERACIONES SOBRE ARBOLES BINARIOS? 1.SI/2.NO  ";
	cin >> dec;
	if (dec == 1) {
	system("cls");
	}
	else {
		system("cls");
		cout << "\nEl algoritmo de Arbol Binario ha finalizado" << endl;
		exit(0);
	}
}

int main()
{
    Arbol arbol = NULL;
    string numero_ingresado;
	int numero_elementos;
    int op, op2;
    string op3;
    
    do
    {
          menu();  cin>> op;
          cout << endl;

          switch(op)
          {
               case 1:
               		
               		cout<<"cuantos elementos desea ingresar?: ";
               		cin>>numero_elementos;
               		for(int i=0;i<numero_elementos;i++){
	                    cout << " Ingrese valor "<<i+1<<"/"<<numero_elementos<<" : ";  cin>> numero_ingresado;
	                    insertar( arbol, numero_ingresado);
               			
					   }
                    break;

               case 2:
                    verArbol(arbol, 0);
                    break;

               case 3:
                   bool band;

                    cout<<" Valor a buscar: "; cin>> numero_ingresado;

                    band = busquedaRec(arbol,numero_ingresado);

                    if(band==1)
                       cout << "\nElemento Encontrado";
                    else
                       cout << "\nElemento no encontrado";
                    break;

               case 4:
               menu2();  
				cin>> op2;

                    if(arbol!=NULL)
                    {
                         switch(op2)
                         {
                             case 1:
                                 enOrden(arbol); break;
                             case 2:
                                 preOrden(arbol); break;
                             case 3:
                                 postOrden(arbol); break;
                            case 4:
                                cout<<"InOrden: ";
                        	 	enOrden(arbol);
                        	 	cout<<"\n"<<endl;
                        	 	cout<<"preOrden: ";
								preOrden(arbol);   
								cout<<"\n"<<endl;              	 	
                        	 	cout<<"postOrden: ";
                                postOrden(arbol);
								cout<<"\n"<<endl; break;
                         }
                    }
                    else
                        cout << "\n Arbol vacio";
                   
                    break;

               case 5:
                    cout<<" Valor a eliminar: "; cin>> numero_ingresado;
                    elimina(arbol, numero_ingresado);
                    cout << "\nElemento eliminado";
                    break;
                    
                case 6:
                    cout<<"	la altura del arbol es: "<<alturaAB(arbol)<<endl;
                	break;
   				case 7:
   					break;
               default:
               		cout<<"\n\n		*no es una opcion*"<<endl;
               		break;
          }
          system("pause"); 
          
    	cout<<"DESEA CONTINUAR CON EL ALGORITMO DE ARBOLES BINARIOS?(SI/NO)"<<endl;
    	cin>>op3;
    	
    }while(op3=="si" || op3=="SI");
      cout << "\nEl algoritmo de Arbol Binario ha finalizado" << endl;
}