#define ERRLEITURA -1
#define ERRALOCA -2

struct rota_t
{
    int origem;
    int destino;
    int *recursos;
    int capacidade;
    short int flagUsada;
};

struct pacote_t
{
    int *recursos;
    int custo;
} pacote_t;

/* Função para ler os dados de entrada */
void leDados(int *m, int *n, int *p, int *q, int *k, int *qtdRotaOrigem, struct rota_t **rota, struct pacote_t **pacote);

/* Função para imprimir a modelagem do problema linear */
void produzModelagemLP(int m, int n, int p, int q, int k, int qtdRotaOrigem, struct rota_t *rota, struct pacote_t *pacote);

/* Função para liberar memória alocada */
void modoUso(char *nomePrograma);