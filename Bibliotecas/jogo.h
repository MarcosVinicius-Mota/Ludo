
#ifndef JOGO__H
#define JOGO__H

#include "tabuleiro.h"
#include "posicao.h"


typedef enum Cor
{
    VERDE,
    AMARELO,
    VERMELHO,
    AZUL
} Cor;

///struct do tipo peça
typedef struct
{
    ///Cordenada atual
    int coordenada;
    ///A casa de saída dela
    int coordenadaDeSaida;
    ///A casa de entrada da reta final
    int coordenadaDeEntrada;
    ///A coordenada do destino; Esse dado existe pois existem 4 coordenadas que levam no mesmo ponto na matriz de coordenada
    int coordenadaFinal;
    ///A coordenada da primeira casa colorida da passarela
    int primeiraCasaDeCor;
    ///Se a peça está na sua casa de inicio
    bool estaNaPosicaoInicial;
    ///Se a peça está em jogo. Esse valor muda para false quando uma peça chegar no final
    bool estaEmJogo;

    ///esses 2 membroa apenas guardam a posição inicial para facilitar na hora de voltar. ESSE VALOR NÃO É ALTERADO
    int posicao_linha;
    int posicao_coluna;

    ///verifica se 2 peças da mesma cor estão na mesma casa
    bool ehTorre;
    ///verifica se 2 peças de cores diferentes estão na mesma casa 
    bool estaSobreposta;
    ///Cor da peça com base no enum
    Cor cor;
    ///Letra que representa a peça
    char letra;

}Piece; //Peça

///Struct do tipo jogador
typedef struct
{
    ///Número de peças desse jogador que ainda estão em jogo
    int pecasEmJogo;
    ///Se esse jogador vai ou não jogar; usada para auxiliar no modo de 3 ou 2 jogadores
    bool vaiJogar;
    ///O vetor de peças de um jogador
    Piece piece[4];
    /// O nome do jogador
    char nome[20];
    ///Cor da peça
    Cor cor;

}Player;

///Pega as letras do tabuleiro e atribui no elemento letra da struct de peças
static void atualizarLetrasPieces(Player & p, char tabuleiro[LINHAS][COLUNAS])
{
    for(int j = 0; j < 4; j++)
    {
        if(p.vaiJogar)
            p.piece[j].letra = tabuleiro[p.piece[j].posicao_linha][p.piece[j].posicao_coluna];
        else
        {
            tabuleiro[p.piece[j].posicao_linha][p.piece[j].posicao_coluna] = '-';
            p.piece[j].letra = '-';
        }

    }


}

///IGNORE as 4 próximas
static void iniciarVerde(Player & p, char tabuleiro[LINHAS][COLUNAS])
{
    int j = 0;
    p.piece[j++].posicao_linha = 3;
    p.piece[j++].posicao_linha = 3;
    p.piece[j++].posicao_linha = 4;
    p.piece[j++].posicao_linha = 4;

    j = 0;
    p.piece[j++].posicao_coluna = 3;
    p.piece[j++].posicao_coluna = 4;
    p.piece[j++].posicao_coluna = 3;
    p.piece[j++].posicao_coluna = 4;

    for(j = 0; j < 4; j++)
    {
        p.piece[j].estaNaPosicaoInicial = true;
        p.piece[j].coordenadaDeSaida = 42;
        p.piece[j].coordenadaDeEntrada = 40;
        p.piece[j].coordenadaFinal = 73 + 6;
        p.piece[j].primeiraCasaDeCor = 73;
        p.piece[j].estaEmJogo = p.vaiJogar;

    }

    atualizarLetrasPieces(p, tabuleiro);
}

static void iniciarAmarelo(Player & p, char tabuleiro[LINHAS][COLUNAS])
{
    int j = 0;
    p.piece[j++].posicao_linha = 3;
    p.piece[j++].posicao_linha = 3;
    p.piece[j++].posicao_linha = 4;
    p.piece[j++].posicao_linha = 4;

    j = 0;
    p.piece[j++].posicao_coluna = 12;
    p.piece[j++].posicao_coluna = 13;
    p.piece[j++].posicao_coluna = 12;
    p.piece[j++].posicao_coluna = 13;

    for(j = 0; j < 4; ++j)
    {
        p.piece[j].estaNaPosicaoInicial = true;
        p.piece[j].coordenadaDeSaida = 3;
        p.piece[j].coordenadaDeEntrada = 1;
        p.piece[j].primeiraCasaDeCor = 52;
        p.piece[j].coordenadaFinal = 52 + 6;
        p.piece[j].estaEmJogo = p.vaiJogar;


    }

    atualizarLetrasPieces(p, tabuleiro);
}

static void iniciarAzul(Player & p, char tabuleiro[LINHAS][COLUNAS])
{
    int j = 0;
    p.piece[j++].posicao_linha = 12;
    p.piece[j++].posicao_linha = 12;
    p.piece[j++].posicao_linha = 13;
    p.piece[j++].posicao_linha = 13;

    j = 0;
    p.piece[j++].posicao_coluna = 12;
    p.piece[j++].posicao_coluna = 13;
    p.piece[j++].posicao_coluna = 12;
    p.piece[j++].posicao_coluna = 13;

    for(j = 0; j < 4; j++)
    {

        p.piece[j].estaNaPosicaoInicial = true;
        p.piece[j].coordenadaDeSaida = 16;
        p.piece[j].coordenadaDeEntrada = 14;
        p.piece[j].primeiraCasaDeCor = 59;
        p.piece[j].coordenadaFinal = 59 + 6;
        p.piece[j].estaEmJogo = p.vaiJogar;

    }

    atualizarLetrasPieces(p, tabuleiro);

}

static void iniciarVermelho(Player & p, char tabuleiro[LINHAS][COLUNAS])
{
    int j = 0;

    p.piece[j++].posicao_linha = 12;
    p.piece[j++].posicao_linha = 12;
    p.piece[j++].posicao_linha = 13;
    p.piece[j++].posicao_linha = 13;

    j = 0;
    p.piece[j++].posicao_coluna = 3;
    p.piece[j++].posicao_coluna = 4;
    p.piece[j++].posicao_coluna = 3;
    p.piece[j++].posicao_coluna = 4;

    for(j = 0; j < 4; j++)
    {
        p.piece[j].estaNaPosicaoInicial = true;
        p.piece[j].coordenadaDeSaida = 29;
        p.piece[j].coordenadaDeEntrada = 27;
        p.piece[j].primeiraCasaDeCor = 66;
        p.piece[j].coordenadaFinal = 66 + 6;
        p.piece[j].estaEmJogo = p.vaiJogar;

    }

    atualizarLetrasPieces(p, tabuleiro);
}

///recebe 1 jogador e a matriz para trocas os valores desse jogador por traços "-"
void removerJogador(Player & p, char tabuleiro[LINHAS][COLUNAS])
{
    for(int i = 0; i < 4; i++)
    {
        p.piece[i].letra = '-';

        int x = p.piece[i].posicao_linha;
        int y = p.piece[i].posicao_coluna;

        tabuleiro[x][y] = '-';
    }
}

/**

    criarJogador ---- IMPORTANTE
    Recebe um único jogador, uma string com o nome, a posição desse jogador, que no caso é a cor, e se ele vai ou não jogar

*/
void criarJogador(Player & p, const char * nome, char tabuleiro[LINHAS][COLUNAS], int pn, bool vaiJogar)
{
    strcpy(p.nome, nome);
    p.pecasEmJogo = 4;
    p.vaiJogar = vaiJogar;



    for(int j = 0; j < 4; j++)
    {
           p.piece[j].ehTorre = false;
           p.piece[j].estaSobreposta = false;
           p.piece[j].cor = (Cor) pn;
           p.piece[j].coordenada = -1;

    }

    if(pn == VERDE)
        iniciarVerde(p, tabuleiro);
    else if(pn == AMARELO)
        iniciarAmarelo(p, tabuleiro);
    else if(pn == VERMELHO)
        iniciarVermelho(p, tabuleiro);
    else if(pn == AZUL)
        iniciarAzul(p, tabuleiro);

    if(!p.vaiJogar)
    {
        removerJogador(p, tabuleiro);
        return;
    }


}



#endif // JOGO__H
