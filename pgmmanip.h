
#ifndef MATRIZ_H
#define MATRIZ_H

#define TAM 1024
#define TRUE 1
#define FALSE 0

typedef int TMatriz[TAM][TAM];

#ifdef __cplusplus
extern "C" {
#endif

void claro(TMatriz m, int col, int lin, int cinza, int intensidade);
void escuro(TMatriz m, int col, int lin, int cinza, int intensidade);
void escrevepgm(const char *arquivo, TMatriz m, int col, int lin, int cinza);
int leiturapgm(const char *arquivo, TMatriz m, int *col, int *lin, int *cinza);
void binaria(const char *arquivo, TMatriz m, int col, int lin, int cinza, int fator);
void ruido(const char *arquivo, TMatriz m, int col, int lin, int cinza);
void negativo(const char *arquivo, TMatriz m, int col, int lin, int cinza);
void iconizar(const char *arquivo, TMatriz m, int col, int lin, int cinza);
void suavizar(const char *arquivo, TMatriz m, int col, int lin, int cinza);

#ifdef __cplusplus
}
#endif

#endif /* MATRIZ_H */

