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
            m[i][j] = -lim + rand() % (2*lim);
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

void soma(TMatriz m1, TMatriz m2, int nl, int nc, TMatriz m3, int *nl3, int *nc3){
    *nl3 = nl;
    *nc3 = nc;
    for(int i = 0; i < nl; i++)
        for(int j = 0; j < nc; j++)
            m3[i][j] = m1[i][j] + m2[i][j];
}

void subtracao(TMatriz m1, TMatriz m2, int nl, int nc, TMatriz m3, int *nl3, int *nc3){
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

int diagonal(TMatriz m, int n){
    int soma = 0;
    for(int i = 0; i < n; i++)
        soma+= m[i][i];
    return soma;
}

void escrevematriz(const char *arquivo, TMatriz m, int nl, int nc){
    ofstream arq(arquivo);
    
    arq << nc << " " << nl << endl << endl;
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
    
    arq >> nc >> nl;
    for(int i = 0; i < nl; i++){
        for (int j = 0; j < nc; j++){
            arq >> m[i][j];
        }
    }
    arq.close();
    return true;
}

bool compara(TMatriz m1, int nl1, int nc1, TMatriz m2, int nl2, int nc2){
    if(nl1 != nl2 || nc1 != nc2){
        return false;
    } else {
        for(int i = 0; i < nl1; i++)
            for(int j = 0; j < nc1; j++)
                if(m1[i][j] != m2[i][j])
                    return false;
    }
    return true;    
}

void claro(TMatriz m, int lin, int col, int intensidade){
    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++){
            if(m[i][j] <= 255 - intensidade)
                m[i][j] += intensidade;
            else m[i][j] = 255;
        }
}

void escuro(TMatriz m, int lin, int col, int intensidade){
    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++){
            if(m[i][j] >= intensidade)
                m[i][j] -= intensidade;
            else m[i][j] = 0;
        }
}

void escrevepgm(const char *arquivo, TMatriz m, int lin, int col){
    ofstream arq(arquivo);
       
    arq << "P2" << endl << col << " " << lin << endl;
    
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            arq << m[i][j] << " ";
            if(j == col - 1){
                arq << endl;
            }
        }
    }
    arq.close();
}

bool leiturapgm(const char *arquivo, TMatriz m, int *lin, int *col, int *cinza){
    ifstream arq(arquivo);
    string P2;
        
    if(!arq.is_open()){
        cout << "ERRO: Imagem não encontrada.";
        return false; 
    }
    
    arq >> P2;

    if(P2 != "P2"){
        cout << "ERRO: Formato incompatível.";
        return false;
    }
    
    arq >> *col >> *lin >> *cinza;
    
    for(int i = 0; i < *lin; i++){
        for(int j = 0; j < *col; j++){
            arq >> m[i][j];
        }
    }
    
    arq.close();
    return true;
}