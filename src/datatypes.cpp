#include "datatypes.hpp"

#include <vector>


// INDEX================================================================================================
//     - The compact index is a value with a length of 1 to 5 bytes, representing a 32 bit signed integer.
//     - The first byte contains a sign bit, and a flag bit inidicating if there are more bytes to read.
//     - The remaining bytes contain 7 bits of the value, with the most significant bit of each byte 
//         indicating if there are more bytes to read.


void read_index(std::fstream &f, int32_t &index)
{
    uint8_t byte;
    bool more;
    bool sign;
    index = 0;

    // read first byte
    f.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    sign = byte & 0x80; // bit 7 
    more = byte & 0x40; // bit 6
    index = byte & 0x3F;  

    // read remaining bytes
    while (more)
    {
        f.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        more = byte & 0x80; // bit 7
        index = (index << 7) | (byte & 0x7F); // shift index left 7 bits, then OR with the 7 bits of the byte
    }

    // set sign bit.
    if (sign)
    {
        index = -index;
    }
}

void dump_index(std::fstream &f, int32_t index)
{
    uint8_t byte;
    bool more;
    bool sign;

    // set sign
    sign = index < 0;
    if (sign)
    {
        index = -index;
    }

    // write first byte
    more = index > 0x3F; // 0x3F = 0011 1111
    byte = (sign << 7) | (more << 6) | (index & 0x3F); // set the sign, more and index bits
    f.write(reinterpret_cast<char*>(&byte), sizeof(byte));

    // write remaining bytes
    while (more)
    {
        index = index >> 7; // shift index right 7 bits
        more = index > 0x7F; // 0x7F = 0111 1111
        byte = (more << 7) | (index & 0x7F); // set the more and index bits
        f.write(reinterpret_cast<char*>(&byte), sizeof(byte));
    }
}

void read_asciiz(std::fstream &f, std::string &string)
{
    // read null terminated string from file

    int8_t c;
    string.clear();

    while (c != '\0')
    {
        f.read(reinterpret_cast<char*>(&c), sizeof(c));
        string.push_back(c);

        if (f.eof())
        {
            throw std::runtime_error("unexpected end of file");
        }
    }
}

void dump_asciiz(std::fstream &f, std::string string)
{
    f.write(string.c_str(), string.size());
    f.put('\0');
}

void read_unicodez(std::fstream &f, std::wstring &string)
{
    // read null terminated string from file

    int16_t c;
    string.clear();


    while (c != '\0')
    {
        f.read(reinterpret_cast<char*>(&c), sizeof(c));
        string.push_back(c);

        if (f.eof())
        {
            throw std::runtime_error("unexpected end of file");
        }
    }
}

void dump_unicodez(std::fstream &f, std::wstring string)
{
    // Reinterpret_cast from 'const wchar_t *' to 'char *' casts away qualifiers

    f.write(reinterpret_cast<const char*>(string.c_str()), string.size() * sizeof(wchar_t));
    // write unicode null terminator
    f.put('\0');
    f.put('\0');
}

void read_string_index(std::fstream &f, bool &is_unicode, uint32_t &length)
{
    int32_t index;
    read_index(f, index);

    is_unicode = index < 0;
    length = abs(index);
}

void dump_string_index(std::fstream &f, bool is_unicode, uint32_t length)
{
    int32_t index = is_unicode ? -length : length; 
    dump_index(f, index);
}

void read_string(std::fstream &f, std::string &string, uint32_t length)
{
    string.clear();
    string.resize(length); // resize string to length

    f.read(&string[0], length);
}

void dump_string(std::fstream &f, std::string string)
{
    f.write(string.c_str(), string.size());
}

void read_string(std::fstream &f, std::wstring &string, uint32_t length)
{
    string.clear();
    string.resize(length); // resize string to length (not bytes)

    f.read(reinterpret_cast<char*>(&string[0]), length * sizeof(wchar_t));
}


void dump_string(std::fstream &f, std::wstring string)
{
    // Reinterpret_cast from 'const wchar_t *' to 'char *' casts away qualifiers

    f.write(reinterpret_cast<const char*>(string.c_str()), string.size() * sizeof(wchar_t));
}