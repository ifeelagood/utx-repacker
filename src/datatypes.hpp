#pragma once

#include <cstdint>
#include <fstream>
#include <string>

// INDEX================================================================================================
//     The compact index is a value with a length of 1 to 5 bytes, representing a 32 bit signed integer.
//     the first byte contains a sign bit, and a flag bit inidicating if there are more bytes to read.
//     the remaining bytes contain 7 bits of the value, with the most significant bit of each byte
//     indicating if there are more bytes to read.
void read_index(std::fstream &f, int32_t &index);
void dump_index(std::fstream &f, int32_t index);


// ASCIIZ================================================================================================
//     The zero terminated ascii string is a sequence of ascii characters terminated by a null character.
void read_asciiz(std::fstream &f, std::string &string);
void dump_asciiz(std::fstream &f, std::string string);


// UNICODEZ============================================================================================
//     The zero terminated unicode string is a sequence of unicode characters terminated by a null character.
void read_unicodez(std::fstream &f, std::wstring &string);
void dump_unicodez(std::fstream &f, std::wstring string);

// STRING===============================================================================================   
//     a string is an INDEX, followed by either zero terminated ascii/unicode chars
//     the sign of the index determines the encoding (0 = ascii, 1 = unicode)
//     the absolute value of the index is the length of the string in chars including the null terminator
void read_string_index(std::fstream &f, bool &is_unicode, uint32_t &length);
void dump_string_index(std::fstream &f, bool is_unicode, uint32_t length);

// ascii/unicode string overloads
void read_string(std::fstream &f, std::string &string, uint32_t length);
void dump_string(std::fstream &f, std::string string);

void read_string(std::fstream &f, std::wstring &string, uint32_t length);
void dump_string(std::fstream &f, std::wstring string);
