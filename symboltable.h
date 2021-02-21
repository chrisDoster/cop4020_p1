#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

struct symbol;
struct symbol_table;
typedef struct symbol Symbol;
typedef struct symbol_table SymbolTable;

void insert(char* s, int type, int line);
int lookup(char* s);


#endif