//
// Created by Pedro on 06/05/2016.
//

#ifndef T1_OAC_I_NUMERIC_BASE_CONVERTER_H
#define T1_OAC_I_NUMERIC_BASE_CONVERTER_H

#include <string>

unsigned int bin_string_to_int(std::string &bin);
std::string int_to_hexa_string(unsigned int num);
std::string int_to_binary_string(unsigned int dec);
std::string hex_string_to_bin_string(std::string &hex);

#endif //T1_OAC_I_NUMERIC_BASE_CONVERTER_H
