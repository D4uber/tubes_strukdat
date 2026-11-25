#ifndef ELFLIST_H_INCLUDED
#define ELFLIST_H_INCLUDED

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

typedef struct elemenElf* adrElf;
typedef struct elemenSym* adrSym;
typedef struct elemenRel* adrRel;

struct Elfinfo {
        uint64_t id;
        uint64_t fileSize;
        string path;
        string machine;
        string elfClass;
        string endian;
        string soname;
        string origin;
        vector<string> needed;
        vector<string> aliases;
};

struct DynsymEvidence{
        uint32_t symbolIdx;
        string rawName;
        string role;
        string type;
        string binding;
        string visibility;
};

struct RelInfo{
        uint64_t id;
        string roles;
        string origin;
        vector<DynsymEvidence> evidence;
};

struct SymInfo{
        uint64_t id;
        string name;
        string origin;
};

struct elemenElf {
        Elfinfo info;
        adrElf next;
};

struct elemenSym{
        SymInfo info;
        adrSym next;
};

struct elemenRel{
        RelInfo info;
        adrElf elf;
        adrSym Symbol;
        adrRel next;
};

struct elfList {
        adrElf head;
        adrElf tail;
        size_t size;
        uint64_t nextId;
};

struct symList{
        adrSym head;
        adrSym tail;
        size_t size;
        uint64_t nextId;
};

struct relList{
        adrRel head;
        adrRel tail;
        size_t size;
        uint64_t nextId;
};


#endif
