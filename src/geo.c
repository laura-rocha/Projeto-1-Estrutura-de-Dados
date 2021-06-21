#include "geo.h"

void analisaGeo(char *bed, char *arqGeo, char *bsd, char *arqQry, int lista, int comando, char *fbArq, char *fbTitulo){

    char *arqSvg = NULL;
    char *nomeGeo = NULL;
    char *nomeQry = NULL;
    char *geoQualificado = NULL;
    char *svgQualificado = NULL;
    char *svgFinalQualificado = NULL;
    char *qryQualificado = NULL;
    char *txtQualificado = NULL;

    long int visitas;
    int nx;

    if(arqGeo[0] == '/')
        arqGeo = strtok(arqGeo, "/");

    geoQualificado = qualificaArquivoBed(bed, arqGeo);
    nomeGeo = nomeArquivo(arqGeo);

    arqSvg = (char *) malloc(strlen(nomeGeo) * sizeof(char) + 5);
    memset(arqSvg, 0, strlen(nomeGeo) * sizeof(char) + 5);
    strcat(arqSvg, nomeGeo);
    strcat(arqSvg, ".svg");
    svgQualificado = qualificaArquivoBed(bsd, arqSvg);

    if(arqQry != NULL){
        qryQualificado = qualificaArquivoBed(bed, arqQry);
        nomeQry = nomeArquivo(arqQry);
        txtQualificado = qualificaArquivoBsd(bsd, nomeGeo, nomeQry, ".txt", "-");
        svgFinalQualificado = qualificaArquivoBsd(bsd, nomeGeo, nomeQry, ".svg", "-");
    }

    if(lista == 1){

        ESTATICA est[3];
        est[0] = NULL;
        est[1] = createEstatica(20);
        est[2] = createEstatica(20);

        est[0] = leGeoEstatica(est[0], geoQualificado);

        iniciaSvg(svgQualificado);
        geraSvgEstatica(est, svgQualificado);
        finalizaSvg(svgQualificado);

        if(arqQry != NULL){

            iniciaSvg(svgFinalQualificado);
            executaQryEstatica(est, qryQualificado, txtQualificado, svgFinalQualificado);
            finalizaSvg(svgFinalQualificado);
        }

        visitas = getVisitasEstatica(est[0]);
        nx = lengthEstatica(est[0]);

        liberaEstatica(est[0]);
        liberaEstatica(est[1]);
        liberaEstatica(est[2]);
    }
    else{

        DINAMICA din[3];
        din[0] = createDinamica(); //guarda os retângulos
        din[1] = createDinamica(); //guarda as bounding boxes
        din[2] = createDinamica(); //guarda os pontos (x, y) do BBI

        leGeoDinamica(din[0], geoQualificado);
        geraSvgDinamica(din, svgQualificado);

        if(qryQualificado != NULL){

            executaQryDinamica(din, qryQualificado, txtQualificado);
            geraSvgDinamica(din, svgFinalQualificado);
        }

        visitas = getVisitasDinamica(din[0]);
        nx = getNxDinamica(din[0]);

        liberaDinamica(din[0]);
        liberaDinamica(din[1]);
        liberaDinamica(din[2]);
    }

    char *txtRelatorio = NULL;
    txtRelatorio = qualificaArquivoBed(bsd, "desempenho.txt");

    if(comando == 1){

        FILE *txt = fopen(txtRelatorio, "w+");
        if(txt != NULL){
            fprintf(txt, "%d %ld\n", nx, visitas);
            fclose(txt);
        }
        else{
            printf("Erro! Nao foi possivel criar o arquivo para armazenar os dados do relatorio de desempenho\n");
        }
    }
    if(comando == 2){

        FILE *txt = fopen(txtRelatorio, "a");
        if(txt != NULL){
            fprintf(txt, "%d %ld\n", nx, visitas);
            fclose(txt);
        }
        else{
            printf("Erro! Nao foi possivel abrir o arquivo para armazenar os dados do relatorio de desempenho\n");
        }
    }
    if(comando == 3){

        char *svgGrafico = NULL;
        svgGrafico = qualificaArquivoBsd(bsd, fbArq, "", ".svg", "");

        FILE *txt = fopen(txtRelatorio, "a");
        if(txt != NULL){
            fprintf(txt, "%d %ld\n", nx, visitas);
            fclose(txt);

            desenhaGrafico(svgGrafico, txtRelatorio, fbTitulo);
        }
        else{
            printf("Erro! Nao foi possivel abrir o arquivo para armazenar os dados do relatorio de desempenho\n");
        }
        libera(svgGrafico);
    }


    libera(txtRelatorio);
    libera(geoQualificado);
    libera(arqSvg);
    libera(svgQualificado);
    libera(svgFinalQualificado);
    libera(qryQualificado);
    libera(txtQualificado);
    libera(nomeGeo);
    libera(nomeQry);
}

void leGeoDinamica(DINAMICA ldd, char *arqGeo){

    FILE *geo = fopen(arqGeo,"r");

    if(geo == NULL){
        printf("ERRO! Arquivo .geo nao pode ser aberto\n");
        exit(1);
    }
    double x, y, w, h;
    char id[30], auxiliar[4], cp[30], cc[30];
    int nx;

    while(1){

        fscanf(geo, "%s", auxiliar);
        if(feof(geo))
            break;

        if(strcmp(auxiliar, "nx") == 0){
            fscanf(geo, "%d\n", &nx);
            setNxDinamica(ldd, nx);
        }
        else{
            if(strcmp(auxiliar, "cp") == 0){
                fscanf(geo, "%s\n", cp);
            }
            else{
                if(strcmp(auxiliar, "cc") == 0){
                    fscanf(geo, "%s\n", cc);
                }
                else{
                    if(strcmp(auxiliar, "r") == 0){
                        fscanf(geo, "%s %lf %lf %lf %lf\n", id, &x, &y, &w, &h);
                        RETANGULO r = criaRetangulo(id, x, y, w, h, cc, cp);
                        insertDinamica(ldd, r);
                    }
                }
            }
        }
    }
    fclose(geo);
}

ESTATICA leGeoEstatica(ESTATICA lse, char *arqGeo){

    FILE *geo = fopen(arqGeo,"r");

    if(geo == NULL){
        printf("ERRO! Arquivo .geo nao pode ser aberto\n");
        exit(1);
    }
    double x, y, w, h;
    int nx;
    char id[30], auxiliar[4], cp[30], cc[30];

    fscanf(geo, "%s", auxiliar);

    if(strcmp(auxiliar, "nx") == 0){
        fscanf(geo, "%d\n", &nx);
        lse = createEstatica(nx);
    }
    else{
        lse = createEstatica(20);
        printf("NX nao foi informado (default: 50)\n");
    }

    while(1){

        fscanf(geo, "%s", auxiliar);
        if(feof(geo))
            break;

        if(strcmp(auxiliar, "cp") == 0){
            fscanf(geo, "%s\n", cp);
            if(strcmp(cp, "@") == 0)
                strcpy(cp, "none");
        }
        else{
            if(strcmp(auxiliar, "cc") == 0){
                fscanf(geo, "%s\n", cc);
                if(strcmp(cc, "@") == 0)
                    strcpy(cc, "none");
            }
            else{
                if(strcmp(auxiliar, "r") == 0){
                    fscanf(geo, "%s %lf %lf %lf %lf\n", id, &x, &y, &w, &h);
                    RETANGULO r = criaRetangulo(id, x, y, w, h, cc, cp);
                    insertEstatica(lse, r);
                }
            }
        }
    }
    fclose(geo);

    return lse;
}
