/*
 * Copyright (c) 2012 Pijus Kasparaitis
 * File:    transcrLUSS.h
 * Purpose: Stressing and transcription subroutine.
 * Author:  Pijus Kasparaitis
 * Email :  pkasparaitis@yahoo.com
 *
 * 2012 06 30
 */
//#include <windows.h>
//#include <afx.h>

#ifndef __TRANSCRLUSS_H__
#define __TRANSCRLUSS_H__

/*typedef int  (*PROCICCISSIII) (char*, char*, int, unsigned short*, unsigned short*, int*, int*, int);
typedef int  (*PROCAIC) (char*);

extern PROCICCISSIII	KircTranskr;
extern PROCAIC			initTranscrLUSS;

BOOL loadTranscrLUSS(char*);
void unloadTranscrLUSS();*/

int KircTranskr(char*, char*, int, unsigned short*, unsigned short*, int*, int*, int);
int initTranscrLUSS(char*);

#endif
