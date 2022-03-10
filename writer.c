#include "writer.h"

int id = 0; // id usato per le label, aumenta ogni volta che si fanno operazioni che richiedono label
char nomeFile[BUFSIZ]; //nome file usato per gli static (da specificare in parser)
char* id_string;
FILE* file_to_write; // file in cui le righe di codice vengono scritte

char* current_function;
// se volessi definire delle funzioni inline (dentro a blocchi di codice),
// dovrei usare uno stack delle funzioni. 

/**
 * Svolge le operazioni iniziali.
 */
void init_write(char* nomeFile_, FILE* file) {
    current_function = malloc(sizeof(char) * BUFSIZ);
    id_string = malloc(sizeof(char) * 16);
    strcpy(current_function, ""); // inizializzo a una stringa vuota
    file_to_write = file;
    strcpy(nomeFile, nomeFile_);
    writeBoostrap();
}
/** Libera la memoria utilizzata da alcune strutture del file.
 * 
 */
void end_write(){
    free(id_string);
    free(current_function);
};

// operazioni iniziali per il processore HACK
void writeBoostrap(){
    fprintf(file_to_write, "%s", "@256\nD=A\n@SP\nM=D\n"); //lo stack parte da 256 e cresce verso l'alto.
}

/** Crea un id incrementando un valore numerico. 
 *  In questo si possono creare label unici per funzioni (per esempio).
 * 
 *  Very ez & simple.
 */
void crea_id(){
    id++;
    // sprintf(id_string, "%d", id);
    int2str(id_string, id);
}

// scrive nel file l'equivalente del comando ADD
void writeAdd(){
    fprintf(file_to_write, "%s", "@SP\nAM=M-1\nD=M\nA=A-1\nM=D+M\n");
    // prendo il valore della stack pointer, e poi lo aggiunge
    // con il valore subito dopo dello stack pointer  
}

// scrive nel file l'equivalente del comando SUB
void writeSub(){
    fprintf(file_to_write, "%s","@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n");
}

// scrive l'equivalente del comando NEG
void writeNeg(){
    fprintf(file_to_write, "%s", "@SP\nA=M-1\nM=-M\n");
    // Prende il valore nello stack pointer e lo nega
}

// scrive l'equivalente del comando AND
void writeAnd(){
    fprintf(file_to_write, "%s", "@SP\nAM=M-1\nD=M\nA=A-1\nM=D&M\n");
    // Prende i due valori dallo stack pointer (scalando lo stack), 
    // ed esegue l'and
}

// scrive l'equivalente del comando OR
void writeOr(){
    fprintf(file_to_write,"%s","@SP\nAM=M-1\nD=M\nA=A-1\nM=D|M\n");
    // Prende i due valori dallo stack pointer (scalando lo stack), 
    // ed esegue l'or
}

// scrive l'equivalente del comando NOT
void writeNot(){
    fprintf(file_to_write, "%s", "@SP\nA=M-1\nM=!M\n");
    // Uguale al NEG, ma fa il  not
}


int writePop(char* arg1, char* arg2){

    char* hack_cmd = malloc(sizeof(char) * BUFSIZ);

    if (strcmp(arg1, "local") == 0) //"punto" alla var locale
    {
        strcpy(hack_cmd, "@LCL\nD=M\n@");
        strcat(hack_cmd, arg2);
        strcat(hack_cmd, "\nD=D+A\n");
    } else 
    if (strcmp(arg1, "argument") == 0) //"punto" a un det. argomento
    {
        strcpy(hack_cmd, "@ARG\nD=M\n@");
        strcat(hack_cmd, arg2);
        strcat(hack_cmd, "\nD=D+A\n");
    } else 
    if (strcmp(arg1, "static") == 0)
    {
        // fa riferimento al file attuale 
        strcpy(hack_cmd, "@");
        strcat(hack_cmd, nomeFile);
        strcat(hack_cmd, ".");
        strcat(hack_cmd, arg2);
        strcat(hack_cmd, "\nD=A\n");
    }
    else {
        return -1; // stato di errore
    }

    fprintf(file_to_write,"%s", hack_cmd);
    fprintf(file_to_write, "%s", POP);
    free(hack_cmd);
    return 1; // success!
}

/** Scrive il codice della push
 *  arg1 e arg2 sono gli argomenti della push.
 * 
 */
int writePush(char* arg1, char* arg2)
{
    char* hack_cmd = malloc(sizeof(char) * BUFSIZ);

    // if (arg1 != NULL) printf("arg1 is not null, is: %s|\n", arg1);
    // if (arg2 != NULL) printf("arg2 is not null, is: %s|\n", arg2);

    if (strcmp(arg1, "constant") == 0){ // copia la costante di A in D
        strcpy(hack_cmd, "@");
        strcat(hack_cmd, arg2);
        strcat(hack_cmd, "\nD=A\n");
    } else
    if (strcmp(arg1, "local") == 0){ // pusha il valore della variabile locale
        strcpy(hack_cmd, "@LCL\nD=M\n@");
        strcat(hack_cmd, arg2);
        strcat(hack_cmd, "\nA=D+A\nD=M\n");
    } else 
    if (strcmp(arg1, "argument") == 0) {
        strcpy(hack_cmd, "@ARG\nD=M\n@");
        strcat(hack_cmd, arg2);
        strcat(hack_cmd, "\nA=D+A\nD=M\n");
    } else 
    if (strcmp(arg1, "static") == 0) { // contiene le variabili "globali", relative al file
        // fa riferimento al file attuale 
        strcpy(hack_cmd, "@");
        strcat(hack_cmd, nomeFile);
        strcat(hack_cmd, ".");
        strcat(hack_cmd, arg2);
        strcat(hack_cmd, "\nD=M\n");
    } else {
        return -1; //stato di errore
    }

    fprintf(file_to_write,"%s", hack_cmd); // metto il valore al TOP dello stack
    fprintf(file_to_write, "%s", "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    free(hack_cmd);
    return 1; // success!
}



/** Scrive il codice relativo a Lt in HACK
 * 
 */
void writeLt()
{
    char *hack_cmd =  malloc(sizeof(char) * BUFSIZ);
    strcpy(hack_cmd, // Prendo i primi due valori dallo SP e li sottraggo.
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "D=M-D\n"
    "@LT.true.");
   
    crea_id();
    strcat(hack_cmd, id_string); // in caso il primo sia minore del secondo (aka D < 0), salta a LT.true
   
    strcat(hack_cmd, "\n"); //se è falso, salta metti M=0 nell'SP e salta a dopo
    strcat(hack_cmd, "D;JLT\n@SP\nA=M-1\nM=0\n@LT.false.");
    strcat(hack_cmd, id_string);
    strcat(hack_cmd, "\n0;JMP\n(LT.true.");
    strcat(hack_cmd, id_string); // se è vero, salta e metti -1
    strcat(hack_cmd, ")\n@SP\nA=M-1\nM=-1\n(LT.false.");
    strcat(hack_cmd, id_string);
    strcat(hack_cmd, ")\n");

    fprintf(file_to_write,"%s", hack_cmd);
    free(hack_cmd);
}

/** Simile a write Lt, ma controlla se uno è più grande dell'altro (duh...)
 * 
 */
void writeGt()
{
    char *hack_cmd =  malloc(sizeof(char) * BUFSIZ);
    strcpy(hack_cmd, // Prendo i primi due valori dallo SP e li sottraggo.
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "D=M-D\n"
    "@GT.true.");
   
    crea_id();
    strcat(hack_cmd, id_string); // in caso il primo sia maggiore del secondo (aka D > 0), salta a GT.true
   
    strcat(hack_cmd, "\n"); //se è falso, salta metti M=0 nell'SP e salta a dopo
    strcat(hack_cmd, "D;JGT\n@SP\nA=M-1\nM=0\n@GT.false.");
    strcat(hack_cmd, id_string);
    strcat(hack_cmd, "\n0;JMP\n(GT.true.");
    strcat(hack_cmd, id_string); // se è vero, salta e metti -1
    strcat(hack_cmd, ")\n@SP\nA=M-1\nM=-1\n(GT.false.");
    strcat(hack_cmd, id_string);
    strcat(hack_cmd, ")\n");

    fprintf(file_to_write,"%s", hack_cmd);
    free(hack_cmd);
}


/** Simile a writeLt, ma controlla se sono uguali (duh...)
 * 
 */
void writeEq()
{
    char *hack_cmd =  malloc(sizeof(char) * BUFSIZ);
    strcpy(hack_cmd, // Prendo i primi due valori dallo SP e li sottraggo.
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "D=M-D\n"
    "@EQ.true.");
   
    crea_id();
    strcat(hack_cmd, id_string); // in caso il primo siano uguali (aka D==0), salta a EQ.true
   
    strcat(hack_cmd, "\n"); //se è falso, salta metti M=0 nell'SP e salta a dopo
    strcat(hack_cmd, "D;JEQ\n@SP\nA=M-1\nM=0\n@EQ.false.");
    strcat(hack_cmd, id_string);
    strcat(hack_cmd, "\n0;JMP\n(EQ.true.");
    strcat(hack_cmd, id_string); // se è vero, salta e metti -1
    strcat(hack_cmd, ")\n@SP\nA=M-1\nM=-1\n(EQ.false.");
    strcat(hack_cmd, id_string);
    strcat(hack_cmd, ")\n");

    fprintf(file_to_write,"%s", hack_cmd);
    free(hack_cmd);
}

/**
 * Salta ad un determinato punto nello scope.
 * Ovvero, @nomeFunzione.label
 */
void writeGoto(char* label)
{
    char *hack_cmd = malloc(sizeof(char) * BUFSIZ);
    strcpy(hack_cmd, "@");
    strcat(hack_cmd, current_function);
    strcat(hack_cmd, ".");
    strcat(hack_cmd, label);
    strcat(hack_cmd, "\n0;JMP\n"); // salta!

    fprintf(file_to_write,"%s", hack_cmd);
    free(hack_cmd);
}



/** Scrive il codice relativo ad un if-goto.
 *  Controlla che il valore nello stack pointer sia != 0 (ovverosia true).
 *  Se è così, fa un salto alla label.
 */
void writeIfGoto(char* label)
{
    char *hack_cmd = malloc(sizeof(char) * BUFSIZ);
    strcpy(hack_cmd, "@SP\nAM=M-1\nD=M\n@");
    strcat(hack_cmd, current_function);
    strcat(hack_cmd, ".");
    strcat(hack_cmd, label);
    strcat(hack_cmd, "\nD;JNE\n");

    fprintf(file_to_write,"%s", hack_cmd);
    free(hack_cmd);
}

/** Scrive il label.
 * 
 */
void writeLabel(char* label){
    char *hack_cmd = malloc(sizeof(char) * BUFSIZ);
    strcpy(hack_cmd, "(");
    strcat(hack_cmd, current_function);
    strcat(hack_cmd, ".");
    strcat(hack_cmd, label);
    strcat(hack_cmd, ")\n");

    fprintf(file_to_write,"%s", hack_cmd);
    free(hack_cmd);
}

/**
 * Scrive il codice equivalente in hack per la chiamata di funzione.
 * n è il numero delle varibiali locali (il numero degli argomenti è specificato
 * solo in call)
 * 
 */
void writeFunction(char* function, char* n)
{
    char *hack_cmd =  malloc(sizeof(char) * BUFSIZ);
    int var_num = myatoi(n); // converti il numero delle variabili in numero
    strcpy(hack_cmd, "(");
    strcat(hack_cmd, function); // metto il nome della funxione come etichetta
    strcat(hack_cmd, ")\n@SP\nA=M\n"); // consideriamo l'indirizzo che si trova 
                                       // al top dello stack

    for (int i = 0; i < var_num; i++)
        strcat(hack_cmd, "M=0\nA=A+1\n"); // e per ogni variabile locale, 
                                          // occupiamo un posto nello stack
                                          // (ovvero, inizializziamo ogni var locale a 0)

    strcat(hack_cmd, "D=A\n@SP\nM=D\n"); // riposiziono SP
    fprintf(file_to_write,"%s", hack_cmd);
    
    strcpy(current_function, function); // copia funzione corrente dentro alla var. apposita.
    free(hack_cmd);
}

/** Scrive le operazioni di return, dalla macro
 * 
 */
void writeReturn(){
    fprintf(file_to_write, "%s", RETURN);
}

/** Scrive il codice relativo alla chiamata di funzione.
 * 
 */
void writeCall (char* called_function, char* number_of_args)
{
    char *hack_cmd = malloc(sizeof(char) * BUFSIZ);

    // salvo lo SP in una var temp ora, così dopo, quando devo riposiz. arg, 
    // non devo togliere 5 
    strcpy(hack_cmd,
    "@SP\n"
    "D=M\n"
    "@R14\n"
    "M=D\n"
    "@Return.");
    
    crea_id();    
    strcat(hack_cmd, id_string);
    // pusho l'indirizzo di ritorno.
    // ovvero, lo metto al top dello stack.
    strcat(hack_cmd, "\n"
    "D=A\n"
    "@SP\n"
    "A=M\n"
    "M=D\n" 
    "@SP\n" // aumento lo stack pointer
    "M=M+1\n"

    "@LCL // salvo LCL del chiamante pushandolo\n"
    "D=M\n"
    "@SP\n"
    "A=M\n"
    "M=D // (push di lcl)\n"
    "@SP\n"
    "M=M+1\n"

    "@ARG // stessa cosa per ARG del chiamante\n"
    "D=M\n"
    "@SP\n"
    "A=M\n"
    "M=D // (push di arg)\n"
    "@SP\n"
    "M=M+1\n"

    // Anche se il progetto non lo richiedeva, 
    // SimpleFunction.vm non superava i test se THIS e THAT
    // non venivano implementati a livello funzione.

    "@THIS // stessa cosa per THIS\n"  
    "D=M\n" 
    "@SP\n" 
    "A=M\n" 
    "M=D // (push di THIS)\n" 
    "@SP\n" // aumento lo stack pointer
    "M=M+1\n"

    "@THAT // stessa cosa per THAT\n" 
    "D=M\n" 
    "@SP\n"
    "A=M\n" 
    "M=D // (push di THAT)\n" 
    "@SP\n" // aumento SP
    "M=M+1\n" 

    "@R14\n" // ripristino 
    "D=M // (D=SP-5)\n"
    "@");
    strcat(hack_cmd, number_of_args); // riposiziono ARG 
    strcat(hack_cmd, "\n"
    "D=D-A //D=(SP-5-n)\n"
    "@ARG\n"
    "M=D\n"
    "@SP\n"
    "D=M\n"
    "@LCL\n"
    "M=D //ripos. di ARG\n"
    "@");
    strcat(hack_cmd, called_function);  // salta alla parte di codice corrisp. 
                                        // alla funzione
    strcat(hack_cmd, "\n0;JMP\n(Return.");
    strcat(hack_cmd, id_string);
    strcat(hack_cmd, ")\n");

    //scrivi tutto sul file
    fprintf(file_to_write,"%s", hack_cmd);
    free(hack_cmd);
}