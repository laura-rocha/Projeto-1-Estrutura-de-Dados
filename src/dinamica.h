#ifndef _DINAMICA
#define _DINAMICA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"

typedef void* FORMA;
typedef void* DINAMICA;
typedef void* NODE;

/*
    Este módulo provê todas operações descritas no TAD para a lista dinâmica duplamente encadeada.
*/

DINAMICA createDinamica();
/*
    Cria um ponteiro do tipo DinamicaStruct.
    Inicializa os valores desse ponteiro.
    Retorna o ponteiro.
*/

void insertDinamica(DINAMICA dinamica, FORMA forma);
/*
    Recebe o ponteiro para a lista dinâmica e um ponteiro void para alguma forma arbitrária.
    Cria um nó do tipo NodeStrcut, armazena a forma nesse nó e insere o nó no fim da lista dinâmica.
*/

void insertAfterDinamica(DINAMICA dinamica, NODE no, FORMA forma);
/*
    Recebe o ponteiro DinamicaStruct para a lista dinâmica, o ponteiro NodeStruct no e o void pointer forma.
    Cria uma nó e armazena a forma nele.
    Insere o nó criado logo após o nó passado como parâmetro.
*/

void insertBeforeDinamica(DINAMICA dinamica, NODE no, FORMA forma);
/*
    Recebe o ponteiro DinamicaStruct para a lista dinâmica, o ponteiro NodeStruct no e o void pointer forma.
    Cria uma nó e armazena a forma nele.
    Insere o nó criado logo antes do nó passado como parâmetro.
*/

NODE getFirstDinamica(DINAMICA dinamica);
/*
    Recebe o ponteiro para a lista dinâmica.
    Retorna o ponteiro para o primeiro nó da lista dinâmica.
*/

NODE getLastDinamica(DINAMICA dinamica);
/*
    Recebe o ponteiro para a lista dinâmica.
    Retorna o ponteiro para o último nó da lista dinâmica.
*/

NODE getNextDinamica(NODE no);
/*
    Recebe o ponteiro para um nó da lista dinâmica.
    Retorna o ponteiro para o próximo nó da lista dinâmica.
*/

NODE getPreviousDinamica(NODE);
/*
    Recebe o ponteiro para um nó da lista dinâmica.
    Retorna o ponteiro para o nó anterior na lista dinâmica.
*/

FORMA getFormaDinamica(NODE no);
/*
    Recebe o ponteiro para um nó da lista dinâmica.
    Retorna o ponteiro FORMA armazenado nesse nó;
*/

void removeDinamica(DINAMICA dinamica, NODE no);
/*
    Recebe o ponteiro para a lista dinâmica e um ponteiro para um nó dessa lista.
    Remove o nó recebido como parâmetro.
*/

void liberaDinamica(DINAMICA dinamica);
/*
    Recebe o ponteiro para a lista dinâmica.
    Libera toda a memória alocada para a lista dinâmica.
*/

void contabilizaVisitaDinamica(DINAMICA dinamica);
/*
    Recebe o ponteiro para a lista dinâmica.
    Contabiliza uma visita na lista dinâmica.
*/

long int getVisitasDinamica(DINAMICA dinamica);
/*
    Recebe o ponteiro para a lista dinâmica.
    Retorna o número total de visitas contabilizadas ao longo da execução do programa.
*/

void setNxDinamica(DINAMICA dinamica, int nx);
/*
    Recebe o ponteiro para a lista dinâmica e um número inteiro nx.
    Armazena o valor de nx na lista dinâmica (ele será usado apenas na criação do gráfico).
*/

int getNxDinamica(DINAMICA dinamica);
/*
    Recebe o ponteiro para a lista dinâmica.
    Retorna o valor de nx inicialmente armazenado na lista dinâmica.
*/

int lengthDinamica(DINAMICA dinamica);
/*
    Recebe o ponteiro para a lista dinâmica.
    Retorna a quantidade atual de nós da lista dinâmica.
*/

#endif //_DINAMICA
