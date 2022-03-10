#pragma once

// nascondi alcuni printf
#define DEBUG 0

// scritto qui questi due comandi perché erano lunghi

/** Passi del Return.
 */
#define RETURN \
"@LCL\n" \
"D=M\n" \
"@5\n" \
"A=D-A // (LCL-5) contiene il return address\n" \
"D=M\n"\
"@R14 // metto return address nella var. temp\n" \
"M=D\n" \
"@SP\n" \
"A=M-1 // Prendi contenuto SP (pop())\n" \
"D=M\n" \
"@ARG\n" \
"A=M\n" \
"M=D // riposiziona return val della funzione\n" \
"D=A+1 // D=ARG+1\n"\
"@SP\n"\
"M=D //SP=ARG+1\n"\
\
"@LCL // riposiz. THAT del chiam.\n" \
"AM=M-1\n" \
"D=M\n" \
"@THAT\n" \
"M=D // THAT=*(LCL-1)\n" \
\
"@LCL // riposiz. THIS del chiam.\n" \
"AM=M-1\n" \
"D=M\n" \
"@THIS\n" \
"M=D // THIS=*(LCL-1-1)\n" \
\
"@LCL // riposiz. ARG del chiam.\n" \
"AM=M-1\n" \
"D=M\n" \
"@ARG\n" \
"M=D // ARG=*(LCL-1-1-1)\n" \
\
"@LCL // riposiz. LCL del chiam.\n" \
"AM=M-1\n" \
"D=M\n" \
"@LCL\n" \
"M=D // LCL=*(LCL-1-1-1-1)\n" \
\
"@R14 //salta al val. di rit.\n" \
"A=M\n" \
"0;JMP\n"

// "@LCL\n"
// "D=M\n"
// "@3 // (LCL-3) contiene ARG del chiam.\n" 
// "A=D-A\n" 
// "D=M\n" 
// "@ARG\n" 
// "M=D //ripris. ARG\n" 
// 
// "@LCL\n" 
// "D=M\n" 
// "@4 //(LCL-4) contiene LCL del chiam.\n"
// "A=D-A\n" 
// "D=M\n" 
// "@LCL\n" 
// "M=D //ripris. LCL\n" 


/** Struttura della POP.
 * 
 */
#define POP \
"@R13 //metto locaz. var. in tempPOP\n" \
"M=D\n"\
"@SP\n"\
"AM=M-1\n"\
"D=M //prendo contenuto dello stack\n"\
"@R13\n"\
"A=M\n"\
"M=D //metto nella var. il cont. stack\n"

