#include "unpacker.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    std::fstream f;
    f.open(argv[1], std::ios::in | std::ios::binary);

    if (!f.is_open())
    {
        std::cout << "FATAL: Could not open file. Exiting..." << std::endl;
        return 1;
    }

    UTUnpacker unpacker;
    unpacker.load(f);

    f.close();


    // print the header
    unpacker.print_header();

    // print the generation table
    unpacker.print_generation_table();


    // print the import table
    unpacker.print_import_table();

    // print the export table
    unpacker.print_export_table();

    // print the name table
    unpacker.print_name_table();


    return 0;
}