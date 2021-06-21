#include "geo.h"
#include "path.h"
#include "dinamica.h"
#include "svg.h"

int main(int argc, char *argv[]){

    char *e = NULL, *o = NULL, *q = NULL, *f = NULL, *fbArq = NULL, *fbTitulo = NULL;
    int ib = 0, cb = 0, fb = 0, ldd = 0, lse = 0, i = 1, comando;

    while(i < argc){

        if(strcmp(argv[i], "-e") == 0){ //parâmetro 1: diretório de entrada

            e = (char *) malloc(strlen(argv[i + 1]) * sizeof(char) + 1);
            strcpy(e, argv[i + 1]);
        }
        else{
            if(strcmp(argv[i], "-o") == 0){ //parâmetro 2: diretório de saída

                o = (char *) malloc(strlen(argv[i + 1]) * sizeof(char) + 1);
                strcpy(o, argv[i + 1]);
            }
            else{
                if(strcmp(argv[i], "-q") == 0){ //parâmetro 3: nome do arquivo .qry

                    q = (char *) malloc(strlen(argv[i + 1]) * sizeof(char) + 1);
                    strcpy(q, argv[i + 1]);
                }
                else{
                    if(strcmp(argv[i], "-f") == 0){ //parâmetro 4: nome do arquivo .geo

                        f = (char *) malloc(strlen(argv[i + 1]) * sizeof(char) + 1);
                        strcpy(f, argv[i + 1]);
                    }
                    else{
                        if(strcmp(argv[i], "-ib") == 0){ //parâmetro 5: inicia coleta de dados de desempenho

                            ib = 1;
                        }
                        else{
                            if(strcmp(argv[i], "-cb") == 0){ //parâmetro 6: continua a coleta de dados

                                cb = 1;
                            }
                            else{
                                if(strcmp(argv[i], "-fb") == 0){ //parâmetro 7: finaliza a coleta e processa os dados

                                    fb = 1;
                                    fbArq = (char *) malloc(strlen(argv[i + 1]) * sizeof(char) + 1);
                                    strcpy(fbArq, argv[i + 1]);
                                    fbTitulo = (char *) malloc(strlen(argv[i + 2]) * sizeof(char) + 1);
                                    strcpy(fbTitulo, argv[i + 2]);
                                }
                                else{
                                    if(strcmp(argv[i], "-ldd") == 0){

                                        ldd = 1;
                                    }
                                    else{
                                        if(strcmp(argv[i], "-lse") == 0){

                                            lse = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        i++;
    }

    if((f == NULL) || (o == NULL)){
        printf("ERRO! Parametro(s) obrigatorio(s) nao informado(s)!\n");
        exit(1);
    }

    if((ldd == 1) && (lse == 1)){
        printf("Ambas as listas foram selecionadas. Lista padrao (dinamica duplamente encadeada) sera executada\n");
        lse = 0;
    }

    comando = 0;

    if(ib == 1)
        comando = 1; //aciona i ib
    if(cb == 1)
        comando = 2; //aciona o cb
    if(fb == 1){
        comando = 3; //acioba o fb
        analisaGeo(e, f, o, q, lse, comando, fbArq, fbTitulo);
    }
    else
        analisaGeo(e, f, o, q, lse, comando, NULL, NULL);

    libera(e);
    libera(o);
    libera(f);
    libera(q);
    libera(fbArq);
    libera(fbTitulo);

    return 0;
}
