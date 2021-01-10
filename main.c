#include <stdio.h>
#include <stdlib.h>
#include "errorhandle.h"
#define CHUNK 1024 /* read 1024 bytes at a time */


int main()
{
    initHandler();
    char *buf = malloc(CHUNK);
    FILE *file;
    size_t nread;
    file = fopen("input.txt", "r");


    if (buf == NULL) {
       ErrorMsg(MallocFail);
       return -1;
    }

    if (file == NULL) {
       ErrorMsg(FileNotFound);
       return -1;
    }

    if (file) {
         while ((nread = fread(buf, 1, CHUNK, file)) > 0){
            fwrite(buf, 1, nread, stdout);
        }
        if (ferror(file)) {
           ErrorMsg(ReadError);
           return -1;
        }
        fclose(file);
    }
}
