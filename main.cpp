#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include "pgmmanip.h"

using namespace std;

int main(){
    
    int lin, col, cinza;
    TMatriz matriz, suavizada;
    srand(time(NULL));
    if(leiturapgm("stanford.pgm", matriz, &col, &lin, &cinza)) 
        return 1;
    ruido("ruido.pgm", matriz, col, lin, cinza, 10);
    suavizar("stanford1.pgm", matriz, col, lin, cinza);

    return 0;
}