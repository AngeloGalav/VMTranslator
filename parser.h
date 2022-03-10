#pragma once

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "writer.h"

int parseFile(FILE* to_parse, FILE* output_file, char* filename);
int parseLine(char* line);