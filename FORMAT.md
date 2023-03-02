# Unreal Package File Format

## Data Types

|Type|Name|Description|
|----|----|-----------|
|uint8 *|INDEX |Compact Index, represents up to 32 bits and a sign. See below|
|uint8 *|ASCIIZ|A null terminated string of 8 bit (ASCII) characters|
|uint16 *|UNICODEZ|A null terminated string of 16 bit (UNICODE) characters|
|uint8/uint16 * |
--- 
### Compact Index

The compact index is a value with a length of 1 to 5 bytes, representing a 32 bit signed integer.

The first byte:

|7|6|5|4|3|2|1|0|
|-|-|-|-|-|-|-|-|
|sign|next byte?|V5|V4|V3|V2|V1|V0|

If next byte is set, then the number extends to the next byte

The second byte:

|7|6|5|4|3|2|1|0|
|-|-|-|-|-|-|-|-|
|next byte?|V12|V11|V10|V9|V8|V7|V6|

and so on...

- Note: 5 byte compact index are almost never used If they are however, the 5 most significant bits are always zero, as 29 bits are already accounted for including the sign.


## File Format Structure 
- Package Version: 118
- Game: Postal 2


### Header


|Offset|Type|Name|Description|
|------|----|----|-----------|
|0|uint32|Package Signature|Always the byte sequence 0xC1 0x83 0x2A 0x9E|
|4|uint16|Package Version|The version of the file format|
|6|uint16|Licensee Version|Licensees may modify their package format. UT2004 writes version 29|
|8|uint32|Package Flags||
|12|uint32|Name Count|The number of entries in the name table|
|16|uint32|Name Offset|Byte position of the name table|
|20|uint32|Export Count|The number of entries in the export table|
|24|uint32|Export Offset|Byte position of the export table|
|28|uint32|Import Count|The number of entries in the import table|
|32|uint32|Import Offset|Byte position of the import table|
|36|uint64|Package GUID|64 bit package guid|
|44|uint32|Generation Count|The number of entries in the generation table|

## Generation Entry
Generation entries contain information on how many export and name table entries are in previous versions (or generations) of the package. This is used in client-server negotiation for indentifiying out of date packages.

---
|Type|Name|Description|
|----|----|-----------|
|uint32|Export Count|Number of entries in previous generation export table|
|uint32|Name Count|Number of entries in previous generation name table|


## Name Table
The size and position of the name table is specified in the header.

|Type|Name|Description|
|----|----|-----------|
|STRING|Name String|The name|
|uint32|Name Flags|Flags pertaining to name|




## Sources
https://wiki.beyondunreal.com/Unreal_package

https://utfiles.lagout.org/UEditor_Developing/UT-package-file-format.pdf

