#include "lista.cpp"
#include "mapeo.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fEliminar (tElemento elemento){

    free(elemento);

}

void fEliminarC (tClave clave){

    free(clave);

}

void fEliminarV (tValor valor){

    free(valor);

}

int fHash(tClave clave) {
    int hash = 0;
    char * palabra=(char *) &clave;
    for (int i = 0; i < strlen(palabra); i++) {
        hash = 31 * hash + palabra[i];
    }
    return hash;
}

int fComparacion(tClave c1,tClave c2){
    return 0;
}

int main(int argc,char ** args)
{


    tMapeo mapeo;
    char ** claveAux;
    int * valorAux;

    crear_mapeo(&mapeo,10,fHash,fComparacion);

    claveAux=(char **) malloc(100*sizeof(char *));
    valorAux=(int *) malloc(sizeof(int));

    char * archivo=args[1];

    char caracter;
    FILE *file;
    file = fopen(archivo, "r");
    int i;

    i=0;

    if (file) {
        while(((caracter = getc(file)) != EOF)){

        /*
        if(caracter != ' ')
            printf("No ");
        else
            printf("Si ");
        */

            if((caracter != ' ')){
                printf("No ");
                (*claveAux)[i]=caracter;
                i++;
            }else{

                if(m_recuperar(mapeo,claveAux)!=NULL){
                    valorAux=m_recuperar(mapeo,claveAux);
                    (*valorAux)++;
                }else{
                    *valorAux=1;
                }

                m_insertar(mapeo,claveAux,valorAux);

                //Limpio la clave auxiliar
                for(i=i;i>0;i--){
                    (*claveAux)[i]=0;
                }

            }
        }

        fclose(file);
    }


    char ** tester=(char **) malloc(4*sizeof(char *));;
    char ** recuperado=(char **) malloc(4*sizeof(char *));;

    (*tester)[0]='s';
    (*tester)[1]='o';
    (*tester)[2]='l';

    recuperado=m_recuperar(mapeo,tester);
    printf("%c %c %c",(*recuperado)[0],(*recuperado)[1],(*recuperado)[2]);


    return 0;
}

void cantidad_apariciones(){

}

void salir(tMapeo * m,tLista * l){

    l_destruir(l,fEliminar);
    m_destruir(m,fEliminarC,fEliminarV);

}
