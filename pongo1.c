#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define LARGURA 60
#define ALTURA 20

int bolaX, bolaY;
int velBolaX, velBolaY;
int raquete1Y, raquete2Y;
int pontuacao1, pontuacao2;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void desenhar() {
    int i, j;

    system("cls");  // Limpa a tela completamente

    // Desenha borda superior
    for (i = 0; i < LARGURA; i++)
        printf("#");
    printf("\n");

    // Desenha o campo
    for (i = 0; i < ALTURA; i++) {
        for (j = 0; j < LARGURA; j++) {
            if (j == 0 || j == LARGURA - 1)
                printf("#");
            else if (j == bolaX && i == bolaY)
                printf("O");
            else if (j == 2 && i >= raquete1Y && i <= raquete1Y + 3)
                printf("|");
            else if (j == LARGURA - 3 && i >= raquete2Y && i <= raquete2Y + 3)
                printf("|");
            else if (j == LARGURA / 2)
                printf(":");
            else
                printf(" ");
        }
        printf("\n");
    }

    // Desenha borda inferior
    for (i = 0; i < LARGURA; i++)
        printf("#");
    printf("\n");

    // Mostra pontuação
    printf("JOGADOR 1: %d          JOGADOR 2: %d\n", pontuacao1, pontuacao2);
    printf("Controles: Jogador 1: W/S | Jogador 2: O/K | Q = Sair\n");
}

void atualizar() {
    bolaX += velBolaX;
    bolaY += velBolaY;

    // Colisão com parede superior/inferior
    if (bolaY <= 0 || bolaY >= ALTURA - 1)
        velBolaY = -velBolaY;

    // Colisão com raquete do jogador 1
    if (bolaX == 3 && bolaY >= raquete1Y && bolaY <= raquete1Y + 3)
        velBolaX = -velBolaX;

    // Colisão com raquete do jogador 2
    if (bolaX == LARGURA - 4 && bolaY >= raquete2Y && bolaY <= raquete2Y + 3)
        velBolaX = -velBolaX;

    // Pontuação (bola saiu)
    if (bolaX <= 0) {
        pontuacao2++;
        bolaX = LARGURA / 2;
        bolaY = ALTURA / 2;
        velBolaX = -velBolaX;
        Sleep(500);
    }

    if (bolaX >= LARGURA - 1) {
        pontuacao1++;
        bolaX = LARGURA / 2;
        bolaY = ALTURA / 2;
        velBolaX = -velBolaX;
        Sleep(500);
    }
}

void entrada() {
    if (_kbhit()) {
        char tecla = _getch();

        // Jogador 1 (W/S)
        if (tecla == 'w' || tecla == 'W') {
            if (raquete1Y > 0)
                raquete1Y--;
        }
        if (tecla == 's' || tecla == 'S') {
            if (raquete1Y < ALTURA - 3)
                raquete1Y++;
        }

        // Jogador 2 (O/K)
        if (tecla == 'o' || tecla == 'O') {
            if (raquete2Y > 0)
                raquete2Y--;
        }
        if (tecla == 'k' || tecla == 'K') {
            if (raquete2Y < ALTURA - 3)
                raquete2Y++;
        }

        // Sair
        if (tecla == 'q' || tecla == 'Q') {
            printf("\nJogo encerrado!\n");
            exit(0);
        }
    }
}

void inicializar() {
    srand(time(NULL));

    bolaX = LARGURA / 2;
    bolaY = ALTURA / 2;
    velBolaX = 1;
    velBolaY = (rand() % 3) - 1;
    if (velBolaY == 0) velBolaY = 1;

    raquete1Y = ALTURA / 2 - 2;
    raquete2Y = ALTURA / 2 - 2;
    pontuacao1 = 0;
    pontuacao2 = 0;
}

int main() {
    inicializar();

    printf("=== PONG EM C ===\n");
    printf("Pressione qualquer tecla para começar...\n");
    _getch();

    // Game loop
    while (1) {
        desenhar();
        entrada();
        atualizar();
        Sleep(50);  // Velocidade do jogo
    }

    return 0;
}
