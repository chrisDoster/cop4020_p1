#include "parser.h"

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
	if (tok[0] == '\n')
	{
		lineNo++;
	}
	if (tok[0] == '~')
	{
		// ignore the token
	}
	
	int type = lookup(tok);
	/*if ((type == NOT_FOUND) && isValidID(tok))
	{
		insert(tok, type, lineNo)
	}*/
	
	return DONE;
}