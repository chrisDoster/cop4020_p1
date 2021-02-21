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
bool isNewLine(int ch)
{
	if ((char)ch == '\n')
	{
		return true;
	}
	return false;
}
bool isWhiteSpace(int ch)
{
	if (isNewLine(ch) || (char)ch == ' ' || (char)ch == '\t')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isOperator(int ch)
{
	if ((char)ch == '+' || (char)ch == '-' || (char)ch == '*' || (char)ch == '/' || (char)ch == '=')
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
	if (isWhiteSpace(ch) || isOperator(ch) || (char)ch == ';' || (char)ch == '(' || (char)ch == ')')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool containsWhiteSpace(char* s)
{
	int i=0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		{
			return true;
		}
		i++;
	}
	return false;
}
char* nextToken(FILE* f)
{
	if (eofReached(f))
	{
		return NULL;
	}
	char* tok = NULL;
	int ch = getc(f);
	
	// find position of first non-whitespace character, the first character of the next token
	while (isWhiteSpace(ch) && !eofReached(f)) 
	{
		ch = getc(f);
		pos++;
	}
	int start = pos;
	
	// handle case that token is operator
	if (isDelimiter(ch))
	{
		pos++;
		tok = (char*) malloc(2*sizeof(char));
		tok[0] = ch;
		tok[1] = '\0';
		return tok;
	}
	
	// find position immediately after current token
	while (!isDelimiter(ch) && !eofReached(f)) // while the next character(ch) is not a delimiter
	{
		ch = getc(f);
		pos++;
	}
	int numCharacters = pos - start;
	
	// ch is a delimiter of some sort at this point
	fseek(f, start, SEEK_SET);
	
	tok = (char*) malloc((numCharacters+1)*sizeof(char)); // allocate space for string
	for (int i=0; i < numCharacters; ++i) // fill string with characters
	{
		tok[i] = getc(f);
	}
	tok[numCharacters] = '\0';
	
	// handle case that whitespace characters were somehow extracted, indicating error
	if (containsWhiteSpace(tok))
	{
		free(tok);
		tok = NULL;
	}
	
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
	symbol*	table;
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
	if (!isalpha(s[0]))
	{
		return false;
	}
	int i=0;
	while (s[i] != '\0')
	{
		if (!isalpha(s[i]) && !isdigit(s[i]) && s[i] != '_')
		{
			return false;
		}
		if (s[i] == '_')
		{
			if (s[i+1] == '_' || s[i+1] == '\0')
			{
				return false;
			}
		}
		i++;
	}
	return true;
}
bool isValidNum(char* s)
{
	int i=0;
	int numDots = 0;
	while (s[i] != '\0')
	{
		if (!isdigit(s[i]) && s[i] != '.')
		{
			return false;
		}
		if (s[i] == '.')
		{
			numDots++;
		}
		if (numDots > 1)
		{
			return false;
		}
		i++;
	}
	return true;
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
		
		int i=0;
		while (!eofReached(fp)) // EOF NOT REACHED : NEXTTOKEN RETURNING NULL
		{
			// get next token and check validity
			char* token = nextToken(fp);
			bool valid = isValidID(token);
			if (true)
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
			i++;
		}
		
		puts("end");
		fclose(fp);
	}
	else
	{
		perror("file error");
	}
}

