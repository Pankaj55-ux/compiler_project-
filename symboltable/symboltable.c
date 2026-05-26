#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symboltable.h"

struct Symbol* head = NULL;

int currentScope = 0;

void enterScope()
{
    currentScope++;
}

void exitScope()
{
    currentScope--;
}

int searchSymbol(char name[])
{
    struct Symbol* temp;

    temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->name, name) == 0
           &&
           temp->scope == currentScope)
        {
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

void insertSymbol(char name[],
                  char type[],
                  char category[])
{
    struct Symbol* newSymbol;
    struct Symbol* temp;

    if(searchSymbol(name))
    {
        printf("ERROR : %s ALREADY DECLARED IN SAME SCOPE\n",
                name);

        return;
    }

    newSymbol =
    (struct Symbol*)malloc(sizeof(struct Symbol));

    strcpy(newSymbol->name, name);

    strcpy(newSymbol->type, type);

    strcpy(newSymbol->category, category);

    newSymbol->scope = currentScope;

    newSymbol->next = NULL;

    if(head == NULL)
    {
        head = newSymbol;
    }
    else
    {
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newSymbol;
    }
}

void printSymbolTable()
{
    struct Symbol* temp;

    temp = head;

    printf("\nSYMBOL TABLE:\n\n");

    while(temp != NULL)
    {
        printf("NAME : %s   TYPE : %s   CATEGORY : %s   SCOPE : %d\n",
                temp->name,
                temp->type,
                temp->category,
                temp->scope);

        temp = temp->next;
    }
}

void saveSymbolTable(FILE* file)
{
    struct Symbol* temp;

    temp = head;

    while(temp != NULL)
    {
        fprintf(file,
                "NAME : %s   TYPE : %s   CATEGORY : %s   SCOPE : %d\n",
                temp->name,
                temp->type,
                temp->category,
                temp->scope);

        temp = temp->next;
    }
}