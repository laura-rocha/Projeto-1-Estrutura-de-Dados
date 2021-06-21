#include "txt.h"

void comando(char *arqTxt, char *texto){

    FILE *txt = fopen(arqTxt, "a");

    if(txt == NULL){
        printf("Erro! Nao foi possivel abrir o arquivo txt!\n");
        exit(1);
    }
    fprintf(txt, "%s", texto);
    fclose(txt);
}

void tpTpr(char *arqTxt, char *id1, char *id2){

    FILE *txt = fopen(arqTxt, "a");

    if(txt == NULL){
        printf("Erro! Nao foi possivel abrir o arquivo txt!\n");
        exit(1);
    }
    fprintf(txt, "%s %s\n", id1, id2);
    fclose(txt);
}

void dpiDr(char *arqTxt, char *id){

    FILE *txt = fopen(arqTxt, "a");

    if(txt == NULL){
        printf("Erro! Nao foi possivel abrir o arquivo txt!\n");
        exit(1);
    }
    fprintf(txt, "%s\n", id);
    fclose(txt);
}

void bbiBbid(char *arqTxt, char *id, char *cp, char *cc){

    FILE *txt = fopen(arqTxt, "a");

    if(txt == NULL){
        printf("Erro! Nao foi possivel abrir o arquivo txt!\n");
        exit(1);
    }
    fprintf(txt, "%s %s %s\n", id, cp, cc);
    fclose(txt);
}

void iidDiid(char *arqTxt, char *id, double x, double y, double w, double h, char *cp, char *cc){

    FILE *txt = fopen(arqTxt, "a");

    if(txt == NULL){
        printf("Erro! Nao foi possivel abrir o arquivo txt!\n");
        exit(1);
    }
    fprintf(txt, "%s %lf %lf %lf %lf %s %s\n", id, x, y, w, h, cc, cp);
    fclose(txt);
}
