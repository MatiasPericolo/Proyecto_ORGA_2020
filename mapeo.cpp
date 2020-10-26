#include <stdio.h>
#include <stdlib.h>

#include "mapeo.h"

/**
 Variables Globales
**/
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


    tValor toReturn;
    tEntrada entradaAux=(tEntrada) malloc(sizeof(struct entrada));
    if(entradaAux==NULL)
        exit(MAP_ERROR_MEMORIA);

    printf("|Aca webon: %s|\n",*((char**)c));
    entradaAux->clave=c;
    entradaAux->valor=v;
    int h = m->hash_code(c);
    h=h%(m->longitud_tabla);
    tLista lAux = m->tabla_hash[h];
    tPosicion puntero = l_primera(lAux);
    tPosicion ultimaEntrada = l_ultima(lAux);
    int encontre = 0;
    tEntrada pos;

    printf("Tamanio: %i \n",l_longitud(lAux));

    while((puntero != ultimaEntrada) && (encontre == 0)){
        pos = (tEntrada) l_recuperar(lAux,puntero);
        if(m->comparador(pos->clave,c)==0){
            encontre = 1;
            pos->clave=c;
        }
        puntero = l_siguiente(lAux,puntero);
    }
    if((puntero == ultimaEntrada) && (encontre == 0)){

        if(m->comparador(pos->clave,c)==0){
            encontre = 1;
            pos->clave=c;
        } else {
            l_insertar(lAux,ultimaEntrada,entradaAux);
            printf("Done pa\n");
        }
    }

    printf("|Aca webon: %s|\n",*((char**)c));

    return toReturn;
}

/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    funcion_eliminar_valor = fEliminarV;
    funcion_eliminar_clave = fEliminarC;

    int h = m->hash_code(c);
    h=h%(m->longitud_tabla);
    tLista lAux = m->tabla_hash[h];
    tPosicion puntero = l_primera(lAux);
    tPosicion ultimaEntrada = l_ultima(lAux);
    int encontre = 0;
    tEntrada pos;

    while((puntero != ultimaEntrada) && (encontre == 0)){
        pos = (tEntrada) l_recuperar(lAux,puntero);
        if(m->comparador(pos->clave,c)==0){
            encontre = 1;
            l_eliminar(lAux,puntero,&funcion_eliminar_entrada);
        }
        puntero = l_siguiente(lAux,puntero);
    }
    if((puntero == ultimaEntrada) && (encontre == 0)){
        if(m->comparador(pos->clave,c)==0){
            l_eliminar(lAux,puntero,&funcion_eliminar_entrada);
        }
    }
}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    unsigned int i;

    for(i=0;i<((*m)->longitud_tabla);i++){
        l_destruir(&((*m)->tabla_hash[i]),&funcion_eliminar_entrada);
    }

    free((*m)->tabla_hash);
    (*m)->tabla_hash = NULL;
    free(m);
    (*m) = NULL;

}

/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/
tValor m_recuperar(tMapeo m, tClave c){

    int h = m->hash_code(c);
    h=h%(m->longitud_tabla);
    printf("Hash: %i \n",h);
    tLista lAux = m->tabla_hash[h];
    tPosicion puntero = l_primera(lAux);
    tPosicion ultimaEntrada = l_ultima(lAux);
    int encontre = 0;
    tEntrada pos;
    tValor toReturn;

    while((puntero != ultimaEntrada) && (encontre == 0)){
        pos = (tEntrada) l_recuperar(lAux,puntero);
        if(m->comparador(pos->clave,c)==0){
            encontre = 1;
            toReturn = pos->valor;
        }
        puntero = l_siguiente(lAux,puntero);
    }
    if((puntero == ultimaEntrada) && (encontre == 0)){
        if(m->comparador(pos->clave,c)==0){
            toReturn = pos->valor;
        }
    }

    if(encontre==0)
        toReturn=NULL;



    return toReturn;

}

/**
 Recibe una entrada y elimina sus datos
**/
void funcion_eliminar_entrada(tElemento e){
    tEntrada entrada=(tEntrada) e;
    funcion_eliminar_valor(entrada->valor);
    funcion_eliminar_clave(entrada->clave);

    free(e);
}

/**
 Recibe dos enteros por parametro y retorna el mayor de ellos
**/
static int max(int numero1,int numero2){

    int mayor;

    mayor = (numero1>numero2) ? numero1 : numero2;

    return mayor;

}
