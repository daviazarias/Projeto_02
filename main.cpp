#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include "matriz.h"

using namespace std;

int main(){
    
    int lin, col, cinza;
    TMatriz matriz;

    if(!leiturapgm("stanford.pgm", matriz, &lin, &col, &cinza)) return 1;
    claro(matriz, lin, col, 100);
    escrevepgm("stanford1.pgm", matriz, lin, col);
    
    return 0;
}