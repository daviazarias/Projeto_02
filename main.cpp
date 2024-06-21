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
/*
    iconizar("icone.pgm", matriz, col, lin, cinza);
*/
    ruido("ruido.pgm", matriz, col, lin, cinza, 20);
/*
    claro("clara.pgm", matriz, col, lin, cinza, 50);
    escuro("escura.pgm", matriz, col, lin, cinza, 50);
    binaria("binaria.pgm", matriz, col, lin, cinza, 127);
    negativo("negativa.pgm", matriz, col, lin, cinza);
    suavizar("suavizada1.pgm", matriz, col, lin, cinza);
    if(leiturapgm("ruido.pgm", matriz, &col, &lin, &cinza)) 
        return 1;
    suavizar("suavizada2.pgm", matriz, col, lin, cinza);
*/
    return 0;
}