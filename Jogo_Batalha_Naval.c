#include <stdio.h>
#include <string.h>

#define TAM_TAB 10
#define TAM_HAB 5

// Função para inicializar o tabuleiro com água (0) e alguns navios (3)
void inicializarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    int i, j;
    for (i = 0; i < TAM_TAB; i++) {
        for (j = 0; j < TAM_TAB; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    // Exemplo de navios fixos
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[7][1] = 3;
}

// Função para criar matriz de habilidade em cone (ponta para baixo)
void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    int i, j;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            // O cone cresce para baixo, centralizado
            if (j >= (TAM_HAB/2 - i) && j <= (TAM_HAB/2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função para criar matriz de habilidade em cruz
void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    int i, j;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB/2 || j == TAM_HAB/2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função para criar matriz de habilidade em octaedro (losango)
void criarOctaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    int i, j;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            // Distância de Manhattan até o centro
            if (abs(i - TAM_HAB/2) + abs(j - TAM_HAB/2) <= TAM_HAB/2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Função para sobrepor a matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int habilidade[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    int i, j;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                // Calcula a posição no tabuleiro centralizando a matriz de habilidade
                int linha = origem_linha + i - TAM_HAB/2;
                int coluna = origem_coluna + j - TAM_HAB/2;
                // Verifica se está dentro dos limites do tabuleiro
                if (linha >= 0 && linha < TAM_TAB && coluna >= 0 && coluna < TAM_TAB) {
                    // Marca área afetada apenas se não for navio
                    if (tabuleiro[linha][coluna] != 3)
                        tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro com legendas
void exibirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("Legenda: ~ = Água | N = Navio | * = Área de habilidade\n\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");
            else if (tabuleiro[i][j] == 3)
                printf("N ");
            else if (tabuleiro[i][j] == 5)
                printf("* ");
            else
                printf("? ");
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    // Inicializa o tabuleiro e as matrizes de habilidade
    inicializarTabuleiro(tabuleiro);
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Exemplo de aplicação das habilidades em diferentes pontos do tabuleiro
    // Ponto de origem: linha, coluna (centralizado)
    aplicarHabilidade(tabuleiro, cone, 2, 2);        // Cone no topo esquerdo
    aplicarHabilidade(tabuleiro, cruz, 5, 5);        // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);    // Octaedro no canto inferior direito

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}

/*
    Comentários:
    - As funções criarCone, criarCruz e criarOctaedro usam loops aninhados e condicionais para montar as áreas de efeito.
    - aplicarHabilidade centraliza a matriz de habilidade no ponto de origem e só marca área de efeito se não houver navio.
    - O tabuleiro é exibido com caracteres diferentes para água (~), navio (N) e área de habilidade (*).
    - O código pode ser facilmente adaptado para receber entradas do usuário ou mudar os pontos de origem.
*/