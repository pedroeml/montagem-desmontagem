//
// Created by Pedro on 06/05/2016.
//

#include <iostream>
#include <stdio.h>
#include "numeric_base_converter.h"

using namespace std;

unsigned int bin_string_to_int(std::string &bin) {
    unsigned int num = 0;
    for (unsigned int i = 0; i < bin.size(); i++) {
        unsigned int b = bin.at(i) == '1' ? 1 : 0;
        num = (num << 1) | b;
    }
    return num;
}

std::string int_to_hexa_string(unsigned int num) {
    char hex[11]; // 32 bits da instrução / 4 bits por digito hexadecimal = 8 digitos hexadecimais.
    hex[11] = '\0';
    char *ptr = &hex[0];
    sprintf(ptr, "0x%X\n", num);
    string hexadecimal(hex);
    return hexadecimal;
}

std::string int_to_binary_string(unsigned int dec) {
    char binary[33] = {0};

    int ix = 32; // subscript of current character
    do {
        binary[--ix] = '0' + dec % 2;
        dec /= 2;
    } while (dec);

    return  (binary+ix);    // ix is offset into char array where answer begins
}

std::string hex_string_to_bin_string(std::string &hex) {
    string bin = "";
    for (unsigned int i = 2; i < hex.size()-1; i++) { // size()-1 por que tem um '\0' no final se a string vier da função int_to_hexa_string
        switch (hex.at(i)) {
            case '0':   bin.append("0000");
                        break;
            case '1':   bin.append("0001");
                        break;
            case '2':   bin.append("0010");
                        break;
            case '3':   bin.append("0011");
                        break;
            case '4':   bin.append("0100");
                        break;
            case '5':   bin.append("0101");
                        break;
            case '6':   bin.append("0110");
                        break;
            case '7':   bin.append("0111");
                        break;
            case '8':   bin.append("1000");
                        break;
            case '9':   bin.append("1001");
                        break;
            case 'A':   bin.append("1010");
                        break;
            case 'B':   bin.append("1011");
                        break;
            case 'C':   bin.append("1100");
                        break;
            case 'D':   bin.append("1101");
                        break;
            case 'E':   bin.append("1110");
                        break;
            case 'F':   bin.append("1111");
                        break;
            default:    std::cout << "CHAR INVÁLIDO PARA FORMATO HEXADECIMAL: " << hex.at(i) << std::endl;
                        break;
        }
    }
    return bin;
}
