#include "quickSortExt.h"

void lerSup(FILE *arqlS, void *reg, int *lS, int nBytes, short int *ordem)
{
    //posiciona o cursor em lS*nBytes distante do início do arquivo
    //E armazena em reg o registro contido nessa posição
    fseek(arqlS, *(lS)*nBytes, SEEK_SET);
    fread(reg, nBytes, 1, arqlS);
    //decrementa o indicador
    (*lS)--;
    //indica que a próxima leitura é lerInf
    *ordem = 0;
}

void lerInf(FILE *arqlI, void *reg, int *lI, int nBytes, short int *ordem)
{
    /* posiciona o cursor em lI*nBytes distante do inicio do arquivo
    e armazena em reg o registro contido nessa posicao*/
    fseek(arqlI, *(lI)*nBytes, SEEK_SET);
    fread(reg, nBytes, 1, arqlI);
    //incrementa o indicador
    (*lI)++;
    //indica que a próxima leitura é lerSup
    *ordem = 1;
}

void escSup(FILE *arqES, void *reg, int *eS, int nBytes)
{
    //posiciona o cursor em eS*nBytes distante do início do arquivo
    //E escreve nessa posição o conteúdo de reg
    fseek(arqES, *(eS)*nBytes, SEEK_SET);
    fwrite(reg, 1, nBytes, arqES);
    //decrementa o indicador
    (*eS)--;
}

void escInf(FILE *arqEI, void *reg, int *eI, int nBytes)
{
    //posiciona o cursor em eI*nBytes distante do início do arquivo
    //E escreve nessa posição o conteúdo de reg
    fseek(arqEI, *(eI)*nBytes, SEEK_SET);
    fwrite(reg, nBytes, 1, arqEI);
    //incrementa o indicador
    (*eI)++;
}

void inserirArea(void *area, int *areaOcupada, void *reg,int nBytes, int(*comp)(void*,void*))
{
    int i = *areaOcupada;
    //Insere o registro de forma ordenada na memória primária
    //Deslocando para direita os registros de valor maior que o registro que será inserido
    while(i > 0)
    {
        if(comp(area + ((i-1)*nBytes), reg) == 1)
            memcpy(area + (i*nBytes), area + ((i-1)*nBytes), nBytes);
        else
            break;
        i--;
    }
    //incrementa areaOcupada
    memcpy(area + (i*nBytes), reg, nBytes);
    (*areaOcupada)++;
}

void rmvPrimeiroArea(void *area, int *areaOcupada, int nBytes)
{
    int i = 0;
    //Remove o primeiro registro da memória primária
    //Desloca o vetor em uma posição para esquerda
    for(i = 0;i < *areaOcupada; i++)
        memcpy(area + (i*nBytes), area + ((i+1)*nBytes), nBytes);
    //Decrementa areaOcupada
    (*areaOcupada)--;
}

void particao(FILE *arq,int inicio, int fim, int *i, int *j, int tamArea, int nBytes, int(*comp)(void*,void*))
{
    /* aloca espaco na memoria primaria */
    void *area = calloc(tamArea, nBytes);
    int areaOcupada = 0;

    int k = 0;

    /* variaveis que indicam posicao */
    int lI = inicio;    /* leitura inferior */
    int lS = fim;       /* leitura superior */
    int eI = inicio;    /* escrita inferior */
    int eS = fim;       /* escrita Superior */

    /*variavel que indica a ordem de leitura*/
    unsigned short int ordem = 1;

    /* Armazenam os limites superiores e inferiores da memoria primaria */
    void *limInf = calloc(1, nBytes);
    void *limSup = calloc(1, nBytes);

    /* Flag que indica se limSup teve seu valor alterado*/
    short int lmSupDif = 0;

    /* Flag que indica se limInf teve seu valor alterado */
    short int lmInfDif = 0;

    /*Armazena o registro lido/escrito*/
    void *registro = calloc(1, nBytes);

    while(lS >= lI)
    {
        if(areaOcupada + 1 < tamArea)
        {
            /* Preenche a area na memoria principal ate areaOcupada = tamArea - 1
            Lendo de forma alternada entre Leitura Superior e Leitura Inferior */
            if(ordem == 1)
                lerSup(arq, registro, &lS, nBytes, &ordem);
            else
                lerInf(arq, registro, &lI, nBytes, &ordem);

            inserirArea(area, &areaOcupada, registro, nBytes, comp);
        }
        else
        {
            /* Interrompe, se necessario, a ordem alternada de leitura para evitar que dados sejam sobrescritos */
            if(lI == eI)
                lerInf(arq, registro, &lI, nBytes, &ordem);
            else if(lS == eS)
                lerSup(arq, registro, &lS, nBytes, &ordem);
            else
            {
                /* Ordem alternada de leitura */
                if(ordem == 1)
                    lerSup(arq, registro, &lS, nBytes, &ordem);
                else
                    lerInf(arq, registro, &lI, nBytes, &ordem);
            }
            /* Verifica se o valor lido esta dentro dos limites de valor da memoria primaria
            Se nao tiver sera escrito na memoria secundaria sem ser armazenado na memoria primaria */
            if((lmSupDif == 1) && (comp(registro, limSup) == 1))
            {
                (*j) = eS;
                escSup(arq, registro, &eS, nBytes);
            }
            else if((lmInfDif == 1) && (comp(registro, limInf) == -1))
            {
                (*i) = eI;
                escInf(arq, registro, &eI, nBytes);
            }
            else
            {
                /* Valor dentro dos limites superior e inferior
                armazena na memoria primaria */
                inserirArea(area, &areaOcupada, registro, nBytes, comp);
                /* memoria primaria cheia */
                if(eI - inicio < fim - eS)
                {
                    /* Se a area a esquerda for menor remove o menor registro da memoria primaria
                    Escreve esse registro na memoria secundaria
                    atribui a limInf o valor desse registro */
                    escInf(arq, area, &eI, nBytes);
                    memcpy(limInf, area, nBytes);
                    /* Muda flag para 1(valor alterado) */
                    lmInfDif = 1;
                    rmvPrimeiroArea(area, &areaOcupada, nBytes);
                }
                else
                {
                    /* senao remove o registro de maior valor da memoria primaria
                    Escreve esse registro na memoria secundaria
                    atribui a limSup o valor desse registro */
                    escSup(arq, area + ((areaOcupada-1)*nBytes), &eS, nBytes);
                    memcpy(limSup, area + ((areaOcupada-1)*nBytes), nBytes);
                    /* Muda flag para 1(valor alterado) */
                    lmSupDif = 1;
                    areaOcupada--;
                }
            }
        }
    }
    /* Escreve no arquivo enquanto houver registros na memoria primaria
    Escrita realizada na posicao indicada por eI */
    for(k = 0; k < areaOcupada; k++)
        escInf(arq, area + (k*nBytes), &eI, nBytes);
}

void quickSortExterno(FILE *arq, int inicio, int fim, int tamArea, int nBytes, int (comp)(void*,void*))
 {
    int i = inicio - 1;
    int j = fim + 1;
    /* Se a area tiver mais que 1 registro */
    if(fim - inicio > 1)
    {
        /* chama particao para a area do arquivo */
        particao(arq, inicio, fim, &i, &j, tamArea, nBytes, comp);
        /* Verifica qual das areas nao ordenadas eh menor */
        if((i - inicio) > (fim - j))
        {
            quickSortExterno(arq, j, fim, tamArea, nBytes, comp);
            quickSortExterno(arq, inicio, i, tamArea, nBytes, comp);
        }
        else
        {
            quickSortExterno(arq, inicio, i, tamArea, nBytes, comp);
            quickSortExterno(arq, j, fim, tamArea, nBytes, comp);
        }

    }
 }
