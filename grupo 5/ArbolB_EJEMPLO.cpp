#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define M 4

using namespace std;
typedef struct _nodo {
        int    n;  //Numero de llaves en el nodo, es menor que el orden del arbol
        int              llaves[M - 1]; /*array de llaves*/
		struct _nodo *p[M]; /* (n+1 apuntadores) */
} nodo;

nodo *raiz = NULL;

typedef enum KeyStatus { //Defino constantes 
    Duplicar,
    BuscarError,
    Exito,
    InsertarIt,
    LlaveMenor,
} KeyStatus;
//Declarar Funciones
void Insertar(int clave); 
void Imprimir(nodo *raiz, int);
void Borrar(int x);
void Busqueda(int x);
KeyStatus ins(nodo *r, int x, int* y, nodo** u);
int buscarPos(int x, int *key_arr, int n);
KeyStatus del(nodo *r, int x);
void eatline(void);
void Ordenar(nodo *ptr);

main() {
		char opc;
		do{
        int clave,n,opcion;
        cout<<"\n--------------------------------------------------------"<<endl;
        cout<<" ASIGNACION DE PRIORIDAD POR EDADES DE LOS CIUDADANOS DE LATACUNGA "<<endl;
        cout<<"\tCreacion del arbol B para M: "<<M<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        		cout<<("***** MENU *****\n");
                cout<<("1.Insertar Clave del ciudadano\n");
                cout<<("2.Borrar Clave del ciudadano\n");
                cout<<("3.Buscar Clave del ciudadano\n");
                cout<<("4.Imprimir estructura de arbol con Claves asignadas\n");
                cout<<("5.Ordenar Claves de los ciudadanos\n");
                cout<<("Ingrese su opcion : ");
                cin>>opcion; 
            
                switch (opcion) {
                case 1:
                		cout<<"\n---------------------------------------------"<<endl;
                        cout<<("Ingrese la Clave del ciudadano: ");
                    	cin>>clave; eatline();
                        Insertar(clave);                        
                        system("pause");
                        system("cls");
                        break;
                case 2:
                		cout<<"\n---------------------------------------------"<<endl;
                        cout<<("Ingrese la clave a borrar de la estructura de arbol B: ");
                        cin>>clave; eatline();
                        Borrar(clave);
                        system("pause");
                        system("cls");
                        break;
                case 3:
                		cout<<"\n---------------------------------------------"<<endl;
                        cout<<("Ingrese clave a buscar en la estructura de arbol B: ");
                        cin>>clave; eatline();
                        Busqueda(clave);
                        system("pause");
                        system("cls");
                        break;
                case 4:
                	{
                		cout<<"\n--------------------------------------------------------"<<endl;
                        cout<<("\tLa impresion del arbol B ");
                        cout<<"\n--------------------------------------------------------"<<endl;
                    	Imprimir(raiz, 0);
                        system("pause");
                        system("cls");
                        break;
					}
                case 5:
                		cout<<"\n--------------------------------------------------------"<<endl;
                		cout<<"\tEl arbol B ordenado  ";
                		cout<<"\n--------------------------------------------------------"<<endl;
            			Ordenar(raiz); 
            			system("pause");
                        system("cls");
						break;              		
                default:
                		cout<<"\n---------------------------------------------"<<endl;
                        cout<<"\tOpcion incorrecta";
                        cout<<"\n---------------------------------------------"<<endl;
                        system("pause");
                        system("cls");
                        break;
                }/*Fin del switch*/
                
        cout<<"Desea continuar con la presentacion de asignacion de prioridad por edades de ciudadanos de Latacunga con Arboles B [S/N]: ";
        cin>>opc;
    	}while(opc!='N');	
    	cout<<" El algoritmo de ASIGNACION DE PRIORIDAD POR EDADES DE LOS CIUDADANOS DE LATACUNGA CON ARBOLES B HA FINALIZADO "<<endl;
        return 0;
}/*Fin de la funcion main()*/

//Funcion para insertar elementos al arbol B
void Insertar(int clave) { 
        nodo *nuevonodo;
        int claveArriba;
        KeyStatus value;
        value = ins(raiz, clave, &claveArriba, &nuevonodo);
        if (value == Duplicar){
        		cout<<"\n---------------------------------------------"<<endl;
        		cout<<"\tClave ya disponible \n ";
        		cout<<"---------------------------------------------"<<endl;
		}
        if (value == InsertarIt) {
                nodo *raizArriba = raiz;
                raiz = (nodo*)malloc(sizeof(nodo));
                raiz->n = 1;
                raiz->llaves[0] = claveArriba;
                raiz->p[0] = raizArriba;
                raiz->p[1] = nuevonodo;
            cout<<"\n---------------------------------------------"<<endl;
			cout<<"\tClave registrada ";
			cout<<"\n---------------------------------------------"<<endl;
        }/*Fin del si*/      
}/*Fin de la funcion insertar()*/

//Clave para revisar el estado de la clave
KeyStatus ins(nodo *aux, int clave, int *claveArriba, nodo **nuevonodo) { 
        nodo *newaux, *lastaux;
        int pos, i, n, splitPos;
        int nuevaClave, ultimaClave;
        KeyStatus value;
        if (aux == NULL) {
                *nuevonodo = NULL;
                *claveArriba = clave;
                return InsertarIt;
        }
        n = aux->n;
        pos = buscarPos(clave, aux->llaves, n);
        if (pos < n && clave == aux->llaves[pos])
                return Duplicar;
        value = ins(aux->p[pos], clave, &nuevaClave, &newaux);
        if (value != InsertarIt)
                return value;
        //Si la llave del nodo es menor que M-1, sabiendo que M es el orden del arbol B
        if (n < M - 1) {
                pos = buscarPos(nuevaClave, aux->llaves, n);
                /*Cambia la clave y apuntador derecho para insertar una nueva clave */
                for (i = n; i>pos; i--) {
                        aux->llaves[i] = aux->llaves[i - 1];
                        aux->p[i + 1] = aux->p[i];
                }
                /*Clave insertada en posicion exacta*/
                aux->llaves[pos] = nuevaClave;
                aux->p[pos + 1] = newaux;
                ++aux->n; //incrementa el numero de llaves del nodo
                return Exito;
        }/*Fin del si */
        //Si las llaves estan llenas y su posicion de insertacion esta al final 
        if (pos == M - 1) {
                ultimaClave = nuevaClave;
                lastaux = newaux;
        }
        else { //Si las claves estan llenas y la posicion no esta al final
                ultimaClave = aux->llaves[M - 2];
                lastaux = aux->p[M - 1];
                for (i = M - 2; i>pos; i--) {
                        aux->llaves[i] = aux->llaves[i - 1];
                        aux->p[i + 1] = aux->p[i];
                }
                aux->llaves[pos] = nuevaClave;
                aux->p[pos + 1] = newaux;
        }
        splitPos = (M - 1) / 2;
        (*claveArriba) = aux->llaves[splitPos];

        (*nuevonodo) = (nodo*)malloc(sizeof(nodo));/*Nodo derecho luego del split*/
        aux->n = splitPos; /*No. de llaves para el nodo izquierdo con split*/
        (*nuevonodo)->n = M - 1 - splitPos;/*No. de llaves para el nodo derecho con split*/
        for (i = 0; i < (*nuevonodo)->n; i++) {
                (*nuevonodo)->p[i] = aux->p[i + splitPos + 1];
                if (i < (*nuevonodo)->n - 1)
                        (*nuevonodo)->llaves[i] = aux->llaves[i + splitPos + 1];
                else
                        (*nuevonodo)->llaves[i] = ultimaClave;
        }
        (*nuevonodo)->p[(*nuevonodo)->n] = lastaux;
        return InsertarIt;
}/*Fin de ins()*/

void Imprimir(nodo *ptr, int espacio) {
        if (ptr) {
                int i;
                for (i = 1; i <= espacio; i++)
                        cout<<(" ");
                for (i = 0; i < ptr->n; i++)
                        cout<<" "<<(ptr->llaves[i]);
                cout<<("\n");       
                for (i = 0; i <= ptr->n; i++)
                        Imprimir(ptr->p[i], espacio + 10);
        }/*Fin del si*/
}/*Fin de Imprimir()*/

void Busqueda(int clave) {
	
        int pos, i, n;
        nodo *ptr = raiz;
        cout<<"\n---------------------------------------------"<<endl;
        cout<<"\tBuscando nodo...";
        cout<<"\n---------------------------------------------"<<endl;
        while (ptr) {
                n = ptr->n;
                for (i = 0; i < ptr->n; i++)
                		cout<<ptr->llaves[i];
                cout<<"\n";
                pos = buscarPos(clave, ptr->llaves, n);
                if (pos < n && clave == ptr->llaves[pos]) {
                		cout<<"\n----------------------------------------------------------------------------------------"<<endl;
                		cout<<"\tClave "<<clave<<" en la posicion "<<i<<" del modelo impreso "<<endl;
                		cout<<"----------------------------------------------------------------------------------------"<<endl;
                        return;
                }
                ptr = ptr->p[pos];
        }
        cout<<"Clave "<<clave<<" no disponible \n";
}/*Fin de Buscar()*/

int buscarPos(int key, int *key_arr, int n) {
        int pos = 0;
        while (pos < n && key > key_arr[pos])
                pos++;
        return pos;
}/*Fin de buscarPos */

void Borrar(int clave) {
        nodo *raizArriba;
        KeyStatus value;
        value = del(raiz, clave);
        switch (value) {
        case BuscarError:
        		cout<<"\n---------------------------------------------"<<endl;
        	    cout<<"\tLa clave "<<clave<<" no esta disponible ";
        	    cout<<"\n---------------------------------------------"<<endl;
                break;
        case LlaveMenor:
                raizArriba = raiz;
                raiz = raiz->p[0];
                free(raizArriba);
                break;
        default:
                return;
        }//Fin del switch
}/*Fin de Borrar()*/

KeyStatus del(nodo *ptr, int key) {
        int pos, i, pivot, n, min;
        int *key_arr;
        KeyStatus value;
        nodo **p, *lptr, *rptr;

        if (ptr == NULL)
                return BuscarError;
        //Asigna valores al nodo
        n = ptr->n;
        key_arr = ptr->llaves;
        p = ptr->p;
        min = (M - 1) / 2;//Minimo numero de llaves 

                                          //Busca la clave para borrarla
        pos = buscarPos(key, key_arr, n);
        // p es una hoja
        if (p[0] == NULL) {
                if (pos == n || key < key_arr[pos])
                        return BuscarError;
                /*Shift keys and pointers left*/
                for (i = pos + 1; i < n; i++)
                {
                        key_arr[i - 1] = key_arr[i];
                        p[i] = p[i + 1];
                }
                return --ptr->n >= (ptr == raiz ? 1 : min) ? Exito : LlaveMenor;
        }//Fin del si
		
		 //si encuentra la clave pero p no es una hoja	
        if (pos < n && key == key_arr[pos]) {
                nodo *qp = p[pos], *qp1;
                int nkey;
                while (1) {
                        nkey = qp->n;
                        qp1 = qp->p[nkey];
                        if (qp1 == NULL)
                                break;
                        qp = qp1;
                }//Fin del while
                key_arr[pos] = qp->llaves[nkey - 1];
                qp->llaves[nkey - 1] = key;
        }//Fin del si
        value = del(p[pos], key);
        if (value != LlaveMenor)
                return value;

        if (pos > 0 && p[pos - 1]->n > min) {
                pivot = pos - 1; //pivote del nodo izquierdo al derecho
                lptr = p[pivot];
                rptr = p[pos];
                //Asigna valores al nodo derecho
                rptr->p[rptr->n + 1] = rptr->p[rptr->n];
                for (i = rptr->n; i>0; i--) {
                        rptr->llaves[i] = rptr->llaves[i - 1];
                        rptr->p[i] = rptr->p[i - 1];
                }
                rptr->n++;
                rptr->llaves[0] = key_arr[pivot];
                rptr->p[0] = lptr->p[lptr->n];
                key_arr[pivot] = lptr->llaves[--lptr->n];
                return Exito;
        }//Fin del si 
        
        if (pos < n && p[pos + 1]->n > min) {
                pivot = pos; //pivote del nodo izquierdo al derecho
                lptr = p[pivot];
                rptr = p[pivot + 1];
                //Asigna valores al nodo izquierdo
                lptr->llaves[lptr->n] = key_arr[pivot];
                lptr->p[lptr->n + 1] = rptr->p[0];
                key_arr[pivot] = rptr->llaves[0];
                lptr->n++;
                rptr->n--;
                for (i = 0; i < rptr->n; i++) {
                        rptr->llaves[i] = rptr->llaves[i + 1];
                        rptr->p[i] = rptr->p[i + 1];
                }//Fin del for
                rptr->p[rptr->n] = rptr->p[rptr->n + 1];
                return Exito;
        }//Fin del si

        if (pos == n)
                pivot = pos - 1;
        else
                pivot = pos;

        lptr = p[pivot];
        rptr = p[pivot + 1];
        /*une el nodo derecho con el izquierdo*/
        lptr->llaves[lptr->n] = key_arr[pivot];
        lptr->p[lptr->n + 1] = rptr->p[0];
        for (i = 0; i < rptr->n; i++) {
                lptr->llaves[lptr->n + 1 + i] = rptr->llaves[i];
                lptr->p[lptr->n + 2 + i] = rptr->p[i + 1];
        }
        lptr->n = lptr->n + rptr->n + 1;
        free(rptr); /*Remueve el nodo derecho*/
        for (i = pos + 1; i < n; i++) {
                key_arr[i - 1] = key_arr[i];
                p[i] = p[i + 1];
        }
        return --ptr->n >= (ptr == raiz ? 1 : min) ? Exito : LlaveMenor;
}/*Fin de del()*/

void eatline(void) {
        char c;
        while ((c = getchar()) != '\n');
}

//Funcion de ordenamiento sort
void Ordenar(nodo *ptr) {
        if (ptr) {
                if (ptr->n >= 1) {
                        Ordenar(ptr->p[0]);
                        cout<<" "<<ptr->llaves[0]<<endl;
                        Ordenar(ptr->p[1]);
                        if (ptr->n == 2) {
                        	    cout<<" "<<ptr->llaves[1]<<endl;
                                Ordenar(ptr->p[2]);
                        }
                }
        }
}







