//
// Created by Pedro on 05/05/2016.
//

#include <iostream>
#include "io_instruction.h"

using namespace std;


/* TODO:
    1) CRIAR INTERPRETADOR PARA LEITURA E DESMONTAGEM DE C�DIGO PARA O FORMATO DE INSTRU��O ASSEMBLY DO MIPS
*/

int main() {
    read_settings("mips_registers.txt", 0);
    read_settings("mips_instructions.txt", 1);

    int select = 10;
    string file_in, file_out, print;


    while (select > 0) {
        cout << "[1] LER ARQUIVO ASM PARA CODIFICAR (n�o suporta instru��es de salto para labels ainda n�o lidos)" << endl;
        cout << "[2] LER ARQUIVO TXT PARA DECODIFICAR (n�o suporta instru��es de salto e as intru��es lw e sw)" << endl;
        cout << "[0] PARA SAIR" << endl;
        cin >> select;
        switch (select) {
            case 1:     file_in = "";
                        file_out = "";
                        print = "";
                        cout << "DIGITE O NOME DO ARQUIVO COM A EXTENS�O 'ASM' A SER LIDO:" << endl;
                        cin >> file_in;
                        cout << "DIGITE O NOME DO ARQUIVO COM A EXTENS�O 'TXT' A SER ESCRITO:" << endl;
                        cin >> file_out;
                        print = read_asm(file_in);
                        cout << "\n" << print << "\n" << endl;
                        write_file(print, file_out);
                        break;
            case 2:     file_in = "";
                        file_out = "";
                        print = "";
                        cout << "DIGITE O NOME DO ARQUIVO COM A EXTENS�O 'TXT' A SER LIDO:" << endl;
                        cin >> file_in;
                        cout << "DIGITE O NOME DO ARQUIVO COM A EXTENS�O 'ASM' A SER ESCRITO:" << endl;
                        cin >> file_out;
                        print = read_hexadecimal(file_in);
                        cout << "\n" << print << "\n" << endl;
                        write_file(print, file_out);
                        break;
            default:    cout << "FUN��O N�O IMPLEMENTADA!" << endl;
                        select = 0;
                        break;
        }
    }


    return 0;
}


