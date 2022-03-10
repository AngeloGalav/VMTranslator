#include "utils.h"

/** Implementazione dello mystrtok, siccome
 *  non possiamo usarla come funz. di libreria.
 */
char* mystrtok(char* stringa, char delim)
{
    // mantiene lo stato della stringa, 
    // in questo modo possiamo avere il prossimo token
    // mettento NULL, come nello stringtok di c
    static char* input = NULL;
 
    // Inizializzazione stringa
    if (stringa != NULL)
        input = stringa;
 
    // Stato finale
    if (input == NULL)
        return NULL;
 
    // Procediamo con il paring vero e proprio in token
    char* result = malloc(sizeof(char)* (strlen(input) + 1));
    int i = 0;
 
    for (; input[i] != '\0'; i++) {
 
        // Se non e' delim, aggiungo il carattere all'output
        if (input[i] != delim)
            result[i] = input[i];
         else {
            // delim trovato! Consegno la stringa
            result[i] = '\0';
            input = input + i + 1;
            return result;
        }
    }
 
    // delimitatore di fine stringa,
    // in caso non venga trovato il delim.
    result[i] = '\0';
    input = NULL;
 
    return result;
}

/** Implementazione di itoa, per evitare di usare sprintf per 
 *  la trasformazione da int a string
 * 
 */
void int2str(char *stringa, int intero )
{
    unsigned int i = 1000000000;

    // in caso in cui n sia negativo, metto il meno
    if (((signed)intero) < 0 ) {
        *stringa++ = '-';
        intero = -intero;
    }

    // prendo il numero di cifre
    while (i > intero) i /= 10;

    do { // aggiungo la cifra
        *stringa++ = '0' + (intero - intero % i) / i % 10;
    } while(i /= 10);

    *stringa = '\0';
}

/** Implementazione di atoi, in caso non fosse permesso.
 * 
 */
int myatoi(char* str)
{
    int res = 0;
    int sign = 1;
    
    // aggiungo cifra per cifra il carette come numero dell'intero finale.
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    if (str[0] == '-'){
        sign *= -1;
    }
 
    return res*sign;
}

/** Controlla l'estensione del file
 * 
 */
int checkExtension(char* filname, char* extension){
    int len = strlen(filname);
    int len2 = strlen(extension);

    if (len < len2) return -1;

    for (int i=0; i < len2; i++){
        if (filname[len - len2 + i] != extension[i])
            return 0;
    }

    // il file ha l'estensione giusta
    return 1;
}