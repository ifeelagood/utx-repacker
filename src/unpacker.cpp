#include "unpacker.hpp"
#include "package.hpp"

#include <fstream>
#include <iostream>

UTUnpacker::UTUnpacker()
{
}

UTUnpacker::~UTUnpacker()
{
}

void UTUnpacker::load(std::fstream &f)
{
    // load the header
    header.load(f);

    // load the generation table    
    if (header.signature != 0x9E2A83C1)
    {
        std::cout << "FATAL: Invalid signature. Exiting..." << std::endl;
        exit(1);
    }
    std::cout << "Loaded header.\n";

    // load the generation table
    for (int i = 0; i < header.generation_count; i++)
    {
        GenerationEntry entry;
        entry.load(f);
        generation_table.push_back(entry);
    }
    std::cout << "Loaded generation table.\n";


    // go to the name table
    f.seekg(header.name_offset);

    // load the name table
    for (unsigned int i = 0; i < header.name_count; i++)
    {
        NameEntry entry;
        entry.load(f);
        name_table.push_back(entry);
    }
    std::cout << "Loaded name table.\n";

    // go to the export table
    f.seekg(header.export_offset);

    // load the export table
    for (unsigned int i = 0; i < header.export_count; i++)
    {
        ExportEntry entry;
        entry.load(f);
        export_table.push_back(entry);
    }
    std::cout << "Loaded export table.\n";

    // go to the import table
    f.seekg(header.import_offset);

    // load the import table
    for (unsigned int i = 0; i < header.import_count; i++)
    {
        ImportEntry entry;
        entry.load(f);
        import_table.push_back(entry);
    }
    std::cout << "Loaded import table.\n";

    std::cout << "Finished loading file.\n";
}

void UTUnpacker::dump(std::fstream &f)
{
    // dump the header
    header.dump(f);

    // dump the generation table
    for (unsigned int i = 0; i < generation_table.size(); i++)
    {
        generation_table[i].dump(f);
    }

    // dump the name table
    for (unsigned int i = 0; i < name_table.size(); i++)
    {
        name_table[i].dump(f);
    }

    // dump the export table
    for (unsigned int i = 0; i < export_table.size(); i++)
    {
        export_table[i].dump(f);
    }

    // dump the import table
    for (unsigned int i = 0; i < import_table.size(); i++)
    {
        import_table[i].dump(f);
    }
}

void UTUnpacker::print_header()
{
    std::cout << "Header:\n";

    std::printf("\tSignature: 0x%08X\n", header.signature);
    std::printf("\tPackage Version: %d\n", header.package_version);
    std::printf("\tLicensee Version: %d\n", header.licensee_version);
    std::printf("\tFlags: 0x%08X\n", header.package_flags);
    std::printf("\tName Count: %d\n", header.name_count);
    std::printf("\tName Offset: 0x%08X\n", header.name_offset);
    std::printf("\tExport Count: %d\n", header.export_count);
    std::printf("\tExport Offset: 0x%08X\n", header.export_offset);
    std::printf("\tImport Count: %d\n", header.import_count);
    std::printf("\tImport Offset: 0x%08X\n", header.import_offset);
    std::printf("\tGeneration Count: %d\n", header.generation_count);
}

void UTUnpacker::print_generation_table()
{
    std::cout << "Generation Table:\n";

    for (unsigned int i = 0; i < generation_table.size(); i++)
    {
        std::printf("\tGeneration %d:\n", i);
        std::printf("\t\tExport Count: %d\n", generation_table[i].export_count);
        std::printf("\t\tName Count: %d\n", generation_table[i].name_count);
    }
}

void UTUnpacker::print_name_table()
{
    std::cout << "Name Table:\n";

    for (unsigned int i = 0; i < name_table.size(); i++)
    {
        std::printf("\tName %d:\n", i);
        std::printf("\t\tName: %s\n", name_table[i].name.c_str());
        std::printf("\t\tFlags: 0x%08X\n", name_table[i].flags);
    }
}

void UTUnpacker::print_export_table()
{
    std::cout << "Export Table:\n";

    for (unsigned int i = 0; i < export_table.size(); i++)
    {
        // get name
        std::string name = name_lookup(export_table[i].name_index);

        std::printf("\tExport %d:\n", i);
        std::printf("\t\tClass Index: %d\n", export_table[i].class_index);
        std::printf("\t\tSuper Index: %d\n", export_table[i].super_index);
        std::printf("\t\tOuter Index: %d\n", export_table[i].outer_index);
        std::printf("\t\tName: %s\n", name.c_str());
        std::printf("\t\tObject Flags: 0x%08X\n", export_table[i].object_flags);
        std::printf("\t\tSerial Size: %d\n", export_table[i].serial_size);
        
        if (export_table[i].serial_size > 0)
        {
            std::printf("\t\tSerial Offset: 0x%08X\n", export_table[i].serial_offset);
        }
    }
}

std::string UTUnpacker::name_lookup(int32_t name_index)
{
    return name_table[name_index].name;
}

std::wstring UTUnpacker::wname_lookup(int32_t name_index)
{
    return name_table[name_index].wname;
}

void UTUnpacker::print_import_table()
{
    std::cout << "Import Table:\n";

    for (unsigned int i = 0; i < import_table.size(); i++)
    {
        // get name
        std::string name = name_lookup(import_table[i].name_index);

        std::printf("\tImport %d:\n", i);
        std::printf("\t\tPackage Index: %d\n", import_table[i].package_index);
        std::printf("\t\tClass Index: %d\n", import_table[i].class_index);
        std::printf("\t\tOuter Index: %d\n", import_table[i].outer_index);
        std::printf("\t\tName: %s\n", name.c_str());
    }
}