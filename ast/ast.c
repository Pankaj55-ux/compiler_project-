#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

struct ASTNode* createNode(char name[])
{
    struct ASTNode* newNode;

    newNode = (struct ASTNode*)malloc(sizeof(struct ASTNode));

    strcpy(newNode->name, name);

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void printAST(struct ASTNode* root, int level)
{
    int i;

    if(root == NULL)
    {
        return;
    }

    for(i = 0; i < level; i++)
    {
        printf("  ");
    }

    printf("%s\n", root->name);

    printAST(root->left, level + 1);

    printAST(root->right, level + 1);
}

void saveAST(struct ASTNode* root,
             int level,
             FILE* file)
{
    int i;

    if(root == NULL)
    {
        return;
    }

    for(i = 0; i < level; i++)
    {
        fprintf(file, "  ");
    }

    fprintf(file, "%s\n", root->name);

    saveAST(root->left,
            level + 1,
            file);

    saveAST(root->right,
            level + 1,
            file);
}