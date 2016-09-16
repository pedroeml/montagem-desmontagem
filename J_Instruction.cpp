//
// Created by Pedro on 07/05/2016.
//

#include "J_Instruction.h"
#include "numeric_base_converter.h"

using namespace std;

J_Instruction::J_Instruction(std::string instruction_name, std::string opcode, std::string label, std::string instruction_address) {
    this->instruction_name = instruction_name;
    this->opcode = opcode;
    this->label = label;
    this->instruction_address = instruction_address;
    setBinary_instruction(opcode + label);
    setHexadecimal_instruction(bin_string_to_int(this->binary_instruction));
}

void J_Instruction::setBinary_instruction(std::string binary_instruction) {
    this->binary_instruction = binary_instruction;
}

void J_Instruction::setHexadecimal_instruction(unsigned int decimal) {
    this->hexadecimal_instruction = int_to_hexa_string(decimal);
}

std::string J_Instruction::getBinary_instruction() {
    return this->binary_instruction;
}

std::string J_Instruction::getHexadecimal_instruction() {
    return this->hexadecimal_instruction;
}

std::string J_Instruction::getInstruction_address() {
    return this->instruction_address;
}
