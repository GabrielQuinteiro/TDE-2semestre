#ifndef _H_QUICKSORTEXT
#define _H_QUICKSORTEXT

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

/* Retornos da funcao de comparacao
   int comp(a,b)
   a>b    1
   a==b    0
   a<b    -1
*/

/*  void lerSup:
        Acao: Le nBytes do arquivo apontado por arqLS na posicao lS*nBytes distante do inicio do arquivo, armazena os dados lidos em reg, decrementa lS e
altera ordem para 0.
        Argumentos:
            - FILE *arqLS - ponteiro para o arquivo onde sera realizada a leitura.
            - void *reg - ponteiro da variavel que armazenara os dados lidos.
            - int *lS - ponteiro para inteiro que indica a posicao a ser lida.
            - int nBytes - variavel que indica o tamanho dos registros.
            - short int *ordem - ponteiro para inteiro (short) que indica qual sera a proxima leitura(1 para lerSup e 0 para lerInf).
        Retorno: Sem retorno.
*/
void lerSup(FILE *arqlS, void *reg, int *lS, int nBytes, short int *ordem);

/*  void lerInf:
        Acao: Le nBytes do arquivo apontado por arqLI na posicao lI*nBytes distante do inicio do arquivo, armazena os dados lidos em reg, incrementa lI e
altera ordem para 1.
        Argumentos:
            - FILE *arqLI - ponteiro para o arquivo onde sera realizada a leitura.
            - void *reg - ponteiro da variavel que armazenara os dados lidos.
            - int *lI - ponteiro para inteiro que indica a posicao a ser lida.
            - int nBytes - variavel que indica o tamanho dos registros.
            - short int *ordem - ponteiro para inteiro (short) que indica qual será a próxima leitura(1 para lerSup e 0 para lerInf).
        Retorno: Sem retorno.
*/
void lerInf(FILE *arqlI, void *reg, int *lI, int nBytes, short int *ordem);

/*  void escSup:
        Acao: Escreve nBytes da variavel reg no arquivo apontado por arqES na posicao eS*nBytes distante do inicio do arquivo e decrementa eS.
        Argumentos:
            - FILE *arqES - ponteiro para o arquivo onde sera realizada a escrita.
            - void *reg - ponteiro da variavel que tera seus dados escritos no arquivo.
            - int *eS - ponteiro para inteiro que indica a posicao a ser escrita.
            - int nBytes - variavel que indica o tamanho dos registros.
        Retorno: Sem retorno.
*/
void escSup(FILE *arqES, void *reg, int *eS, int nBytes);

/*  void escInf:
        Acao: Escreve nBytes da variavel reg no arquivo apontado por arqEI na posicao eI*nBytes distante do inicio do arquivo e incrementa eI.
        Argumentos:
            - FILE *arqEI - ponteiro para o arquivo onde sera realizada a escrita.
            - void *reg - ponteiro da variavel que terao seus dados escritos no arquivo.
            - int *eI - ponteiro para inteiro que indica a posicao a ser escrita.
            - int nBytes - variavel que indica o tamanho dos registros.
        Retorno: Sem retorno.
*/
void escInf(FILE *arqEI, void *reg, int *eI, int nBytes);

/*  void inserirArea:
        Acao: Insere a variavel reg de forma ordenada na area da memoria primaria apontada por area e incrementa areaOcupada.
        Argumentos:
            - void *area - ponteiro da area da memoria primaria.
            - int *areaOcupada - ponteiro para inteiro da variavel que armazena a area ocupada da memoria primaria.
            - void *reg - ponteiro da variavel que sera armazenada na area.
            - int nBytes - variavel que indica o tamanho dos registros.
            - int(*comp)(void*,void*) - ponteiro para a funcao de comparacao.
        Retorno: Sem retorno.
*/
void inserirArea(void *area, int *areaOcupada, void *reg, int nBytes, int(*comp)(void*,void*));

/*  void rmvPrimeiroArea:
        Acao: Remove o primeiro elemento armazenado na area da memoria primaria apontada por area e decrementa areaOcupada.
        Argumentos:
            - void *area - ponteiro da area da memoria primaria.
            - int *areaOcupada - ponteiro para inteiro da variavel que armazena a area ocupada da memoria primaria.
            - int nBytes - variavel que indica o tamanho dos registros.
        Retorno: Sem retorno.
*/
void rmvPrimeiroArea(void *area, int *areaOcupada, int nBytes);

/*  void particao:
        Acao: Particiona o arquivo apontado por arq em tras subarquivo:
        area 1 - Registros com o valor menor ou igual que o registro com o menor valor da area 2.
        area 2 - Registros ordenados.
        area 3 - Registros com o valor maior ou igual que o registro com o maior valor da area 2.
        Argumentos:
            - FILE *arq - ponteiro para o arquivo a ser particionado.
            - int inicio - inteiro que indica o primeiro elemento do vetor a ser particionado.
            - int fim - inteiro que indica o último elemento do vetor a ser particionado.
            - int *i - ponteiro para inteiro que indica o inicio da area 2.
            - int *j - ponteiro para inteiro que indica o fim da area 2.
            - int tamArea - inteiro que indica o tamanho da area na memoria principal.
            - int nBytes - variavel que indica o tamanho dos registros.
            - int(*comp)(void*,void*) - ponteiro para a funcao de comparacao.
        Retorno: Sem retorno.
*/
void particao(FILE *arq,int inicio, int fim, int *i, int *j, int tamArea, int nBytes, int(*comp)(void*,void*));

/*  void quickSortExterno:
        Acao: Ordena os registros do arquivo apontado por arq.
        Argumentos:
            - FILE *arq - ponteiro para o arquivo a ser ordenado.
            - int inicio - inteiro que indica o primeiro registro do arquivo a ser ordenado.
            - int fim - inteiro que indica o ultimo registro do arquivo a ser ordenado.
            - int tamArea - inteiro que indica o tamanho da área na memoria primaria.
            - int nBytes - variavel que indica o tamanho dos registros.
            - int(*comp)(void*,void*) - ponteiro para a funcao de comparacao.
        Retorno: Sem retorno.
*/
void quickSortExterno(FILE *arq, int inicio, int fim, int tamArea, int nBytes, int (comp)(void*,void*));

#endif
