#pragma once

#include "package.hpp"

#include <vector>

class UTUnpacker
{
public:
    UTUnpacker();
    ~UTUnpacker();

    void load(std::fstream &f);
    void dump(std::fstream &f);

    Header header;
    std::vector<GenerationEntry> generation_table;
    std::vector<NameEntry> name_table;
    std::vector<ExportEntry> export_table;
    std::vector<ImportEntry> import_table;


    void print_header();
    void print_generation_table();
    void print_name_table();
    void print_export_table();
    void print_import_table();

    void dump_textures(std::string path);

private:
    // name lookup
    std::string name_lookup(int32_t name_index); 
    std::wstring wname_lookup(int32_t name_index);

    // classes can only be ascii
    std::string class_lookup(int32_t class_index);


    std::string outer_lookup(int32_t outer_index);

};
