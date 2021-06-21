#ifndef _TXT
#define _TXT

#include <stdio.h>
#include <stdlib.h>

/*
    Este módulo provê operações para o registro de informações em arquivo de texto. O nome da função chamada pelo arquivo qry
    é escrito no arquivo de texto por meio da função comando(). Já as informações obtidas nas execuções das consultas do qry são registradadas
    no arquivo de texto por meio das demais funções deste modulo.
 */


void comando(char *arqTxt, char *texto);
/*
    Abre o arquivo arqTxt e escreve a string texto no fim do arquivo.
    Caso o arquivo não exista, a função o cria.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
 */

void tpTpr(char *arqTxt, char *id1, char *id2);
/*
    Abre o arquivo arqTxt e registra, no fim dele, os identificadores de dois retângulos (id1 e id2), referentes à consulta tp ou tpr.
    Caso o arquivo não exista, a função o cria.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
*/

void dpiDr(char *arqTxt, char *id);
/*
    Abre o arquivo arqTxt e registra, no fim dele, o identificador (id) do retângulo removido na consulta dpi ou dr.
    Caso o arquivo não exista, a função o cria.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
*/

void bbiBbid(char *arqTxt, char *id, char *cp, char *cc);
/*
    Abre o arquivo arqTxt e registra, no fim dele, o identificador (id) e a respectiva cor de preenchimento (cp) e de contorno (cc) originais do
retângulo selecionado na consulta bbi ou bbid.
    Caso o arquivo não exista, a função o cria.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
*/

void iidDiid(char *arqTxt, char *id, double x, double y, double w, double h, char *cp, char *cc);
/*
    Abre o arquivo arqTxt e registra, no fim dele, os dados relativos ao retângulo identificado por id, com âcora no ponto (x, y),
de largura w, altura h, cor de preenchimento cp e cor de contorno cc, referente à consulta iid ou diid.
    Caso o arquivo não exista, a função o cria.
    Caso haja algum erro na abertura do arquivo, a função é encerrada.
*/

#endif // _TXT
