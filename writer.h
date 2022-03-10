#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "definitions.h"
#include "utils.h"

// ---- Funzioni generali ----
void init_write(char* nomeFile_, FILE* file);
void writeBoostrap();
void crea_id();
void end_write();

// ---- Comandi VM tradotti ----
void writeAdd();
void writeSub();
void writeNeg();
void writeAnd();
void writeOr();
void writeNot();

int writePop(char* arg1, char* arg2);
int writePush(char* arg1, char* arg2);

void writeLt();
void writeGt();
void writeEq();
void writeGoto(char* label);
void writeIfGoto(char* label);

void writeLabel(char* label);
void writeFunction(char* function, char* n);
void writeReturn();
void writeCall (char* called_function, char* number_of_args);