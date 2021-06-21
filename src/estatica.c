#include "estatica.h"

typedef struct{
    FORMA forma;
    int proximo;
}SimpleNodeStruct;

typedef struct{
    SimpleNodeStruct *vetor;                //ultimo: índice do último elemento da lista
    int primeiro, ultimo, livre, size;     //primeiro: índice do primeiro elemento da lista; livre: índice da primeira posição livre
    long int visitas;
}EstaticaStruct;

ESTATICA createEstatica(int nx){

    EstaticaStruct *est = (EstaticaStruct *) malloc(sizeof(EstaticaStruct));

    est->vetor = malloc(sizeof(SimpleNodeStruct) * nx);
    est->primeiro = -1;
    est->ultimo = -1;
    est->livre = 0;
    est->size = nx;
    est->visitas = 1;

    for(int i = 0; i <= (nx-1); i++){ //-2 na variável proximo significa que o node está livre
        est->vetor[i].proximo = -2;
        est->vetor[i].forma = NULL;
        est->visitas++;
    }

    return est;
}

void insertEstatica(ESTATICA estatica, FORMA forma){

    EstaticaStruct *est = (EstaticaStruct *) estatica;

    if(est->livre != -1){ //se a lista nao estiver cheia

        est->vetor[est->livre].forma = forma;
        est->vetor[est->livre].proximo = -1; //porque estou inserindo na última posição livre

        if(est->primeiro == -1){ //se a lista estava vazia (não precisamos procurar o ultimo elemento pra apontar pra no)

            est->primeiro = 0;
            est->ultimo = 0;
        }
        else{ //a lista nao está vazia, então precisamos procurar o ultimo elemento pra apontar pra no
            est->vetor[est->ultimo].proximo = est->livre;
            est->ultimo = est->livre;
        }
        est->livre = encontraPosicLivre(est);
    }
    else{
        printf("Lista estática cheia! Funcao insertEstatica() falhou\n");
    }
    est->visitas++;
}

void insertAfterEstatica(ESTATICA estatica, NO node, FORMA forma){

    EstaticaStruct *est = (EstaticaStruct *) estatica;
    SimpleNodeStruct *no = (SimpleNodeStruct *) node;

    if(est->livre != -1){

        int i = est->primeiro;
        while(i != -1){

            if(strcmp(getRetanguloID(no->forma), getRetanguloID(est->vetor[i].forma)) == 0)
                break;
            i = est->vetor[i].proximo;
        }

        if(i != -1){

            est->vetor[est->livre].forma = forma;
            est->vetor[est->livre].proximo = est->vetor[i].proximo;
            est->vetor[i].proximo = est->livre;

            if(i == est->ultimo)
                est->ultimo = est->livre;

            est->livre = encontraPosicLivre(est);
        }
        else{
            printf("ERRO! id nao existente. Funcao insertAfterEstatica() falhou\n");
            exit(1);
        }
    }
    else
        printf("ERRO! Lista estatica cheia. Funcao insertAfterEstatica() falhou\n");
}

void insertBeforeEstatica(ESTATICA estatica, NO node, FORMA forma){

    EstaticaStruct *est = (EstaticaStruct *) estatica;
    SimpleNodeStruct *no = (SimpleNodeStruct *) node;

    if(est->livre != -1){

        int i = est->primeiro;
        while(i != -1){

            if(strcmp(getRetanguloID(no->forma), getRetanguloID(est->vetor[i].forma)) == 0)
                break;
            i = est->vetor[i].proximo;
        }
        if(i != -1){

            int *indice = NULL;
            SimpleNodeStruct *anterior = (SimpleNodeStruct *) getPreviousEstatica(est, no, indice);

            est->vetor[est->livre].forma = forma;
            est->vetor[est->livre].proximo = i;

            if(i == est->primeiro)
                est->primeiro = est->livre;
            else
                anterior->proximo = est->livre;

            est->livre = encontraPosicLivre(est);

        }
        else{
            printf("ERRO! id nao existente. Funcao insertBeforeEstatica() falhou\n");
            exit(1);
        }
    }
    else
        printf("ERRO! Lista estatica cheia. Funcao insertBeforeEstatica() falhou\n");

}

int encontraPosicLivre(ESTATICA estatica){

    EstaticaStruct *est = (EstaticaStruct *) estatica;

    for(int j = 0; j <= (est->size - 1); j++){
        if(est->vetor[j].proximo == -2)
            return j;
        est->visitas++;
    }
    return -1;
}

NO getFirstEstatica(ESTATICA estatica){

    EstaticaStruct *lse = (EstaticaStruct *) estatica;
    SimpleNodeStruct *node = &(lse->vetor[lse->primeiro]);
    lse->visitas++;
    return node;
}

int getIndiceFirstEstatica(ESTATICA estatica){

    EstaticaStruct *lse = (EstaticaStruct *) estatica;
    lse->visitas++;
    return lse->primeiro;
}

NO getLastEstatica(ESTATICA estatica){

    EstaticaStruct *lse = (EstaticaStruct *) estatica;
    SimpleNodeStruct *node = &(lse->vetor[lse->ultimo]);
    lse->visitas++;
    return node;

}

NO getNextEstatica(ESTATICA estatica, NO no){

    EstaticaStruct *lse = (EstaticaStruct *) estatica;
    SimpleNodeStruct *node = (SimpleNodeStruct *) no;

    if(node->proximo == -1)
        return NULL;
    int p = node->proximo;
    node = &(lse->vetor[p]);
    lse->visitas++;
    return node;
}

int getIndiceNextEstatica(ESTATICA estatica, int indice){

    EstaticaStruct *lse = (EstaticaStruct *) estatica;
    lse->visitas++;
    return lse->vetor[indice].proximo;
}

NO getPreviousEstatica(ESTATICA estatica, NO no, int *indice){

    EstaticaStruct *lse = (EstaticaStruct *) estatica;

    SimpleNodeStruct *node = (SimpleNodeStruct *) no;
    SimpleNodeStruct *aux = (SimpleNodeStruct *) getFirstEstatica(estatica);

    int atual = lse->primeiro;
    int anterior = -1;

    while(strcmp(getRetanguloID(aux->forma), getRetanguloID(node->forma)) != 0){

        anterior = atual;
        atual = lse->vetor[atual].proximo;
        aux = &(lse->vetor[atual]);
        lse->visitas++;
    }
    *(indice) = anterior;

    if(anterior == -1)
        return NULL;

    aux = &(lse->vetor[anterior]);
    return aux;
}

FORMA getFormaEstatica(NO no){

    SimpleNodeStruct *node = (SimpleNodeStruct *) no;
    return node->forma;
}

void removeEstatica(ESTATICA estatica, int i){

    EstaticaStruct *est = (EstaticaStruct *) estatica;
    int auxiliar;

    if(i == est->primeiro){ //se vamos remover o primeiro elemento
        if(i == est->ultimo){ //se for o primeiro e único elemento
            est->primeiro = -1;
            est->ultimo = -1;
            est->livre = 0;
        }
        else{ //se i foir o primeiro mas não for o último
            est->primeiro = est->vetor[i].proximo;
        }
    }
    else{
        auxiliar = est->primeiro;

        while(est->vetor[auxiliar].proximo != i){
            auxiliar = est->vetor[auxiliar].proximo;
            est->visitas++;
        }

        if(i == est->ultimo){ //se vamos remover o último elemento
            est->vetor[auxiliar].proximo = -1;
            est->ultimo = auxiliar;
        }
        else{ //se vamos remover elementos do meio
            est->vetor[auxiliar].proximo = est->vetor[i].proximo;
        }
    }
    est->visitas++;
    est->vetor[i].proximo = -2; //indicando q essa posicao esta livre agora
}

void liberaEstatica(ESTATICA estatica){

    EstaticaStruct *est = (EstaticaStruct *) estatica;

    for(int i = 0; i <= (est->size-1); i++){
        free(est->vetor[i].forma);
    }
    free(est->vetor);
    free(est);
}

void contabilizaVisitaEstatica(ESTATICA estatica){

    EstaticaStruct *est = (EstaticaStruct *) estatica;
    est->visitas++;
}

long int getVisitasEstatica(ESTATICA estatica){

    EstaticaStruct *est = (EstaticaStruct *) estatica;
    return est->visitas;
}

int lengthEstatica(ESTATICA estatica){

    EstaticaStruct *est = (EstaticaStruct *) estatica;
    return est->size;
}
