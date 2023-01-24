#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"
#define _CRT_SECURE_NO_DEPRECATE

#define TAMANHO_PALAVRA 20

char chutes[26];
int chutesdados = 0;
char palavra[TAMANHO_PALAVRA];

void abertura()
{
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta()
{
    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou (char letra)
{
    int achou=0;
    for(int j= 0;j<chutesdados; j++)
            {
                if(chutes[j] == letra)
                {
                    achou=1;
                    break;
                }
            }    
    return achou;
}

void escreveforca()
{

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c    \n", (erros()>=1 ? '(' : ' '), (erros()>=1 ? '_' : ' '), (erros()>=1 ? ')' : ' '));
    printf(" |      %c%c%c   \n", (erros()>=2 ? '\\' : ' '), (erros()>=2 ? '|' : ' '), (erros()>=2 ? '/' : ' '));
    printf(" |       %c     \n", (erros())>=3 ? '|' : ' ');
    printf(" |      %c %c   \n", (erros()>=4 ? '/' : ' '), (erros()>=4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    for(int i=0;i < strlen(palavra);i++)
        {
            int achou=jachutou(palavra[i]);

            if(achou)
            {
                printf("%c ",palavra[i]);
            }
            else
            {
                printf("_ ");
            }
        }
        printf("\n");
}

void adicionapalavra()
{
    char quer;

    printf("voce deseja adicionar uma nova palavra no jogo?(s/n): ");
    scanf(" %c", &quer);

    if(quer=='s')
    {
        char novapalavra[TAMANHO_PALAVRA];
        printf("qual palavra desejas inserir?: ");
        scanf("%s",novapalavra);

        FILE* f;

        f = fopen("forca_palavras.txt", "r+");

        if(f == 0) 
        {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d",&qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f,"%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f,"\n%s", novapalavra);


        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }

}

void escolhepalavra() {
    FILE* f;

    f = fopen("forca_palavras.txt", "r");
    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavra);
    }

    fclose(f);
}

int erros()
{
    int erros =0;
     for(int i=0;i<chutesdados;i++)
    {
        if(!jachutou(palavra[i])) erros++;
    }

    return erros;
}

int acertou()
{
    for(int i=0;i<strlen(palavra); i++)
    {
        if(!jachutou(palavra[i]))
        {
            return 0;
        }
    }

    return 1;
}

int enforcou()
{
    return erros()>=5;
}

int main()
{
    escolhepalavra();
    abertura();

    do {
        
        escreveforca();

        chuta();

    } while(!acertou() && !enforcou());

    if(enforcou())
    {
        printf("\nvoce foi enforcado(:\n");
        printf("a palavra era %s\n\n",palavra);

        printf("           ______          \n");
        printf("        .-\"      \"-.     \n");
        printf("       /            \\     \n");
        printf("      |              |     \n");
        printf("      |,  .-.  .-.  ,|     \n");
        printf("      | )(__/  \\__)( |    \n");
        printf("      |/     /\\     \\|   \n");
        printf("      (_     ^^     _)     \n");
        printf("       \\__|IIIIII|__/     \n");
        printf("        | \\IIIIII/ |      \n");
        printf("        \\          /      \n");
        printf("         `--------`        \n");

    }
    else
    {
        printf("parabens, voce ganhou:)\n\n");

        printf("        ___________     \n"); 
        printf("       '._==_==_=_.'        \n");
        printf("       .-\\:      /-.       \n");
        printf("      | (|:.     |) |       \n");
        printf("       '-|:.     |-'        \n");
        printf("         \\::.    /         \n");
        printf("          '::. .'           \n");
        printf("            ) (             \n");
        printf("          _.' '._           \n");
    }

    adicionapalavra();
}