#include <iostream>
#include "./Bibliotecas/gconio.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <time.h>

#define DELAY 150

using namespace std;

#include "./Bibliotecas/tabuleiro.h"
#include "./Bibliotecas/posicao.h"
#include "./Bibliotecas/jogo.h"
#include "./Bibliotecas/auxiliares.h"
#include "./Bibliotecas/analisador.h"
#include "./Bibliotecas/desenhos.h"

void posicionarCursorNoMeio();
void darZoom(int a);
int vezDoProximo(int vezAtual, Player p[]);
int iniciarJogo(int mode);

void logo();
int menuInicial();
int menuInicial2();
int menuDeAjuda();
int selecionarNumDePlayers();
void viewinformation(int op);
void winner(int numplayer);

const int x = 27;

int COR_FUNDO = BLACK;
int COR_LETRA = WHITE;

int main()
{
    srand(time(NULL));

#ifdef _WIN32
    darZoom(7);
    system("chcp 65001");
    system("MODE con cols=80 lines=22");
#endif
    clrscr();
    logo();
    
    #ifdef _WIN32
    gotoxy(9, 16);
    printf("Use as setas direcionais para navegar e ENTER para confirmar");
    #else
    gotoxy(13, 16);
    printf("Use W, A, S e D para navegar e ENTER para confirmar");
    #endif
    gotoxy(18, 17);
    pausa();

    while (menuInicial());
    return 0;
}

int menuInicial()
{
    logo();
    gotoxy(x, 11);
    printf("  Entrar");
    gotoxy(x, 12);
    printf("  Encerrar");

    int opc = selecionar_opcao(27, 11, 2);

    switch (opc)
    {
    case 1:
        return menuInicial2();
    case 2:
        return 0;
    }
    return -1;
}

int menuInicial2()
{
    logo();
    gotoxy(x, 11);
    printf("  Iniciar partida");
    gotoxy(x, 12);
    printf("  Sobre o jogo");
    gotoxy(x, 13);
    printf("  Retroceder");
    int opc = selecionar_opcao(27, 11, 3);
    int i, temp;

    switch (opc)
    {
    case 1:
        i = selecionarNumDePlayers();
        if (i == 4)
        {
            return menuInicial2();
        }
        temp = iniciarJogo(i + 1);
        return menuInicial2();
    case 2:
        return menuDeAjuda();
    case 3:
        return menuInicial();
    }
    return -1;
}

int selecionarNumDePlayers()
{
    logo();
    gotoxy(x, 11);
    printf("  2 Jogadores");
    gotoxy(x, 12);
    printf("  3 Jogadores");
    gotoxy(x, 13);
    printf("  4 Jogadores");
    gotoxy(x, 14);
    printf("  Retroceder");
    gotoxy(x, 15);
    return selecionar_opcao(27, 11, 4);
}

int menuDeAjuda()
{
    int posx;
    desenhar_quadrado(80, 22, 0, 0);
    gotoxy(27, 1);
    printf("Informações sobre o jogo");
    gotoxy(27, 20);
    printf("Pressione enter para sair.");
    desenhar_quadrado(78, 18, 1, 2);
    int opcao = 1;
    char direction;
    viewinformation(opcao);
    do
    {
        direction = getch();
        switch (direction)
        {
        case KEY_LEFT:
            if (opcao > 1)
            {
                opcao--;
            }
            viewinformation(opcao);
            break;

        case KEY_RIGHT:
            if (opcao < 2)
            {
                opcao++;
            }
            viewinformation(opcao);
            break;
        case KEY_ENTER:
            return menuInicial2();
        }
    } while (1);
}

void logo()
{
    textbackground(COR_FUNDO);
    textcolor(COR_LETRA);
    desenhar_quadrado(80, 22, 0, 0);
    //...
    gotoxy(x, 3);
    printf(" _     _    _ _____   ____  ");
    gotoxy(x, 4);
    printf("| |   | |  | |  __ \\ / __ \\ ");
    gotoxy(x, 5);
    printf("| |   | |  | | |  | | |  | |");
    gotoxy(x, 6);
    printf("| |   | |  | | |  | | |  | |");
    gotoxy(x, 7);
    printf("| |___| |__| | |__| | |__| |");
    gotoxy(x, 8);
    printf("|______\\____/|_____/ \\____/");
    gotoxy(56, 20);
    printf("copyright(c) by grupo01");
}

int iniciarJogo(int mode)
{
    clrscr();

    char tabuleiro[LINHAS][COLUNAS];
    Player players[4];
    iniciarTabuleiro(tabuleiro);

    int numplayers;
    int vezDe;

    if (mode == 2)
    {
        /// Cria��o dos jogares. Isso n�o pode sair do programa
        /// Passa o jogador que vc quer criar, o nome dele, o tabuleiro e se ele vai ou n�o jogar;
        /// A� vc faz um jeito de perguntar quantos v�o jogar e atribui o ultimo elemento com true ou false

        // DOIS PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, false);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, false);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 2;
        vezDe = 2;
    }
    else if (mode == 3)
    {
        // TRES PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, true);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, false);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 3;
        vezDe = 2;
    }
    else if (mode == 4)
    {
        // QUATRO PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, true);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, true);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 4;
        vezDe = 2;
    }

    printTabuleiro(tabuleiro);

    // LACOS DE PARTIDA
    desenhar_quadrado(40, 17, 35, 0);
    while (1)
    {
        size_t size;
        int *vetor = sortearDados(size);

        if (contarNum6(vetor, size) < 3)
        {
            for (int i = 0; i < size; i++)
            {
                textcolor(15);
                desenhar_quadrado(40, 17, 35, 0);
                desenhar_quadrado(74, 3, 1, 17);

                // apenas exemplo
                gotoxy(4, 18);
                int tokenFinal = 0;

                for (int i = 0; i < 4; i++)
                {
                    if (players[i].vaiJogar)
                    {
                        tokenFinal += 4 - players[i].pecasEmJogo;
                    }
                }
                cout << "Tokens que ja finalizaram: " << tokenFinal << " Sobreposições: ";
                
                atualizarSobreposicao(players);

                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (players[i].piece[j].estaSobreposta)
                        {
                            cout << players[i].piece[j].letra << " ";
                        }
                    }
                }

                gotoxy(42, 1);
                cout << "Vez de " << players[vezDe].nome;
                desenhar_linha_horizontal(37, 2, 36);
                viewvector(vetor, size, 39, 3);

                getch();

                gotoxy(39, 6);
                cout << "Selecione o token: ";
                char temp = selecionartoken(players[vezDe], vetor, size);

                if (temp == ' ')
                {
                    gotoxy(39, 6);
                    cout << "Sem possibilidades de jogo";
                    gotoxy(39, 7);
                    cout << "Perdeu a vez...";
                    getch();
                    break;
                }

                // desenhar_quadrado(40, 20, 35, 0);
                preencher_com_espacos(38, 10, 36, 5);

                int dado;

                if (qtddDeNumeros(vetor, size) == 1)
                {
                    for (int i = 0; i < size; i++)
                    {
                        dado = vetor[i];
                        if (dado != 0)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    gotoxy(39, 6);
                    cout << "Selecione o numero: ";
                    dado = selecionarNumero(vetor, size, temp, players[vezDe]);
                }

                gotoxy(39, 12);
                if(players[vezDe].piece[posicaoPeca(players[vezDe], temp)].estaNaPosicaoInicial)
                {
                    cout << "Peça " << temp << " entra em jogo...";
                }
                else
                {
                   cout << "Peça " << temp << " anda " << dado << " casa(s)...";
                }

                getch();
                int r = andarCasas(tabuleiro, dado, temp, players);

                for (int i = 0; i < size; i++)
                {
                    if (vetor[i] == dado)
                    {
                        vetor[i] = 0;
                        break;
                    }
                }

                textcolor(WHITE);

                if(r == -2)
                {
                    gotoxy(39, 12);
                    cout << "Removeu token do adversário";
                }
                else if(r == 1)
                {
                    gotoxy(39, 12);
                    cout << "Um token chegou no final";

                }
               
                if (r == -2 || r == 1)
                {
                    gotoxy(39, 13);
                    cout << "Sorteando novos dados..."; 
                    vetor = sortearDados(size, vetor);
                    getch();
                }
                
                if (players[vezDe].pecasEmJogo == 0)
                {
                    winner(vezDe);
                    return 0;
                }
            }
        }

        vezDe = vezDoProximo(vezDe, players);
        free(vetor);
    }

    printTabuleiro(tabuleiro);

    return 0;
}

void viewinformation(int op)
{
    int posx = 4, posy = 4;
    preencher_com_espacos(76, 16, 2, 3);
    switch (op)
    {
    case 1:
        gotoxy(posx, posy++);
        printf("1- O jogador tem direito a três sorteios de dados no início de toda");
        gotoxy(posx, posy++);
        printf("   jogada e só consegue tirar seu token da casa apenas quando cair algum");
        gotoxy(posx, posy++);
        printf("   número 6, mas se o 6 cair três vezes ele perde a vez.");
        gotoxy(posx, posy + 1);
        printf("2- O vencedor será o jogador que conseguir levar seus 4 tokens até o fim.");
        gotoxy(posx, posy + 3);
        printf("3- Dois ou mais tokens simples do mesmo jogador formam uma torre se");
        gotoxy(posx, posy + 4);
        printf("   estiverem sobrepostos.");
        gotoxy(2, 18);
        printf("██████████████████████████████████████");
        gotoxy(55, 18);
        printf("Próximo >");
        gotoxy(52, 20);
        break;
    case 2:
        gotoxy(posx, posy++);
        printf("4- Se você sobrepor um token único do adversário e ele não estiver na casa");
        gotoxy(posx, posy++);
        printf("   de saída ou posição X, ele será movido para a casa inicial e tu terás");
        gotoxy(posx, posy++);
        printf("   direito a mais um sorteio de dados, dessa vez não há restrição da ");
        gotoxy(posx, posy++);
        printf("   quantidade de números 6.");
        gotoxy(posx, posy + 7);
        printf("Analíse cada jogada com sabedoria e tenha um bom jogo!");
        gotoxy(40, 18);
        printf("██████████████████████████████████████");
        gotoxy(15, 18);
        printf("< Anterior");
        gotoxy(52, 20);
        break;
    case 4:
        break;
    }
    return;
}

void winner(int numplayer)
{

    textcolor(getColor((Cor) numplayer));
    numplayer++;
    int posx = 16, posy = 6, posx2 = posx + 42, posy2 = posy + 4;
    preencher_com_espacos(78, 20, 1, 1);
    desenhar_linha_horizontal(posx - 3, posy - 1, 55);
    desenhar_linha_horizontal(posx - 3, posy + 8, 55);
    gotoxy(posx + 12, posy + 9);
    cout << "Pressione alguma tecla...";
    gotoxy(posx, posy++);
    printf(" _____   __   _____   _____   _____   __   _____ ");
    gotoxy(posx, posy++);
    printf("|  |  | |  | |_   _| |     | | __  | |  | |  _  |");
    gotoxy(posx, posy++);
    printf("|  |  | |--|   | |   |  |  | |    -| |--| |     |");
    gotoxy(posx, posy++);
    printf(" \\___/  |__|   |_|   |_____| |__|__| |__| |__|__|  ");
    gotoxy(posx, posy++);
    printf(" _____  __     _____  __ __  _____  _____");
    gotoxy(posx, posy++);
    printf("|  _  ||  |   |  _  ||  |  ||   __|| __  |");
    gotoxy(posx, posy++);
    printf("|   __||  |__ |     ||_   _||   __||    -|");
    gotoxy(posx, posy++);
    printf("|__|   |_____||__|__|  |_| ||_____||__|__|");
    switch (numplayer)
    {
    case 1:
        gotoxy(posx2, posy2++);
        printf(" ___");
        gotoxy(posx2, posy2++);
        printf("|_  |");
        gotoxy(posx2, posy2++);
        printf(" _| |_");
        gotoxy(posx2, posy2++);
        printf("|_____|");
        break;
    case 2:
        gotoxy(posx2, posy2++);
        printf("  ____");
        gotoxy(posx2, posy2++);
        printf(" |__  |");
        gotoxy(posx2, posy2++);
        printf(" |  __|");
        gotoxy(posx2, posy2++);
        printf(" |____|");
        break;
    case 3:
        gotoxy(posx2, posy2++);
        printf("  ____");
        gotoxy(posx2, posy2++);
        printf(" |__  |");
        gotoxy(posx2, posy2++);
        printf(" |__  |");
        gotoxy(posx2, posy2++);
        printf(" |____|");
        break;
    case 4:
        gotoxy(posx2, posy2++);
        printf(" _____");
        gotoxy(posx2, posy2++);
        printf("|  |  |");
        gotoxy(posx2, posy2++);
        printf("|__   |");
        gotoxy(posx2, posy2++);
        printf("   |__|");
        break;

    default:
        break;
    }
    gotoxy(posx+36, posy);
    getch();
    return;
}

#ifdef _WIN32
void posicionarCursorNoMeio()
{
    SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
}

void darZoom(int a)
{
    keybd_event(VK_LCONTROL, 0x36, 0, 0);

    for (int i = 0; i < a; i++)
    {
        posicionarCursorNoMeio();
        mouse_event(MOUSEEVENTF_WHEEL, MOUSEEVENTF_ABSOLUTE, MOUSEEVENTF_ABSOLUTE, WHEEL_DELTA, 0);
    }
    keybd_event(VK_LCONTROL, 0x1C, KEYEVENTF_KEYUP, 0);
}

#else

void posicionarCursorNoMeio()
{
}

void darZoom(int a)
{
}

#endif

int vezDoProximo(int vezAtual, Player p[])
{
    /*vezDoProximo recebe o jogador da vez e o vetor de jogadores
    retorna o proximo a jogar*/
    int resultado;
    if (vezAtual == VERMELHO)
        vezAtual = -1;

    for (int i = vezAtual + 1; i < 4; i++)
    {
        if (i == 2)
        {
            if (p[AZUL].vaiJogar)
                return AZUL;
            else
                continue;
        }

        else if (i == 3)
        {
            if (p[VERMELHO].vaiJogar)
                return VERMELHO;
            else
                i = -1;
        }
        else
        {
            if (p[i].vaiJogar)
                return i;
        }
    }
    return VERMELHO;
}