#include "circulo.h"

typedef struct node{
    char cc[20], cp[20];
    double x, y, raio;
}CirculoStruct;


CIRCULO criaCirculo(double x, double y, double raio, char cc[], char cp[]){

    CirculoStruct *cir = (CirculoStruct *) malloc(sizeof(CirculoStruct));

    cir->x = x;
    cir->y = y;
    cir->raio = raio;
    strcpy(cir->cc, cc);
    strcpy(cir->cp, cp);

    return cir;
}

char * getCirculoCC(CIRCULO circulo){

    CirculoStruct *cir = (CirculoStruct *) circulo;
    return cir->cc;
}

char * getCirculoCP(CIRCULO circulo){

    CirculoStruct *cir = (CirculoStruct *) circulo;
    return cir->cp;
}

double getCirculoX(CIRCULO circulo){

    CirculoStruct *cir = (CirculoStruct *) circulo;
    return cir->x;
}

double getCirculoY(CIRCULO circulo){

    CirculoStruct *cir = (CirculoStruct *) circulo;
    return cir->y;
}

double getCirculoRaio(CIRCULO circulo){

    CirculoStruct *cir = (CirculoStruct *) circulo;
    return cir->raio;
}
