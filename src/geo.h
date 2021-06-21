#ifndef _GEO
#define _GEO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "path.h"
#include "dinamica.h"
#include "estatica.h"
#include "retangulo.h"
#include "svg.h"
#include "txt.h"
#include "qryEstatica.h"
#include "qryDinamica.h"

/*
    Este módulo provê as três macrofunções bases que gerenciam o programa.
*/

void analisaGeo(char *bed, char *arqGeo, char *bsd, char *arqQry, int lista, int comando, char *fbArq, char *fbTitulo);
/*
    Recebe os parâmetros inseridos pelo usuário.
    Verifica qual tipo de lista foi escolhida.
    Chama as funções que realizam a leitura do arquivo geo, leitura do arquivo qry e impressão em arquivo svg.
    Libera a memória alocada dinamicamente.
*/
void leGeoDinamica(DINAMICA ldd, char *arqGeo);
/*
    Recebe o ponteiro para a lista dinâmica e para o arquivo geo.
    Realiza a leitura do arquivo geo, inserindo os retângulos lidos na lista dinâmica.
*/

ESTATICA leGeoEstatica(ESTATICA lse, char *arqGeo);
/*
    Recebe o ponteiro para a lista estática (inicializado com NULL) e para o arquivo geo.
    Cria uma lista estática.
    Realiza a leitura do arquivo geo, inserindo os retângulos lidos na lista estática criada.
    Retorna o ponteiro da lista estática criada.
*/

#endif // _GEO
