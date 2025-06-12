#include <stdio.h>
#include <stdlib.h> // Para abs

#define TAM 10
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define TAM_NAVIO 3

void inicializa_tabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

int pode_posicionar(int tabuleiro[TAM][TAM], int posicoes[3][2]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];

        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM)
            return 0;

        if (tabuleiro[linha][coluna] != AGUA)
            return 0;
    }
    return 1;
}

void posicionar_navio(int tabuleiro[TAM][TAM], int posicoes[3][2]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];
        tabuleiro[linha][coluna] = NAVIO;
    }
}

void exibir_tabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n   ");
    for (int j = 0; j < TAM; j++)
        printf("%2d", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%2d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void construir_cone(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
}

void construir_cruz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

void construir_octaedro(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (abs(i - 2) + abs(j - 2) <= 2) ? 1 : 0;
}

void aplicar_habilidade(int tabuleiro[TAM][TAM], int habilidade[5][5], int origem_linha, int origem_coluna) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linha_tabuleiro = origem_linha - 2 + i;
            int coluna_tabuleiro = origem_coluna - 2 + j;

            if (linha_tabuleiro >= 0 && linha_tabuleiro < TAM &&
                coluna_tabuleiro >= 0 && coluna_tabuleiro < TAM &&
                habilidade[i][j] == 1 &&
                tabuleiro[linha_tabuleiro][coluna_tabuleiro] == AGUA) {
                    tabuleiro[linha_tabuleiro][coluna_tabuleiro] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializa_tabuleiro(tabuleiro);

    int navio_horizontal[3][2] = {{2, 4}, {2, 5}, {2, 6}};
    if (pode_posicionar(tabuleiro, navio_horizontal))
        posicionar_navio(tabuleiro, navio_horizontal);

    int navio_vertical[3][2] = {{5, 1}, {6, 1}, {7, 1}};
    if (pode_posicionar(tabuleiro, navio_vertical))
        posicionar_navio(tabuleiro, navio_vertical);

    int navio_diagonal[3][2] = {{0, 9}, {1, 8}, {2, 7}};
    if (pode_posicionar(tabuleiro, navio_diagonal))
        posicionar_navio(tabuleiro, navio_diagonal);

    int cone[5][5], cruz[5][5], octaedro[5][5];
    construir_cone(cone);
    construir_cruz(cruz);
    construir_octaedro(octaedro);

    aplicar_habilidade(tabuleiro, cone, 4, 4);
    aplicar_habilidade(tabuleiro, cruz, 7, 7);
    aplicar_habilidade(tabuleiro, octaedro, 1, 2);

    exibir_tabuleiro(tabuleiro);

    return 0;
}