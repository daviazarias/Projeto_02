/*
 * File:   main.cpp
 * Author: Vinicius Ribeiro da Silva do Carmo ( 2023.2.08.003 ) e Davi Azarias ( 2024.1.08.006 )
 *
 * Created on 17 de junho de 2024, 15:00
 */

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include "pgmmanip.h"

using namespace std;

// Programa que realiza manipulações em uma imagem //

int main(){
    
    cout << "\n-------------------------------------------------------------" << endl;
    cout << "\n\t  Bem-vindo(a) a Edição de Imagem  " <<endl;
    cout << "\n-------------------------------------------------------------" << endl;

    char nomeArquivoEntrada[1024]; // um vetor de caracteres para armazenar o nome do arquivo de entrada //
    cout << "\n Digite o nome do arquivo PGM de entrada, digitando 'nomeArquivo.pgm': ";
    cin >> nomeArquivoEntrada;

    TMatriz imagem; // armazena os dados da imagem em formato PGM após a leitura do arquivo //
    int linhas, colunas, maxTons;
    
    // Leitura da imagem //
    
    if (leiturapgm(nomeArquivoEntrada, imagem, &colunas, &linhas, &maxTons) != 0) {
        cout << "\n Erro ao ler o arquivo PGM." << endl;
        return 1;
    }
    
    int opcao;
    
    do{
        
        cout << "\n-------------------------------------------------------------" << endl;
        cout << "\n Escolha qual opção deseja proseguir: " << endl;
        cout << "\n 1: Escurecer a imagem";
        cout << "\n 2: Clarear a imagem";
        cout << "\n 3: Negativo da imagem";
        cout << "\n 4: Binarizar a Imagem";
        cout << "\n 5: Iconizar a Imagem";
        cout << "\n 6: Adicionar Ruído";
        cout << "\n 7: Aplicar Filtro";
        cout << "\n 8: Sair" << endl;
        cout << "\n Digite a opção desejada: ";
        cin >> opcao;
        cout << "\n-------------------------------------------------------------" << endl;

        while (opcao <= 0 || opcao > 8) {

            cout << "\n Digite novamente uma opção válida: ";
            cin >> opcao;

        }


        char nomeArquivoSaida[1024]; // um vetor de caracteres para armazenar o nome do arquivo de saída //
        int intensidade;
        
        switch(opcao){
            
            case 1: // Escurecer a imagem //

                cout << "\n Digite a intensidade para escurecer a imagem (%): ";
                cin >> intensidade;
                cout << "\n Digite o nome do arquivo de saída, digitando 'nomeArquivo.pgm': ";
                cin >> nomeArquivoSaida;
                escuro(nomeArquivoSaida, imagem, colunas, linhas, maxTons, intensidade);
                
            break;    
            
            case 2: // Clarear a imagem //
                
                cout << "\n Digite a intensidade para clarear a imagem (%): ";
                cin >> intensidade;
                cout << "\n Digite o nome do arquivo de saída, digitando 'nomeArquivo.pgm': ";
                cin >> nomeArquivoSaida;
                claro(nomeArquivoSaida, imagem, colunas, linhas, maxTons, intensidade);
                
            break;    
            
            case 3: // Negativo da imagem //

                cout << "\n Digite o nome do arquivo de saída, digitando 'nomeArquivo.pgm': ";
                cin >> nomeArquivoSaida;
                negativo(nomeArquivoSaida, imagem, colunas, linhas, maxTons);
                
            break;    
            
            case 4: // Binarizar a Imagem //

                cout << "\n Digite o fator para binarizar a imagem: ";
                cin >> intensidade;
                cout << "\n Digite o nome do arquivo de saída, digitando 'nomeArquivo.pgm':";
                cin >> nomeArquivoSaida;
                binaria(nomeArquivoSaida, imagem, colunas, linhas, maxTons, intensidade);
                
            break;    
            
            case 5: // Iconizar a Imagem //

                cout << "\n Digite o nome do arquivo de saída, digitando 'nomeArquivo.pgm': ";
                cin >> nomeArquivoSaida;
                iconizar(nomeArquivoSaida, imagem, colunas, linhas, maxTons);
                
            break;    
            
            case 6: // Adicionar Ruído //

                cout << "\n Digite a intensidade de ruído (%): ";
                cin >> intensidade;
                cout << "\n Digite o nome do arquivo de saída, digitando 'nomeArquivo.pgm':";
                cin >> nomeArquivoSaida;
                ruido(nomeArquivoSaida, imagem, colunas, linhas, maxTons, intensidade);
                
            break;    
            
            case 7: // Aplicar Filtro //

                cout << "\n Digite o nome do arquivo de saída, digitando 'nomeArquivo.pgm': ";
                cin >> nomeArquivoSaida;
                suavizar(nomeArquivoSaida, imagem, colunas, linhas, maxTons);
                
            break;    
            
            case 8:
                
                cout << "\n Obrigado por utilizar nosso programa! Até breve!" << endl;
                
            break;    
            
        }
        
    } while (opcao != 8);

    return 0;
}