#ifndef ELFLIST_H_INCLUDED
#define ELFLIST_H_INCLUDED

#include <iostream>

using namespace std;

typedef struct elemenElf* adrElf;
typedef struct elemenSym* adrSym;
typedef struct elemenRel* adrRel;
typedef struct elemenGeneric* adrGrc;
typedef struct elemenDynsym* adrDynsym;

struct Elfinfo{
        int id;
        int fileSize;
        string path;
        string machine;
        string elfClass;
        string endian;
        string soname;
        string origin;
        adrGrc needed;
        adrGrc aliases;
};

struct DynsymEvidence{
        int symbolIdx;
        string rawName;
        string role;
        string type;
        string binding;
        string visibility;
};

struct RelInfo{
        int id;
        string roles;
        string origin;
        adrDynsym evidence;	
};

struct SymInfo{
        int id;
        string name;
        string origin;
};


struct elemenGeneric{
	string info;
	adrGrc next;
};

struct elemenDynsym{
	DynsymEvidence info;
	adrDynsym next;
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

struct grcList{
	adrGrc head;
	int size;
};

struct dynsymList{
	adrDynsym head;
	int size;
}:

struct elfList{
        adrElf head;
        adrElf tail;
        int size;
        int nextId;
};

struct symList{
        adrSym head;
        adrSym tail;
        int size;
        int nextId;
};

struct relList{
        adrRel head;
        adrRel tail;
        int size;
        int nextId;
};


//function definitions
//create lists
void createElfList(elfList &L);
void createSymList(symList &L);
void createRelList(relList &L);
void createGrcList(grcList &L);
void createDynsymList(dynsymList &L);

//create elements
adrElf createElfElm(ElfInfo E);



#endif
