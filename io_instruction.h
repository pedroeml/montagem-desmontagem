//
// Created by Pedro on 11/05/2016.
//

#ifndef IO_INSTRUCTION_H_INCLUDED
#define IO_INSTRUCTION_H_INCLUDED

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include "numeric_base_converter.h"
#include "R_Instruction.h"
#include "I_Instruction.h"
#include "J_Instruction.h"

extern std::map<std::string, std::string> map_registers;
extern std::map<std::string, std::vector<std::string> > map_instructions;
extern std::map<std::string, unsigned int> map_labels;
extern std::map<std::string, std::string> map_opcode_funct;

void read_settings(std::string file_path, int select);
void split_instruction(std::string instruction, std::vector<std::string> &array_instruction);
J_Instruction* read_J_Instruction(std::string mips_instruction, std::string instruction_address);
J_Instruction* create_J_Instruction(std::vector<std::string> &instruction, std::string instruction_address);
I_Instruction* read_I_Instruction(std::string mips_instruction, std::string instruction_address);
I_Instruction* create_I_Instruction(std::vector<std::string> &instruction, std::string instruction_address);
R_Instruction* read_R_Instruction(std::string mips_instruction, std::string instruction_address);
R_Instruction* create_R_Instruction(std::vector<std::string> &instruction, std::string instruction_address);
std::string read_asm(std::string file_path);
void write_file(std::string instructions, std::string file_name);
std::string read_hexadecimal(std::string file_path);

#endif // IO_INSTRUCTION_H_INCLUDED
