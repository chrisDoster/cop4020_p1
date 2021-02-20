#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "parser.h"


// SCANNER
int pos=0, lookahead=-1;
bool done = false;
bool eofReached(FILE* f)
{
	if (!done)
	{
		done = feof(f);
		return done;
	}
	return done;
}
bool isWhiteSpace(int ch)
{
	if ((char)ch == ' ' || (char)ch == '\t')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isDelimiter(int ch) // note: delimiter refers to any character that will stop the token-extraction process, white spaces are included as well as all legal operators
{
	if (isWhiteSpace(ch) || (char)ch == '+' || (char)ch == '-' || (char)ch == '*' 
		|| (char)ch == '/' || (char)ch == ';' || (char)ch == '(' || (char)ch == ')')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isNewLine(int ch)
{
	if ((char)ch == '\n')
	{
		return true;
	}
	return false;
}
char* nextToken(FILE* f)
{
	char* tok = NULL;
	int ch = getc(f);
	int start = pos;
	while (!isDelimiter(ch) && !eofReached(f)) // while the next character(ch) is not a delimiter
	{
		ch = getc(f);
		// puts("one");
		pos++;
	}
	int numCharacters = pos - start;
	// ch is a delimiter at this point
	fseek(f, start, SEEK_SET);
	tok = (char*) malloc((numCharacters+1)*sizeof(char)); // allocate space for string
	for (int i=0; i < numCharacters; ++i)
	{
		// puts("two");
		tok[i] = getc(f);
	}
	tok[numCharacters] = '\0';
	
	// find start of next token
	while (isWhiteSpace(ch = getc(f)) && !eofReached(f))
	{
		// puts("three");
		pos++;
	}
	
	// ensure file points to first char of next tok
	fseek(f, -1, SEEK_CUR);
	
	return tok;
}


// SYMBOL TABLE
// struct serving as a single entry for a particular id
typedef struct symbol symbol;
struct symbol
{
	symbol* next;
	char* id;
	int type;
	int line;
};
// symbol table
struct symbol_table
{
	struct symbol*	table;
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


// PARSER
int lineNo = 1;

bool isValidID(char* s)
{
	// fixme
	return true;
}
bool isValidNum(char* s)
{
	// fixme
}
char* errorMsg()
{
	// fixme
	return "error not yet implemented";
}
int analyze(char* tok)
{
	int type = lookup(tok);
	/*if ((type == NOT_FOUND) && isValidID(tok))
	{
		insert(tok, type, lineNo)
	}*/
}




int line = 0;
struct symbol_table st;

int main(int argc, char* argv[])
{
	FILE* fp = NULL;
	fp = fopen(argv[1], "r");
	
	if (fp != NULL)
	{
		puts("start");
		
		while (!eofReached(fp))
		{
			//puts("four");
			// get next token and check validity
			char* token = nextToken(fp);
			bool valid = (token != NULL);
			if (valid)
			{
				// if token is valid, print token
				puts(token);
			}
			else
			{
				// if token invalid, print error message
				puts(errorMsg()); 
			}
			free(token);
		}
		
		puts("end");
		fclose(fp);
	}
	else
	{
		perror("file error");
	}
}

