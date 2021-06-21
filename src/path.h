#ifndef _PATH
#define _PATH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Este módulo provê uma série de funções para maniputação de strings que representam caminhos relativos ou absolutos,
 bem como nomes de arquivos.
*/

char * qualificaArquivoBed(char *caminho, char *nome);
/*
    Recebe um caminho e um nome de arquivo.
    Verifica se o caminho é NULL, se for, utiliza apenas o nome.
    Realiza as devidas análises para concatenar corretamente as duas strings na forma <caminho>/<nome>.
    Retorna um ponteiro para o caminho qualificado.
*/

char * qualificaArquivoBsd(char *bsd, char *geo, char *qry, char *extensao, char *separacao);
/*
    Recebe o diretório do arquivo, os nomes dos dois arquivos que irão compor o nome do arquivo final, a extensão do arquivo final e a separão que será
colocada entre os nomes dos dois arquivos.
    Realiza as devidas análises para criar um arquivo qualificado com nome <bsd><geo><separacao><qry><extensao>.
    Retorna o ponteiro para o arquivo final qualificado.
*/

char * nomeArquivo(char *arquivo);
/*
    Recebe o nome de um arquivo, possivelmente com extensão e com diretório.
    Realiza as devidas análises para deconsidera o diretório e a extensão.
    Retorna apenas o nome do arquivo (sem diretório, "/" e extensão).
*/

void libera(char *variavel);
/*
    Libera o char* alocado dinamicamente se este for diferente de NULL.
*/

int hasSlash(char *path);
/*
    Recebe uma string.
    Retorna 1 se ela possui, pelo menos, um caractere barra.
    Retorna 0, caso contrário.
*/

#endif // _PATH
