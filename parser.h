#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "symboltable.h"

#define NOT_FOUND 404
#define ID 400
#define NUMERIC 402
#define DONE 403

int analyze(char* tok);

#endif