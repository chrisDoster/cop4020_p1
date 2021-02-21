#include "symboltable.h"

// SYMBOL TABLE
// struct serving as a single entry for a particular id
struct symbol
{
	Symbol* next;
	char* id;
	int type;
	int line;
};
// symbol table
struct symbol_table
{
	Symbol*	table;
};
void insert(char* s, int type, int line)
{
	// fixme
}
int lookup(char* s)
{
	// fixme
	return -1;
}