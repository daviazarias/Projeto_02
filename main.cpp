#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include "pgmmanip.h"

using namespace std;

int main(){
    
    int lin, col, cinza;
    TMatriz matriz;
    srand(time(NULL));
    if(leiturapgm("stanford.pgm", matriz, &col, &lin, &cinza)) 
        return 1;
    escuro("escurecida.pgm", matriz, col, lin, cinza, 20);
    return 0;
}