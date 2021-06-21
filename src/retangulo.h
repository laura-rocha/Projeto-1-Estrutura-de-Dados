#ifndef _RET
#define _RET

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dinamica.h"
#include "estatica.h"

typedef void* RETANGULO;

/*
    Este módulo provê operações necessárias para a criação de uma struct que armazena dados de um retangulo e de
operações para obtenção e alteração desses dados. Além disso, o módulo conta com operações de comparacão entre retângulos e
uma operação de verificação de um ponto dentro de um retângulo.
 */

RETANGULO criaRetangulo(char id[], double x, double y, double w, double h, char cc[], char cp[]);
/*
   Aloca dinamicamente uma estrutura do tipo RetanguloStruct e armazena nela os seguintes dados de um retângulo: identificador (id), coordenada (x, y)
do vértice superior esquerdo, largura (w), altura (h), cor de contorno (cc) e cor de preenchimento (cp).
   Retorna o ponteiro para a estrutura alocada.
 */

char * getRetanguloID(RETANGULO retangulo);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, retorna o identificador armazenado na estrutura.
*/

char * getRetanguloCC(RETANGULO retangulo);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, retorna a cor de contorno armazenada na estrutura.
*/

char * getRetanguloCP(RETANGULO retangulo);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, retorna a cor de preenchimento armazenada na estrutura.
*/

double getRetanguloX(RETANGULO retangulo);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, retorna o valor de x armazenado na estrutura.
    O valor de x é a componente x do ponto (x, y) que representa a coordenada âncora do retângulo na representação svg.
*/

double getRetanguloY(RETANGULO retangulo);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, retorna o valor de y armazenado na estrutura.
    O valor de y é a componente y do ponto (x, y) que representa a coordenada âncora do retângulo na representação svg.
*/

double getRetanguloW(RETANGULO retangulo);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, retorna a largura armazenada na estrutura.
*/

double getRetanguloH(RETANGULO retangulo);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, retorna a altura armazenada na estrutura.
*/

void setRetanguloID(RETANGULO retangulo, char id[]);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, define como id o identificador na estrutura.
*/

void setRetanguloCC(RETANGULO retangulo, char cc[]);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, define como cc a cor de contorno na estrutura.
*/

void setRetanguloCP(RETANGULO retangulo, char cp[]);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, define como cp a cor de preenchimento na estrutura.
*/

void setRetanguloX(RETANGULO retangulo, double x);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, define como x o valor do componente x na estrutura.
*/

void setRetanguloY(RETANGULO retangulo, double y);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, define como y o valor do componente y na estrutura.
*/

void setRetanguloW(RETANGULO retangulo, double w);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, define como w o valor da largura na estrutura.
*/

void setRetanguloH(RETANGULO retangulo, double h);
/*
    Dado um ponteiro (retangulo) para uma estrutura do tipo RetanguloStruct, define como h o valor da altura na estrutura.
*/

int retInterRet(FORMA formaA, FORMA formaB);
/*
    Recebe como parâmetro dois ponteiros (formaA e formaB) para estruturas do tipo RetanguloStruct.
    Retorna 1 caso haja interseção entre os retângulos.
    Retorna 0, caso contrário.
    Essa operação também considera como interseção a sobreposição de pontos do contorno dos retângulo, visto que o contorno do
retângulo faz parte da figura como um todo.
*/

int retDentroRet(FORMA formaA, FORMA formaB);
/*
    Recebe como parâmetro dois ponteiros (formaA e formaB) para estruturas do tipo RetanguloStruct.
    Retorna 1 caso o retângulo formaB esteja inteiramente contido dentro da área do retângulo formaA.
    Retorna 0, caso contrário.
    Essa operação também considera formaB dentro de formaA caso os dois tenham exatamente os mesmos valores de x, y, w e h.
*/

int pontoDentroRet(FORMA formaA, double x, double y);
/*
    Recebe como parâmetro um ponteiro (formaA) para uma estrutura do tipo RetanguloStruct e dois números reais (x e y).
    Retorna 1 caso o ponto de coordenadas (x, y) esteja dentro da área do retângulo formaA.
    Retorna 0, caso contrário.
*/

int retanguloCmp(FORMA formaA, FORMA formaB);
/*
    Recebe como parâmetro dois ponteiros (formaA e formaB) para estruturas do tipo RetanguloStruct.
    Retorna 1 caso o identificador de formaA seja igual ao identificador de formaB.
    Retorna 0, caso contrário.
*/

#endif // _RET
