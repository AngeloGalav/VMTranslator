#include "parser.h"

int main (int argc, char** argv)
{
    char* path_buf = malloc(sizeof(char)*64);

    if (argv[1] == NULL){
        printf("No input file specified...\n");
        return 0;
    }

    strcpy(path_buf, argv[1]);

    FILE *entry_file; // putantore al file che leggo
    FILE *output;

    if (checkExtension(path_buf, ".vm"))
    {
        strcpy(path_buf, argv[1]);
        // esegui la traduzione
        printf("Translating: %s\n", path_buf);
        entry_file = fopen(path_buf, "rw");

        char* name_without_extension;
        name_without_extension = mystrtok(path_buf, '.');
        
        // formattazione nome del nuovo file
        strcpy(path_buf, name_without_extension);
        strcat(path_buf, ".asm");

        printf("output: %s\n", path_buf);
        
        // output della compilazione (apre il file in append mode)
        output = fopen(path_buf, "a");

        // parsing del file iniziato.
        if (parseFile(entry_file, output, name_without_extension) == -1)
            printf("Error parsing file.\n");
        else printf("File translation successful!\n");

        printf("\n");
    } else {
        printf("File has the wrong extension. Aborting...\n");
    }

    return 0;
}