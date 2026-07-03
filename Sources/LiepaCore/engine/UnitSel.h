/*
 * Copyright (c) 2012 Pijus Kasparaitis
 * File:    UnitSel.h
 * Purpose: Unit Selection.
 *          Interface of the DLL
 * Author:  Pijus Kasparaitis
 * Email :  pkasparaitis@yahoo.com
 *
 * 2012 06 30
 */
//#include <windows.h>

#ifndef __UNITSEL_H__
#define __UNITSEL_H__

/*typedef int (*PROCBIC)(char *);
typedef int (*PROCBISSSIII)(unsigned short[],unsigned short[],unsigned short[],int,unsigned int[],unsigned int*);

extern PROCBIC initUnitSel;
extern PROCBISSSIII selectUnits;

BOOL loadUnitSel(char*);
void unloadUnitSel();*/

int initUnitSel(char *);

//int selectUnits(unsigned short[],unsigned short[],unsigned short[],int,int[],int*);
int selectUnits(unsigned short[],unsigned short[],unsigned short[],int,unsigned int[],unsigned int*);
//int selectUnits(unsigned short *,unsigned short *,unsigned short *,int,unsigned int*,unsigned int*);

//int selectUnits(unsigned short unitsRow[], unsigned short unitsRowNextSeparators[], unsigned short unitsRowDurr[], int unitsRowLength, int retUnits[], int * retCost)

#endif