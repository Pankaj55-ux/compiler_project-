#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tac.h"

char tac[200][200];

int tacIndex = 0;

int tempCount = 0;

int labelCount = 0;

void generateTACAssignment(char var[], char value[])
{
    sprintf(tac[tacIndex],
            "%s = %s",
            var,
            value);

    tacIndex++;
}

char* generateTACTemp(char arg1[],
                      char op[],
                      char arg2[])
{
    static char temp[20];

    sprintf(temp, "t%d", tempCount);

    sprintf(tac[tacIndex],
            "%s = %s %s %s",
            temp,
            arg1,
            op,
            arg2);

    tacIndex++;

    tempCount++;

    return temp;
}

char* generateLabel()
{
    static char label[20];

    sprintf(label, "L%d", labelCount);

    labelCount++;

    return label;
}

void generateIfTAC(char arg1[],
                   char relop[],
                   char arg2[],
                   char label[])
{
    sprintf(tac[tacIndex],
            "if %s %s %s goto %s",
            arg1,
            relop,
            arg2,
            label);

    tacIndex++;
}

void generateGoto(char label[])
{
    sprintf(tac[tacIndex],
            "goto %s",
            label);

    tacIndex++;
}

void generateLabelCode(char label[])
{
    sprintf(tac[tacIndex],
            "%s :",
            label);

    tacIndex++;
}

char* optimizeConstantFolding(char arg1[],
                              char op[],
                              char arg2[])
{
    static char result[20];

    int num1;
    int num2;
    int value;

    if(isdigit(arg1[0]) && isdigit(arg2[0]))
    {
        num1 = atoi(arg1);

        num2 = atoi(arg2);

        if(strcmp(op, "+") == 0)
        {
            value = num1 + num2;
        }
        else if(strcmp(op, "-") == 0)
        {
            value = num1 - num2;
        }
        else if(strcmp(op, "*") == 0)
        {
            value = num1 * num2;
        }
        else if(strcmp(op, "/") == 0)
        {
            value = num1 / num2;
        }

        sprintf(result, "%d", value);

        return result;
    }

    return generateTACTemp(arg1, op, arg2);
}

void deadCodeElimination()
{
    int i;
    int j;

    int used;

    char temp[20];

    for(i = 0; i < tacIndex; i++)
    {
        if(tac[i][0] == 't')
        {
            sscanf(tac[i], "%s =", temp);

            used = 0;

            for(j = i + 1; j < tacIndex; j++)
            {
                if(strstr(tac[j], temp) != NULL)
                {
                    used = 1;
                    break;
                }
            }

            if(used == 0)
            {
                strcpy(tac[i], "");
            }
        }
    }
}

void printTAC()
{
    int i;

    printf("\nTHREE ADDRESS CODE:\n\n");

    deadCodeElimination();

    for(i = 0; i < tacIndex; i++)
    {
        if(strlen(tac[i]) > 0)
{
    printf("%s\n", tac[i]);
}
    }
}

void saveTAC(FILE* file)
{
    int i;

    deadCodeElimination();

    for(i = 0; i < tacIndex; i++)
    {
        if(strlen(tac[i]) > 0)
{
    fprintf(file, "%s\n", tac[i]);
}
    }
}