#ifndef _QRYESTATICA
#define _QRYESTATICA

#include "geo.h"
#include "estatica.h"
#include "retangulo.h"
#include "circulo.h"
#include "txt.h"
#include "svg.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Este módulo contém todas as funções relacionadas ao arquivo qry, desde leitura do arquivo às diferentes consultas
*/

void executaQryEstatica(ESTATICA *estatica, char *arqQry, char *arqTxt, char *arqSvg);
/*
    Macrofunção que lê e executa cada consulta do arquivo qry.
*/

void tpTprEstatica(ESTATICA est, char *txt, double x, double y, double w, double h, int opcao);
/*
    Identifica todos os pares de retângulos que se sobrepõem.
    OU
    Identifica todos os retângulos que estejam inteiramente dentro da área delimitada pelo retângulo
especificado nos parâmetros x, y, w, h.
    Escreve no arquivo de texto os identificadores dos retângulos (um par por linha).
    Altera a cor dos par pares de retângulos para a mesma cor de preenchimento.
*/

void tpEstatica(ESTATICA lse, char *arqTxt);
/*
    Chama a função tpTprEstatica() com os devidos parâmetros.
*/

void tprEstatica(ESTATICA lse, char *arqTxt, double x, double y, double w, double h);
/*
    Chama a função tpTprEstatica() com os devidos parâmetros.
*/

void dpiDrEstatica(ESTATICA est, char *txt, FORMA forma, double x, double y, int opcao);
/*
    Remover todos os retângulos para os quais o ponto (x,y) é interno.
    OU
    Remove retângulos que estejam inteiramente dentro do retângulo de identificador id.
    Reportar os identificadores dos retângulos removidos no arquivo de texto.
*/

void dpiEstatica(ESTATICA est, char *txt, double x, double y);
/*
    Chama a função dpiDrEstatica() com os devidos parâmetros.
*/

void drEstatica(ESTATICA est, char *txt, char *id);
/*
    Verifica se existe retângulo com o identificador id.
    Caso exista, chama a função dpiDrEstatica() com os devidos parâmetros.
    Caso não exista, encerra a função.
*/

void bbiBbidEstatica(ESTATICA *estatica, char *txt, FORMA forma, double x, double y, int opcao);
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

void bbiEstatica(ESTATICA *estatica, char *txt, double x, double y);
/*
    Chama a função bbiBbidEstatica() com os devidos parâmetros.
*/

void bbidEstatica(ESTATICA *estatica, char *txt, char *id);
/*
    Verifica se existe retângulo com o identificador id.
    Caso exista, chama a função bbiBbidEstatica() com os devidos parâmetros.
    Caso não exista, encerra a função.
*/

void iidDiidEstatica(ESTATICA est, char *txt, NO nodeA, int k, int opcao);
/*
    Reporta os dados relativos ao retângulo identificado por id e os k elementos
posteriores (k > 0), ou anteriores (k < 0).
    OU
    Reportar dados e remove os k elementos anteriores ou posteriores.
    Registra o id, âncora, largura, altura, cor de contorno, cor de preenchimento de cada
um dos retângulos no arquivo de texto.
*/

void iidEstatica(ESTATICA est, char *txt, char *id, int k);
/*
    Verifica se existe retângulo com o identificador id.
    Caso exista, chama a função iidDiidEstatica() com os devidos parâmetros.
    Caso não exista, encerra a função.
*/

void diidEstatica(ESTATICA est, char *txt, char *id, int k);
/*
    Verifica se existe retângulo com o identificador id.
    Caso exista, chama a função iidDiidEstatica() com os devidos parâmetros.
    Caso não exista, encerra a função.
*/

#endif // _QRYESTATICA
