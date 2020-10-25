#include "lista.cpp"
#include "mapeo.cpp"
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

int fHash(char *palabra) {
    int hash = 0;
    for (int i = 0; i < strlen(palabra); i++) {
        hash = 31 * hash + palabra[i];
    }

    return hash;
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
