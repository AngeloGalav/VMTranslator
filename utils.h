#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* mystrtok(char* stringa, char delim);
void int2str(char *stringa, int intero);
int myatoi(char* str);
int checkExtension (char* filname, char* extension);