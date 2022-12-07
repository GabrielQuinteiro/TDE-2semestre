#include "quickSortExt.h"

#define MAX_L 100
#define TAMAREA 15
#define TEMP "temp.bin"
#define ARQUIVO "20220509_leitos_ocupados_por_unidade_hospitalar.csv"
#define BUFFER 1024

typedef struct
{
    char drs[MAX_L];
    char municipio[MAX_L];
    char US[MAX_L];
    char nomeMedida[MAX_L];
    int valoresMedida;
}Base;

int comparaCrescente(void *a, void *b);
int comparaDecrescente(void *a, void *b);
void geraArquivo(FILE *arq, FILE *temp, int nElem);
int contaLinhas(FILE *arq);

int main()
{
    FILE *arq, *temp;

    if((arq = fopen(ARQUIVO, "r")) == NULL) return 1;
    temp = fopen(TEMP, "wb+");
    Base b;
    int li = 0;
    short int o = 0;

    int tamArq = contaLinhas(arq);

    geraArquivo(arq, temp, tamArq);
    printf("=========================================================================================================================================================================================\n");
    printf("| %-24s | %-23s | %-76s | %-28s | %-18s |\n", "DRS", "Municipio", "Unidade de Saude", "Nome de Medida", "Valores de Medida");
    printf("=========================================================================================================================================================================================\n");
    while(li < tamArq)
    {
        lerInf(temp, (void*)(&b), &li, sizeof(Base), &o);
        printf("| %-24s | %-23s | %-76s | %-28s | %-18d |\n", b.drs, b.municipio, b.US, b.nomeMedida, b.valoresMedida);
    }
   printf("=========================================================================================================================================================================================\n");
    #ifdef OS_Windows
    system("pause");
    #else
    system("echo 'Pressione enter para continuar...'; read dummy;");
    #endif
    
    int opcao;
    do
    {
        #ifdef OS_Windows
        system("cls");
        #else
        system("clear");
        #endif
        
        printf("=======================================================\n");
        printf("|                 Escolha uma opcao                   |\n");
        printf("|=====================================================|\n");
        printf("| 1. Ordenacao Decrescente                            |\n");
        printf("|-----------------------------------------------------|\n");
        printf("| 2. Ordenacao Crescente                              |\n");
        printf("|-----------------------------------------------------|\n");
        printf("| 0. Sair                                             |\n");
        printf("=======================================================\n");
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            #ifdef OS_Windows
            system("cls");
            #else
            system("clear");
            #endif
            
            quickSortExterno(temp, 0, tamArq, TAMAREA, sizeof(Base), comparaDecrescente);
            li = 0;
            printf("=========================================================================================================================================================================================\n");
            printf("| %-24s | %-23s | %-76s | %-28s | %-18s |\n", "DRS", "Municipio", "Unidade de Saude", "Nome de Medida", "Valores de Medida");
            printf("=========================================================================================================================================================================================\n");

            while(li < tamArq)
            {
                lerInf(temp, (void*)(&b), &li, sizeof(Base), &o);
                printf("| %-24s | %-23s | %-76s | %-28s | %-18d |\n", b.drs, b.municipio, b.US, b.nomeMedida, b.valoresMedida);
            }
                printf("=========================================================================================================================================================================================\n");
                #ifdef OS_Windows
                system("pause");
                #else
                system("echo 'Pressione enter para continuar...'; read dummy;");
                #endif
        }
        else if(opcao == 2)
        {
            #ifdef OS_Windows
            system("cls");
            #else
            system("clear");
            #endif
            
            quickSortExterno(temp, 0, tamArq, TAMAREA, sizeof(Base), comparaCrescente);
            li = 0;
            printf("=========================================================================================================================================================================================\n");
            printf("| %-24s | %-23s | %-76s | %-28s | %-18s |\n", "DRS", "Municipio", "Unidade de Saude", "Nome de Medida", "Valores de Medida");
            printf("=========================================================================================================================================================================================\n");

            while(li < tamArq)
            {
                lerInf(temp, (void*)(&b), &li, sizeof(Base), &o);
                printf("| %-24s | %-23s | %-76s | %-28s | %-18d |\n", b.drs, b.municipio, b.US, b.nomeMedida, b.valoresMedida);
            }
            printf("=========================================================================================================================================================================================\n");
            #ifdef OS_Windows
            system("pause");
            #else
            system("echo 'Pressione enter para continuar...'; read dummy;");
            #endif
        }
        else if(opcao == 0)
        {
            #ifdef OS_Windows
            system("cls");
            #else
            system("clear");
            #endif
            
            printf("=======================================================\n");
            printf("|                  Fim do Programa!                   |\n");
            printf("=======================================================\n");
        }
        else
        {
            #ifdef OS_Windows
            system("cls");
            #else
            system("clear");
            #endif
            
            printf("\nInsira um valor valido!\n");
            #ifdef OS_Windows
            system("pause");
            #else
            system("echo 'Pressione enter para continuar...'; read dummy;");
            #endif

        }
    }while(opcao != 0);

    fclose(arq);
    fclose(temp);
    remove(TEMP);
    return 0;
}

int contaLinhas(FILE *f)
{
    int linhas = 0;

    char conta;
    while((conta = fgetc(f))!= EOF)
    {
        if(conta == '\n') linhas++;
    }

    return linhas - 1;
}

int comparaCrescente(void *a, void *b)
{
    Base* elemento1 = (Base*)a;
    Base* elemento2 = (Base*)b;
    int result;

    if (elemento2->valoresMedida < elemento1->valoresMedida)
    {
        return 1;
    }
    else if (elemento2->valoresMedida > elemento1->valoresMedida)
    {
        return -1;
    }
    else
    {
        result = strcmp(elemento1->drs, elemento2->drs);
        if (result == 1) /* elemento2->drs < elemento1->drs */
        {
            return 1;
        }
        else if (result == 0) /* elemento2->drs > elemento1->drs) */
        {
            return -1;
        }
        else
        {
            result = strcmp(elemento2->municipio, elemento1->municipio);
            if (result == 0) /* elemento2->municipio > elemento1->municipio) */
            {
                return 1;
            }
            else if (result == 1) /* elemento2->municipio < elemento1->municipio) */
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }
}

int comparaDecrescente(void *a, void *b)
{
    Base* elemento1 = (Base*)a;
    Base* elemento2 = (Base*)b;
    int result;

    if (elemento2->valoresMedida < elemento1->valoresMedida)
    {
        return -1;
    }
    else if (elemento2->valoresMedida > elemento1->valoresMedida)
    {
        return 1;
    }
    else
    {
        result = strcmp(elemento1->drs, elemento2->drs);
        if (result == 0) /* elemento2->drs < elemento1->drs */
        {
            return -1;
        }
        else if (result == 1) /* elemento2->drs > elemento1->drs) */
        {
            return 1;
        }
        else
        {
            result = strcmp(elemento2->municipio, elemento1->municipio);
            if (result == 1) /* elemento2->municipio > elemento1->municipio) */
            {
                return -1;
            }
            else if (result == 0) /* elemento2->municipio < elemento1->municipio) */
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

void geraArquivo(FILE *arq, FILE *temp, int nElem)
{
    Base *b = (Base*)calloc(192, sizeof(Base));
    char buffer[BUFFER], *sp;
    int lCount = 0, i = 0;
    rewind(temp);
    rewind(arq);

    while(fgets(buffer, BUFFER, arq) != NULL)
    {
        lCount++;
        if(lCount == 1) /* descarta cabeçalho */
        {
            continue;
        }
        sp = strtok(buffer, ";");
        strcpy(b[i].drs, sp);

        sp = strtok(NULL,";");
        strcpy(b[i].municipio, sp);

        sp = strtok(NULL,";");
        strcpy(b[i].US, sp);

        sp = strtok(NULL,";");
        strcpy(b[i].nomeMedida, sp);

        sp = strtok(NULL,";");
        b[i].valoresMedida = atoi(sp); /* converte o char em int */

        i++;
    }
    fwrite(b, sizeof(Base), nElem, temp);
}
