#ifndef TABULEIRO__H
#define TABULEIRO__H

#define LINHAS 17
#define COLUNAS 18

#include "posicao.h"
#include "jogo.h"

///Fodasse os comentários dessa biblioteca, apenas use.

void iniciarTabuleiro(char tabuleiro[LINHAS][COLUNAS]){


    FILE * file = fopen("./Bibliotecas/tabuleiro.txt", "r");

    for(int i = 0; i < LINHAS; i++)
    {
        for(int j = 0; j < COLUNAS; j++){
            tabuleiro[i][j] = fgetc(file);
        }
    }

    fclose(file);
}

void printTabuleiro(char tabuleiro[LINHAS][COLUNAS]){
    cout << " ";
    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){


            char temp = tabuleiro[i][j];

            if(temp == '1' || temp == '2' || temp == '6' || temp == '4')
            {
                #ifdef __linux__
                    temp -= 48;
                #endif
                textcolor((int) temp);
                cout << "██";

            }
            else
            {
                char verde[] = "ghjkGHJK";
                char amarelo[] = "yuioYUIO";
                char vermelho[] = "rtqwRTQW";
                char azul[] = "bncvNBCV";

                textbackground(0);
                textcolor(WHITE);
                if(temp == 'e')
                    cout << "┌─";
                else if(temp == 'a')
                    cout << "┘ ";
                else if(temp == 'm')
                    cout << "└─";
                else if(temp == 'd')
                    cout << "┐ ";
                else if(temp == '*')
                    cout << "──";
                else if(temp == '+')
                    cout << "│ ";
                else if(indexOf(amarelo, temp) != -1)
                {
                    textcolor(BROWN);
                    cout << temp << " ";
                }
                else if(indexOf(azul, temp) != -1)
                {
                    textcolor(BLUE);
                    cout << temp << " ";
                }
                else if(indexOf(vermelho, temp) != -1)
                {
                    textcolor(RED);
                    cout << temp << " ";
                }
                else if(indexOf(verde, temp) != -1)
                {
                    textcolor(GREEN);
                    cout << temp << " ";
                }
                else
                    cout << temp << " ";

            }

        }
    }
    cout << endl;


}



#endif // TABULEIRO__H
