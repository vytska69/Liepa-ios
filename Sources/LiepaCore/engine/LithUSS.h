///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Projektas LIEPA (https://liepa.raðtija.lt)
// Sintezatoriaus komponentas LithUSStest.exe
// Failas LithUSS_Error.h
// Autorius dr. Pijus Kasparaitis (pkasparaitis@yahoo.com)
// 2015 08 11
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//#include <windows.h>

#ifndef __LITHUSS_H__
#define __LITHUSS_H__

struct event {short Id; short phonviz; int charOffset; long signOffset;}; 

int initLUSS(char*, char*);
//int synthesizeWholeText(char*, short*, long*, event*, int*, int, int);
//int synthesizeWholeText(char*, short*, unsigned int*, struct event*, int*, int, int);
int synthesizeWholeText(unsigned short*, unsigned int, short*, unsigned int*, struct event*, int*, int, int, int, int, int, int);
char* id2fv(unsigned short);
void unloadLibraries();
#endif