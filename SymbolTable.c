#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SymbolTable.h"
#include "Queue.h"

/**
 * This function initiate the given symbol table.
 */
void initSymbolTable(symboltable st[])
{
	int i = 0;
	for(; i < numOfLetters; i++){
		st[i].name = "NULL";
		st[i].next = NULL;
	}
}

/**
 * This function insert a string and address to the symbol table.
 * name - the new string.
 * address - the address of the string.
 * printAddress - this variable contains the line number even if the label is for data.
 */
void insertToSymbolTable(symboltable s[], string name, int address, int printAddress)
{
	int idx = returnSymbolTableIdx(name[0]);
	symboltable* ptr = &s[idx];
	while(strcmp(ptr->name , "NULL") != 0)
		ptr = (*ptr).next;
	(*ptr).name = (char*)strdup(name);
	(*ptr).address = address;
	(*ptr).printAddress = printAddress;
	(*ptr).next = malloc(sizeof(symboltable));
	(*(*ptr).next).name = "NULL";
}

/**
 * This function returns the address of the given label in the symbol table.
 * name - the given label.
 * st - the symbol table.
 * returns the index on the table if found or -1 otherwise.
 */
int getLabelAddress(string name, symboltable st[])
{
	int letterIdx = returnSymbolTableIdx(name[0]);
	if(!isalpha(name[0]))
		return -1;
	symboltable* ptr =  &st[letterIdx];
	while(strcmp(ptr->name, "NULL") != 0){
		if(strcmp((*ptr).name, name) == 0)
			return (*ptr).printAddress;
		ptr = (*ptr).next;
	}
	return -1;
}

/**
 * This function return the index of the line in the symbol table (according to the given character).
 */
int returnSymbolTableIdx(char c)
{
	int min;
	if(c >= 97)
		min = 97;
	else
		min = 65;
	return c - min;
}

/**
 * This function initiate the table for another use.
 * st - symbol table.
 */
void freeSymbolTable(symboltable st[])
{
	int i = 0;
	for(; i < numOfLetters; i++){
		st[i].address = 0;
		freeList(st + i);
	}
}

/**
 * This function frees the node of the list.
 */
void freeList(symboltable* st)
{
	if(strcmp(st->name, "NULL") != 0){
		freeList(st->next);
		free(st->name);
		free(st->next);
		st->name = "NULL";
		st->next = NULL;
	}
}

/**
 * This function set addresses on the entry or extern tables.
 * st - symbol table.
 */
void seAddressEnEX(symboltable st[])
{
	int letterIdx = 0;
	symboltable* ptr;
	while(letterIdx < numOfLetters ){
		if(strcmp(st[letterIdx].name, "NULL") == 0)
			letterIdx++;
		else{
			ptr = &st[letterIdx];
			do{
				(*ptr).address = getLabelAddress((*ptr).name, labelTABLE);
				ptr = (*ptr).next;
			}while(strcmp(ptr->name, "NULL") != 0 );
			letterIdx++;
		}
	}
}

/*
 * This function prints the entry table.
 * file - the name of the file to write to.
 */
void printEntryTable(symboltable s[], string file)
{
	int i = 0;
	symboltable st;
	FILE* fp = fopen(file, "w");
	fprintf(fp, "\nEntry table:\n");
	for(;i < numOfLetters;i++){
		st = s[i];
		while(strcmp(st.name, "NULL") != 0){
			fprintf(fp, "%s ", st.name);
			cast10ToBase4( st.address + startIcValue, fp);
			fprintf(fp, "\n");
			st = *(st.next);
		}
	}
}

/*
 * This function prints the external table.
 * file - the name of the file to write to.
 */
void printExternTable(string file)
{
	QUE_setPtrToHead();
	FILE* fp = fopen(file, "w");
	fprintf(fp, "\nExtern table:\n");
	while(strcmp(QUE_getLabel(),"NULL") != 0)
	{
		if(QUE_returnIsExtern() == TRUE){
			fprintf(fp, "%s ", QUE_getLabel());
			cast10ToBase4(QUE_getLine() + startIcValue, fp);
			fprintf(fp, "\n");
		}
		QUE_getNext();
	}
}

/*
 * This function cast the decimal value to base 4 and prints it.
 * num - the number to cast.
 * fp - the name of the file that the function writes to.
 */
void cast10ToBase4(int num, FILE* fp)
{
	int shalem = 0, shever = 0, place = 1;
	while(num != 0){
		shalem = num / 4;
		shever += (num % 4)* place;
		place = place * 10;
		num = shalem;
	}
	fprintf(fp, "%d ", shever);
}
