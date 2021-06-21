#include "path.h"

char * qualificaArquivoBed(char *caminho, char *nome){

    char *completo;
    int tamanho;

    if(caminho == NULL){
    tamanho = strlen(nome) * sizeof(char) + 1;
        completo = (char *) malloc(tamanho);
        memset(completo, 0, (tamanho));

        strcpy(completo, nome);
    }
    else{
        tamanho = (strlen(caminho) + strlen(nome)) * sizeof(char) + 2;
        completo = (char *) malloc(tamanho);
        memset(completo, 0, tamanho);

        if((caminho[strlen(caminho) - 1] == '/') && (nome[0] == '/'))
            caminho[strlen(caminho) - 1] = '\0';

        strcat(completo, caminho);

        if((caminho[strlen(caminho) - 1] != '/') && (nome[0] != '/'))
            strcat(completo, "/");

        strcat(completo, nome);
    }
    return completo;
}

char * qualificaArquivoBsd(char *bsd, char *geo, char *qry, char *extensao, char *separacao){

    int tamanho = (strlen(geo) + strlen(qry) + strlen(bsd) + strlen(extensao)) * sizeof(char) + 5;

    char *arquivo = (char *) malloc(tamanho);
    memset(arquivo, 0, tamanho);
    strcat(arquivo, bsd);
    if(bsd[strlen(bsd)-1] != '/')
        strcat(arquivo, "/");
    strcat(arquivo, geo);
    strcat(arquivo, separacao);
    strcat(arquivo, qry);
    strcat(arquivo, extensao);

    return arquivo;
}

char * nomeArquivo(char *arquivo){

    char *nome = NULL;
    int i, j = 0, len = strlen(arquivo) - 1;

    for(i = len; i >= 0; i--)
        if(arquivo[i] == '/')
            break;
    i++;

    nome = (char *) malloc(len * sizeof(char) + 5);
    while(1){
        if((j == len) || (arquivo[i] == '.'))
            break;
        nome[j] = arquivo[i];
        i++;
        j++;
    }
    nome[j] = '\0';

    return nome;
}

void libera(char *variavel){

    if(variavel != NULL)
        free(variavel);
}

int hasSlash(char *path){

    for(int i = 0; i < strlen(path); i++)
        if(path[i] == '/')
            return 1;
    return 0;
}
