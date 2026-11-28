Index and search:
  stats                          Corpus totals and most reused imports
  binaries [glob]                List indexed ELF objects (e.g. binaries *httpd*)
  inspect <binary>               ELF metadata and symbol/dependency counts
  search <symbol-glob> [--all]   Find symbol names (e.g. search 'rdp_*')

Cross-references:
  symbol <name>                  List objects importing/exporting a symbol
  importers <name>               List objects importing a symbol
  exporters <name>               List objects exporting a symbol
  imports <binary> [--all]       Undefined dynamic symbols in a binary
  exports <binary> [--all]       Defined public dynamic symbols in a binary
  needed <binary>                Declared DT_NEEDED libraries
  users <library-name>           Objects declaring DT_NEEDED on that name
  common <bin1> <bin2> [--all]   Shared imported symbols
  only <bin1> <bin2> [--all]     Symbols imported by bin1 but not bin2



functions needed:
1. General Information
Command What it does
binaries [pattern]  Lists indexed ELF files, optionally filtering by a wildcard pattern.
inspect <binary>  Displays an ELF's metadata, import count, export count, and library dependency count.
stats Displays statistics about the entire indexed corpus.

Data structure usage: ELF list for metadata and file listings; all three lists for statistics.
2. Binary Cross-Reference
Command What it does
imports <binary>  Lists all symbols imported by a particular ELF.
exports <binary>  Lists all symbols exported by a particular ELF.

Data structure usage: Find the ELF node, traverse the relation list, filter by role, and retrieve the associated symbol nodes.
3. Symbol Cross-Reference
Command What it does
importers <symbol>  Lists all ELFs importing a particular symbol.
exporters <symbol>  Lists all ELFs exporting a particular symbol.
symbol <name> Displays both importers and candidate exporters of a symbol.

Data structure usage: Find the symbol node, traverse the relation list, filter by role, and retrieve the associated ELF nodes.
4. Library Dependencies
Command What it does
needed <binary> Lists shared libraries that an ELF declares as dependencies, including possible matching library files.
users <library> Lists all ELFs declaring a dependency on a particular library name.

Data structure usage: ELF list and the needed, soname, and aliases attributes. No relation list traversal is required.
5. Binary Comparison
Command What it does
common <binary1> <binary2>  Lists symbols imported by both binaries.
only <binary1> <binary2>  Lists symbols imported by the first binary but not the second.

Data structure usage: Retrieve imported symbols for both ELF nodes, then perform set intersection or set difference.
6. Symbol Search
Command What it does
search <pattern>  Searches for symbol names matching a wildcard pattern and displays their importer and exporter counts.

Example:
xref> search 'rdp_*'

rdp_getObj          imports=12  exports=1
rdp_updateFirmware  imports=2   exports=1


Illustrative output.

Data structure usage: Traverse the symbol list, match names against the pattern, and count corresponding relations.
7. Shell Management
Command What it does
help  Displays available commands and their usage.
quit  Exits the program.
exit  Same as quit.


. Mandatory MLL Functions (Grading Rubric)
Separate from the analytical commands above, we need to implement the following 20 operations for the Type B assignment.
No. Required function
1 Insert an ELF node.
2 Insert a symbol node.
3 Insert a relation node.
4 Delete an ELF node.
5 Delete a symbol node.
6 Delete a relation node.
7 Find an ELF node.
8 Find a symbol node.
9 Find a relation between a particular ELF and symbol.
10  Show all ELF nodes.
11  Show all symbol nodes.
12  Show all symbols related to a particular ELF.
13  Show all ELFs related to a particular symbol.
14  Show every ELF with its related symbols and relation information.
15  Show every symbol with its related ELFs and relation information.
16  Count symbols related to a particular ELF.
17  Count ELFs related to a particular symbol.
18  Count symbols without any related ELF.
19  Count ELFs without any related symbol.
20  Edit a relation's ELF endpoint and/or symbol endpoint, supporting changes to either.










1. General Information
binaries [pattern]  Lists indexed ELF files, optionally filtering by a wildcard pattern.

inspect <binary>  Displays an ELF's metadata, import count, export count, and library dependency count.

stats Displays statistics about the entire indexed corpus.

Data structure usage: ELF list for metadata and file listings; all three lists for statistics.


Binaries: 
print all ELF path, can filter with a pattern (idk how to do that)
its basically just a print function that prints info.path

inspect:
just prints binary info
no other bullshit, just prints the info

stats:
big print function
takes in all 3 lists
find the data from elf list, rel, sym
prints the number of elf,,,,, ill do this later



2. Binary Cross-Reference

imports <binary>  Lists all symbols imported by a particular ELF.

exports <binary>  Lists all symbols exported by a particular ELF.

imports & exports:
find the elf node address first, then goes to the rel list and find that address, when found then filter by role, then get the address of symbol node, then print the name of the symbol
so we need:
elf name search
path name normalize print from addr for each
import export function that takes in elf addr, im/ex type, all or limited type for --all

find x
...: y
loops rel till end
  finds x in rel, filter by type
    get sym addr
    print sym name from addr


3. Symbol Cross-Reference

importers <symbol>  Lists all ELFs importing a particular symbol.

exporters <symbol>  Lists all ELFs exporting a particular symbol.

symbol <name> Displays both importers and candidate exporters of a symbol.


basically the same thing as above, just flip the addr around
so we need:
sym name search
importer exporter function that takes in sym addr, im/ex type or both

4. Library Dependencies

needed <binary> Lists shared libraries that an ELF declares as dependencies, including possible matching library files.

users <library> Lists all ELFs declaring a dependency on a particular library name.

needed:
search the elf list for the name, then it passes the addres to a function that takes elf addr, looks at its needed list, for each item there it looks the elf list again for a matching soname or path or alias, then outputs the path or alias

so we need:
needed function that takes in elf addr, then iterates through each needed entry. 
function that takes in the needed entry, then traverses the elf list for that entry, matching soname/path/alias, and then prints.

users:
basically just traverses through the elf list looking at their needed list if it has the library name thats being searched


should we make a generalized printer?
it prints from a list that takes in strings, and outputs it. this should be able to handle the --all flag, much better implementation for stacks

actually stack implementation just for a damn dyn array is fucking stupid



5. Binary Comparison

common <binary1> <binary2>  Lists symbols imported by both binaries.

only <binary1> <binary2>  Lists symbols imported by the first binary but not the second.


common:
find each of the binary name and get their addr
traverse through the relation list for each, putting each of the sym entry in a list
then compare each element in list 1 to list 2, if its on the 2nd list, then copy the data to a 3rd list
do that till list 1 is done
then list 3 will be the final list thats gonna get printed

only: basically the same, but the logic is reversed, only putting to the 3rd list if its not on the 2nd list

find x, find y
rel list traverse, conditional for x and y
put the sym addr to a list, for each
comparison for each, put into list if condition matches

so we need:
reuse find function
function to create list
function to put thing into list
function to compare each items in the list
reuse print function


6. Symbol Search

search <pattern>  Searches for symbol names matching a wildcard pattern and displays their importer and exporter counts.

its just a search function, but can filter according to a pattern. it then traverses the rel list to count the imports and exports





Insert an ELF node.
Insert a symbol node.
Insert a relation node.

Delete an ELF node.
Delete a symbol node.
Delete a relation node.

Find an ELF node. done
Find a symbol node. done

Find a relation between a particular ELF and symbol. done


Show all ELF nodes. done
Show all symbol nodes. done
Show all symbols related to a particular ELF. done
Show all ELFs related to a particular symbol. done


Show every ELF with its related symbols and relation information. done

Show every symbol with its related ELFs and relation information. done

Count symbols related to a particular ELF. done

Count ELFs related to a particular symbol. done

Count symbols without any related ELF. 

Count ELFs without any related symbol.

Edit a relation's ELF endpoint and/or symbol endpoint, supporting changes to either.
