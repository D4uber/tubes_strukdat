#ifndef ELFLIST_H_INCLUDED
#define ELFLIST_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

typedef struct elemenELF *adrELF;
struct elf{
	int64_t id;
	int fileSize;
	string path;
	string machine;
	string elfClass;
	string endian;
	string sonamei;
  string origin;
  vector<string> needed;
  vector<string> aliases;
}
struct elemenELF{
  ELF info;
  adrELF next;
}
struct elfList{
  adrELF head;
  adrELF tail;
  size_t size;
  uint64_t nextId;
}
