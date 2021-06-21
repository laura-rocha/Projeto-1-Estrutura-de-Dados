#include "svg.h"

void iniciaSvg(char *arqSvg){

    FILE *svg = fopen(arqSvg, "w");

    if(svg == NULL){
        printf("ERRO! Arquivo .svg nao pode ser aberto\n");
        exit(1);
    }
    fprintf(svg, "<svg xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:cc=\"http://creativecommons.org/ns#\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:svg=\"http://www.w3.org/2000/svg\">\n");
    fclose(svg);
}

void finalizaSvg(char *arqSvg){

    FILE *svg = fopen(arqSvg, "a");

    if(svg == NULL){
        printf("ERRO! Arquivo .svg nao pode ser finalizado");
        exit(1);
    }
    fprintf(svg, "</svg>");
    fclose(svg);
}

void geraSvgDinamica(DINAMICA *din, char *arqSvg){

    iniciaSvg(arqSvg);

    FILE *arq = fopen(arqSvg, "a");
    DINAMICA ldd;
    NODE node;
    int indice;


    if(arq != NULL){

        for(indice = 0; indice < 3; indice++){

            ldd = din[indice];

            for(node = getFirstDinamica(ldd); node != NULL; node = getNextDinamica(node)){

                if(indice == 0){

                    RETANGULO ret = getFormaDinamica(node);
                    desenhaRetangulo(ret, arq);
                }
                else{
                    if(indice == 1){

                        RETANGULO ret = getFormaDinamica(node);
                        desenhaBoundingBox(ret, arq);
                    }
                    else{
                        if(indice == 2){
                            CIRCULO cir = getFormaDinamica(node);
                            desenhaCirculo(cir, arq, "");
                        }
                    }
                }
                contabilizaVisitaDinamica(din[indice]);
            }
        }
        fclose(arq);
    }
    finalizaSvg(arqSvg);
}

void geraSvgEstatica(ESTATICA *est, char *arqSvg){

    FILE *arq = fopen(arqSvg, "a");
    int indice;
    ESTATICA lse;

    if(arq != NULL){
        for(indice = 0; indice < 3; indice++){
            lse = est[indice];

            NO node = getFirstEstatica(lse);
            int i = getIndiceFirstEstatica(lse);

            while(i != -1){

                if(indice == 0){
                    RETANGULO ret = getFormaEstatica(node);
                    desenhaRetangulo(ret, arq);
                }
                else{
                    if(indice == 1){
                        RETANGULO ret = getFormaEstatica(node);
                        desenhaBoundingBox(ret, arq);
                    }
                    else{
                        if(indice == 2){
                            CIRCULO cir = getFormaEstatica(node);
                            desenhaCirculo(cir, arq, "");
                        }
                    }
                }
                node = getNextEstatica(lse, node);
                i = getIndiceNextEstatica(lse, i);
            }

        }
        fclose(arq);
    }
}

void desenhaRetangulo(RETANGULO ret, FILE *svg){

    double x, y, w, h;
    char cp[30], cc[30];

    x = getRetanguloX(ret);
    y = getRetanguloY(ret);
    w = getRetanguloW(ret);
    h = getRetanguloH(ret);
    strcpy(cp, getRetanguloCP(ret));
    strcpy(cc, getRetanguloCC(ret));

    fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width =\"1\"/>\n",x,y,w,h,cp,cc);
}

void desenhaBoundingBox(RETANGULO ret, FILE* svg){

    double x, y, w, h;
    char cc[20];

    x = getRetanguloX(ret);
    y = getRetanguloY(ret);
    w = getRetanguloW(ret);
    h = getRetanguloH(ret);
    strcpy(cc, getRetanguloCC(ret));

    fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"%s\" stroke-width =\"2\" stroke-dasharray=\"1\" />\n",x,y,w,h,cc);
}

void desenhaCirculo(CIRCULO cir, FILE* svg, char *extra){

    double x, y, raio;
    char cc[20], cp[20];

    x = getCirculoX(cir);
    y = getCirculoY(cir);
    raio = getCirculoRaio(cir);
    strcpy(cc, getCirculoCC(cir));
    strcpy(cp, getCirculoCP(cir));

    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" %s/>\n ", x, y, raio, cc, cp, extra);
}

void desenhaReta(FILE* svg, double x1, double y1, double x2, double y2, char *extra){

    fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" %s/>\n", x1, y1, x2, y2, extra);
}

void desenhaGrafico(char *arqSvg, char *arqTxt, char *titulo){

    iniciaSvg(arqSvg);
    FILE *svg = fopen(arqSvg, "a");
    FILE *txt = fopen(arqTxt, "r");

    if((svg == NULL) || (txt == NULL)){
        printf("Erro na abertura dos arquivos svg e txt. O grafico nao pode ser criado!\n");
        exit(1);
    }

    long int visitas, maiorVisitas = 0;
    int nx, maiorNx = 0;

    while(1){

        fscanf(txt, "%d", &nx);
        if(feof(txt))
            break;

        fscanf(txt, "%ld", &visitas);

        if((maiorNx == 0) && (maiorVisitas == 0)){
            maiorNx = nx;
            maiorVisitas = visitas;
        }
        else{
            if(nx > maiorNx)
                maiorNx = nx;
            if(visitas > maiorVisitas)
                maiorVisitas = visitas;
        }
    }

    fprintf(svg, "\t<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"1100\" style=\"stroke:black;stroke-width:3\"/>\n"); //eixo y
    fprintf(svg, "\t<line x1=\"0\" y1=\"1100\" x2=\"1100\" y2=\"1100\" style=\"stroke:black;stroke-width:3\"/>\n"); //eixo x
    fprintf(svg, "\t <polygon points=\"50,0 0,140 100,140\" style=\"fill:black;stroke-width:1\" transform=\"matrix(0.08434519,0,0,0.09895663,-4.2346553,-13.592225)\"/>\n"); //seta y
    fprintf(svg, "\t<polygon points=\"100,140 50,0 0,140\" style=\"fill:black;stroke-width:1\" transform=\"matrix(0,0.08434519,-0.09895663,0,1113.7288,1095.7166)\"/>\n"); //seta x
    fprintf(svg, "\t<text font-size=\"26\" x=\"1125\" y=\"1135\" fill=\"black\">Tamanho</text>\n");
    fprintf(svg, "\t<text font-size=\"26\" x=\"-98\" y=\"-18\" fill=\"black\">Visitas</text>\n");

    long int visitasAux = maiorVisitas;

    while(1){

        if(maiorVisitas <= 10){
            visitasAux = 10;
            break;
        }

        if(visitasAux % 100 == 0){
            break;
        }
        visitasAux = ((visitasAux / 10) + 1) * 10;
    }

    int fatorSomay = visitasAux / 10;
    long int aux = fatorSomay;

    int nxAux = maiorNx;

    while(1){

        if(maiorNx <= 10){
            nxAux = 10;
            break;
        }

        if(nxAux % 100 == 0){
            break;
        }
        nxAux = ((nxAux / 10) + 1) * 10;
    }
    int fatorSomax = nxAux / 10;
    int aux2 = fatorSomax;

    int i;
    long int yFator = 1000;
    int xFator = 0;

    for(i = 0; i < 10; i++){
        fprintf(svg, "\t<line x1=\"-8\" y1=\"%ld\" x2=\"8\" y2=\"%ld\" style=\"stroke:black;stroke-width:2\"/>\n", yFator, yFator);
        fprintf(svg, "\t<line x1=\"-5\" y1=\"%ld\" x2=\"5\" y2=\"%ld\" style=\"stroke:black;stroke-width:2\"/>\n", yFator + 50, yFator + 50);
        fprintf(svg, "\t<text font-size=\"20\" x=\"-120\" y=\"%ld\" fill=\"black\">%ld</text>\n", yFator, aux);
        yFator -= 100;
        aux += fatorSomay;

        fprintf(svg, "\t<line x1=\"%d\" y1=\"1095\" x2=\"%d\" y2=\"1105\" style=\"stroke:black;stroke-width:2\"/>\n", xFator + 50, xFator + 50);
        xFator += 100;
        fprintf(svg, "\t<line x1=\"%d\" y1=\"1092\" x2=\"%d\" y2=\"1108\" style=\"stroke:black;stroke-width:2\"/>\n", xFator, xFator);
        fprintf(svg, "\t<text font-size=\"20\" x=\"%d\" y=\"1135\" fill=\"black\">%d</text>\n", xFator, aux2);
        aux2 += fatorSomax;

    }
    fclose(svg);
    fclose(txt);

    svg = fopen(arqSvg, "a+");
    txt = fopen(arqTxt, "r");

    if(svg == NULL){
        printf("Erro na abertura dos arquivos svg. Os pontos nao podem ser plotados!\n");
        exit(1);
    }
    double x = 0;
    double y = 0;
    while(1){

        fscanf(txt, "%d", &nx);
        if(feof(txt))
            break;

        fscanf(txt, "%ld", &visitas);

        x = (nx * 1000) / (double) nxAux;
        y = (visitas * 1000) / (double) visitasAux;

        CIRCULO ponto = criaCirculo(x, y, 10, "black", "black");
        desenhaCirculo(ponto, svg, "transform=\"matrix(1,0,0,-1,0,1100)\"");
        desenhaReta(svg, 0, y, x, y, "transform=\"matrix(1,0,0,-1,0,1100)\" stroke-dasharray=\"10, 10\" stroke-width =\"2\" stroke=\"black\"");
        desenhaReta(svg, x, y, x, 0, "transform=\"matrix(1,0,0,-1,0,1100)\" stroke-dasharray=\"10, 10\" stroke-width =\"2\" stroke=\"black\"");
        free(ponto);

    }

    fprintf(svg, "\t<text font-size=\"45\" x=\"550\" y=\"1250\" fill=\"black\">%s</text>\n", titulo);

    fclose(svg);
    fclose(txt);
    finalizaSvg(arqSvg);
}
