/*
 * Copyright (c) 2013 Pijus Kasparaitis
 * File:    RateChange.h
 * Purpose: DB rate change.
 *          Interface of the DLL
 * Author:  Pijus Kasparaitis
 * Email :  pkasparaitis@yahoo.com
 *
 * 2013 07 30
 */
//#include <windows.h>
//#include <afx.h>
#include <stdlib.h> //20201204


#ifndef __RATECHANGE_H__
#define __RATECHANGE_H__

/*typedef int (*PROCICICILS)(char *, int, char[][4], int *, long *, short **);
typedef int (*PROCICCILS)(char *, char[][4], int *, long *, short **);
//typedef int (*PROCIIISI)(int, unsigned int, short *, unsigned int);
typedef int (*PROCIIISI)(int, int, unsigned int, short *, unsigned int);

extern PROCICICILS change_DB_rate;
extern PROCICCILS initRateChange;
extern PROCIIISI change_phoneme_rate;

BOOL loadRateChange(char*);
void unloadRateChange();*/

int change_DB_rate(char *, int, char[][4], int *, long *, short **);
int initRateChange(char *, char[][4], int *, long *, short **);
int change_phoneme_rate(int, int, unsigned int, short *, size_t); //20201204 unsigned int
void atlaisvinti_atminti_ir_inicializuoti();

// debuginimui
extern int debuginam;
void spausdinti_loga(char* pranesimas);
template< class T> void spausdinti_int_masyva(T masyvas, int ilgis);
void spausdinti_short_masyva(char *text, short* signbuf, int signbufsize);

#endif