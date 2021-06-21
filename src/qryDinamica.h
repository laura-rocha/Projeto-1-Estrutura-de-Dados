#ifndef _QRYDINAMICA
#define _QRYDINAMICA

#include "geo.h"
#include "dinamica.h"
#include "retangulo.h"
#include "circulo.h"
#include "txt.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Este módulo contém todas as funções relacionadas ao arquivo qry, desde leitura do arquivo às diferentes consultas
*/

void executaQryDinamica(DINAMICA *din, char *arqQry, char *arqTxt);
/*
    Macrofunção que lê e executa cada consulta do arquivo qry.
*/

void tpTprDinamica(DINAMICA din, char *txt, double x, double y, double w, double h, int opcao);
/*
    Identifica todos os pares de retângulos que se sobrepõem.
    Identifica todos os retângulos que estejam inteiramente dentro da área delimitada pelo retângulo
especificado nos parâmetros x, y, w, h.
    Escreve no arquivo de texto os identificadores dos retângulos (um par por linha).
    Altera a cor dos par pares de retângulos para a mesma cor de preenchimento.
*/

void tpDinamica(DINAMICA din, char *txt);
/*
    Chama a função tpTprDinamica() com os devidos parâmetros.
*/

void tprDinamica(DINAMICA din, char *txt, double x, double y, double w, double h);
/*
    Chama a função tpTprDinamica() com os devidos parâmetros.
*/

void dpiDrDinamica(DINAMICA din, char *txt, FORMA forma, double x, double y, int opcao);
/*
    Remover todos os retângulos para os quais o ponto (x,y) é interno.
    OU
    Remove retângulos que estejam inteiramente dentro do retângulo de identificador id.
    Reportar os identificadores dos retângulos removidos no arquivo de texto.
*/

void dpiDinamica(DINAMICA din, char *txt, double x, double y);
/*
    Chama a função dpiDrDinamica() com os devidos parâmetros.
*/

void drDinamica(DINAMICA din, char *txt, char *id);
/*
    Verifica se existe retângulo com o identificador id.
    Caso exista, chama a função dpiDrDinamica() com os devidos parâmetros.
    Caso não exista, encerra a função.
*/
void bbiBbidDinamica(DINAMICA *ldd, char *txt, FORMA forma, double x, double y, int opcao);
/*
    Cria um retângulo “bounding box” contendo todos os retângulos para os quais o ponto (x,y) é
interno e cria um ponto com coordenadas centrais (x, y).
    OU
    Cria um retângulo “bounding box” selecionando todos os retângulos que estejam inteiramente
contidos no retângulo com identificador id.
    Registra os identificadores dos retângulos selecionados e respectivas cores (preenchimento e contorno)
originais no arquivo de texto.
    Inverte as cores de preenchimento e contorno dos retângulos selecionados.
*/

void bbiDinamica(DINAMICA *din, char *txt, double x, double y);
/*
    Chama a função bbiBbidDinamica() com os devidos parâmetros.
*/

void bbidDinamica(DINAMICA *ldd, char *txt, char *id);
/*
    Verifica se existe retângulo com o identificador id.
    Caso exista, chama a função bbiBbidDinamica() com os devidos parâmetros.
    Caso não exista, encerra a função.
*/

void iidDiidDinamica(DINAMICA din, char *txt, NODE nodeA, int k, int opcao);
/*
    Reporta os dados relativos ao retângulo identificado por id e os k elementos
posteriores (k > 0), ou anteriores (k < 0).
    OU
    Reportar dados e remove os k elementos anteriores ou posteriores.
    Registra o id, âncora, largura, altura, cor de contorno, cor de preenchimento de cada
um dos retângulos no arquivo de texto.
*/

void iidDinamica(DINAMICA din, char *txt, char *id, int k);
/*
    Verifica se existe retângulo com o identificador id.
    Caso exista, chama a função iidDiidDinamica() com os devidos parâmetros.
    Caso não exista, encerra a função.
*/
void diidDinamica(DINAMICA din, char *txt, char *id, int k);
/*
    Verifica se existe retângulo com o identificador id.
    Caso exista, chama a função iidDiidDinamica() com os devidos parâmetros.
    Caso não exista, encerra a função.
*/

#endif // _QRYDINAMICA

