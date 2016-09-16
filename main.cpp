//
// Created by Pedro on 05/05/2016.
//

#include <iostream>
#include "io_instruction.h"

using namespace std;


/* TODO:
    1) CRIAR INTERPRETADOR PARA LEITURA E DESMONTAGEM DE CÓDIGO PARA O FORMATO DE INSTRUÇÃO ASSEMBLY DO MIPS
*/

int main() {
    read_settings("mips_registers.txt", 0);
    read_settings("mips_instructions.txt", 1);

    int select = 10;
    string file_in, file_out, print;


    while (select > 0) {
        cout << "[1] LER ARQUIVO ASM PARA CODIFICAR (não suporta instruções de salto para labels ainda não lidos)" << endl;
        cout << "[2] LER ARQUIVO TXT PARA DECODIFICAR (não suporta instruções de salto e as intruções lw e sw)" << endl;
        cout << "[0] PARA SAIR" << endl;
        cin >> select;
        switch (select) {
            case 1:     file_in = "";
                        file_out = "";
                        print = "";
                        cout << "DIGITE O NOME DO ARQUIVO COM A EXTENSÃO 'ASM' A SER LIDO:" << endl;
                        cin >> file_in;
                        cout << "DIGITE O NOME DO ARQUIVO COM A EXTENSÃO 'TXT' A SER ESCRITO:" << endl;
                        cin >> file_out;
                        print = read_asm(file_in);
                        cout << "\n" << print << "\n" << endl;
                        write_file(print, file_out);
                        break;
            case 2:     file_in = "";
                        file_out = "";
                        print = "";
                        cout << "DIGITE O NOME DO ARQUIVO COM A EXTENSÃO 'TXT' A SER LIDO:" << endl;
                        cin >> file_in;
                        cout << "DIGITE O NOME DO ARQUIVO COM A EXTENSÃO 'ASM' A SER ESCRITO:" << endl;
                        cin >> file_out;
                        print = read_hexadecimal(file_in);
                        cout << "\n" << print << "\n" << endl;
                        write_file(print, file_out);
                        break;
            default:    cout << "FUNÇÃO NÃO IMPLEMENTADA!" << endl;
                        select = 0;
                        break;
        }
    }


    return 0;
}


