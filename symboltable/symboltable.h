#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

struct Symbol
{
    char name[50];
    char type[50];
    char category[50];
    int scope;

    struct Symbol* next;
};

extern int currentScope;

void enterScope();

void exitScope();

void insertSymbol(char name[],
                  char type[],
                  char category[]);

int searchSymbol(char name[]);

void printSymbolTable();
void saveSymbolTable(FILE* file);

#endif