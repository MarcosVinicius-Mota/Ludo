#ifndef ANALISE__H
#define ANALISE__H

#include "desenhos.h"

int *sortearDados(size_t &size)
{
    size = 1;
    int i = 0;
    //Alocar 1 espaço de memória pra int
    int *vetor = (int *)malloc(sizeof(int));

    vetor[i] = rand() % 6 + 1;

    //Enquanto o número sorteado for 6, ele realloca esse espaço e adiciona outro número
    while (vetor[i++] == 6 && size <= 2)
    {
        size++;
        vetor = (int *)realloc(vetor, sizeof(int) * size);
        vetor[i] = rand() % 6 + 1;
    }

    return vetor;
}

//Faz basicamente a mesma coisa do sorteio anterior, a diferença é que esse array já foi alocando pelo menos uma vez
int *sortearDados(size_t & size, int * vetor)
{
    int i = size;

    do
    {
        size++;
        vetor = (int*) realloc(vetor, sizeof(int) * size);
        vetor[i] =  rand() % 6 + 1;;
    } while (vetor[i++] == 6);

    return vetor;

}

int contarNum6(int *vetor, size_t size)
{
    int r = 0;
    for (int i = 0; i < size; i++)
    {
        if (vetor[i] == 6)
        {
            r++;
        }
    }

    return r;
}


bool containSix(int *vetor, int tam)
{
    for (int i = 0; i < tam; i++)
        if (vetor[i] == 6)
            return true;

    return false;
}

//Verifica se uma determinada peça pode jogar em pelo menos um dos resultados do valor do dado
bool pecaEstaNaRetaFinalEPodeJogar(int * vetor, int size, Piece p)
{
    if(p.coordenada >= 0 && p.coordenada <= 52)
        return true;

    for(int i = 0; i < size; i++)
    {

        if(p.coordenadaFinal - p.coordenada >= vetor[i] && vetor[i] != 0 && !p.estaNaPosicaoInicial)
        {
            return true;
        }
    }
    return false;
}

// Percorre todas as peças de um determinado jogador e verifica se ele pode jogar em pelo menos uma casa do vetor e monta o menu de seleção 
int tokensDisponiveis(Player p, int _pos_x, int __pos_y, char vetor[], int * vetorDados, int size)
{
    int r = 0;
    for (int i = 0; i < 4; i++)
    {
        if (p.piece[i].letra != ' ')
        {
            if (containSix(vetorDados, size) && p.piece[i].estaNaPosicaoInicial)
            {
                gotoxy(_pos_x, __pos_y++);
                cout << "[" << p.piece[i].letra << "]";
                vetor[r] = p.piece[i].letra;
                r++;
            }
            else if(pecaEstaNaRetaFinalEPodeJogar(vetorDados, size, p.piece[i]))
            {
                gotoxy(_pos_x, __pos_y++);
                cout << "[" << p.piece[i].letra << "]";
                vetor[r] = p.piece[i].letra;
                r++;
            }
            
        }
    }

    return r;
}

//Menu de seleção de TOKEN
char selecionartoken(Player p, int * vetor, int size)
{
    char tokensdisp[4];
    int quantidade = tokensDisponiveis(p, 40, 7, tokensdisp, vetor, size);
    
    int numescolha;

    if(quantidade > 1)
    {
        numescolha = selecionar_opcao(37, 7, quantidade);
    }
    else if(quantidade == 1)
    {
        numescolha = 1;
    }
    else
    {
        return ' ';
    }

    return tokensdisp[numescolha - 1];
}

//Imprime os valores do dado

void viewvector(int vetor[], int tam, int posx, int posy)
{
    gotoxy(posx, posy);
    for (int i = 0; i < 10; i++)
    {
        printf("   ");
    }
    int i = 0;
    gotoxy(posx, posy);
    for (int i = 0; i < tam; i++)
    {
        if (vetor[i] != 0)
            printf("[%i]", vetor[i]);
    }
}



//Pega o vetor de dados e uma peça e verifica em quais números aquela peça pode jogar
int selecionarNumero(int *vetor, int size, char l, Player p)
{
    int x = 40, y = 7;
    int *arr = (int *)malloc(sizeof(int) * size);
    int k = 0;
    int pos = posicaoPeca(p, l);
    int temp2 = p.piece[pos].coordenadaFinal - p.piece[pos].coordenada;

    if(p.piece[pos].estaNaPosicaoInicial)   
    {
        return 6;
    }


    if (temp2 <= 6 && temp2 >= 0)
    {
        for (int i = 0; i < size; i++)
        {
            if (vetor[i] <= temp2 && vetor[i] != 0)
            {
                gotoxy(x, y++);
                printf("[%d]", vetor[i]);
                arr[k] = vetor[i];
                k++;
            }
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (vetor[i] != 0)
            {
                gotoxy(x, y++);
                printf("[%d]", vetor[i]);
                arr[k] = vetor[i];
                k++;
            }
        }
    }

    if(k == 0)
    {
        return 0;
    }
    if(k == 1)
    {
        return arr[0];
    }


    int temp = selecionar_opcao(39, 7, k) - 1;
    return arr[temp];
}


//Retorna o tamanho "Lógico" do vetor, já que o número 0 é um item nulo
int qtddDeNumeros(int * vetor, int tam)
{
    int num = 0;

    for(int i = 0; i < tam; i++)
    {
        if(vetor[i] != 0)
        {
            num++;
        }
    }

    return num;
}

#endif