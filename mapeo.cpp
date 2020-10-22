#include <stdio.h>
#include <stdlib.h>

#include "mapeo.h"

static int max(int numero1,int numero2);
void (* funcion_eliminar_clave)(void *);
void (* funcion_eliminar_valor)(void *);
void funcion_eliminar_entrada(tElemento e);

/**
 Inicializa un mapeo vacío, con capacidad inicial igual al MAX(10, CI).
 Una referencia al mapeo creado es referenciada en *M.
 A todo efecto, el valor hash para las claves será computado mediante la función fHash.
 A todo efecto, la comparación de claves se realizará mediante la función fComparacion.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){

    tMapeo mapeoAux =(tMapeo) malloc(sizeof(struct mapeo));
    int capacidad=max(10,ci);
    int i;

    if(mapeoAux==NULL)
        exit(MAP_ERROR_MEMORIA);

    mapeoAux->cantidad_elementos = 0;
    mapeoAux->comparador = fComparacion;
    mapeoAux->hash_code = fHash;
    mapeoAux->longitud_tabla=capacidad;

    mapeoAux->tabla_hash=(tLista *) malloc(capacidad*sizeof(tLista));
    for(i=0;i<capacidad;i++){
        crear_lista(&(mapeoAux->tabla_hash[i]));
    }

    *m=mapeoAux;
}

/**
 Inserta una entrada con clave C y valor V, en M.
 Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
 Retorna NULL si la clave C no existía en M, o Vi en caso contrario.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
tValor m_insertar(tMapeo m, tClave c, tValor v){

    tEntrada entradaAux =(tEntrada) malloc(sizeof(struct entrada));
    entradaAux->clave=c;
    entradaAux->valor=v;



    return entradaAux;
}

/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    funcion_eliminar_valor = fEliminarV;
    funcion_eliminar_clave = fEliminarC;

    /*Busco la entrada que corresponde*/{
        l_eliminar(m->tabla_hash,posicion_de_entrada,&funcion_eliminar_entrada);
    }

}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    tPosicion nodoEliminar;
    tPosicion nodoDerecho;
    tEntrada entradaEliminar;
    tPosicion p=l_primera(m->tabla_hash);

    while(p->siguiente!=NULL){
        nodoEliminar=p->siguiente;
        nodoDerecho=nodoEliminar->siguiente;
        p->siguiente=nodoDerecho;
        entradaEliminar = nodoEliminar->elemento;
        fEliminarV(entradaEliminar->valor);
        fEliminarC(entradaEliminar->clave);

        nodoEliminar->elemento=NULL;
        nodoEliminar->siguiente=NULL;
        free(nodoEliminar);
    }

}

/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/
tValor m_recuperar(tMapeo m, tClave c){

}

/**
 Recibe una entrada y elimina sus datos
**/
void funcion_eliminar_entrada(tElemento e){
    tEntrada entrada=(tEntrada) e;
    funcion_eliminar_valor(entrada->valor);
    funcion_eliminar_clave(entrada->clave);
}

/**
 Recibe dos enteros por parametro y retorna el mayor de ellos
**/
static int max(int numero1,int numero2){

    int mayor;

    mayor = (numero1>numero2) ? numero1 : numero2;

    return mayor;

}
