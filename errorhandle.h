#define FileNotFound 0
#define MallocFail 1
#define ReadError 2
#include <string.h>

char errMessage[30][30];

void initHandler()
{
    strcpy(errMessage[FileNotFound], "File not found.");
    strcpy(errMessage[MallocFail], "Memory allocation failure.");
    strcpy(errMessage[ReadError], "Unknown error occured while reading file.");

}



void ErrorMsg(int errcode)
{
    printf("ERROR: ");
    printf("%s ",  errMessage[errcode]);
    printf("Proceeding to exit.\n");
}
