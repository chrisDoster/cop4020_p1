#include "scanner.h"

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