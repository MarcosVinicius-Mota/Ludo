#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "tabuleiro.h"
#include "posicao.h"
#include "jogo.h"

/**

posicaoPeca.
Recebe um jagador e uma letra e faz a busca dessa letra no vetor de peças desse jogador;
Essa função retorna a posição do vetor;
Se não achar, retorna -1, pode ser útil para uns IF ELSE

*/
int posicaoPeca(Player p, char l)
{
    for(int i = 0; i < 4; i++)
    {
        if(p.piece[i].letra == l)
        {
            return i;
        }
    }
    return -1;
}


/**
IndexOf;
Essa função nem é muito usada
Recebe uma string e um caractere e retorna a posição dessa caractere na string
Retorna -1 caso não ache
*/
int indexOf(char str[], char ch)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] == ch)
            return i;
    }
    return -1;
}

/**
Recebe uma letra e procura o jogador que contém essa letra;
Retorna o jogador que possui essa peça
exemplo:
int a = getPlayer(t);
o valor de a vai ser 2, que é a posição do jogador vermelho no vetor
*/
int getPlayer(char letra)
{
    char verde[] = "ghjkGHJK";
    char amarelo[] = "yuioYUIO";
    char vermelho[] = "rtqwRTQW";
    char azul[] = "bncvNBCV";

    if(indexOf(verde, letra) != -1)
    {
        return 0;
    }
    if(indexOf(amarelo, letra) != -1)
    {
        return 1;
    }
    if(indexOf(vermelho, letra) != -1)
    {
        return 2;
    }
    if(indexOf(azul, letra) != -1)
    {
        return 3;
    }
    return -1;

}



#endif // AUXILIARES_H
