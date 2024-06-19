#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "pgmmanip.h"

void claro(const char *arquivo, TMatriz m, int col, int lin, int cinza, int intensidade){
    FILE *arq;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    
    intensidade = cinza*intensidade/100;
    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++){
            if(m[i][j] <= 255 - intensidade)
                m[i][j] += intensidade;
            else m[i][j] = 255;
        }
    fclose(arq);
}

void escuro(const char *arquivo, TMatriz m, int col, int lin,int cinza, int intensidade){
    FILE *arq;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    
    intensidade = cinza*intensidade/100;
    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++){
            if(m[i][j] >= intensidade)
                m[i][j] -= intensidade;
            else m[i][j] = 0;
        }
    fclose(arq);
}

void escrevepgm(const char *arquivo, TMatriz m, int col, int lin, int cinza){
    FILE *arq;
    arq = fopen(arquivo, "w");
    
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            fprintf(arq, "%d ", m[i][j]);
            if(j == col - 1){
                fprintf(arq, "\n");
            }
        }
    }
    fclose(arq);
}

int leiturapgm(const char *arquivo, TMatriz m, int *col, int *lin, int *cinza){
    FILE *arq;
    arq = fopen(arquivo, "r");
        
    if(arq == NULL)
        return FALSE; 
    
    char P2[3];
    fscanf(arq, "%s", P2);

    if(strcmp(P2, "P2"))
        return FALSE;
    
    fscanf(arq, "%d %d", col, lin);
    fscanf(arq, "%d", cinza);
    
    for(int i = 0; i < *lin; i++){
        for(int j = 0; j < *col; j++){
            fscanf(arq, "%d", &m[i][j]);
        }
    }
    
    fclose(arq);
    return TRUE;
}

void negativo(const char *arquivo, TMatriz m, int col, int lin, int cinza){
    FILE *arq;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++){
            fprintf(arq, "%d ", cinza - m[i][j]);
            if(j == col - 1)
                fprintf(arq, "\n");
        }
    fclose(arq);
}

void binaria(const char *arquivo, TMatriz m, int col, int lin, int cinza, int fator){
    FILE *arq;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++){
            if(m[i][j] > fator)
                fprintf(arq, "%d ", cinza);
            else fprintf(arq, "%d ", 0);
            if(j == col - 1)
                fprintf(arq, "\n");
        }
    fclose(arq);
}

void ruido(const char *arquivo, TMatriz m, int col, int lin, int cinza){
    FILE *arq;
    int ruido;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++){
            ruido = rand() % 21;
            if(ruido == 0){
                fprintf(arq, "%d ", 0);
            } else if (ruido == 1){
                fprintf(arq, "%d ", cinza);
            } else fprintf(arq, "%d ", m[i][j]);
            if(j == col - 1)
                fprintf(arq, "\n");
        }
    fclose(arq);
}

void iconizar(const char *arquivo, TMatriz m, int col, int lin, int cinza){
    FILE *arq;
    int iconlin= lin/64, iconcol = col/64;
    int pixel;
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col, lin, cinza);
    for(int i = 0; i < 64; i++)
        for(int j = 0; j < 64; j++){
            int soma = 0;
            for(int k = i*iconlin; k < iconlin*(i+1); k++)
                for(int l = j*iconcol; l < iconcol*(j+1); l++){
                    soma += m[k][l];
                }
            pixel = soma/(iconlin*iconcol);
            fprintf(arq, "%d ", pixel);
            if(j == 63)
                fprintf(arq, "\n");
        }
    fclose(arq);
}

/*Função utilizada somente pela função "suavizar", recebe uma matriz de 9 números inteiros
 *e retorna a mediana dos 9 números. 
 */
int filtro(int matriz[3][3]){
    int vetor[9];
    int aux;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            vetor[3*i + j] = matriz[i][j];
        }
    }
    for (int i = 1; i < 9; i++) {
        aux = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > aux) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = aux;
    }
    return vetor[4];
}

void suavizar(const char *arquivo, TMatriz m, int col, int lin, int cinza){
    FILE *arq;
    int pixel[3][3];
    arq = fopen(arquivo, "w");
    fprintf(arq, "P2\n%d %d\n%d\n", col - 2, lin - 2, cinza);
    for(int i = 1; i < lin - 1; i++){
        for(int j = 1; j < col - 1; j++){
            for(int k = -1; k <= 1; k++){
                for(int l = -1; l <= 1; l++){
                    pixel[k+1][l+1] = m[i+k][j+l];
                }
            }
            fprintf(arq, "%d ", filtro(pixel));
            if(j == 16)
                fprintf(arq, "\n");
        }
    }
    fclose(arq);
}

