#include <stdio.h>
#include <stdlib.h>
#include "libAux.h"


/* Função para ler os dados de entrada */
void leDados(int *m, int *n, int *p, int *q, int *k, int *qtdRotaOrigem, struct rota_t **rota, struct pacote_t **pacote)
{

    // ENTRADA - Ler os valores de n, m, k, q, p e outras informações do problema aqui
    if (scanf("%d %d %d %d %d", n, m, k, q, p) != 5)
    {
        fprintf(stderr, "Erro ao ler valores de n, m, k, q e p\n");
        exit(ERRLEITURA);
    }

    // Alocar memória para rota
    if((*rota = malloc(sizeof(struct rota_t)*(*m))) == NULL)
    {
        fprintf(stderr,"Erro ao alocar memória para rota\n");
        exit(ERRALOCA);
    }

    // m linhas com origem, destino, capacidade e k recursos
    int qtd = 0;
    for(int i = 0; i < *m; i++)
    {
        // ENTRADA - Ler origem, destino e capacidade da rota
        fscanf(stdin, "%d %d %d", &((*rota)[i].origem), &((*rota)[i].destino), &((*rota)[i].capacidade));
        // Contar rotas com origem em 1
        if((*rota)[i].origem == 1)
            qtd++;

        // Alocar memória para recursos de cada rota
        if(((*rota)[i].recursos = (int *)malloc(*k * sizeof(int))) == NULL)
        {
            fprintf(stderr,"Erro ao alocar memória para recursos do vetor de tranportes\n");
            exit(ERRALOCA);
        }

        // ENTRADA - Ler os recursos de cada rota
        for(int j = 0; j < *k; j++)
            fscanf(stdin, "%d", &((*rota)[i].recursos[j]));
    }

    // Qtd de rotas com origem em 1
    *qtdRotaOrigem = qtd;

    // Alocar memória para pacote
    if((*pacote = malloc(sizeof(struct pacote_t)*(*q))) == NULL)
    {
        fprintf(stderr,"Erro ao alocar memória para pacote\n");
        exit(ERRALOCA);
    }

    // q linhas com custo de cada pacote
        for(int i = 0; i < *q; i++)
        {
            // ENTRADA -Ler custo de cada pacote
            fscanf(stdin, "%d", &((*pacote)[i].custo));

            // Alocar memória para recursos de cada pacote
            if(((*pacote)[i].recursos = (int *)malloc(*k * sizeof(int))) == NULL)
            {
                fprintf(stderr,"Erro ao alocar memória para recursos do vetor de pacotes\n");
                exit(ERRALOCA);
            }

            // ENTRADA - k recursos
            for(int j = 0; j < *k; j++)
                fscanf(stdin, "%d", &((*pacote)[i].recursos[j]));
        }    
}


/* Função para imprimir a modelagem do problema linear */
void produzModelagemLP(int m, int n, int p, int q, int k, int qtdRotaOrigem, struct rota_t *rota, struct pacote_t *pacote)
{
    // Função Objetivo
    int qtdRota = qtdRotaOrigem;
    printf("max: ");
    for(int i = 0; i < m; i++)
    {
        if(rota[i].origem == 1 )
        {
            if(qtdRota == 1)
                printf("%dx%d%d", p, 1, rota[i].destino);
            else
                printf("%dx%d%d + ", p, 1, rota[i].destino);
            qtdRota--;
        }
    }
    for(int i = 0; i < q; i++)
        printf(" - %dy%d", pacote[i].custo, i+1);
    printf(";\n\n");
    
    
    // Restrições de capacidade
    for(int i = 0; i < m; i++)
        printf("- %d <= x%d%d <= %d;\n", rota[i].capacidade, rota[i].origem, rota[i].destino, rota[i].capacidade);
    printf("\n");

    qtdRota = qtdRotaOrigem;
    // Restrições de fluxo
    for(int i = 0; i < m; i++)
    {
        if(rota[i].origem == 1 && rota[i].flagUsada == 0)
        {
            rota[i].flagUsada = 1;
            printf("x%d%d ", rota[i].origem, rota[i].destino);
        }

        for(int j = 0; j < m; j++)
        {
            if(i != j)
                if(rota[j].destino == rota[i].destino)
                {
                    if(rota[j].flagUsada != 1)
                        printf("+ x%d%d ", rota[j].origem, rota[j].destino);
                }
        }

        if(qtdRota > 0)
        {
            printf("= ");
            
            for(int j = 0; j < m; j++)
            {
                if(i != j)
                    if(rota[j].origem == rota[i].destino)
                    {
                        if(rota[j].flagUsada != 1)
                        {
                            printf("x%d%d + ", rota[j].origem, rota[j].destino);
                            if(rota[j].destino == n)
                                rota[j].flagUsada = 1;
                        }
                    }
            }
            printf("0;\n");
        }
        qtdRota--;
    }
    printf("\n");

    // Faz modulo de xij
    for(int i = 0; i < m; i++)
    {
        printf("t%d%d >= 0;\n", rota[i].origem, rota[i].destino);
        printf("t%d%d >= x%d%d;\n", rota[i].origem, rota[i].destino, rota[i].origem, rota[i].destino);
        printf("t%d%d >= -x%d%d;\n", rota[i].origem, rota[i].destino, rota[i].origem, rota[i].destino);
    }
    printf("\n");


    // Restrições de recursos    
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(j != m-1)
            {
                printf("%dt%d%d + ", rota[j].recursos[i], rota[j].origem, rota[j].destino);
            }
            else
            {
                printf("%dt%d%d ", rota[j].recursos[i], rota[j].origem, rota[j].destino);
                printf("<= ");
            }
        }
        for(int j = 0; j < q; j++)
        {
            if(j != q-1)
                printf("%dy%d + ", pacote[j].recursos[i], j+1);
            else
                printf("%dy%d", pacote[j].recursos[i], j+1);
        }
        printf(";\n"); 
    }
    printf("\n");

    // Restrições de não negatividade
    for(int i = 1; i < q+1; i++)
        printf("y%d >= 0;\n", i);

}

/* Função para liberar memória alocada */
void modoUso(char *nomePrograma)
{
    fprintf(stderr, "Uso: %s < dadosEntrada.txt | lp_solve\n", nomePrograma);
    fprintf(stderr, "Uso: %s | lp_solve\n", nomePrograma);
    fprintf(stderr, "Uso: %s -f nomeArquivo.lp < dadosEntrada.txt | lp_solve\n", nomePrograma);
    fprintf(stderr, "Uso: %s -f nomeArquivo.lp | lp_solve\n", nomePrograma);
    exit(ERRLEITURA);
}