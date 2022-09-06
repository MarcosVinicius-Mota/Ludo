#ifndef POS__H
#define POS__H

#include "tabuleiro.h"
#include "jogo.h"
#include "auxiliares.h"

#define STAR1 11
#define STAR2 24
#define STAR3 37
#define STAR4 50


static const int coord[][2] = {{1, 7},
                     {1, 8},
                     {1, 9},
                     //linha de cima

                     {2, 9},
                     {3, 9},
                     {4, 9},
                     {5, 9},
                     {6, 9},
                     //primeira coluna

                     {7, 10},
                     {7, 11},
                     {7, 12},
                     {7, 13},
                     {7, 14},
                     {7, 15},
                     //primeira linha direira

                     {8, 15},
                     {9, 15},
                     //segunda coluna direita

                     {9, 14},
                     {9, 13},
                     {9, 12},
                     {9, 11},
                     {9, 10},
                     //segunda linha direita

                     {10, 9},
                     {11, 9},
                     {12, 9},
                     {13, 9},
                     {14, 9},
                     {15, 9},
                     //terceira coluna direira

                     {15, 8},
                     {15, 7},
                     //linha inferior

                     {14, 7},
                     {13, 7},
                     {12, 7},
                     {11, 7},
                     {10, 7},
                     //terceira coluna esquerda

                     {9, 6},
                     {9, 5},
                     {9, 4},
                     {9, 3},
                     {9, 2},
                     {9, 1},
                     //segunda linha esquerda

                     {8, 1},
                     {7, 1},
                     //segunda coluna esquerda

                     {7, 2},
                     {7, 3},
                     {7, 4},
                     {7, 5},
                     {7, 6},
                     //primeira linha esquerda

                     {6, 7},
                     {5, 7},
                     {4, 7},
                     {3, 7},
                     {2, 7},

                    { 2, 8 }, {3, 8}, {4, 8}, {5, 8}, {6 , 8}, {7, 8}, {8, 8},
                    { 8, 14}, {8, 13}, {8, 12}, {8, 11}, {8, 10}, {8, 9}, {8 , 8},
                    { 14, 8}, {13, 8}, {12, 8}, {11, 8}, {10 , 8}, {9, 8}, {8, 8},
                    { 8, 2}, { 8, 3}, {8, 4}, {8 , 5}, {8 , 6}, {8 , 7}, {8, 8}

};
                     //primeira coluna esquerda};



char getLetra(Player p, int posicao)
{
    ///Recebe um jogador e uma posição de peça e retorna a letra. Essa função nem é usada, mas existe;
    return p.piece[posicao].letra;
}

///Recebe o jogador e uma letra e retorna a letra que está na mesma casa que char l
///Caso não tenha, retorna um espaço em branco
void atualizarSobreposicao(Player & p)
{

    for(int i = 0; i < 4; i++)
    {
        if(p.piece[i].ehTorre)
        {
            for(int j = 0; j < 4; j++)
                if(p.piece[i].coordenada != p.piece[j].coordenada && i != j || p.piece[i].estaNaPosicaoInicial)
                {
                    p.piece[i].ehTorre = false;
                    p.piece[j].ehTorre = false;
                }
                else
                {
                    p.piece[i].ehTorre = true;
                    p.piece[j].ehTorre = true;
                }
        }

    }
}

bool sobreposta(Piece p, Piece p2[])
{

    for(int i = 0; i < 4; i++)
    {
        if(p2[i].letra != p.letra && p.letra != ' ' && p2[i].letra != ' ' && p2[i].letra != '-')
        {
            if(p2[i].coordenada == p.coordenada && p.estaNaPosicaoInicial == false)
            {
                return true;
            }
        }
    }

    return false;
}

void atualizarSobreposicao(Player p[])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(p[i].vaiJogar)
            {
                p[i].piece[j].estaSobreposta = sobreposta(p[i].piece[j], p[0].piece) || sobreposta(p[i].piece[j], p[1].piece) || sobreposta(p[i].piece[j], p[2].piece) || sobreposta(p[i].piece[j], p[3].piece);
            }
        }
    }
}

///printa um quadrado nas posições X e Y
static void printarQuadrado(int x, int y, int cor)
{
    textcolor(cor);
    gotoxy(x, y);
    cout << "██";
}

/**
    getColor
    recebe a posição do jogador no vetor
    retorna a cor de um jogador, mas nesse caso, retorna a do da CONIO, para usar na coloração das casas e peças
*/
int getColor(Cor p)
{
    if(p == AMARELO)
        return BROWN;
    if(p == AZUL)
        return BLUE;
    if(p == VERDE)
        return GREEN;
    return RED;
}
///Essa função atualiza a matriz logo depois de atualizar o visual;
void atualizarMatrix(char tabuleiro[LINHAS][COLUNAS], Player players[])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(players[i].piece[j].coordenada != -1)
            {
                int x = coord[players[i].piece[j].coordenada][0];
                int y = coord[players[i].piece[j].coordenada][1];

                tabuleiro[x][y] = players[i].piece[j].letra;

                textcolor( (int) getColor( (Cor)getPlayer(tabuleiro[x][y])));

                gotoxy(y * 2 + 1, x);
                cout << tabuleiro[x][y] << " ";

            }

        }
    }
}

///recebe uma coordenada e retorna true se a casa for uma estrela
bool eh_estrela(int casa)
{
    return casa == STAR1 || casa == STAR2 || casa == STAR3 || casa == STAR4;
}

///Recebe o vetor de jogadores e uma coordenada e retorna true se a casa for especial;
///As peças não podem sair de jogo enquanto estiverem em uma casa especial
bool ehCasaEspecial(Player p[], int casa)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(p[i].piece[j].coordenadaDeSaida == casa)
                return true;
        }
    }
    return false || eh_estrela(casa);
}


///faz a troca de um caractere de lugar na matriz, vc n vai usar, então rlx
static int atualizarPosicao(int linha, int coluna, int newLinha, int newColuna, char tabuleiro[LINHAS][COLUNAS], Player players[], bool ehUltimaVolta)
{
    int resultado = 0;
    fflush(stdout);

    char temp = tabuleiro[linha][coluna];
    int p = getPlayer(temp);
    char temp2 = tabuleiro[newLinha][newColuna];


    if(ehUltimaVolta)
    {
        int corDoProximo = getPlayer(temp2);

        if(corDoProximo != -1)
        {
            if(corDoProximo != getPlayer(temp))
            {
                int c2 = players[corDoProximo].piece[posicaoPeca(players[corDoProximo], temp2)].coordenada;

                if(!players[corDoProximo].piece[posicaoPeca(players[corDoProximo], temp2)].ehTorre && !ehCasaEspecial(players, c2))
                {
                    int p2 = posicaoPeca(players[corDoProximo], temp2);
                    int x = players[corDoProximo].piece[p2].posicao_linha;
                    int y = players[corDoProximo].piece[p2].posicao_coluna;
                    players[corDoProximo].piece[p2].estaNaPosicaoInicial = true;

                    players[corDoProximo].piece[p2].coordenada = -1;
                    tabuleiro[x][y] = temp2;

                    textcolor( (int) getColor( (Cor)getPlayer(tabuleiro[x][y])));

                    gotoxy(y * 2 + 1, x);
                    cout << tabuleiro[x][y] << " ";

                    resultado = -2;

                }
            }
            else
            {
                players[p].piece[posicaoPeca(players[p], temp)].ehTorre = true;
                players[p].piece[posicaoPeca(players[p], temp2)].ehTorre = true;
            }

        }
    }

    tabuleiro[linha][coluna] = '-';

    bool ehEstrela = false;
    int star = STAR1;
    for(int i = 0; i < 4; i++)
    {
        if(coord[star][0] == linha && coord[star][1] == coluna)
            ehEstrela = true;
        star += 13;
    }
    if(ehEstrela)
    {
        tabuleiro[linha][coluna] = 'x';
        gotoxy(coluna * 2 + 1, linha);
        textcolor(WHITE);
        cout << "x ";
    }
    else if((linha == 7 && coluna == 2) || (coluna >= 2 && coluna < 8 && linha == 8))
    {
        tabuleiro[linha][coluna] = '2';
        printarQuadrado(coluna * 2 + 1, linha, 2);
    }
    else if((linha == 9 && coluna == 14) || (coluna <= 14 && coluna > 8 && linha == 8))
    {
        tabuleiro[linha][coluna] = '1';
        printarQuadrado(coluna * 2 + 1, linha, 1);
    }
    else if((linha == 14 && coluna == 7) || (linha <= 14 && linha > 8 && coluna == 8))
    {
        tabuleiro[linha][coluna] = '4';
        printarQuadrado(coluna * 2+ 1, linha, 4);
    }
    else if((linha == 2 && coluna == 9) || (linha <= 7 && linha >= 2 && coluna == 8))
    {
        tabuleiro[linha][coluna] = '6';
        printarQuadrado(coluna * 2 + 1, linha, 6);
    }
    else
    {
        textcolor(WHITE);
        gotoxy(coluna * 2 + 1, linha);
        cout << "- ";

        textcolor(getColor( (Cor) p));
        gotoxy(newColuna * 2 + 1, newLinha);
        cout << temp << " ";
    }

    tabuleiro[newLinha][newColuna] = temp;
    atualizarMatrix(tabuleiro, players);

    return resultado;
}

/**
    andarCasas
    recebe o tabuleiro, o resultado do dado, a letra a ser movimentada e o vetor de jogadores
    retornos:
    retorna 20 caso o peça esteja na reta final e tire mais doq oq falta pra chegar no final
    retorna -1 se a peça estiver na posição inicial e o dado não foi 6
    retorna 0 se a jogada ocorreu com sucesso
    retorna 1 se uma peça chegou no destino

*/
int andarCasas(char tabuleiro[LINHAS][COLUNAS], int numDeCasas, char letra, Player players[])
{
    int resultado = 0;
    int player = getPlayer(letra);
    int peca = posicaoPeca(players[player], letra);

    int temp = players[player].piece[peca].coordenadaFinal - players[player].piece[peca].coordenada;

    if(temp <= 6)
        if(numDeCasas > temp)
            return 20;

    atualizarSobreposicao(players[player]);

    int coordenada, linha, coluna, novaLinha, novaColuna;

    if(players[player].piece[peca].estaNaPosicaoInicial)
    {
        if(numDeCasas != 6)
            return -1;

        coordenada = players[player].piece[peca].coordenadaDeSaida;
        players[player].piece[peca].coordenada = coordenada;

        linha = players[player].piece[peca].posicao_linha;
        coluna = players[player].piece[peca].posicao_coluna;

        novaLinha  = coord[coordenada][0];
        novaColuna = coord[coordenada][1];

        resultado = atualizarPosicao(linha, coluna, novaLinha, novaColuna, tabuleiro, players, false);
        players[player].piece[peca].estaNaPosicaoInicial = false;
        return resultado;
    }

    for(int i = 0; i < numDeCasas; i++)
    {
        coordenada = players[player].piece[peca].coordenada;

        if(coordenada == players[player].piece[peca].coordenadaDeEntrada)
        {

            linha  = coord[coordenada][0];
            coluna = coord[coordenada][1];

            coordenada = players[player].piece[peca].primeiraCasaDeCor;

            novaLinha  = coord[coordenada][0];
            novaColuna = coord[coordenada][1];

            players[player].piece[peca].coordenada = coordenada;

        }

        else if(coordenada == 51)
        {

            linha  = coord[coordenada][0];
            coluna = coord[coordenada][1];

            coordenada = 0;

            novaLinha  = coord[coordenada][0];
            novaColuna = coord[coordenada][1];

            players[player].piece[peca].coordenada = coordenada;
        }
        else
        {
            linha  = coord[coordenada][0];
            coluna = coord[coordenada][1];

            novaLinha  = coord[coordenada + 1][0];
            novaColuna = coord[coordenada + 1][1];

            players[player].piece[peca].coordenada = coordenada + 1;

        }


        resultado = atualizarPosicao(linha, coluna, novaLinha, novaColuna, tabuleiro, players, i + 1 == numDeCasas);

        if(novaColuna == 8 && novaLinha == 8)
        {
            players[getPlayer(letra)].piece[posicaoPeca(players[getPlayer(letra)], letra)].letra = ' ';
            players[getPlayer(letra)].piece[posicaoPeca(players[getPlayer(letra)], letra)].estaEmJogo = false;
            players[getPlayer(letra)].pecasEmJogo--;
            atualizarMatrix(tabuleiro, players);

            return 1;
        }
        delay(DELAY);
    }

    return resultado;

}



#endif // POS__H
