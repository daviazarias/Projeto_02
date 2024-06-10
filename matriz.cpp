#include <iostream>
#include <time.h>
#include <fstream>
#include "matriz.h"

using namespace std;

void copia(TMatriz m1, int nl1, int nc1, TMatriz m2, int *nl2, int *nc2){
    *nl2 = nl1;
    *nc2 = nc1;
    for(int i = 0; i < nl1; i++)
        for(int j = 0; j < nc1; j++)
            m2[i][j] = m1[i][j];
}

void imprime(TMatriz m, int nl, int nc){
    for(int i = 0; i < nl; i++)
        for(int j = 0; j < nc; j++){
            cout << m[i][j] << " ";
            if(j == nc - 1)
                cout << endl;
        }
    cout << endl;
}

void gerar(TMatriz m, int nl, int nc, int lim){  
    int sinal;
    for(int i = 0; i < nl; i++)
        for(int j = 0; j < nc; j++){
            m[i][j] = rand() % lim;
//            sinal = rand() % 2;
//            if(sinal)
//                m[i][j] *= -1;
        }
}

void transposta(TMatriz m1, int nl1, int nc1, TMatriz m2, int *nl2, int *nc2){
    *nl2 = nc1;
    *nc2 = nl1;
    for(int i = 0; i < nl1; i++){
        for(int j = 0; j < nc1; j++){
            m2[j][i] = m1[i][j];
        }
    }
}

void soma(TMatriz m1, int nl, int nc, TMatriz m2, TMatriz m3, int *nl3, int *nc3){
    *nl3 = nl;
    *nc3 = nc;
    for(int i = 0; i < nl; i++)
        for(int j = 0; j < nc; j++)
            m3[i][j] = m1[i][j] + m2[i][j];
}

void subtracao(TMatriz m1, int nl, int nc, TMatriz m2, TMatriz m3, int *nl3, int *nc3){
    *nl3 = nl;
    *nc3 = nc;
    for(int i = 0; i < nl; i++)
        for(int j = 0; j < nc; j++)
            m3[i][j] = m1[i][j] - m2[i][j];
}

void prodmat(TMatriz m1, int nl1, int nc1, TMatriz m2, int nl2, int nc2, TMatriz m3, int *nl3, int *nc3){
    int soma = 0;
    *nl3 = nl1;
    *nc3 = nc2;
    if(nc1 == nl2){
        for(int i = 0; i < nl1; i++)
            for(int j = 0; j < nc2; j++){
                for(int k = 0; k < nc1; k++)
                    soma += m1[i][k]*m2[k][j];
                m3[i][j] = soma;
                soma = 0;
            }
    } else cout << endl << "Produto indeterminado." << endl << endl;
}

void prodesc(TMatriz m1, int nl1, int nc1, int esc, TMatriz m2, int *nl2, int *nc2){
    *nl2 = nl1;
    *nc2 = nc1;
    for(int i = 0; i < nl1; i++)
        for(int j = 0; j < nc1; j++)
            m1[i][j] *= esc;
}

int somacol(TMatriz m, int nl, int j){
    int soma = 0;
    for(int i = 0; i < nl; i++)
        soma += m[i][j];
    return soma;
}

int somalin(TMatriz m, int nc, int i){
    int soma = 0;
    for(int j = 0; j < nc; j++)
        soma += m[i][j];
    return soma;
}

void escrevematriz(const char *arquivo, TMatriz m, int nl, int nc){
    ofstream arq(arquivo);
    
    arq << nl << " " << nc << endl;
    for(int i = 0; i < nl; i++){
        for (int j = 0; j < nc; j++){
            arq << m[i][j] << " ";
            if (j == nc - 1 && i != nl - 1) arq << endl;
        }
    }
    arq.close();
}

bool leituramatriz(const char *arquivo, TMatriz m){
    int nl, nc;
    ifstream arq(arquivo);
    if(!arq.is_open()) return false;
    
    arq >> nl >> nc;
    for(int i = 0; i < nl; i++){
        for (int j = 0; j < nc; j++){
            arq >> m[i][j];
        }
    }
    arq.close();
    return true;
}

bool compara(TMatriz m1, int nl1, int nc1, TMatriz m2, int nl2, int nc2){
    bool resposta = true;
    if(nl1 != nl2 || nc1 != nc2){
        resposta = false;
    } else {
        for(int i = 0; i < nl1; i++)
            for(int j = 0; j < nc1; j++)
                if(m1[i][j] != m2[i][j]){
                    resposta = false;
                }
    }
    return resposta;
}