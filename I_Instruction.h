//
// Created by Pedro on 07/05/2016.
//

#ifndef T1_OAC_I_I_INSTRUCTION_H
#define T1_OAC_I_I_INSTRUCTION_H

#include <string>

class I_Instruction {
private:
    std::string instruction_name, binary_instruction, hexadecimal_instruction, opcode, rs, rd, imm, instruction_address;
public:
    I_Instruction(std::string instruction_name, std::string opcode, std::string rs, std::string rd, std::string imm, std::string instruction_address);
    void setBinary_instruction(std::string binary_instruction);
    void setHexadecimal_instruction(unsigned int decimal);
    std::string getBinary_instruction();
    std::string getHexadecimal_instruction();
    std::string getInstruction_address();
};


#endif //T1_OAC_I_I_INSTRUCTION_H
