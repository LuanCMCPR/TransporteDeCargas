#include <stdio.h>
#include <stdlib.h>

#define ERRLEITURA -1
#define ERRALOCA -2

struct rota_t
{
    int origem;
    int destino;
    int *recursos;
    int capacidade;
};

struct pacote_t
{
    int *recursos;
    int custo;
} pacote_t;

int main()
{
    //  Variáveis
    int n, // Qtd Cidades
        m, // Qtd Rotas
        k, // Qtd Recursos
        q, // Qtd Tipos de pacotes
        p, // Preço do combustível
        qtdRotaOrigem; // Qtd de rotas que saem da cidade 1 (Origem)
    struct rota_t *rota; // Vetor de transporte
    struct pacote_t *pacote; // Vetor de pacotes

    // Ler os valores de n, m, k, q, p e outras informações do problema aqui

    if (scanf("%d %d %d %d %d", &n, &m, &k, &q, &p) != 5)
    {
        fprintf(stderr, "Erro ao ler valores de n, m, k, q e p\n");
        exit(ERRLEITURA);
    }

    if((rota = malloc(sizeof(struct rota_t)*m)) == NULL)
    {
        fprintf(stderr,"Erro ao alocar memória para rota\n");
        exit(ERRALOCA);
    }

    // ENTRADA - m linhas com origem, destino, capacidade e k recursos
    for(int i = 0; i < m; i++)
    {
        fscanf(stdin, "%d %d %d", &(rota[i].origem), &(rota[i].destino), &(rota[i].capacidade));
        if(rota[i].origem == 1)
            qtdRotaOrigem++;
        if((rota[i].recursos = (int *)malloc(k * sizeof(int))) == NULL)
        {
            fprintf(stderr,"Erro ao alocar memória para recursos do vetor de tranportes\n");
            exit(ERRALOCA);
        }
        for(int j = 0; j < k; j++)
            fscanf(stdin, "%d", &(rota[i].recursos[j]));
    }

    if((pacote = malloc(sizeof(struct pacote_t)*q)) == NULL)
    {
        fprintf(stderr,"Erro ao alocar memória para pacote\n");
        exit(ERRALOCA);
    }

    // ENTRADA - q linhas com custo de cada pacote
    for(int i = 0; i < q; i++)
    {
        fscanf(stdin, "%d", &pacote[i].custo);
        if((pacote[i].recursos = (int *)malloc(k * sizeof(int))) == NULL)
        {
            fprintf(stderr,"Erro ao alocar memória para recursos do vetor de pacotes\n");
            exit(ERRALOCA);
        }
        // ENTRADA - k recursos
        for(int j = 0; j < k; j++)
            fscanf(stdin, "%d", &pacote[i].recursos[j]);
    }


    FILE *arq;
    arq = fopen("entrada.lp", "w");
    
    fprintf(arq, "max: ");
    for(int i = 0; i < m; i++)
    {
        if(rota[i].origem == 1)
            fprintf(arq, "%dx%d%d + ", p, 1, rota[i].destino);
    }
        fprintf(arq, " 0");

    for(int i = 0; i < q; i++)
        fprintf(arq, " - %dy%d", pacote[i].custo, i+1);
    fprintf(arq, ";\n");

    for(int i = 0; i < m; i++)
        fprintf(arq, " - %d <= x%d%d <= %d\n", rota[i].capacidade, rota[i].origem, rota[i].destino, rota[i].capacidade);

    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(j != m-1)
            {
                fprintf(arq, "%dx%d%d + ", rota[j].recursos[i], rota[j].origem, rota[j].destino);
            }
            else
            {
                fprintf(arq, "%dx%d%d ", rota[j].recursos[i], rota[j].origem, rota[j].destino);
                fprintf(arq, "<= ");
            }
        }
        for(int j = 0; j < q; j++)
        {
            {
                if(j != q-1)
                    fprintf(arq, "%dy%d + ", pacote[j].recursos[i], i+1);
                else
                    fprintf(arq, "%dy%d", pacote[j].recursos[i], i+1);
            }
        }
        fprintf(arq, ";\n"); 
    }
    for(int i = 1; i < q+1; i++)
        fprintf(arq, "y%d >= 0;\n", i); 
    return 0;

    fclose(arq);
}
