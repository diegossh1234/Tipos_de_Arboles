#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#ifdef TURBOC
#define _getch getch
#endif
//#define MAXIMO 50

using namespace std;

typedef enum {IZQUIERDA, CENTRO, DERECHA} Sentido;

typedef struct TDAArbol
{
    struct TDAArbol *izq;
    struct TDAArbol *der;
    char *cadena;
} *Arbol;

Arbol arbol_insertar       (Arbol nodo, const char *cadena);
Arbol arbol_quitar         (Arbol nodo, const char *cadena);
Arbol arbol_quitar_y_rotar (Arbol nodo, const char *cadena, Sentido rotacion);
void  arbol_preorden       (Arbol raiz, Arbol nodo);
void  arbol_inorden        (Arbol raiz, Arbol nodo);
void  arbol_postorden      (Arbol raiz, Arbol nodo);
int   arbol_altura         (Arbol nodo);
Arbol arbol_balancear      (Arbol nodo);
int   arbol_nodos          (Arbol nodo);
int   arbol_completo       (Arbol nodo);
int   arbol_balanceado     (Arbol nodo); 
void ingresar();
int main (void)
{
    Arbol raiz = NULL;
    char cadena[256]="";
    int opcion,cuanto,seg,i;
    do {
        system ("cls");       
        printf("\t___________________________________________________________________\n");
        printf("\n\t  UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE SEDE LATACUNGA\n");
        printf("\tDesarrollado por : GRUPO N-4\n");
        printf("\tMateria: ESTRUCTURA DE DATOS\n\n");
        printf("\t___________________________________________________________________\n");
        printf (
            "\n\t |========= MEN\351=========| \n"
            "\t|1.- Insertar cadena      |\n"
            "\t|2.- Quitar cadena        |\n"
            "\t|3.- Listado en preorden  |\n"
            "\t|4.- Listado en inorden   |\n"
            "\t|5.- Listado en postorden |\n"
            "\t|6.- Verificar el balanceo|\n"
            "\t|7.- Consultar propiedades|\n"
            "\t|8.- Recorrido sistematico|\n"
            "\t|9.- Salir                |\n\n"
            "Seleccione una opci\242n: ");
        do {
            opcion = _getch ();
        } while (opcion<'1' || opcion>'9');
        printf ("%c\n\n", opcion);
        if (raiz == NULL && opcion != '1' && opcion != '8' && opcion != '9')
            printf ("El \240rbol est\240 vac\241o.\n");
        else switch (opcion)
        {        	
            case '1':   
            printf("\t  -> Cuantos datos desea ingresar:\n");
            scanf("%i",&seg);
			for(i=0;i<seg;i++){        
			system("cls");
			printf("\t ||  INGRESAR DATOS  ||");  				       	
                printf ("\nIngrese la cadena a insertar: ");
                cin >> cadena;
							
                raiz = arbol_insertar (raiz, cadena);                
                printf ("\nCadenas agregadas correctamente.......!!\n\n");			
				
			}			  
				   break;
                
            
            case '2':
                printf ("Ingrese la cadena a quitar: ");
                scanf ("%[^\r\n]", cadena);
                (void) getchar ();
                raiz = arbol_quitar (raiz, cadena);
                printf ("\nCadena borrada correctamente.....!!\n");
                break;
            case '3': 
			printf("\t || PREORDEN DEL ARBOL AVL ||\n\n");
			arbol_preorden  (raiz, raiz); break;
            case '4': 
			printf("\t || INORDEN DEL ARBOL AVL ||\n\n");
			arbol_inorden   (raiz, raiz); break;
            case '5': 
			printf("\t || POSTORDEN DEL ARBOL AVL ||\n\n");
			arbol_postorden (raiz, raiz); break;
            case '6':
            
                printf ("El \265rbol se encuentra balanceado........!!!\n");
                raiz = arbol_balancear (raiz); 
				break;
            case '7':
                printf ("Altura    : %d\n", arbol_altura (raiz));
                printf ("Nodos     : %d\n", arbol_nodos  (raiz));
                printf ("Completo  : si\n");
                printf ("Balanceado: %s\n", arbol_balanceado (raiz) ? "si" : "no");
                break;
                
            case '8':
            printf("\t || PREORDEN DEL ARBOL AVL ||\n\n");
			arbol_preorden  (raiz, raiz); 
			printf("\n");
			
			printf("\t || INORDEN DEL ARBOL AVL ||\n\n");
			arbol_inorden   (raiz, raiz); 
			printf("\n");
			
			printf("\t || POSTORDEN DEL ARBOL AVL ||\n\n");
			arbol_postorden (raiz, raiz); break;
			
            case '9':
            	system("cls");
            	printf("EL ALGORITMO SOBRE LAS OPERACIONES DE ARBOL AVL HA TERMINADO.");
            	exit(0);
		}
        if (opcion!='9')
        {
            putchar ('\n');            
            system ("pause");
        }
    } while (opcion!='9');
    return EXIT_SUCCESS;
}

Arbol arbol_insertar (Arbol nodo, const char *cadena)
{
    if (nodo == NULL)
    {
        nodo = (Arbol) malloc (sizeof (struct TDAArbol));
        nodo->izq = NULL;
        nodo->der = NULL;
        nodo->cadena = strdup (cadena);
    }
    else if (strcmp (cadena, nodo->cadena) < 0)
        nodo->izq = arbol_insertar (nodo->izq, cadena);
    else
        nodo->der = arbol_insertar (nodo->der, cadena);
    return nodo;
}

Arbol arbol_quitar (Arbol nodo, const char *cadena)
{
    return arbol_quitar_y_rotar (nodo, cadena, IZQUIERDA);
}

Arbol arbol_quitar_y_rotar (Arbol nodo, const char *cadena, Sentido rotacion)
{
    Arbol pivote;
    int comparacion;
    if (nodo != NULL)
    {
        comparacion = strcmp (cadena, nodo->cadena);
        if (comparacion == 0)
        {
            if (nodo->izq == NULL)
                pivote = nodo->der;
            else if (nodo->der == NULL)
                pivote = nodo->izq;
            else if (rotacion == IZQUIERDA)
            {
                for (pivote = nodo->izq; pivote->der != NULL; pivote = pivote->der);
                pivote->der = nodo->der;
                pivote = nodo->izq;
            } else {
                for (pivote = nodo->der; pivote->izq != NULL; pivote = pivote->izq);
                pivote->izq = nodo->izq;
                pivote = nodo->der;
            }
            free (nodo->cadena);
            free (nodo);
            nodo = pivote;
        }
        else if (comparacion < 0)
            nodo->izq = arbol_quitar_y_rotar (nodo->izq, cadena, rotacion);
        else
            nodo->der = arbol_quitar_y_rotar (nodo->der, cadena, rotacion);
    }
    return nodo;
}

void arbol_preorden (Arbol raiz, Arbol nodo)
{
    Arbol pivote;
    int hermanos = 0, borde1, borde2;
    Sentido direccion = CENTRO;
    if (nodo != NULL)
    {
        pivote = raiz;
        while (pivote!=nodo)
        {
            printf ("%c ",hermanos==2 && direccion == IZQUIERDA ? '\263': ' ');
            hermanos = 0;
            if (pivote->izq!=NULL)
                hermanos++;
            if (pivote->der!=NULL)
                hermanos++;
            if (strcmp (nodo->cadena, pivote->cadena) < 0)
            {
                pivote = pivote->izq;
                direccion = IZQUIERDA;
            }
            else
            {
                pivote = pivote->der;
                direccion = DERECHA;
            }
        }
        borde1 = direccion == CENTRO ? '\304' :
            (hermanos == 1 || direccion == DERECHA ? '\300' : '\303');
        borde2 = nodo->izq != NULL || nodo->der != NULL ? '\302' : '\304';
        printf ("%c\304%c%s\n", borde1, borde2, nodo->cadena);
        arbol_preorden (raiz, nodo->izq);
        arbol_preorden (raiz, nodo->der);
    }
}

void arbol_inorden (Arbol raiz, Arbol nodo)
{
    Arbol pivote;
    Sentido direccion = CENTRO;
    int borde1, borde2;
    if (nodo != NULL)
    {
        arbol_inorden (raiz, nodo->izq);
        pivote = raiz;
        while (pivote!=nodo)
            if (strcmp (nodo->cadena, pivote->cadena) < 0)
            {
                printf ("%c ", direccion == DERECHA? '\263': ' ');
                pivote = pivote->izq;
                direccion = IZQUIERDA;
            }
            else
            {
                printf ("%c ", direccion == IZQUIERDA? '\263': ' ');
                pivote = pivote->der;
                direccion = DERECHA;
            }
        switch (direccion)
        {
            case IZQUIERDA: borde1 = '\332'; break;
            case CENTRO   : borde1 = '\304'; break;
            case DERECHA  : borde1 = '\300'; break;
        }
        if (nodo->izq!=NULL && nodo->der!=NULL)
            borde2 = '\305';
        else if (nodo->izq!=NULL)
            borde2 = '\301';
        else if (nodo->der!=NULL)
            borde2 = '\302';
        else
            borde2 = '\304';
        printf ("%c\304%c%s\n", borde1, borde2, nodo->cadena);
        arbol_inorden (raiz, nodo->der);
    }
}

void arbol_postorden (Arbol raiz, Arbol nodo)
{
    Arbol pivote;
    int hermanos = 0, borde1, borde2;
    Sentido direccion = CENTRO;
    if (nodo != NULL)
    {
        arbol_postorden (raiz, nodo->izq);
        arbol_postorden (raiz, nodo->der);
        pivote = raiz;
        while (pivote!=nodo)
        {
            printf ("%c ", hermanos==2 && direccion==DERECHA? '\263': ' ');
            hermanos = 0;
            if (pivote->izq!=NULL)
                hermanos++;
            if (pivote->der!=NULL)
                hermanos++;
            if (strcmp (nodo->cadena, pivote->cadena) < 0)
            {
                pivote = pivote->izq;
                direccion = IZQUIERDA;
            }
            else
            {
                pivote = pivote->der;
                direccion = DERECHA;
            }
        }
        borde1 = direccion == CENTRO ? '\304' :
            (hermanos==1 || direccion == IZQUIERDA? '\332': '\303');
        borde2 = nodo->izq!=NULL || nodo->der!=NULL? '\301': '\304';
        printf ("%c\304%c%s\n", borde1, borde2, nodo->cadena);
    }
}

int arbol_altura (Arbol nodo)
{
    int izq, der;
    if (nodo==NULL)
        return 0;
    izq = arbol_altura (nodo->izq);
    der = arbol_altura (nodo->der);
    return 1 + (izq > der ? izq : der);
}

Arbol arbol_balancear (Arbol nodo)
{
    int diferencia;
    char *cadena;
    if (nodo != NULL)
    {
        nodo->izq = arbol_balancear (nodo->izq);
        nodo->der = arbol_balancear (nodo->der);
        diferencia = arbol_altura (nodo->izq) - arbol_altura (nodo->der);
        if (diferencia > 1 || diferencia < -1)
        {
            cadena = strdup (nodo->cadena);
            nodo = arbol_balancear (arbol_insertar (
                arbol_quitar_y_rotar (nodo, cadena,
                    diferencia > 1 ? DERECHA : IZQUIERDA), cadena));
            free (cadena);
        }
    }
    return nodo;
}

int arbol_nodos (Arbol nodo)
{
    return nodo==NULL ? 0 : 1 + arbol_nodos (nodo->izq) + arbol_nodos (nodo->der);
}

int arbol_completo (Arbol nodo)
{
    return nodo==NULL || (
        arbol_nodos (nodo->izq) == arbol_nodos (nodo->der) &&
        arbol_completo (nodo->izq) &&
        arbol_completo (nodo->der) );
}

int arbol_balanceado (Arbol nodo)
{
    int diferencia;
    if (nodo==NULL)
        return 1;
    diferencia = arbol_altura (nodo->izq) - arbol_altura (nodo->der);
    return diferencia >= -1 && diferencia <= 1 &&
        arbol_balanceado (nodo->izq) && arbol_balanceado (nodo->der);
}