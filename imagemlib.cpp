#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "pgmmanip.h"

/*
 * Função que lê um arquivo em formato .pgm "P2" e preenche uma matriz com os valores de cada pixel da imagem.
 * Ela retorna o valor 0 caso o arquivo seja encontrado e tenha o texto "P2" em sua primeira linha ou retorna 1 caso contrário. 
 * Parâmetros:
 * - Nome do arquivo a ser gerado.
 * - Endereço de memória da matriz onde está a imagem de entrada.
 * - Endereço de memória onde deve ser guardada a quantidade de colunas.
 * - Endereço de memória onde deve ser guardada a quantidade de linhas.
 * - Endereço de memória onde deve ser guardado o número máximo permitido para um pixel (cor branca).
 */
int leiturapgm(const char *arquivo, TMatriz m, int *col, int *lin, int *cinza){
    FILE *arq;
    arq = fopen(arquivo, "r");
        
    if(arq == NULL)
        return 1; 
    
    char P2[3];
    fscanf(arq, "%s", P2);

    if(strcmp(P2, "P2"))
        return 1;
    
    fscanf(arq, "%d %d", col, lin);
    fscanf(arq, "%d", cinza);
    
    for(int i = 0; i < *lin; i++){
        for(int j = 0; j < *col; j++){
            fscanf(arq, "%d", &m[i][j]);
        }
    }
    
    fclose(arq);
    return 0;
}

/*
 * Função que cria uma imagem a partir do clareamento de uma imagem de entrada.
 * A intensidade do clareamento é recebida como parâmetro.
 * Parâmetros:
 * - Nome do arquivo a ser gerado.
 * - Endereço de memória da matriz onde está a imagem de entrada.
 * - Número de colunas da imagem de entrada.
 * - Número de linhas da imagem de entrada.
 * - Tons de cinza da imagem de entrada.
 * - Intensidade, em porcentagem, de clareamento.
 */
void claro(const char *arquivo, TMatriz m, int col, int lin, int cinza, int intensidade){
    FILE *arq;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    
    intensidade = cinza*intensidade/100;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(m[i][j] <= cinza - intensidade)
                fprintf(arq, "%d ", m[i][j] + intensidade);
            else fprintf(arq, "%d ", cinza);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}

/*
 * Função que cria uma imagem a partir do escurecimento de uma imagem de entrada.
 * A intensidade do escurecimento é recebida como parâmetro.
 * Parâmetros:
 * - Nome do arquivo a ser gerado.
 * - Endereço de memória da matriz onde está a imagem de entrada.
 * - Número de colunas da imagem de entrada.
 * - Número de linhas da imagem de entrada.
 * - Tons de cinza da imagem de entrada.
 */
void escuro(const char *arquivo, TMatriz m, int col, int lin,int cinza, int intensidade){
    FILE *arq;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    
    intensidade = cinza*intensidade/100;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(m[i][j] >= intensidade)
                fprintf(arq, "%d ", m[i][j] - intensidade);
            else fprintf(arq, "0 ");
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}

/*
 * Função que cria a imagem negativa de uma imagem de entrada.
 * Parâmetros:
 * - Nome do arquivo a ser gerado.
 * - Endereço de memória da matriz onde está a imagem de entrada.
 * - Número de colunas da imagem de entrada.
 * - Número de linhas da imagem de entrada.
 * - Tons de cinza da imagem de entrada.
 */
void negativo(const char *arquivo, TMatriz m, int col, int lin, int cinza){
    FILE *arq;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            fprintf(arq, "%d ", cinza - m[i][j]);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}

/*
 * Função que cria uma imagem binarizada a partir de uma imagem de entrada. Cada pixel da imagem
 * gerada será preto ou branco, correspondendo ao pixel de mesma posição na imagem de entrada, seguindo a seguinte lógica:
 * Se o pixel da imagem de entrada for mais escuro que o "ponto médio" (recebido como parâmetro), o pixel de mesma posição
 * na imagem gerada será preto.
 * Se o pixel da imagem de entrada for mais claro que o "ponto médio", o pixel de mesma posição na imagem gerada será branco.
 * Parâmetros:
 * - Nome do arquivo a ser gerado.
 * - Endereço de memória da matriz onde está a imagem de entrada.
 * - Número de colunas da imagem de entrada.
 * - Número de linhas da imagem de entrada.
 * - Tons de cinza da imagem de entrada.
 * - Fator (ponto médio).
 */
void binaria(const char *arquivo, TMatriz m, int col, int lin, int cinza, int fator){
    FILE *arq;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(m[i][j] > fator)
                fprintf(arq, "%d ", cinza);
            else fprintf(arq, "0 ");
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}

/*
 * Função que gera ruídos em preto e branco em uma imagem de entrada, criando uma outra imagem. 
 * Parâmetros:
 * - Nome do arquivo a ser gerado.
 * - Endereço de memória da matriz onde está a imagem de entrada.
 * - Número de colunas da imagem de entrada.
 * - Número de linhas da imagem de entrada.
 * - Tons de cinza da imagem de entrada.
 */
void ruido(const char *arquivo, TMatriz m, int col, int lin, int cinza, int intensidade){
    FILE *arq;
    int ruido;
    float percnt = (float) intensidade/100;
    intensidade = 1/percnt + 3;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    for (int i = 0; i < lin; i++){
        for (int j = 0; j < col; j++){
            ruido = rand() % intensidade;
            if(ruido == 0){
                fprintf(arq, "0 ");
            } else if (ruido == 1){
                fprintf(arq, "%d ", cinza);
            } else fprintf(arq, "%d ", m[i][j]);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}

/*
 * Função que gera um ícone 64x64 a partir de uma imagem de entrada. Cada pixel do ícone
 * equivale à média dos pixels da imagem de entrada. A quantidade de pixels da imagem de entrada
 * usados para calcular um pixel do ícone dependerá de seu tamanho.
 * Número de linhas usadas = Parte inteira de (número de linhas da imagem de entrada / 64).
 * Número de colunas usadas = Parte inteira de (número de colunas da imagem de entrada / 64).
 * Parâmetros:
 * - Nome do arquivo a ser gerado.
 * - Endereço de memória da matriz onde está a imagem de entrada.
 * - Número de colunas da imagem de entrada.
 * - Número de linhas da imagem de entrada.
 * - Tons de cinza da imagem de entrada.
 */
void iconizar(const char *arquivo, TMatriz m, int col, int lin, int cinza){
    FILE *arq;
    int iconlin= lin/64, iconcol = col/64;
    int pixel;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n64 64\n%d\n", cinza);
    for(int i = 0; i < 64; i++){
        for(int j = 0; j < 64; j++){
            int soma = 0;
            for(int k = i*iconlin; k < iconlin*(i+1); k++)
                for(int l = j*iconcol; l < iconcol*(j+1); l++){
                    soma += m[k][l];
                }
            pixel = soma/(iconlin*iconcol);
            fprintf(arq, "%d ", pixel);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}

/*
 * Função utilizada somente pela função "suavizar", recebe um vetor de 9 elementos 
 * e retorna a mediana dos 9 números. 
 */
int mediana(int vetor[9]){
    int aux;
    //Algoritmo de ordenação por inserção, que garante que os elementos no vetor estejam dispostos em ordem crescente.
    for (int i = 1; i < 9; i++) {
        aux = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > aux) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = aux;
    }
    //O valor na posição do meio do vetor (a mediana dos elementos do vetor) será o novo pixel da imagem suavizada.
    return vetor[4];
}

/*
 * Função que gera uma imagem suavizada por mediana a partir de uma imagem de entrada.
 * Cada pixel da imagem de entrada (exceto os pixels das bordas) é substituído pela mediana entre
 * ele mesmo e os 8 pixels a seu redor.
 * Parâmetros:
 * - Nome do arquivo a ser gerado.
 * - Endereço de memória da matriz onde está a imagem de entrada.
 * - Número de colunas da imagem de entrada.
 * - Número de linhas da imagem de entrada.
 * - Tons de cinza da imagem de entrada.
 */
void suavizar(const char *arquivo, TMatriz m, int col, int lin, int cinza){
    FILE *arq;
    int pixel[9];
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col - 2, lin - 2, cinza);
    for(int i = 1; i < lin - 1; i++){
        for(int j = 1; j < col - 1; j++){
            for(int k = -1; k <= 1; k++){
                for(int l = -1; l <= 1; l++){
                    /* Cada pixel da imagem que está sendo gerada será definido pela criação
                     * de um vetor que contenha seu pixel correspondente na imagem de entrada
                     * e os 8 pixels a seu redor.
                     */
                    pixel[3*(k+1) + l + 1] = m[k+i][l+j];
                }
            }
            fprintf(arq, "%d ", mediana(pixel));
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}