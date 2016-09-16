//
// Created by Pedro on 04/05/2016.
//

#include "R_Instruction.h"
#include "numeric_base_converter.h"

using namespace std;

R_Instruction::R_Instruction(std::string instruction_name, std::string opcode, std::string rs, std::string rt, std::string rd, std::string shamt, std::string funct, std::string instruction_address) {
    this->instruction_name = instruction_name;
    this->opcode = opcode;
    this->rs = rs;
    this->rt = rt;
    this->rd = rd;
    this->shamt = shamt;
    this->funct = funct;
    this->instruction_address = instruction_address;
    setBinary_instruction(opcode + rs + rt + rd + shamt + funct);
    setHexadecimal_instruction(bin_string_to_int(this->binary_instruction));
}

void R_Instruction::setBinary_instruction(std::string binary_instruction) {
    this->binary_instruction = binary_instruction;
}

void R_Instruction::setHexadecimal_instruction(unsigned int decimal) {
    this->hexadecimal_instruction = int_to_hexa_string(decimal);
}

std::string R_Instruction::getBinary_instruction() {
    return this->binary_instruction;
}

std::string R_Instruction::getHexadecimal_instruction() {
    return this->hexadecimal_instruction;
}

std::string R_Instruction::getInstruction_address() {
    return this->instruction_address;
}
