#include "package.hpp"
#include "datatypes.hpp"

#include <fstream>


void Header::load(std::fstream &f)
{
    // use reinterpret cast
    f.read(reinterpret_cast<char*>(&signature), sizeof(signature));
    f.read(reinterpret_cast<char*>(&package_version), sizeof(package_version));
    f.read(reinterpret_cast<char*>(&licensee_version), sizeof(licensee_version));
    f.read(reinterpret_cast<char*>(&package_flags), sizeof(package_flags));
    f.read(reinterpret_cast<char*>(&name_count), sizeof(name_count));
    f.read(reinterpret_cast<char*>(&name_offset), sizeof(name_offset));
    f.read(reinterpret_cast<char*>(&export_count), sizeof(export_count));
    f.read(reinterpret_cast<char*>(&export_offset), sizeof(export_offset));
    f.read(reinterpret_cast<char*>(&import_count), sizeof(import_count));
    f.read(reinterpret_cast<char*>(&import_offset), sizeof(import_offset));
    f.read(reinterpret_cast<char*>(&guid), sizeof(guid));
    f.read(reinterpret_cast<char*>(&generation_count), sizeof(generation_count));
}

void Header::dump(std::fstream &f)
{
    f.write(reinterpret_cast<char*>(&signature), sizeof(signature));
    f.write(reinterpret_cast<char*>(&package_version), sizeof(package_version));
    f.write(reinterpret_cast<char*>(&licensee_version), sizeof(licensee_version));
    f.write(reinterpret_cast<char*>(&package_flags), sizeof(package_flags));
    f.write(reinterpret_cast<char*>(&name_count), sizeof(name_count));
    f.write(reinterpret_cast<char*>(&name_offset), sizeof(name_offset));
    f.write(reinterpret_cast<char*>(&export_count), sizeof(export_count));
    f.write(reinterpret_cast<char*>(&export_offset), sizeof(export_offset));
    f.write(reinterpret_cast<char*>(&import_count), sizeof(import_count));
    f.write(reinterpret_cast<char*>(&import_offset), sizeof(import_offset));
    f.write(reinterpret_cast<char*>(&guid), sizeof(guid));
    f.write(reinterpret_cast<char*>(&generation_count), sizeof(generation_count));
}

void NameEntry::load(std::fstream &f)
{
    uint32_t name_length;

    // read the name index
    read_string_index(f, is_unicode, name_length);
    
    // read into the correct string
    if (is_unicode)
    {
        read_string(f, wname, name_length);
    }
    else
    {
        read_string(f, name, name_length);
    };

    // read the flags
    f.read(reinterpret_cast<char*>(&flags), sizeof(flags));
}

void NameEntry::dump(std::fstream &f)
{
    uint32_t name_length = is_unicode ? wname.length() : name.length();

    // write the name index
    dump_string_index(f, is_unicode, name_length);

    // write the string
    if (is_unicode)
    {
        dump_string(f, wname);
    }
    else
    {
        dump_string(f, name);
    }
}


void ExportEntry::load(std::fstream &f)
{
    // load both the class and the super class indices
    read_index(f, class_index);
    read_index(f, super_index);

    
    // read the outer_index
    f.read(reinterpret_cast<char*>(&outer_index), sizeof(outer_index));

    // load the name index
    read_index(f, name_index);

    // read the flags
    f.read(reinterpret_cast<char*>(&object_flags), sizeof(object_flags));

    // load the serial size
    read_index(f, serial_size);

    // load the serial offset, if the serial size is > 0    
    if (serial_size > 0)
    {
        read_index(f, serial_offset);
    }
}

void ExportEntry::dump(std::fstream &f)
{
    // write both the class and the super class indices
    dump_index(f, class_index);
    dump_index(f, super_index);


    // write the outer_index
    f.write(reinterpret_cast<char*>(&outer_index), sizeof(outer_index));

    // write the nae index
    dump_index(f, name_index);

    // write the flags
    f.write(reinterpret_cast<char*>(&object_flags), sizeof(object_flags));

    // write the serial size
    dump_index(f, serial_size);

    // write the serial offset, if the serial size is > 0
    if (serial_size > 0)
    {
        dump_index(f, serial_offset);
    }
}

void ImportEntry::load(std::fstream &f)
{
    // load the package and class indices
    read_index(f, package_index);
    read_index(f, class_index);

    // read the outer_index
    f.read(reinterpret_cast<char*>(&outer_index), sizeof(outer_index));

    // load the name index
    read_index(f, name_index);
}

void ImportEntry::dump(std::fstream &f)
{
    // write the package and class indices
    dump_index(f, package_index);
    dump_index(f, class_index);

    // write the outer_index
    f.write(reinterpret_cast<char*>(&outer_index), sizeof(outer_index));

    // write the name index
    dump_index(f, name_index);
}

void GenerationEntry::load(std::fstream &f)
{
    f.read(reinterpret_cast<char*>(&export_count), sizeof(export_count));
    f.read(reinterpret_cast<char*>(&name_count), sizeof(name_count));
}
 
void GenerationEntry::dump(std::fstream &f)
{
    f.write(reinterpret_cast<char*>(&export_count), sizeof(export_count));
    f.write(reinterpret_cast<char*>(&name_count), sizeof(name_count));
}