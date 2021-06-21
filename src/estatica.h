#ifndef _ESTATICA
#define _ESTATICA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"
#include "dinamica.h"

typedef void* ESTATICA;
typedef void* NO;

/*
    Este módulo provê todas operações descritas no TAD para a lista estática simplesmente encadeada.
*/

ESTATICA createEstatica(int nx);
/*
    Cria um ponteiro do tipo EstaticaStruct com nx elementos do tipo SimpleNodeStruct.
    Inicializa os valores da struct.
    Retorna o ponteiro do tipo EStaticaStruct criado
*/

void insertEstatica(ESTATICA estatica, FORMA forma);
/*
    Recebe o ponteiro para a lista estática e um ponteiro void para alguma forma arbitrária.
    Armazena a forma no nó da primeira posição livre da lista, caso exista.
*/

void insertAfterEstatica(ESTATICA estatica, NO node, FORMA forma);
/*
    Recebe o ponteiro EstaticaStruct para a lista estática, o ponteiro SimpleNodeStruct node e o void pointer forma.
    Se houver espaço disponível na lista, insere a forma nesse espaço livre.
    Altera os índices da ordem da lista para que o node aponte para o novo elemento.
*/

void insertBeforeEstatica(ESTATICA estatica, NO node, FORMA forma);
/*
    Recebe o ponteiro EstaticaStruct para a lista estática, o ponteiro SimpleNodeStruct node e o void pointer forma.
    Se houver espaço disponível na lista, insere a forma nesse espaço livre.
    Altera os índices da ordem da lista para que o nó do novo elemento aponte para o node.
*/

int encontraPosicLivre(ESTATICA estatica);
/*
    Recebe o ponteiro para a lista estática.
    Percorre os nós da lista à procuca de um nó livre.
    Retorna o índice do nó livre, caso tenha recontrado.
    Retorna -1, caso contrário.
*/

NO getFirstEstatica(ESTATICA estatica);
/*
    Recebe o ponteiro para a lista estática.
    Retorna o endereço do primeiro nó da lista estática.
*/

int getIndiceFirstEstatica(ESTATICA estatica);
/*
    Recebe o ponteiro para a lista estática.
    Retorna o índice do primeiro nó da lista estática.
*/

NO getLastEstatica(ESTATICA estatica);
/*
    Recebe o ponteiro para a lista estática.
    Retorna o endereço do último nó da lista estática.
*/

NO getNextEstatica(ESTATICA estatica, NO no);
/*
    Recebe o ponteiro para a lista estática e o ponteiro para um nó da lista estática.
    Retorna o endereço do nó posterior ao nó recebido como parâmetro.
*/

int getIndiceNextEstatica(ESTATICA estatica, int indice);
/*
    Recebe o ponteiro para a lista estática.
    Retorna o índice do nó posterior ao nó na posição indice.
*/

NO getPreviousEstatica(ESTATICA estatica, NO no, int *indice);
/*
    Recebe o ponteiro para a lista estática, o ponteiro para um nó da lista estática e um ponteiro para um indice.
    Altera o ponteiro indice para o valor do índice do elemento anterior ao elemento no.
    Retorna o endereço do nó anterior ao nó dado como parâmetro.
*/

FORMA getFormaEstatica(NO no);
/*
    Recebe o ponteiro para um nó da lista estática.
    Retorna o ponteiro FORMA armazenado nesse nó;
*/

void removeEstatica(ESTATICA estatica, int i);
/*
    Recebe o ponteiro para a lista estática e o índice para um nó dessa lista.
    Remove o nó do índice recebido como parâmetro.
*/

void liberaEstatica(ESTATICA estatica);
/*
    Recebe o ponteiro para a lista estatica.
    Libera toda a memória alocada para a lista estática.
*/

void contabilizaVisitaEstatica(ESTATICA estatica);
/*
    Recebe o ponteiro para a lista estática.
    Contabiliza uma visita na lista estática.
*/

long int getVisitasEstatica(ESTATICA estatica);
/*
    Recebe o ponteiro para a lista estática.
    Retorna o número total de visitas contabilizadas ao longo da execução do programa.
*/

int lengthEstatica(ESTATICA estatica);
/*
    Recebe o ponteiro para a lista estática.
    Retorna o tamanho da lista estática.
    Visto que a lista é estática, essa função sempre retorna o valor de nx informado no arquivo geo.
*/


#endif // _ESTATICA
