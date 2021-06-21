#ifndef _CIRCULO
#define _CIRCULO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dinamica.h"
#include "estatica.h"

typedef void* CIRCULO;

/*
    Este módulo provê operações necessárias para a criação de uma struct que armazena dados de um circulo e
operações para obtenção desses dados.
 */

CIRCULO criaCirculo(double x, double y, double raio, char cc[], char cp[]);
/*
   Aloca dinamicamente uma estrutura do tipo CirculoStruct e armazena nela os seguintes dados de um circulo: coordenada (x, y)
do centro do circulo, valor do raio, cor de contorno (cc) e cor de preenchimento (cp).
   Retorna o ponteiro para a estrutura alocada.
 */

char* getCirculoCC(CIRCULO circulo);
/*
    Dado um ponteiro (circulo) para uma estrutura do tipo CirculoStruct, retorna a cor de contorno armazenada na estrutura.
*/

char* getCirculoCP(CIRCULO circulo);
/*
    Dado um ponteiro (circulo) para uma estrutura do tipo CirculoStruct, retorna a cor de preenchimento armazenada na estrutura.
*/

double getCirculoX(CIRCULO circulo);
/*
    Dado um ponteiro (circulo) para uma estrutura do tipo CirculoStruct, retorna o valor de x armazenado na estrutura.
    O valor de x é a componente x do ponto (x, y) que representa a coordenada do centro do circulo na representação svg.
*/

double getCirculoY(CIRCULO circulo);
/*
    Dado um ponteiro (circulo) para uma estrutura do tipo CirculoStruct, retorna o valor de y armazenado na estrutura.
    O valor de y é a componente y do ponto (x, y) que representa a coordenada do centro do circulo na representação svg.
*/

double getCirculoRaio(CIRCULO circulo);
/*
    Dado um ponteiro (circulo) para uma estrutura do tipo CirculoStruct, retorna o valor de raio armazenado na estrutura.
    Essa variável armazena valor do raio do circulo na representação svg.
*/

#endif // _CIRCULO
