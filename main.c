#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "parser.h"
#include "symboltable.h"


int line = 0;
SymbolTable* st;

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
			
			int type = analyze(token);
			switch(type)
			{
				case DONE:
					puts("done!!");
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
	
	free(st);
}

