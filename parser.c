#include "parser.h"

/** Esegue il parsing del file.
 * 
 */
int parseFile(FILE* to_parse, FILE* output_file, char* filename){
    int line_count = 0;

    printf("Started parsing file...\n");

    if (output_file == NULL) {printf("ERROR: outfile is null.\n"); return -1;}
    if (to_parse == NULL) {printf("ERROR: infile is null\n"); return -1;}

    // inizializza file .asm
    init_write(filename, output_file);

    if (to_parse == NULL) {
        printf("Error: input file is NULL\n");
        return -1;
    }
    
    if (output_file == NULL) {
        printf("Error: output file is NULL\n");
        return -1;
    }

    // char * line = NULL;
    // while ((read = getline(&line, &len, to_parse)) != -1) {
    //     line_count++;
    //     if (DEBUG) printf("Reading line %d, ", line_count);
    //     if (parseLine(line) == -1 && DEBUG){ // esegui il parse della linea
    //         printf(" at line %d\n", line_count);
    //     }
    // }

    char line[BUFSIZ]; // rifatta usando i limiti imposti
    while(fgets(line, 64, to_parse) != NULL)
    {
        line_count++;
        if (DEBUG) printf("Reading line %d, ", line_count);
        if (parseLine(line) == -1 && DEBUG){ // esegui il parse della linea
            printf(" at line %d\n", line_count);
        }
    }

    return 0;
}


/** Fa il parsing di una linea unica.
 * 
 */
int parseLine(char* line_){
    char line[BUFSIZ];
    strcpy(line, line_);
    // eliminazione del carattere endline finale
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 2] = ' '; // se mettevo \0 c'erano
                                                                      // forti problemi di formattazione.
    char* token = mystrtok(line, ' ');

    while (token != NULL) {

        char* arg2;
        char* arg1 = mystrtok(NULL, ' ');
        if (arg1 != NULL) arg2 = mystrtok(NULL, ' ');

        if (strcmp(token, "add") == 0) writeAdd();
        else if (strcmp(token, "sub") == 0) writeSub();
        else if (strcmp(token, "neg") == 0) writeNeg();
        else if (strcmp(token, "and") == 0) writeAnd();
        else if (strcmp(token, "or") == 0) writeOr();
        else if (strcmp(token, "not") == 0) writeNot();
        else if (strcmp(token, "eq") == 0) writeEq();
        else if (strcmp(token, "gt") == 0) writeGt();
        else if (strcmp(token, "lt") == 0) writeLt();
        else if (strcmp(token, "return") == 0) writeReturn();
        else if (strcmp(token, "push") == 0) writePush(arg1, arg2);
        else if (strcmp(token, "pop") == 0) writePop(arg1, arg2);
        else if (strcmp(token, "label") == 0) writeLabel(arg1);
        else if (strcmp(token, "goto") == 0) writeGoto(arg1);
        else if (strcmp(token, "if-goto") == 0) writeIfGoto(arg1);
        else if (strcmp(token, "call") == 0) writeCall(arg1, arg2);
        else if (strcmp(token, "function") == 0) writeFunction(arg1, arg2);
        else {
            if (DEBUG)
            {
                printf("Parsing warning: unknown command %s,", line);
                return -1;
            }
        }   

        return 0;
    }

    return -1;
}