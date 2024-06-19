
#ifndef MATRIZ_H
#define MATRIZ_H

#define TAM 1024
#define TRUE 0
#define FALSE 1

typedef int TMatriz[TAM][TAM];

#ifdef __cplusplus
extern "C" {
#endif
    
int leiturapgm(const char *arquivo, TMatriz m, int *col, int *lin, int *cinza);
void claro(TMatriz m, int col, int lin, int cinza, int intensidade);
void escuro(TMatriz m, int col, int lin, int cinza, int intensidade);
void binaria(const char *arquivo, TMatriz m, int col, int lin, int cinza, int fator);
void ruido(const char *arquivo, TMatriz m, int col, int lin, int cinza, int intensidade);
void negativo(const char *arquivo, TMatriz m, int col, int lin, int cinza);
void iconizar(const char *arquivo, TMatriz m, int col, int lin, int cinza);
void suavizar(const char *arquivo, TMatriz m, int col, int lin, int cinza);

#ifdef __cplusplus
}
#endif

#endif /* MATRIZ_H */

