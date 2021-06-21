#include "qryDinamica.h"

void executaQryDinamica(DINAMICA *din, char *arqQry, char *arqTxt){

    DINAMICA ldd = din[0];

    FILE *qry = fopen(arqQry, "r");

    if(qry == NULL){
        printf("Erro! Arquivo qry nao pode ser aberto!\n");
        exit(1);
    }

    char auxiliar[5], idDR[40], idBBID[40], idIID[40], idDIID[40];
    double xTPR, yTPR, wTPR, hTPR, xDPI, yDPI, xBBI, yBBI;
    int kIID, kDIID;

    while(1){

        fscanf(qry, "%s", auxiliar);
        if(feof(qry))
            break;

        if(strcmp(auxiliar, "tp") == 0){
            comando(arqTxt, "tp\n");
            tpDinamica(ldd, arqTxt);
        }
        else{
            if(strcmp(auxiliar, "tpr") == 0){
                fscanf(qry, "%lf %lf %lf %lf\n", &xTPR, &yTPR, &wTPR, &hTPR);
                comando(arqTxt, "tpr\n");
                tprDinamica(ldd, arqTxt, xTPR, yTPR, wTPR, hTPR);
            }
            else{
                if(strcmp(auxiliar, "dpi") == 0){
                    fscanf(qry, "%lf %lf\n", &xDPI, &yDPI);
                    comando(arqTxt, "dpi\n");
                    dpiDinamica(ldd, arqTxt, xDPI, yDPI);
                }
                else{
                    if(strcmp(auxiliar, "dr") == 0){
                        fscanf(qry, "%s\n", idDR);
                        comando(arqTxt, "dr\n");
                        drDinamica(ldd, arqTxt, idDR);
                    }
                    else{
                        if(strcmp(auxiliar, "bbi") == 0){
                            fscanf(qry, "%lf %lf\n", &xBBI, &yBBI);
                            comando(arqTxt, "bbi\n");
                            bbiDinamica(din, arqTxt, xBBI, yBBI);
                        }
                        else{
                            if(strcmp(auxiliar, "bbid") == 0){
                                fscanf(qry, "%s\n", idBBID);
                                comando(arqTxt, "bbid\n");
                                bbidDinamica(din, arqTxt, idBBID);
                            }
                            else{
                                if(strcmp(auxiliar, "iid") == 0){
                                    fscanf(qry, "%s %d\n", idIID, &kIID);
                                    comando(arqTxt, "iid ");
                                    iidDinamica(ldd, arqTxt, idIID, kIID);
                                }
                                else{
                                    if(strcmp(auxiliar, "diid") == 0){
                                        fscanf(qry, "%s %d\n", idDIID, &kDIID);
                                        comando(arqTxt, "diid ");
                                        diidDinamica(ldd, arqTxt, idDIID, kDIID);
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
}

void tpTprDinamica(DINAMICA din, char *txt, double x, double y, double w, double h, int opcao){ //opcao = 1(tpr) ou 0 (tp)

    char* corP[20] = {"darkmagenta", "dodgerblue", "deeppink", "lightgreen", "mediumblue", "olivedrab", "plum", "turquoise", "darkgreen", "slateblue"};
    int l = 0, c, cor = 0;
    NODE noB = NULL;
    FORMA formaB = NULL;
    FORMA formaA = NULL;
    RETANGULO delimitador = NULL;

    if(opcao == 1)
        delimitador = criaRetangulo("delimitador", x, y, w, h, "null", "null");

    for(NODE noA = getFirstDinamica(din); noA != NULL; noA = getNextDinamica(noA)){

        formaA = getFormaDinamica(noA);
        c = 0;

        for(noB = getFirstDinamica(din); noB != NULL; noB = getNextDinamica(noB)){

            formaB = getFormaDinamica(noB);

            if((l < c) && (retanguloCmp(formaA, formaB) != 1) && (retInterRet(formaA, formaB) == 1)){ //não vai compara um retangulo com ele mesmo

                if((opcao == 0) || ((opcao == 1) && (retDentroRet(delimitador, formaA) == 1) && (retDentroRet(delimitador, formaB) == 1))){
                    tpTpr(txt, getRetanguloID(formaA), getRetanguloID(formaB));
                    setRetanguloCP(formaA, corP[cor]);
                    setRetanguloCP(formaB, corP[cor]);
                    cor++;
                    if(cor == 10)
                        cor = 0;
                }
            }
            c++;
            contabilizaVisitaDinamica(din);
        }
        l++;
    }

    if(delimitador != NULL)
        free(delimitador);
}

void tpDinamica(DINAMICA din, char *txt){

    tpTprDinamica(din, txt, 0, 0, 0, 0, 0);
}

void tprDinamica(DINAMICA din, char *txt, double x, double y, double w, double h){

    tpTprDinamica(din, txt, x, y, w, h, 1);
}

void dpiDrDinamica(DINAMICA din, char *txt, FORMA forma, double x, double y, int opcao){ //opcao = 0 (dpi) ou 1 (dr)


    NODE noA, aux;
    FORMA formaA = NULL;

    for(noA = getFirstDinamica(din); noA != NULL;){

        formaA = getFormaDinamica(noA);

        aux = noA;

        if(((opcao == 0) && (pontoDentroRet(formaA, x, y))) || ((opcao == 1) && (retanguloCmp(formaA, forma) != 1) && (retDentroRet(forma, formaA)))){

            dpiDr(txt, getRetanguloID(formaA));
            noA = getNextDinamica(noA);
            removeDinamica(din, aux);
        }
        else
            noA = getNextDinamica(noA);
        contabilizaVisitaDinamica(din);
    }
}

void dpiDinamica(DINAMICA din, char *txt, double x, double y){

    dpiDrDinamica(din, txt, NULL, x, y, 0);
}

void drDinamica(DINAMICA din, char *txt, char *id){

    NODE noA;
    FORMA formaA;

    for(noA = getFirstDinamica(din); noA != NULL; noA = getNextDinamica(noA)){

        formaA = getFormaDinamica(noA);

        if(strcmp(getRetanguloID(formaA), id) == 0){

            dpiDrDinamica(din, txt, formaA, -1, -1, 1);
            return;
        }
        contabilizaVisitaDinamica(din);
    }
    printf("Id nao existente! Funcao dr falhou!");
    return;
}

void bbiBbidDinamica(DINAMICA *ldd, char *txt, FORMA forma, double x, double y, int opcao){ //opcao = 0 (bbi) ou 1 (bbid)

    DINAMICA din = ldd[0];
    NODE noA;
    FORMA formaA = NULL;
    FORMA BB = NULL;
    FORMA ponto = NULL;
    int bbi = 0, bbid = 0;
    char cc[20];
    double x1, x2, y1, y2;
    double w = 0, h = 0;

    for(noA = getFirstDinamica(din); noA != NULL; noA = getNextDinamica(noA)){

        formaA = getFormaDinamica(noA);

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
        contabilizaVisitaDinamica(din);
    }
    if((opcao == 0) && (bbi > 0)){
        BB = criaRetangulo("boundingbox", x1, y1, (x2 - x1), (y2 - y1), "red", "null");
        ponto = criaCirculo(x, y, 3, "blueviolet", "yellow");
        insertDinamica(ldd[1], BB);
        insertDinamica(ldd[2], ponto);

    }
    if((opcao == 1) && (bbid > 0)){
        BB = criaRetangulo("boundingbox", getRetanguloX(forma), getRetanguloY(forma), getRetanguloW(forma), getRetanguloH(forma), "red", "null");
        insertDinamica(ldd[1], BB);
    }
}

void bbiDinamica(DINAMICA *din, char *txt, double x, double y){

    bbiBbidDinamica(din, txt, NULL, x, y, 0);
}

void bbidDinamica(DINAMICA *ldd, char *txt, char *id){

    DINAMICA din = ldd[0];
    NODE noA;
    FORMA formaA;

    for(noA = getFirstDinamica(din); noA != NULL; noA = getNextDinamica(noA)){

        formaA = getFormaDinamica(noA);

        if(strcmp(getRetanguloID(formaA), id) == 0){

            bbiBbidDinamica(ldd, txt, formaA, -1, -1, 1);
            return;
        }
        contabilizaVisitaDinamica(din);
    }
    printf("Id nao existente! Funcao bbid falhou!");
    return;
}

void iidDiidDinamica(DINAMICA din, char *txt, NODE nodeA, int k, int opcao){ //opcao = 0 (iid) ou 1 (diid)

    NODE nodeB = nodeA;
    NODE aux;
    FORMA formaB = getFormaDinamica(nodeB);
    FORMA formaA = getFormaDinamica(nodeA);
    iidDiid(txt, getRetanguloID(formaA), getRetanguloX(formaA), getRetanguloY(formaA), getRetanguloW(formaA), getRetanguloH(formaA), getRetanguloCP(formaA), getRetanguloCC(formaA));
    int i = 0;

    if(k < 0){
        nodeB = getPreviousDinamica(nodeB);
        contabilizaVisitaDinamica(din);

        while(i > k){

            if(nodeB == NULL)
                break;

            aux = nodeB;
            formaB = getFormaDinamica(nodeB);
            iidDiid(txt, getRetanguloID(formaB), getRetanguloX(formaB), getRetanguloY(formaB), getRetanguloW(formaB), getRetanguloH(formaB), getRetanguloCP(formaB), getRetanguloCC(formaB));

            if(opcao == 1){
                nodeB = getPreviousDinamica(nodeB);
                removeDinamica(din, aux);
            }
            else
                nodeB = getPreviousDinamica(nodeB);

            i--;
            contabilizaVisitaDinamica(din);
        }
    }
    if(k > 0){
        nodeB = getNextDinamica(nodeB);
        contabilizaVisitaDinamica(din);

        while(i < k){

            if(nodeB == NULL)
                break;

            aux = nodeB;
            formaB = getFormaDinamica(nodeB);
            iidDiid(txt, getRetanguloID(formaB), getRetanguloX(formaB), getRetanguloY(formaB), getRetanguloW(formaB), getRetanguloH(formaB), getRetanguloCP(formaB), getRetanguloCC(formaB));

            if(opcao == 1){
                nodeB = getNextDinamica(nodeB);
                removeDinamica(din, aux);
            }
            else
                nodeB = getNextDinamica(nodeB);

            i++;
            contabilizaVisitaDinamica(din);
        }
    }
}

void iidDinamica(DINAMICA din, char *txt, char *id, int k){

    NODE noA;
    FORMA formaA;

    for(noA = getFirstDinamica(din); noA != NULL; noA = getNextDinamica(noA)){

        formaA = getFormaDinamica(noA);

        if(strcmp(getRetanguloID(formaA), id) == 0){

            iidDiidDinamica(din, txt, noA, k, 0);
            return;
        }
        contabilizaVisitaDinamica(din);
    }
    printf("Id nao existente! Funcao iid falhou!\n");
    return;
}

void diidDinamica(DINAMICA din, char *txt, char *id, int k){

    NODE noA;
    FORMA formaA;

    for(noA = getFirstDinamica(din); noA != NULL; noA = getNextDinamica(noA)){

        formaA = getFormaDinamica(noA);

        if(strcmp(getRetanguloID(formaA), id) == 0){

            iidDiidDinamica(din, txt, noA, k, 1);
            return;
        }
        contabilizaVisitaDinamica(din);
    }
    printf("Id nao existente! Funcao diid falhou!\n");
    return;
}
