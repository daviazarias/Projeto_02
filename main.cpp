#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include "matriz.h"

using namespace std;

int main(){
    
    TMatriz A, B, C;
    int i = 2;
    int j = 2;
    int k = 3;
    int l = 2;
    int m, n;
    
    gerar(A, i, j, 10);
    gerar(B, k, l, 10);
    imprime(A, i, j);
    imprime(B, k, l);
    prodmat(A, i, j, B, k, l ,C, &m, &n);
    imprime(C, m, n);
    return 0;
}