#include "lista.h"
#include "mapeo.h"
#include <stdio.h>
#include <stdlib.h>

void fEliminar (tElemento elemento){

    free(elemento);

}

void fEliminarC (tClave clave){

    free(clave);

}

void fEliminarV (tValor valor){

    free(valor);

}

int main(int argc,char ** args)
{
    printf("Hello world!\n");
    printf("Cantidad de parametros: %d\n",argc);



    return 0;
}

void cantidad_apariciones(){

}

void salir(tMapeo * m,tLista * l){

    l_destruir(l,fEliminar);
    m_destruir(m,fEliminarC,fEliminarV);

}
