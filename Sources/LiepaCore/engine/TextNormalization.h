/*
 * Copyright (c) 2015 Pijus Kasparaitis
 * File:    TextNormalization.h
 * Purpose: Text Normalization subroutine.
 *          Interface of the DLL
 * Author:  Pijus Kasparaitis
 * Email :  pkasparaitis@yahoo.com
 *
 * 2015 02 08
 */
//#include <windows.h>
//#include <afx.h>

#ifndef __TEXTNORM_H__
#define __TEXTNORM_H__

/*typedef int (*PROCICC) (char *, char *);
typedef int (*PROCISSII)(char *, char*, int, int*);

extern PROCICC		initTextNorm;
extern PROCISSII	normalizeText;
extern PROCISSII	spellText;

BOOL loadTextNorm(char*);
void unloadTextNorm();*/

int initTextNorm(char *, char *);
//int normalizeText(char *, char*, int, int*);
//int normalizeText(unsigned short*, unsigned int, char*, int, int*);
int normalizeText(unsigned short*, unsigned int, char*, int, int*, int, int, int, int);
int spellText(char *, char*, int, int*);
void unloadTextNormalization();

#endif