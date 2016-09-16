//
// Created by Pedro on 11/05/2016.
//

#include <iostream>
#include "io_instruction.h"

using namespace std;

std::map<std::string, std::string> map_registers;
std::map<std::string, std::vector<std::string> > map_instructions;
std::map<std::string, unsigned int> map_labels;
std::map<std::string, std::string> map_opcode_funct;

/*
 * Adiciona mapeamentos nos maps declarados.
 */
void read_settings(string file_path, int select) {
    ifstream file(file_path.c_str());
    string str;
    while (getline(file, str)) {
        vector<string> elems = vector<string>();
        istringstream iss(str);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(elems));

        switch (select) {
            case 0:     map_registers[elems.at(0)] = elems.at(2);   // mapeia o registrador $nome para o seu valor binário de 5 digitos
                        map_registers[elems.at(1)] = elems.at(2);   // mapeia o registrador $numero para o seu valor binário de 5 digitos
                        break;
            case 1:     map_instructions[elems.at(1)] = elems;
                        if (elems.at(0).compare("R") == 0)
                            map_opcode_funct[elems.at(10)] = elems.at(1);   // mapeia funct da instrução R p/ o nome da instrução R
                        else if (elems.at(0).compare("I") == 0) {    // o que segue abaixo mapeia opcode da instrução I p/ o nome da instrução I
                            if (elems.at(1).compare("addi") == 0 || elems.at(1).compare("addiu") == 0 || elems.at(1).compare("andi") == 0 || elems.at(1).compare("sltiu") == 0 || elems.at(1).compare("beq") == 0 || elems.at(1).compare("bne") == 0)
                                map_opcode_funct[elems.at(5)] = elems.at(1);
                            else if (elems.at(1).compare("lw") == 0 || elems.at(1).compare("sw") == 0)
                                map_opcode_funct[elems.at(4)] = elems.at(1);
                        }
                        else if (elems.at(0).compare("J") == 0)
                            map_opcode_funct[elems.at(3)] = elems.at(1);    // mapeia opcode da instrução J p/ o nome da instrução J
                        break;
            default:    printf("FUNÇÃO NÃO IMPLEMENTADA!\n");
                        break;
        }
    }
}

/*
 * Faz o split de uma instrução removendo vírgulas e separando cada palavra por espaço em uma posição no vector.
 */
void split_instruction(string instruction, vector<string> &array_instruction) {
    unsigned int index;
    while ((index = instruction.find(',')) != string::npos)
        instruction.erase(instruction.begin()+index);

    istringstream iss(instruction);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(array_instruction));
}

/*
 * Cria um objeto instrução do tipo J
 */
J_Instruction* read_J_Instruction(string mips_instruction, string instruction_address) {
    vector<string> instruction;
    split_instruction(mips_instruction, instruction);
    return create_J_Instruction(instruction, instruction_address);
}

J_Instruction* create_J_Instruction(vector<string> &instruction, string instruction_address) {
    J_Instruction *ins;
    vector<string> mapped_instruction = map_instructions.find(instruction.at(0))->second;   // mapeia o nome da instrução retornando um vetor com os dados do txt

    if (instruction.at(0).compare("j") == 0) {
        string opcode = mapped_instruction.at(3);   // captura a string de 6 digitos do opcode
        unsigned int address = map_labels.find(instruction.at(1))->second;
        string label = "000000000"+int_to_binary_string(address); // 0x00400000 = 0000 0000 0100 0000 0000 0000 0000 0000, é o valor mínimo. Os 9 bits à esquerda são o que faltam para compeltar 32 bits.
        label = label.substr(label.size()-32, 32); // garantir que a string possui apenas 32 posições.
        label = label.substr(label.size()-32, 30); // remove os 2 bits menos significativos.
        label = label.substr(label.size()-26, 26); // remove os 4 bits mais significativos.
        ins = new J_Instruction(instruction.at(0), opcode, label, instruction_address);
    }

    return ins;
}

/*
 * Cria um objeto instrução do tipo I
 */
I_Instruction* read_I_Instruction(string mips_instruction, string instruction_address) {
    vector<string> instruction;
    split_instruction(mips_instruction, instruction);
    return create_I_Instruction(instruction, instruction_address);
}

I_Instruction* create_I_Instruction(vector<string> &instruction, string instruction_address) {
    I_Instruction *ins;
    vector<string> mapped_instruction = map_instructions.find(instruction.at(0))->second;   // mapeia o nome da instrução retornando um vetor com os dados do txt
    string opcode;

    if (instruction.at(0).compare("addi") == 0 || instruction.at(0).compare("addiu") == 0 || instruction.at(0).compare("andi") == 0 || instruction.at(0).compare("sltiu") == 0 || instruction.at(0).compare("beq") == 0 || instruction.at(0).compare("bne") == 0) {
        opcode = mapped_instruction.at(5);   // captura a string de 6 digitos do opcode
        string rs = map_registers.find(instruction.at(2))->second;   // mapeia a string de 5 digitos do registrador na posição capturada
        string rd = map_registers.find(instruction.at(1))->second;   // mapeia a string de 5 digitos do registrador na posição capturada

        if (instruction.at(0).compare("beq") == 0 || instruction.at(0).compare("bne") == 0) {
            string bin_next_instruction_address = hex_string_to_bin_string(instruction_address);
            unsigned int next_instruction_address = bin_string_to_int(bin_next_instruction_address) + 4; // corresponde ao Program Counter (PC) que contém sempre o endereço da instrução seguinte
            unsigned int address = map_labels.find(instruction.at(3))->second;
            address -= next_instruction_address; // pega a diferença entre a instrução que segue ao label e o PC
            string label = "000000000"+int_to_binary_string(address); // 0x00400000 = 0000 0000 0100 0000 0000 0000 0000 0000, é o valor mínimo. Os 9 bits à esquerda são o que faltam para compeltar 32 bits.
            label = label.substr(label.size()-16, 16); // garantir que a string possui apenas 16 posições.
            ins = new I_Instruction(instruction.at(0), opcode, rs, rd, label, instruction_address);
            return ins;
        }

        string imm = "000000000000000"+int_to_binary_string(atoi(instruction.at(3).c_str()));  // captura o número, o converte para decimal e então o converte para uma string no formato binário
        imm = imm.substr(imm.size()-16, 16);  // faz um substring que deixa os 16 bits menos significativos.
        ins = new I_Instruction(instruction.at(0), opcode, rs, rd, imm, instruction_address);
    }
    else if (instruction.at(0).compare("lw") == 0 || instruction.at(0).compare("sw") == 0) {
        opcode = mapped_instruction.at(4);  // captura a string de 6 digitos do opcode com uma posição anterior, pois lw e sw usam um argumento a menos na instrução
        string rs = "00000";    // como não tem declaração do rs na instrução, então defino como 0
        string rd = map_registers.find(instruction.at(1))->second;   // mapeia a string de 5 digitos do registrador na posição capturada
        string address = instruction.at(2);
        unsigned int first = address.find("("), last = address.find(")");
        unsigned int deslocamento = atoi(address.substr(0, first).c_str());
        string registrador = map_registers.find(address.substr(first+1, last-first-1))->second; // mapeia a string de 5 digitos do registrador na posição capturada
        unsigned int reg = bin_string_to_int(registrador);
        /*  NOTA: o que está sendo feito para recuperar o valor do registrador não é seu mapeamento em memória! É simplesmente
            pegar seu número correspondente como registrador. Iria exigir uma análise semântica do arquivo .ASM para saber qual é
            o endereço em memória que o registrador aponta, isso é complexo! */
        string imm = "000000000000000"+int_to_binary_string(deslocamento+reg);
        imm = imm.substr(imm.size()-16, 16);  // faz um substring que deixa os 16 bits menos significativos.
        ins = new I_Instruction(instruction.at(0), opcode, rs, rd, imm, instruction_address);
    }

    return ins;
}

/*
 * Cria um objeto instrução do tipo R
 */
R_Instruction* read_R_Instruction(string mips_instruction, string instruction_address) {
    vector<string> instruction;
    split_instruction(mips_instruction, instruction);
    return create_R_Instruction(instruction, instruction_address);
}

R_Instruction* create_R_Instruction(vector<string> &instruction, string instruction_address) {
    R_Instruction *ins;
    vector<string> mapped_instruction = map_instructions.find(instruction.at(0))->second;   // mapeia o nome da instrução retornando um vetor com os dados do txt
    string opcode = mapped_instruction.at(5);   // captura a string de 6 digitos do opcode
    string rd = map_registers.find(instruction.at(1))->second;   // mapeia a string de 5 digitos do registrador na posição capturada
    string funct = mapped_instruction.at(10);   // string de 6 digitos do funct na posição capturada

    if (instruction.at(0).compare("add") == 0 || instruction.at(0).compare("addu") == 0 || instruction.at(0).compare("and") == 0 || instruction.at(0).compare("slt") == 0) {
        string rs = map_registers.find(instruction.at(2))->second;   // mapeia a string de 5 digitos do registrador na posição capturada
        string rt = map_registers.find(instruction.at(3))->second;   // mapeia a string de 5 digitos do registrador na posição capturada
        string shamt = mapped_instruction.at(9);   // string de 5 digitos do shamt na posição capturada
        ins = new R_Instruction(instruction.at(0), opcode, rs, rt, rd, shamt, funct, instruction_address);
    }
    else if (instruction.at(0).compare("sll") == 0 || instruction.at(0).compare("srl") == 0) {
        string rs = "00000";    // como não tem declaração do rs na instrução, então defino como 0
        string rt = map_registers.find(instruction.at(2))->second;   // mapeia a string de 5 digitos do registrador na posição capturada
        string shamt = "0000"+int_to_binary_string(atoi(instruction.at(3).c_str()));    // converte a string decimal para um valor decimal e então converte para uma string no formato binário
        shamt = shamt.substr(shamt.size()-5, 5);   // faz um substring que deixa apenas os 5 bits menos significativos
        ins = new R_Instruction(instruction.at(0), opcode, rs, rt, rd, shamt, funct, instruction_address);
    }

    return ins;
}


string read_asm(string file_path) {
    unsigned int instruction_address = 4194304; // 0x00400000
    ifstream file(file_path.c_str());
    string line, output_hexadecimal_instruction_code = "";
    while (getline(file, line)) {
        cout << line << endl;
        if (line.find(".") == 0)   // se não for uma instrução, simplesmente pula p/ próx. repetição
            continue;
        unsigned int label = line.find(":");
        if (label != string::npos) {
            string key = line.substr(0, label);
            map_labels[key] = instruction_address;
            continue;
        }
        vector<string> instruction;
        split_instruction(line, instruction);
        vector<string> mapped_instruction = map_instructions.find(instruction.at(0))->second;   // mapeia o nome da instrução retornando um vetor com os dados do txt
        string type = mapped_instruction.at(0);     // recebe R, I ou J
        /*  NOTA: só é possível a montagem de instruções de salto condicional e incondicional se o label de
            salto já tiver sido lido e armazenado no map de labels! */
        if (type.compare("R") == 0) {
            R_Instruction *ins;
            ins = create_R_Instruction(instruction, int_to_hexa_string(instruction_address));
            output_hexadecimal_instruction_code += ins->getHexadecimal_instruction();
            cout << ins->getBinary_instruction() << endl;
            delete ins;
        }
        else if (type.compare("I") == 0) {
            I_Instruction *ins;
            ins = create_I_Instruction(instruction, int_to_hexa_string(instruction_address));
            output_hexadecimal_instruction_code += ins->getHexadecimal_instruction();
            cout << ins->getBinary_instruction() << endl;
            delete ins;
        }
        else if (type.compare("J") == 0) {
            J_Instruction *ins;
            ins = create_J_Instruction(instruction, int_to_hexa_string(instruction_address));
            output_hexadecimal_instruction_code += ins->getHexadecimal_instruction();
            cout << ins->getBinary_instruction() << endl;
            delete ins;
        }
        else
            cout << "TIPO DE INSTRUÇÃO NÃO IMPLEMENTADO!" << endl;

        instruction_address += 4;
    }
    file.close();
    return output_hexadecimal_instruction_code;
}

void write_file(string instructions, string file_name) {
    ofstream file(file_name.c_str());
    file << instructions;
    file.close();
}

string read_hexadecimal(string file_path) {
    ifstream file(file_path.c_str());
    string line, output_asm_instruction = ".text\n.global main\nmain:\n";
    while (getline(file, line)) {
        /*  NOTA: não é decodificado instruções de salto nem lw e sw! */
        string binary_line = "000000000000000"+hex_string_to_bin_string(line);
        binary_line = binary_line.substr(binary_line.size()-32, 32); // garantir que a string tenha 32 posições.
        string opcode = binary_line.substr(0, 6);
        cout << binary_line << endl;
        if (opcode.compare("000000") == 0) {    // é tipo R
            string funct = binary_line.substr(binary_line.size()-6, 6);
            string rd = binary_line.substr(16, 5);
            rd = "$"+bin_string_to_int(rd); // formato de registrador $numero
            string rt = binary_line.substr(11, 5);
            rt = "$"+bin_string_to_int(rt); // formato de registrador $numero

            string instruction_name = map_opcode_funct.find(funct)->second;
            output_asm_instruction += instruction_name + " " + rd + ", ";

            if (instruction_name.compare("sll") == 0 || instruction_name.compare("srl") == 0) {
                string aux = binary_line.substr(21, 5);
                int shamt = (int) bin_string_to_int(aux);
                aux = ""+shamt;
                output_asm_instruction += rt + ", " + aux;
            }
            else {
                string rs = binary_line.substr(6, 5);
                rs = "$"+bin_string_to_int(rs); // formato de registrador $numero
                output_asm_instruction += rs + ", " + rt;
            }
        }
        else if (opcode.compare("001000") == 0 || opcode.compare("001001") == 0 || opcode.compare("001100") == 0 || opcode.compare("001011") == 0) { // se for addi, addiu, andi ou sltiu
            string instruction_name = map_opcode_funct.find(opcode)->second;
            string rs = binary_line.substr(6, 5);
            rs = "$"+bin_string_to_int(rs); // formato de registrador $numero
            string rd = binary_line.substr(11, 5);
            rd = "$"+bin_string_to_int(rd); // formato de registrador $numero
            string aux = binary_line.substr(16, 16);
            int imm = (int) bin_string_to_int(aux);
            aux = ""+imm;
            output_asm_instruction += instruction_name + " " + rd + ", " + rs + ", " + aux;
        }

        output_asm_instruction += "\n";
    }
    file.close();
    return output_asm_instruction;
}
