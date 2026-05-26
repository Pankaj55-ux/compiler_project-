#ifndef AST_H
#define AST_H

struct ASTNode
{
    char name[50];

    struct ASTNode* left;
    struct ASTNode* right;
};

struct ASTNode* createNode(char name[]);

void printAST(struct ASTNode* root, int level);
void saveAST(struct ASTNode* root,
             int level,
             FILE* file);

#endif