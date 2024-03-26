#include <stdio.h>
#include <stdlib.h>

#define ERRLEITURA -1
#define ERRALOCA -2

struct rota_t
{
    int origem;
    int destino;
};

struct pacote_t
{
    int *recursos;
    int custo;
} pacote_t;

typedef struct transporte_t
{
    struct rota_t *rota;
    int *recursos;
    int capacidade;
} transporte_t;

int main()
{
    //  Variáveis
    int n, // Qtd Cidades
        m, // Qtd Rotas
        k, // Qtd Recursos
        q, // Qtd Tipos de pacotes
        p; // Preço do combustível

    struct transporte_t *transporte; // Vetor de transporte
    struct pacote_t *pacote; // Vetor de pacotes

    // Ler os valores de n, m, k, q, p e outras informações do problema aqui

    if (scanf("%d %d %d %d %d", &n, &m, &k, &q, &p) != 5)
    {
        fprintf(stderr, "Erro ao ler valores de n, m, k, q e p\n");
        exit(ERRLEITURA);
    }

    if((transporte = malloc(sizeof(struct transporte_t*)*m) == NULL))
    {
        fprintf(stderr,"Erro ao alocar memória para transporte\n");
        exit(ERRALOCA);
    }

    // ENTRADA - m linhas com origem, destino, capacidade e k recursos
    for(int i = 0; i < m; i++)
    {
        fscanf(stdin, "%d %d %d", &(transporte[i].rota->origem), &(transporte[i].rota->destino), &(transporte[i].capacidade));
        if((transporte[i].recursos = (int *)malloc(k * sizeof(int)) == NULL))
        {
            fprintf(stderr,"Erro ao alocar memória para recursos do vetor de tranportes\n");
            exit(ERRALOCA);
        }
        for(int j = 0; j < k; j++)
            fscanf(stdin, "%d", &(transporte[i].recursos[j]));
    }

    if((pacote = malloc(sizeof(struct pacote_t)*q) == NULL))
    {
        fprintf(stderr,"Erro ao alocar memória para pacote\n");
        exit(ERRALOCA);
    }

    // ENTRADA - q linhas com custo de cada pacote
    for(int i = 0; i < q; i++)
    {
        fscanf(stdin, "%d", &pacote[i].custo);
        if((pacote[i].recursos = (int *)malloc(k * sizeof(int)) == NULL))
        {
            fprintf(stderr,"Erro ao alocar memória para recursos do vetor de pacotes\n");
            exit(ERRALOCA);
        }
        // ENTRADA - k recursos
        for(int j = 0; j < k; j++)
            fscanf(stdin, "%d", &pacote[i].recursos[j]);
    }

    return 0;
}
