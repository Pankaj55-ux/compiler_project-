#ifndef TAC_H
#define TAC_H

void generateTACAssignment(char var[], char value[]);

char* generateTACTemp(char arg1[],
                      char op[],
                      char arg2[]);

char* generateLabel();

void generateIfTAC(char arg1[],
                   char relop[],
                   char arg2[],
                   char label[]);

void generateGoto(char label[]);

void generateLabelCode(char label[]);

char* optimizeConstantFolding(char arg1[],
                              char op[],
                              char arg2[]);

void deadCodeElimination();                             

void printTAC();

void saveTAC(FILE* file);

#endif