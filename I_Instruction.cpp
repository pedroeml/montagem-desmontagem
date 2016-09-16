//
// Created by Pedro on 07/05/2016.
//

#include "I_Instruction.h"
#include "numeric_base_converter.h"

using namespace std;

I_Instruction::I_Instruction(std::string instruction_name, std::string opcode, std::string rs, std::string rd, std::string imm, std::string instruction_address) {
    this->instruction_name = instruction_name;
    this->opcode = opcode;
    this->rs = rs;
    this->rd = rd;
    this->imm = imm;
    this->instruction_address = instruction_address;
    setBinary_instruction(opcode + rs + rd + imm);
    setHexadecimal_instruction(bin_string_to_int(this->binary_instruction));
}

void I_Instruction::setBinary_instruction(std::string binary_instruction) {
    this->binary_instruction = binary_instruction;
}

void I_Instruction::setHexadecimal_instruction(unsigned int decimal) {
    this->hexadecimal_instruction = int_to_hexa_string(decimal);
}

std::string I_Instruction::getBinary_instruction() {
    return this->binary_instruction;
}

std::string I_Instruction::getHexadecimal_instruction() {
    return this->hexadecimal_instruction;
}

std::string I_Instruction::getInstruction_address() {
    return this->instruction_address;
}
