#include "ellp.h"

//create list

void createElfList(elfList &L){
	L.head = nullptr;
	L.tail = nullptr;
	L.size = 0;
	L.nextid = 1;
}

void createSymList(symList &L){
	L.head = nullptr;
	L.tail = nullptr;
	L.size = 0;
	L.nextid = 1;
}

void createRelList(relList &L){
	L.head = nullptr;
	L.tail = nullptr;
	L.size = 0;
	L.nextid = 1;
}

void createGrcList(grcList &L){
	L.head = nullptr;
	L.size = 0;
}

void createDynsymList(dynsymList &L){
	L.head = nullptr;
	L.size = 0;
}

//create element

adrElf createElfElm(ElfInfo data){
	adrElf p = new elemenElf;
	p->info = data;
	p->next = nullptr;
	return p;
}

adrSym createSymElm(SymInfo data){
	adrSym p = new elemenSym;
	p->info = data;
	p->next = nullptr;
	return p;
}
