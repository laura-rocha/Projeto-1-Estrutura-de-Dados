#ifndef _SVG
#define _SVG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"
#include "circulo.h"
#include "dinamica.h"
#include "estatica.h"

/*
    Este módulo provê uma série de funções para criar e finalizar arquivos svg, bem como para desenhar diferentes figuras nele.
 */

void iniciaSvg(char *arqSvg);
/*
    Cria um arquivo svg vazio para escrita (arqSvg).
    Insere no arquivo a string que inicializa o svg.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
 */

void finalizaSvg(char *arqSvg);
/*
    Abre o arquivo svg para a escrita no fim (arqSvg).
    Insere no arquivo a string que finaliza o svg.
    Caso arquivo não exista, a função o cria.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
 */

void geraSvgDinamica(DINAMICA *din, char *arqSvg);
/*
    Recebe um ponteiro duplo (din) para um vetor de listas dinâmicas e o nome de um arquivo svg.
    Abre o arquivo svg para escrita no final dele.
    Caso arquivo não exista, a função o cria.
    Lê cada lista dinâmica e desenha a figura que seus nós guardam com base no índice da lista.
    A lista dinamica 0 (din[0]) armazena os retângulos lidos no arquivo geo.
    A lista dinamica 1 (din[1]) armazena os retângulos do tipo bounding box das consultas bbi e bbid.
    A lista dinamica 2 (din[2]) armazena os pontos (x, y) das consultas bbi e bbid.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
*/

void geraSvgEstatica(ESTATICA *est, char *arqSvg);
/*
    Recebe um ponteiro duplo (est) para um vetor de listas estáticas e o nome de um arquivo svg.
    Abre o arquivo svg para escrita no final dele.
    Caso arquivo não exista, a função o cria.
    Lê cada lista estática e desenha a figura que esses nós guardam com base no índice da lista.
    A lista estática 0 (est[0]) armazena os retângulos lidos no arquivo geo.
    A lista estática 1 (est[1]) armazena os retângulos do tipo bounding box das consultas bbi e bbid.
    A lista estática 2 (est[2]) armazena os pontos (x, y) das consultas bbi e bbid.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
*/

void desenhaRetangulo(RETANGULO ret, FILE *svg);
/*
    Recebe um ponteiro para uma estrutura do tipo RetanguloStruct (ret) e um ponteiro FILE de um arquivo svg.
    Insere no arquivo svg, um retâgulo determinado pela altura, largura, âcora, cor de contorno e cor de preenchimento
especificados no retângulo ret.
*/

void desenhaBoundingBox(RETANGULO ret, FILE *svg);
/*
    Recebe um ponteiro para uma estrutura do tipo RetanguloStruct (ret) e um ponteiro FILE de um arquivo svg.
    Insere no arquivo svg, um retâgulo determinado pela altura, largura, âcora e cor de contorno
especificados no retângulo ret.
    O retângulo não apresenta cor de preenchimento e possui a característica "dash-array = 1" (traços).
*/

void desenhaCirculo(CIRCULO cir, FILE* svg, char *extra);
/*
    Recebe um ponteiro para uma estrutura do tipo CirculoStruct (ret), um ponteiro FILE de um arquivo svg e uma string extra.
    Insere no arquivo svg, um circulo determinado pelo raio, ponto central (x, y), cor de contorno e cor de preenchimento
especificados no circulo cir.
    Além disso, é escrito, nas características do circulo, a string extra, que pode conter outros elementos de formatação svg para circulos.
Como, por exemplo, "transform" e "dash-array".
*/

void desenhaReta(FILE* svg, double x1, double y1, double x2, double y2, char *extra);
/*
    Recebe um ponteiro FILE de um arquivo svg e uma string extra, além dos números reais x1, x2, y1, y2.
    Insere no arquivo svg, uma reta que se inicia no ponto (x1, y1) e termina no ponto (x2, y2).
    Além disso, é escrito, nas características da reta, a string extra, que pode conter outros elementos de formatação svg para retas.
Como, por exemplo, "transform" e "dash-array".
*/

void desenhaGrafico(char *arqSvg, char *arqTxt, char *titulo);
/*
    Recebe os nomes de um arquivo svg (arqSvg) e de um arquivo de texto (arqTxt), além de uma string titulo que guarda o titulo do gráfico
(informado após o parâmetro -fb).
    O arquivo de texto armazena os valores de pontos (x, y) a serem plotados em um gráfico arqSvg.
    A função determina os maiores valores de x e de y, calcula uma escala de valores a serem distribuidos nos eixos x e y
e plota os pontos.
*/

#endif //_SVG
