#pragma once


#include <cstdint>
#include <fstream>



class Header
{

public:
    void load(std::fstream &f);
    void dump(std::fstream &f);

    // Header
    uint32_t signature;
    uint16_t package_version;
    uint16_t licensee_version;
    uint32_t package_flags;
    uint32_t name_count;
    uint32_t name_offset;
    uint32_t export_count;
    uint32_t export_offset;
    uint32_t import_count;
    uint32_t import_offset;
    uint8_t guid[16];
    uint32_t generation_count;
};


// Generation entries contain information on how many export and name table entries 
// are in previous versions (or generations) of the package. 
// This is used in client-server negotiation for indentifiying out of date packages.
class GenerationEntry
{
public:
    void load(std::fstream &f);
    void dump(std::fstream &f);

    uint32_t export_count; 
    uint32_t name_count;
};

class NameEntry
{
public:
    void load(std::fstream &f);
    void dump(std::fstream &f);

    bool is_unicode; 

    std::string name;
    std::wstring wname;     // if unicode is true, then the name is stored as a 16-bit unicode string

    uint32_t flags;
};

class ExportEntry
{
public:
    void load(std::fstream &f);
    void dump(std::fstream &f);

    int32_t class_index; // index type
    int32_t super_index; // index type
    int32_t outer_index; // normal int32 (fuck you tim sweeney)
    int32_t name_index;  // index type
    uint32_t object_flags; 
    int32_t serial_size;   // index type
    int32_t serial_offset; // index type
};

class ImportEntry
{
public:
    void load(std::fstream &f);
    void dump(std::fstream &f);

    int32_t package_index; // package to import this object from.
    int32_t class_index;   // class of the imported object.
    int32_t outer_index;   // once again, normal int32 (fuck you tim sweeney)
    int32_t name_index;    
};

