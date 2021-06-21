#include "qryEstatica.h"

void executaQryEstatica(ESTATICA *estatica, char *arqQry, char *arqTxt, char *arqSvg){

    FILE *qry = fopen(arqQry, "r");

    if(qry == NULL){
        printf("Erro! Arquivo qry nao pode ser aberto!\n");
        exit(1);
    }

    char auxiliar[5], idDR[40], idBBID[40], idIID[40], idDIID[40];
    double xTPR, yTPR, wTPR, hTPR, xDPI, yDPI, xBBI, yBBI;
    int kIID, kDIID;

    ESTATICA lse = estatica[0];

    while(1){

        fscanf(qry, "%s", auxiliar);
        if(feof(qry))
            break;

        if(strcmp(auxiliar, "tp") == 0){
            comando(arqTxt, "tp\n");
            tpEstatica(lse, arqTxt);
        }
        else{
            if(strcmp(auxiliar, "tpr") == 0){
                fscanf(qry, "%lf %lf %lf %lf\n", &xTPR, &yTPR, &wTPR, &hTPR);
                comando(arqTxt, "tpr\n");
                tprEstatica(lse, arqTxt, xTPR, yTPR, wTPR, hTPR);
            }
            else{
                if(strcmp(auxiliar, "dpi") == 0){
                    fscanf(qry, "%lf %lf\n", &xDPI, &yDPI);
                    comando(arqTxt, "dpi\n");
                    dpiEstatica(lse, arqTxt, xDPI, yDPI);

                }
                else{
                    if(strcmp(auxiliar, "dr") == 0){
                        fscanf(qry, "%s\n", idDR);
                        comando(arqTxt, "dr\n");
                        drEstatica(lse, arqTxt, idDR);
                    }
                    else{
                        if(strcmp(auxiliar, "bbi") == 0){
                            fscanf(qry, "%lf %lf\n", &xBBI, &yBBI);
                            comando(arqTxt, "bbi\n");
                            bbiEstatica(estatica, arqTxt, xBBI, yBBI);
                        }
                        else{
                            if(strcmp(auxiliar, "bbid") == 0){
                                fscanf(qry, "%s\n", idBBID);
                                comando(arqTxt, "bbid\n");
                                bbidEstatica(estatica, arqTxt, idBBID);
                            }
                            else{
                                if(strcmp(auxiliar, "iid") == 0){
                                    fscanf(qry, "%s %d\n", idIID, &kIID);
                                    comando(arqTxt, "iid ");
                                    iidEstatica(lse, arqTxt, idIID, kIID);
                                }
                                else{
                                    if(strcmp(auxiliar, "diid") == 0){
                                        fscanf(qry, "%s %d\n", idDIID, &kDIID);
                                        comando(arqTxt, "diid ");
                                        diidEstatica(lse, arqTxt, idDIID, kDIID);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(qry);

    geraSvgEstatica(estatica, arqSvg);
}

void tpTprEstatica(ESTATICA est, char *txt, double x, double y, double w, double h, int opcao){ //opcao = 1(tpr) ou 0 (tp)

    char* corP[20] = {"darkmagenta", "dodgerblue", "deeppink", "lightgreen", "mediumblue", "olivedrab", "plum", "turquoise", "darkgreen", "slateblue"};
    int l = 0, c, cor = 0;
    NO noB = NULL;
    RETANGULO delimitador = NULL;

    if(opcao == 1)
        delimitador = criaRetangulo("delimitador", x, y, w, h, "null", "null");

    for(NO noA = getFirstEstatica(est); noA != NULL; noA = getNextEstatica(est, noA)){

        c = 0;

        for(noB = getFirstEstatica(est); noB != NULL; noB = getNextEstatica(est, noB)){

            if((l < c) && (retanguloCmp(getFormaEstatica(noA), getFormaEstatica(noB)) != 1) && (retInterRet(getFormaEstatica(noA), getFormaEstatica(noB)) == 1)){ //não vai compara um retangulo com ele mesmo

                if((opcao == 0) || ((opcao == 1) && (retDentroRet(delimitador, getFormaEstatica(noA)) == 1) && (retDentroRet(delimitador, getFormaEstatica(noB)) == 1))){

                    tpTpr(txt, getRetanguloID(getFormaEstatica(noA)), getRetanguloID(getFormaEstatica(noB)));
                    setRetanguloCP(getFormaEstatica(noA), corP[cor]);
                    setRetanguloCP(getFormaEstatica(noB), corP[cor]);
                    cor++;
                    if(cor == 10)
                        cor = 0;
                }
            }
            c++;
            contabilizaVisitaEstatica(est);
        }
        l++;
    }

    if(delimitador != NULL)
        free(delimitador);
}

void tpEstatica(ESTATICA lse, char *arqTxt){

    tpTprEstatica(lse, arqTxt, 0, 0, 0, 0, 0);
}

void tprEstatica(ESTATICA lse, char *arqTxt, double x, double y, double w, double h){

    tpTprEstatica(lse, arqTxt, x, y, w, h, 1);
}

void dpiDrEstatica(ESTATICA est, char *txt, FORMA forma, double x, double y, int opcao){ //opcao = 0 (dpi) ou 1 (dr)

    NO noA = getFirstEstatica(est);
    FORMA formaA;
    int i = getIndiceFirstEstatica(est), aux;

    while(i != -1){

        aux = i;
        formaA = getFormaEstatica(noA);

        if(((opcao == 0) && (pontoDentroRet(formaA, x, y))) || ((opcao == 1) && (retanguloCmp(formaA, forma) != 1) && (retDentroRet(forma, formaA)))){
            dpiDr(txt, getRetanguloID(formaA));
            noA = getNextEstatica(est, noA);
            i = getIndiceNextEstatica(est, i);
            removeEstatica(est, aux);
        }
        else{
            noA = getNextEstatica(est, noA);
            i = getIndiceNextEstatica(est, i);
        }

        if(i == -2){
            printf("ERRO! i == -2\n");
            break;
        }
    }
}

void dpiEstatica(ESTATICA est, char *txt, double x, double y){

    dpiDrEstatica(est, txt, NULL, x, y, 0);
}

void drEstatica(ESTATICA est, char *txt, char *id){

    NODE noA;
    FORMA formaA;

    for(noA = getFirstEstatica(est); noA != NULL; noA = getNextEstatica(est, noA)){

        formaA = getFormaEstatica(noA);

        if(strcmp(getRetanguloID(formaA), id) == 0){

            dpiDrEstatica(est, txt, formaA, -1, -1, 1);
            return;
        }
    }
    printf("Id nao existente! Funcao dr falhou!");
    return;
}

void bbiBbidEstatica(ESTATICA *estatica, char *txt, FORMA forma, double x, double y, int opcao){ //opcao = 0 (bbi) ou 1 (bbid)

    ESTATICA est = estatica[0];
    NO noA = getFirstEstatica(est);
    FORMA formaA;
    FORMA BB = NULL;
    FORMA ponto = NULL;
    int bbi = 0, bbid = 0, i = getIndiceFirstEstatica(est);
    char cc[20];
    double x1, x2, y1, y2;
    double w = 0, h = 0;

    while(i != -1){

        formaA = getFormaEstatica(noA);

        if(((opcao == 0) && (pontoDentroRet(formaA, x, y))) || ((opcao == 1) && (retanguloCmp(formaA, forma) != 1) && (retDentroRet(forma, formaA)))){

            bbiBbid(txt, getRetanguloID(formaA), getRetanguloCP(formaA), getRetanguloCC(formaA));
            strcpy(cc, getRetanguloCC(formaA));
            setRetanguloCC(formaA, getRetanguloCP(formaA));
            setRetanguloCP(formaA, cc);

            if(opcao == 0){
                if((w == 0) && (h == 0)){ //primeiro retangulo pra entrar no bounding box
                    w = getRetanguloW(formaA);
                    h = getRetanguloH(formaA);
                    x1 = getRetanguloX(formaA);
                    x2 = x1 + w;
                    y1 = getRetanguloY(formaA);
                    y2 = y1 + h;
                }
                else{
                    if(getRetanguloX(formaA) < x1)
                        x1 = getRetanguloX(formaA);
                    if(getRetanguloY(formaA) < y1)
                        y1 = getRetanguloY(formaA);
                    if((getRetanguloX(formaA) + getRetanguloW(formaA)) > x2)
                        x2 = getRetanguloX(formaA) + getRetanguloW(formaA);
                    if((getRetanguloY(formaA) + getRetanguloH(formaA)) > y2)
                        y2 = getRetanguloY(formaA) + getRetanguloH(formaA);
                }
                bbi++;
            }
            else
                bbid++;
        }
        noA = getNextEstatica(est, noA);
        i = getIndiceNextEstatica(est, i);

        if(i == -2){
            printf("ERRO! i == -2\n");
            break;
        }
    }

    if((opcao == 0) && (bbi > 0)){
        BB = criaRetangulo("boundingbox", x1, y1, (x2 - x1), (y2 - y1), "red", "null");
        insertEstatica(estatica[1], BB);

        ponto = criaCirculo(x, y, 3, "blueviolet", "yellow");
        insertEstatica(estatica[2], ponto);
    }
    if((opcao == 1) && (bbid > 0)){
        BB = criaRetangulo("boundingbox", getRetanguloX(forma), getRetanguloY(forma), getRetanguloW(forma), getRetanguloH(forma), "red", "null");
        insertEstatica(estatica[1], BB);
    }
}

void bbiEstatica(ESTATICA *estatica, char *txt, double x, double y){

    bbiBbidEstatica(estatica, txt, NULL, x, y, 0);
}

void bbidEstatica(ESTATICA *estatica, char *txt, char *id){

    ESTATICA est = estatica[0];

    NO noA = getFirstEstatica(est);
    FORMA formaA;
    int i = getIndiceFirstEstatica(est);

    while(i != -1){

        formaA = getFormaEstatica(noA);

        if(strcmp(getRetanguloID(formaA), id) == 0){

            bbiBbidEstatica(estatica, txt, formaA, 0, 0, 1);
            return;
        }
        noA = getNextEstatica(est, noA);
        i = getIndiceNextEstatica(est, i);

        if(i == -2){
            printf("ERRO! i == -2\n");
            break;
        }
    }
    printf("Id nao existente! Funcao bbid falhou!");
    return;
}

void iidDiidEstatica(ESTATICA est, char *txt, NO nodeA, int k, int opcao){ //opcao = 0 (iid) ou 1 (diid)

    NO nodeB;
    FORMA formaB;
    FORMA formaA = getFormaEstatica(nodeA);

    iidDiid(txt, getRetanguloID(formaA), getRetanguloX(formaA), getRetanguloY(formaA), getRetanguloW(formaA), getRetanguloH(formaA), getRetanguloCP(formaA), getRetanguloCC(formaA));
    int i = 0, indiceAux;
    int *indice = (int *) malloc(sizeof(int));
    *(indice) = -1;

    if(k < 0){
        nodeB = nodeA;
        nodeB = getPreviousEstatica(est, nodeB, indice);

        while(i > k){

            if(*(indice) == -1)
                break;

            indiceAux = *(indice);
            formaB = getFormaEstatica(nodeB);

            iidDiid(txt, getRetanguloID(formaB), getRetanguloX(formaB), getRetanguloY(formaB), getRetanguloW(formaB), getRetanguloH(formaB), getRetanguloCP(formaB), getRetanguloCC(formaB));

            if(opcao == 1){

                nodeB = getPreviousEstatica(est, nodeB, indice);
                removeEstatica(est, indiceAux);
            }
            else
                nodeB = getPreviousEstatica(est, nodeB, indice);

            i--;
        }
    }
    if(k > 0){
        nodeB = getFirstEstatica(est);
        *(indice) = getIndiceFirstEstatica(est);
        formaB = getFormaEstatica(nodeB);

        while(strcmp(getRetanguloID(formaB), getRetanguloID(getFormaEstatica(nodeA))) != 0){
            nodeB = getNextEstatica(est, nodeB);
            formaB = getFormaEstatica(nodeB);
            *(indice) = getIndiceNextEstatica(est, *(indice));
        }

        nodeB = getNextEstatica(est, nodeB);
        *(indice) = getIndiceNextEstatica(est, *(indice));

        while(i < k){

            if(*(indice) == -1)
                break;
            if(i == -2){
                printf("ERRO! i == -2\n");
                break;
            }

            indiceAux = *(indice);
            formaB = getFormaEstatica(nodeB);
            iidDiid(txt, getRetanguloID(formaB), getRetanguloX(formaB), getRetanguloY(formaB), getRetanguloW(formaB), getRetanguloH(formaB), getRetanguloCP(formaB), getRetanguloCC(formaB));

            if(opcao == 1){

                nodeB = getNextEstatica(est, nodeB);
                *(indice) = getIndiceNextEstatica(est, *(indice));
                removeEstatica(est, indiceAux);
            }
            else{
                nodeB = getNextEstatica(est, nodeB);
                *(indice) = getIndiceNextEstatica(est, *(indice));
            }
            i++;
        }
    }
    free(indice);
}

void iidEstatica(ESTATICA est, char *txt, char *id, int k){

    NO noA;
    FORMA formaA;

    for(noA = getFirstEstatica(est); noA != NULL; noA = getNextEstatica(est, noA)){

        formaA = getFormaEstatica(noA);

        if(strcmp(getRetanguloID(formaA), id) == 0){

            iidDiidEstatica(est, txt, noA, k, 0);
            return;
        }
    }
    printf("Id nao existente! Funcao dr falhou!");
    return;

}

void diidEstatica(ESTATICA est, char *txt, char *id, int k){

    NO noA;
    FORMA formaA;

    for(noA = getFirstEstatica(est); noA != NULL; noA = getNextEstatica(est, noA)){

        formaA = getFormaEstatica(noA);

        if(strcmp(getRetanguloID(formaA), id) == 0){

            iidDiidEstatica(est, txt, noA, k, 1);
            return;
        }
    }
    printf("Id nao existente! Funcao dr falhou!");
    return;
}
