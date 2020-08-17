// (c) COPYRIGHT 2020 HST CARD TECNOLOGY Ltda,
// Campinas (SP), Brasil
// ALL RIGHTS RESERVED – TODOS OS DIREITOS RESERVADOS
// CONFIDENTIAL, UNPUBLISHED PROPERTY OF HST E. E. Ltda
// PROPRIEDADE CONFIDENCIAL NAO PUBLICADA DA HST Ltda. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char secretWord[WORD_SIZE];
char kickedLetter[26];
int numberKick = 0;

void openGame()
{
    printf("**************************\n");
    printf("*      Jogo da Forca     *\n");
    printf("**************************\n");
}
//Selecionar uma palavra
void selectWord()
{
    srand(time(0));
    int totalWorld = 0;
    int random = 0;
    FILE* file;
    
    file = fopen("palavras.txt", "r");
    if( file == 0)
    {
        printf("Desculpe, banco de dados não disponível.\n\n");
        exit(1);
    }
    fscanf(file, "%d", &totalWorld);
    random = rand() % totalWorld;
    
    for(int i = 0; i <= random; i++)
    {
        fscanf(file, "%s", secretWord);
    }
	
    fclose(file);
}
//Adicionar novas palavras
void addWord()
{
    char want;
    
    printf("Você deseja adicionar uma nova palavra no jogo? (S/N) ");
    scanf(" %c", &want);
    
    if(want == 'S')
    {
        int totalWorld = 0;
        char newWorld[WORD_SIZE];
        FILE* file;
        
        printf("Qual a nova palavra? ");
        scanf("%s", newWorld);
        
        file = fopen("palavras.txt", "r+");
        if( file == 0)
        {
            printf("Desculpe, banco de dados não disponível.\n\n");
            exit(1);
        }
        fscanf(file, "%d", &totalWorld);
        
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d", ++totalWorld);
        
        fseek(file, 0, SEEK_END);
        fprintf(file, "\n%s", newWorld);
        
        fclose(file);
    }
}
//Receber uma letra chutada pelo usuário
void kickLetter()
{
    char kick;
    
    printf("\nChute uma letra: ");
    scanf(" %c", &kick);
	
    kickedLetter[numberKick++] = kick;
}
//Encontrar letra
int findLetter(char letter)
{
    int find = 0;
    for(int i = 0; i < numberKick; i++)
    {
        if(kickedLetter[i] == letter)
        {
            find = 1;
            break;
        }
    }
    return find;
}
//Desenhar a forca
void drawHangman()
{
    int error = totalKickError();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (error >= 1 ? '(' : ' '), 
                                 (error >= 1 ? '_' : ' '), 
                                 (error >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (error >= 3 ? '\\' : ' '), 
                                 (error >= 2 ? '|' : ' '), 
                                 (error >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (error >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (error >= 4 ? '/' : ' '), 
                                 (error >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___       \n\n\n");
    
    for(int i = 0; i < strlen(secretWord); i++)
    {
        if(findLetter(secretWord[i]))
        {
            printf("%c ", secretWord[i]);
        }
        else
        {
            printf("_ ");
        }
    }
}
//Contar a quantidade de chutes errados
int totalKickError()
{
    int totalError = 0;
    
    for(int i = 0; i < numberKick; i++)
    {
        int exist = 0;
        for(int j = 0; j < strlen(secretWord); j++)
        {
            if(kickedLetter[i] == secretWord[j])
            {
                exist = 1;
                break;
            }
        }
        
        if(!exist)
        {
            totalError++;
        }
    }
    return totalError;
}
//Verificar se perdeu o Jogo
int lose()
{
    return (totalKickError() >= 5); 
}
//Verificar se ganhou o Jogo
int win ()
{
    for(int i = 0; i < strlen(secretWord); i++)
    {
        if(!findLetter(secretWord[i]))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    selectWord();
    openGame();
    
    do
    {
        drawHangman();
        kickLetter();
        
    }while(!win() && !lose());
    
    if(win())
    {
		drawHangman();
        printf("\nParabéns, você ganhou!\n\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
		
		addWord();
    }
    else
    {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", secretWord);
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
    return 0;
}
