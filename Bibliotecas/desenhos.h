
/*Esse pequena biblioteca tem algumas funções para controle de vídeo*/

#ifndef __DESENHOS_H
#define __DESENHOS_H

#ifdef _WIN32
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#else
#define KEY_ENTER '\n'
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#endif
// Compilação condicional para ter comportamentos diferentes de acordo com o compilador
// Nesse caso, MINGW, Clang e GCC
#ifdef _WIN32
#include <windows.h>
#include "gconio.h"
// Na bibliotaca gconio.h, existe a função delay(), ela tem a mesma funcionalidade da Sleep()
// Para unificar, caso a delay seja chamada no compilador MINGW, padrão do codeblocks, ela chamará a Sleep()
void delay(int n)
{
    Sleep(n);
}
#elif __linux__
#include "gconio.h"
#include <stdio_ext.h> //__fpurge

#endif

// Tamanho das dimensões da aplicação
#define TAMANHO_LINHAS 24
#define TAMANHO_COLUNAS 80

// Declaração das funcões
int selecionar_opcao(int x, int y, int num_de_opcoes);
int selecionar_opcao_horizontal(int x, int y, int num_de_opcoes, int espacamento);
void preencher_com_espacos(int largura, int altura, int pos_x, int pos_y);
void desenhar_quadrado(int largura, int altura, int pos_x, int pos_y);
void desenhar_linha_vertical(int pos_x, int pos_y, int tamanho);
void desenhar_linha_horizontal(int pos_x, int pos_y, int tamanho);
void pausa();

/*
Nome: selecionar_opcao
Parâmetros:   int x -> posição do cursor em relação as colunas
              int y -> posição do cursor em relação as linhas
              int num_de_opcoes -> Quantas opções o menu vai ter
Retorno: Retorna um inteiro baseado na opção selecionada
Funcionalidade: Descrita no código
*/
int selecionar_opcao(int x, int y, int num_de_opcoes)
{

    char up_or_down;
    // Por padrão, já vem selecionada a primeira opção
    int opcao = 1;
    // Variavel para que o valor de y não seja alterado
    int ponteiro = y;

    // Vai para a coluna e a linha passada para a função
    gotoxy(x, ponteiro);
    printf(">");

    do
    {
        /*
        getch para ler variavel sem dar enter
        Essa função só aceita W e S para mover a seta e qualquer outra tecla para retornar
        Na hora de selecionar a sua opção, recomendamos apertar qualquer tecla de letra ou enter
        Algumas teclas, como a setinha, pode ocorrer erros e ficar pendente na stdin, comprometendo outros getch que terão mais tarde
        */
        up_or_down = getch();
        switch (up_or_down)
        {

        case KEY_UP:
            // se a seta estiver em cima, não é possível subir
            if (opcao > 1)
            {
                // Apaga a seta atual e desenha uma nova na posição x , ponteiro - 1
                gotoxy(x, ponteiro);
                printf(" ");
                ponteiro--;
                gotoxy(x, ponteiro);
                printf(">");
                opcao--;
            }
            break;

        case KEY_DOWN:
            // Se a seta estiver embaixo, não é possivel descer
            if (opcao < num_de_opcoes)
            {
                gotoxy(x, ponteiro);
                printf(" ");
                ponteiro++;
                gotoxy(x, ponteiro);
                printf(">");
                opcao++;
            }
            break;
        case KEY_ENTER:
            // Retorna o valor de opção
            return opcao;
        }
    } while (1);
}

int selecionar_opcao_horizontal(int x, int y, int num_de_opcoes, int espacamento)
{

    char direction;
    // Por padrão, já vem selecionada a primeira opção
    int opcao = 1;
    // Variavel para que o valor de y não seja alterado
    int ponteiro = x;

    // Vai para a coluna e a linha passada para a função
    gotoxy(ponteiro, y);
    printf(">");

    do
    {
        /*
        getch para ler variavel sem dar enter
        Essa função só aceita A e D para mover a seta e qualquer outra tecla para retornar
        Na hora de selecionar a sua opção, recomendamos apertar qualquer tecla de letra ou enter
        Algumas teclas, como a setinha, pode ocorrer erros e ficar pendente na stdin, comprometendo outros getch que terão mais tarde
        */
        direction = getch();
        switch (direction)
        {

        case KEY_LEFT:
            // se a seta estiver a esquerda máxima, não é possível subir
            if (opcao > 1)
            {
                // Apaga a seta atual e desenha uma nova na posição x , ponteiro - 1
                gotoxy(ponteiro, y);
                printf(" ");
                ponteiro -= espacamento;
                gotoxy(ponteiro, y);
                printf(">");
                opcao--;
            }
            break;

        case KEY_RIGHT:
            // Se a seta estiver a direita máxima, não é possivel descer
            if (opcao < num_de_opcoes)
            {
                gotoxy(ponteiro, y);
                printf(" ");
                ponteiro += espacamento;
                gotoxy(ponteiro, y);
                printf(">");
                opcao++;
            }
            break;
        case KEY_ENTER:
            // Retorna o valor de opção caso qualquer tecla seja digitada, exceto w e s
            return opcao;
        }
    } while (1);
}

/*
Nome: preencher_com_espaços
Parâmetros:   int largura -> Recebe a largura que será preenchida
              int altura -> Recebe a altura que será preenchida
              int pos_x -> posição do cursor em relação as colunas
              int pos_y -> posição do cursor em relação as linhas
Retorno: void
Funcionalidade: Vai preencher largura colunas e altura linhas com espaços, começando das coordenadas pos_x e pos_y
Resumindo, apaga um pedaço da tela
*/
void preencher_com_espacos(int largura, int altura, int pos_x, int pos_y)
{
    gotoxy(pos_x, pos_y);
    // linhas
    for (int k = 0; k < altura; k++)
    {
        // colunas
        for (int c = 0; c < largura; c++)
        {
            printf(" ");
        }
        // O valor de posição primeiro e incrementado e depois o cursor é posicionado
        gotoxy(pos_x, ++pos_y);
    }
}

/*
    Nome: desenhar_quadrado
    Parâmetros:   int largura -> Recebe a largura que será preenchida
                  int altura -> Recebe a altura que será preenchida
                  int pos_x -> posição do cursor em relação as colunas
                  int pos_y -> posição do cursor em relação as linhas
    Retorno: void
    Funcionalidade: Desenhará bordas na posiçao pos_x e pos_y e vai estender até altura e largura
    Logo depois, esse espaço interno será preenchido
    */

void desenhar_quadrado(int largura, int altura, int pos_x, int pos_y)
{
    gotoxy(pos_x, pos_y);
    // Desenha a borda e a linha horizontal superior
    printf("┌");
    desenhar_linha_horizontal(pos_x + 1, pos_y, largura - 2);
    printf("┐");
    // Desenha as 2 linhas verticais, uma no começo e outra no final
    desenhar_linha_vertical(pos_x, pos_y + 1, altura - 2);
    desenhar_linha_vertical(largura + pos_x - 1, pos_y + 1, altura - 2);

    // Desenha a borda e a linha horizontal inferior
    gotoxy(pos_x, altura + pos_y - 1);
    printf("└");
    desenhar_linha_horizontal(pos_x + 1, altura + pos_y - 1, largura - 2);
    printf("┘");
    // Preenche a parte interna com espaços
    preencher_com_espacos(largura - 2, altura - 2, pos_x + 1, pos_y + 1);
}

/*
    Nome: desenhar_linha_vertical
    Parâmetros:   int tamanho -> Recebe o tamanho da linha que vai ser desenhada
                  int pos_x -> posição do cursor em relação as colunas
                  int pos_y -> posição do cursor em relação as linhas
    Retorno: void
    Funcionalidade: Desenhará "│" na posiçao pos_x e pos_y e do tamanho que escolhido
*/
void desenhar_linha_vertical(int pos_x, int pos_y, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        // Posiciona o cursor e logo depois aumenta a variavel das linhas
        gotoxy(pos_x, pos_y++);
        printf("│");
    }
}

/*
    Nome: desenhar_linha_vertical
    Parâmetros:   int tamanho -> Recebe o tamanho da linha que vai ser desenhada
                  int pos_x -> posição do cursor em relação as colunas
                  int pos_y -> posição do cursor em relação as linhas
    Retorno: void
    Funcionalidade: Desenhará um traço na posiçao pos_x e pos_y e do tamanho que escolhido
*/

void desenhar_linha_horizontal(int pos_x, int pos_y, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        // Posiciona o cursor e logo depois aumenta a variavel das colunas
        gotoxy(pos_x++, pos_y);
        printf("─");
    }
}

/*
    Nome: pausa
    Parâmetros: -
    Retorno: void
    Funcionalidade: Caso seja windows, ele chamará a pausa do próprio SO,pois ela é mais consistente
    do que a segunda implementação, que vai ter que limpar tudo que está pendente na entrada padrão
    exemplo: Após digitar o valor de int atravez de um scanf e dar enter, a variável receberá o "nextint", ou seja, o proximo inteiro que achar
    e o enter, '\n', ficará pendente e será consumido pela próxima leitura de char, o que pode acarretar bugs.
    Na implementação para outros SO, a pausa espera por um enter, pois a funcao fgetc espera um enter para acabar
    Não foi usado getch para aumentar a consistência
*/
#ifdef _WIN32

void pausa()
{
    system("pause");
}

#else

void pausa()
{
    printf("Pressione a tecla ENTER para continuar...");
    // Limpa o que está pendente na entrada
    __fpurge(stdin);
    fgetc(stdin);
    // Limpa denovo, pois a teimosia do usuário pode levar ele a digitar uma palavra inteira
    // e como o fgetc só pega um char, o restante fica pendente
    __fpurge(stdin);
}

#endif

#endif /*__DESENHOS_H*/
