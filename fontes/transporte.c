#include <stdio.h>
#include <stdlib.h>
#include "libAux.h"


int main(int argc, char *argv[])
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

    // Ler dados de entrada
    leDados(&m, &n, &p, &q, &k, &qtdRotaOrigem, &rota, &pacote);

    // Produzir modelagem do problema linear
    if(argc == 3 && argv[1][1] == 'f') 
    {
        produzModelagemLPArquivo(m, n, p, q, k, qtdRotaOrigem, rota, pacote, argv[2]);
    }
    else
        produzModelagemLP(m, n, p, q, k, qtdRotaOrigem, rota, pacote);

    
    return 0;    
}
