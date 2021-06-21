#include "dinamica.h"

typedef struct no{
    FORMA forma;
    struct no *anterior, *proximo;
}NodeStruct;

typedef struct din{
    NodeStruct *primeiro;
    NodeStruct *ultimo;
    int size;
    int nx;
    long int visitas;
}DinamicaStruct;

DINAMICA createDinamica(){

    DinamicaStruct *din = (DinamicaStruct *) malloc(sizeof(DinamicaStruct));
    memset(din, 0, sizeof(DinamicaStruct));
    din->primeiro = NULL;
    din->ultimo = NULL;
    din->size = 0;
    din->visitas = 1;

    return din;
}

void insertDinamica(DINAMICA dinamica, FORMA forma){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    NodeStruct *no = (NodeStruct *) malloc(sizeof(NodeStruct));

    no->forma = forma;
    if(din->primeiro == NULL){
        no->anterior = NULL;
        din->primeiro = no;
    }
    else{
        din->ultimo->proximo = no;
        no->anterior = din->ultimo;
    }
    no->proximo = NULL;
    din->ultimo = no;
    din->size++;
    din->visitas++;
}

void insertAfterDinamica(DINAMICA dinamica, NODE no, FORMA forma){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    NodeStruct *nodeForma = (NodeStruct *) no;
    NodeStruct *aux = (NodeStruct *) malloc(sizeof(NodeStruct));

    aux->forma = forma;

    if(nodeForma->proximo == NULL){
        nodeForma->proximo = aux;
        aux->anterior = nodeForma;
        aux->proximo = NULL;
        din->ultimo = aux;
    }
    else{
        NodeStruct *aux1 = nodeForma->proximo;
        nodeForma->proximo = aux;
        aux->proximo = aux1;
        aux->anterior = nodeForma;
        aux1->anterior = aux;
    }
    din->size++;
    din->visitas++;
}

void insertBeforeDinamica(DINAMICA dinamica, NODE no, FORMA forma){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    NodeStruct *nodeForma = (NodeStruct *) no;
    NodeStruct *aux = (NodeStruct *) malloc(sizeof(NodeStruct));

    aux->forma = forma;

    if(nodeForma->anterior == NULL){
        nodeForma->anterior = aux;
        aux->anterior = NULL;
        aux->proximo = nodeForma;
        din->primeiro = aux;
    }
    else{
        NodeStruct *aux1 = nodeForma->anterior;
        aux1->proximo = aux;
        aux->anterior = aux1;
        aux->proximo = nodeForma;
        nodeForma->anterior = aux;
    }
    din->size++;
    din->visitas++;
}

NODE getFirstDinamica(DINAMICA dinamica){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    din->visitas++;
    return din->primeiro;
}

NODE getLastDinamica(DINAMICA dinamica){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    din->visitas++;
    return din->ultimo;
}

NODE getNextDinamica(NODE no){

    NodeStruct *nodeForma = (NodeStruct *) no;
    return nodeForma->proximo;
}

NODE getPreviousDinamica(NODE no){

    NodeStruct *nodeForma = (NodeStruct *) no;
    return nodeForma->anterior;
}

FORMA getFormaDinamica(NODE no){

    NodeStruct *nodeForma = (NodeStruct *) no;
    return nodeForma->forma;
}

void removeDinamica(DINAMICA dinamica, NODE no){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    NodeStruct *nodeForma = (NodeStruct *) no;
    NodeStruct *aux1;
    NodeStruct *aux2;

    if(din->size == 0)
        exit(1);

    if(nodeForma->anterior == NULL){ //remoção do primeiro elemento
        aux1 = din->primeiro;
        din->primeiro = din->primeiro->proximo;

        if(din->primeiro == NULL)
            din->ultimo = NULL;
        else
            din->primeiro->anterior = NULL;
    }
    else{
        if(nodeForma->proximo == NULL){ //remoção do último elemento
            aux1 = din->ultimo;
            din->ultimo->anterior->proximo = NULL;
            din->ultimo = din->ultimo->anterior;
        }
        else{ //remoção em outro lugar
            aux2 = nodeForma;
            aux1 = nodeForma;
            aux2->anterior->proximo = aux2->proximo;
            aux2->proximo->anterior = aux2->anterior;
        }
    }
    din->size--;
    din->visitas++;
    free(getFormaDinamica(aux1));
    free(aux1);
}

void liberaDinamica(DINAMICA dinamica){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    NodeStruct *node = getFirstDinamica(din);
    NodeStruct *aux;

    while(node != NULL){
        aux = node;
        node = node->proximo;
        free(aux->forma);
        free(aux);
    }
    free(din);
}

void contabilizaVisitaDinamica(DINAMICA dinamica){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    din->visitas++;
}

long int getVisitasDinamica(DINAMICA dinamica){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    return din->visitas;
}

void setNxDinamica(DINAMICA dinamica, int nx){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    din->nx = nx;
}

int getNxDinamica(DINAMICA dinamica){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    return din->nx;
}

int lengthDinamica(DINAMICA dinamica){

    DinamicaStruct *din = (DinamicaStruct *) dinamica;
    return din->size;
}
