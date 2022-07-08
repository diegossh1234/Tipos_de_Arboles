#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <conio.h> 
#include <windows.h> 
//////

using namespace std;
struct Nodo 
{ 
    int Cod; 
    char nombre[40]; 
    Nodo *HI; 
    Nodo *HD; 
}; 


Nodo* crearNodo(int id, char* n); 
Nodo* buscar (Nodo* p, int matricula); 
void insertar (Nodo** raiz, int matricula, char* nombre); 
void reemplazar(Nodo** act); 
void eliminar (Nodo** raiz, int matricula); 
void visualizar (Nodo* r, int x, int y); 
int profundidad (Nodo *raiz); 
void gotoxy(int x,int y);
void preorden(Nodo *arbol){
	if(arbol==NULL){
		return;
	}else{
		printf("-%d",arbol->Cod);
		preorden(arbol->HI);
		preorden(arbol->HD);
	}
}

int x=10, y=5;

Nodo* crearNodo(int id, char *n) 
{ 
        Nodo *t; 
        t = (Nodo*)malloc(sizeof(Nodo)); 
        t->Cod=id; 
        strcpy(t->nombre, n); 
        t->HI=NULL; 
        t->HD=NULL; 
        return(t); 
} 

//Busca un nodo dado: ITERATIVO 
Nodo* buscar (Nodo* raiz, int matricula) 
{ 
      int encontrado = 0; 

      while (!encontrado && raiz != NULL) 
      { 
            if (matricula == raiz->Cod) 
               encontrado = 1; 
            else if (matricula < raiz->Cod) 
                 raiz = raiz->HI; 
            else if (matricula > raiz->Cod) 
                 raiz = raiz->HD; 
      } 
      return raiz; 
} 

//Inserta un nodo con matricula en el lugar que le corresponde 
void insertar (Nodo** raiz, int matricula, char *nombre) 
{ 
   if (!(*raiz)) 
      *raiz = crearNodo(matricula, nombre); 
   else 
   if (matricula < (*raiz)->Cod) 
      insertar (&((*raiz)->HI),matricula, nombre); 
      else 
           insertar (&((*raiz)->HD),matricula, nombre); 
} 

void eliminar (Nodo** r, int matricula) 
{ 
     if (!(*r)) 
        printf("!! Nodo no encontrado !!\n\n"); 
     else 
          if (matricula < (*r)->Cod) 
              eliminar(&(*r)->HI, matricula); 
          else 
             if (matricula> (*r)->Cod) 
                 eliminar(&(*r)->HD,matricula); 
             else // Nodo encontrado 
             { 
                   Nodo* q; // puntero al nodo a suprimir 
                   q = (*r); 
                   if (q -> HI == NULL) 
                      (*r) = q -> HD; 
                   else 
                        if (q -> HD == NULL) 
                           (*r) = q -> HI; 
                        else 
                        { // tiene rama izquierda y derecha 
                             reemplazar(&q); 
                        } 
                        free(q); 
                        printf("%d eliminado ...!!\n\n", matricula); 
             } 
} 
//

void reemplazar(Nodo** act) 
{ 
     Nodo* a, *p; 

     p = *act; 
     a = (*act)->HI;// rama de menores 
     while (a->HD) 
     { 
           p = a; 
           a = a -> HD; 
     } 
     (*act)->Cod=a->Cod; 
     strcpy((*act)->nombre,a->nombre); 
     if (p == (*act)) 
        p->HI = a -> HI; 
     else 
        p->HD = a -> HI; 
        (*act) = a; 
} 

//Visualiza utilizando recorrido inorden 
void visualizar (Nodo* r, int x, int y) 
{ 
     if (r) 
     { 
       
        
        gotoxy(x,y);
        printf("k:%d, d:%s\n",r->Cod,r->nombre); 
        x=x-5;
        y=y+5;
        visualizar(r -> HI,x,y); 
        x=x+10;
        visualizar(r -> HD,x,y); 
        y=y-5;         
     } 
} 

//Elimina cada uno de los nodos del arbol 
void eliminarbol(Nodo *r) 
{ 
     if (r != NULL) 
     { 
        eliminarbol(r -> HI); 
        eliminarbol(r -> HD); 
        printf("\tNodo borrado "); 
        free(r); 
     } 
} 
//Determina la mayor profundidad entre sub arbol izquierdo y derecho 
int profundidad (Nodo *raiz) 
{ 
    if (!raiz) 
       return 0; 
    else 
    { 
         int profundidadI = profundidad (raiz->HI); 
         int profundidadD = profundidad (raiz->HD); 
         if (profundidadI > profundidadD) 
            return profundidadI + 1; 
         else 
            return profundidadD + 1; 
    } 
} 

void gotoxy(int x,int y)
{  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
} 

int main() 
{ 
    int nm, i=1; 
    char nom[30]; 
    Nodo *Q, *raiz = NULL; 
    int x;
    do {
    do{ 
            system("cls"); 
            printf("\t\tMACHINE LEARNING APLICADO AL ANALISIS DE IMAGENES SATELITALES\n\n"); 
            printf("\t1. Ingresar Registros\n"); 
            printf("\t2. Mostrar el árbol\n"); 
            printf("\t3. Buscar dato\n"); 
            printf("\t4. Eliminar un registro\n"); 
            printf("\t5. Altura del Arbol\n"); 
            printf("\t6. Recorrido\n"); 
            printf("\t7. Salir\n "); 
            do{ 
                printf("\n\tDigite su opcion ---> "); 
                scanf("%d%*c", &nm); 
            }while(nm<1 || nm>7); 
            { 
                        if (nm == 1) 
                        { 
                           // Crea el árbol 
                           do{ 
                                system("cls"); 
                                printf("\t\tELEMENTO DEL MACHINE LEARNING APLICADO AL ANALISIS DE IMAGENES SATELITALES \n\n"); 
                                printf("\tRegistro %d\n", i); 
                                printf("Codigo(0:Fin)---> "); 
                                scanf("%d%*c",&nm); 
                                if (nm) 
                                { 
                                   printf("Nombre ---------> "); 
                                   gets(nom); 
                                   insertar(&raiz,nm,nom); 
                                } 
                                i=i+1; 
                           }while (nm); 
                        } 
                        if (nm == 2) 
                        { 
                            system("cls"); 
                            printf("\n\t IMPRESION ELEMENTO DEL MACHINE LEARNING APLICADO AL ANALISIS DE IMAGENES\n\n"); 
                            visualizar(raiz,x,y);
                            printf("\n\n\n"); 
                            system("pause"); 
                        } 
                        if (nm == 3) 
                        { 
                           int cl; 
                           system("cls"); 
                           printf("\n\t BUSCAR POR DATO :\n\n"); 
                           printf("Codigo ---> "); 
                           scanf("%d",&cl); 
                           Q=buscar(raiz,cl); 
                           if(Q!=NULL) 
                           { 
                               printf("\nDato encontrato: %d %s\n\n",Q->Cod, Q->nombre); 
                           } 
                           else 
                           { 
                                printf("\n%d DATO NO encontrato...\n\n",cl); 
                           } 
                           system("pause"); 
                           printf("\n");
                        } 
                        if (nm == 4) 
                        { 
                           int cl; 
                           system("cls"); 
                           printf("\n\t RUNTINA DE ELIMINACION\n\n"); 
                           printf("Codigo ---> "); 
                           scanf("%d",&cl); 
                           eliminar(&raiz,cl); 
                           system("pause"); 
                           printf("\n");
                        } 
                        else 
                             if(nm == 5) 
                             { 
                                   system("cls"); 
                                   int Altura; 
                                   printf("\n\t RUNTINA DE CALCULO DEL ARBOL\n\n"); 
                                   Altura=profundidad(raiz); 
                                   printf("\nAltura del arbol ---> %d\n", Altura-1); 
                                   system("pause"); 
                             } 
                    if(nm == 6){
                    	printf("\nRecorrido en PreOrden : ");
                    	preorden(raiz);
                    	system("pause");
                    	printf("\n");
					}
            } 
    }while (nm != 7); 
	  cout<<"\n¿DESEA CONTINUAR CON LA PRESENTACION DEL ALGORITMO SOBRE LAS OPERACIONES DE ARBOLES B+ APLICADO AL ANALISIS DE IMAGENES? (SI/NO)\n\n1. SI\n2. NO\n\n"; 
        cin>>x;  
	if(x==1) 
	    system("CLS"); 
    } while(x==1);
    system("CLS");  
  cout<<"EL ALGORITMO SOBRE LAS OPERACIONES DE ARBOLES B+ APLICADO AL ANALISIS DE IMAGENES HA TERMINADO";
} 

