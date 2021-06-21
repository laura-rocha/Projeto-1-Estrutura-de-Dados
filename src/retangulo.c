#include "retangulo.h"

typedef struct node{
    char id[40], cc[20], cp[20];
    double x, y, w, h;
}RetanguloStruct;

RETANGULO criaRetangulo(char id[], double x, double y, double w, double h, char cc[], char cp[]){

    RetanguloStruct *ret = (RetanguloStruct *) malloc(sizeof(RetanguloStruct));

    ret->x = x;
    ret->y = y;
    ret->w = w;
    ret->h = h;
    strcpy(ret->id, id);
    strcpy(ret->cc, cc);
    strcpy(ret->cp, cp);

    return ret;
}

char * getRetanguloID(RETANGULO retangulo){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    return ret->id;
}

char * getRetanguloCC(RETANGULO retangulo){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    return ret->cc;
}

char * getRetanguloCP(RETANGULO retangulo){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    return ret->cp;
}

double getRetanguloX(RETANGULO retangulo){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    return ret->x;
}

double getRetanguloY(RETANGULO retangulo){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    return ret->y;
}

double getRetanguloW(RETANGULO retangulo){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    return ret->w;
}

double getRetanguloH(RETANGULO retangulo){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    return ret->h;
}

void setRetanguloID(RETANGULO retangulo, char id[]){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    strcpy(ret->id, id);
}

void setRetanguloCC(RETANGULO retangulo, char cc[]){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    strcpy(ret->cc, cc);
}

void setRetanguloCP(RETANGULO retangulo, char cp[]){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    strcpy(ret->cp, cp);
}

void setRetanguloX(RETANGULO retangulo, double x){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    ret->x = x;
}

void setRetanguloY(RETANGULO retangulo, double y){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    ret->y = y;
}

void setRetanguloW(RETANGULO retangulo, double w){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    ret->w = w;
}

void setRetanguloH(RETANGULO retangulo, double h){

    RetanguloStruct *ret = (RetanguloStruct *) retangulo;
    ret->h = h;
}

int retInterRet(FORMA formaA, FORMA formaB){

    RetanguloStruct *fa = (RetanguloStruct *) formaA;
    RetanguloStruct *fb = (RetanguloStruct *) formaB;

    double x1a, x2a, y1a, y2a, x1b, x2b, y1b, y2b;

    x1a = fa->x;
    y1a = fa->y;
    x1b = fb->x;
    y1b = fb->y;

    x2a = x1a + fa->w;
    y2a = y1a + fa->h;
    x2b = x1b + fb->w;
    y2b = y1b + fb->h;

    if((x1a <= x2b) && (x2a >= x1b) && (y1a <= y2b) && (y2a >= y1b))
        return 1;
    else
        return 0;
}

int retDentroRet(FORMA formaA, FORMA formaB){ //verifica se a formaB está dentro da formaA

    RetanguloStruct *fa = (RetanguloStruct *) formaA;
    RetanguloStruct *fb = (RetanguloStruct *) formaB;

    double x1a, x2a, y1a, y2a, x1b, x2b, y1b, y2b;

    x1a = fa->x;
    y1a = fa->y;
    x1b = fb->x;
    y1b = fb->y;

    x2a = x1a + fa->w;
    y2a = y1a + fa->h;
    x2b = x1b + fb->w;
    y2b = y1b + fb->h;

    if((x1a <= x1b) && (x2a >= x2b) && (y1a <= y1b) && (y2a >= y2b))
        return 1;
    else
        return 0;
}

int pontoDentroRet(FORMA formaA, double X, double Y){

    RetanguloStruct *fa = (RetanguloStruct *) formaA;
    double x1, x2, y1, y2;

    x1 = fa->x;
    y1 = fa->y;
    x2 = x1 + fa->w;
    y2 = y1 + fa->w;

    if((x1 <= X) && (x2 >= X) && (y1 <= Y) && (y2 >= Y))
        return 1;
    else
        return 0;
}

int retanguloCmp(FORMA formaA, FORMA formaB){

    RetanguloStruct *fa = (RetanguloStruct *) formaA;
    RetanguloStruct *fb = (RetanguloStruct *) formaB;

    if(strcmp(fa->id, fb->id) == 0)
        return 1;
    else
        return 0;
}
