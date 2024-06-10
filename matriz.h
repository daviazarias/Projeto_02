
#ifndef MATRIZ_H
#define MATRIZ_H

#define TAM 128

typedef int TMatriz[TAM][TAM];

#ifdef __cplusplus
extern "C" {
#endif

void copia(TMatriz m1, int nl1, int nc1, TMatriz m2, int *nl2, int *nc2);
void imprime(TMatriz m, int nl, int nc);
void gerar(TMatriz m, int nl, int nc, int lim);
void transposta(TMatriz m1, int nl1, int nc1, TMatriz m2, int *nl2, int *nc2);
void soma(TMatriz m1, int nl, int nc, TMatriz m2, TMatriz m3, int *nl3, int *nc3);
void subtracao(TMatriz m1, int nl, int nc, TMatriz m2, TMatriz m3, int *nl3, int *nc3);
void prodmat(TMatriz m1, int nl1, int nc1, TMatriz m2, int nl2, int nc2, TMatriz m3, int *nl3, int *nc3);
void prodesc(TMatriz m1, int nl1, int nc1, int esc, TMatriz m2, int *nl2, int *nc2);
int somacol(TMatriz m, int nl, int j);
int somalin(TMatriz m, int nc, int i);
void escrevematriz(const char *arquivo, TMatriz m, int nl, int nc);
bool leituramatriz(const char *arquivo, TMatriz m);
bool compara(TMatriz m1, int nl1, int nc1, TMatriz m2, int nl2, int nc2);

#ifdef __cplusplus
}
#endif

#endif /* MATRIZ_H */

