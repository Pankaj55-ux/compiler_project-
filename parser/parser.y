%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ast/ast.h"
#include "../symboltable/symboltable.h"
#include "../tac/tac.h"

void yyerror(const char *s);
int yylex();

struct ASTNode* root;

char ifLabel[20];
char endLabel[20];
%}

%union
{
    struct ASTNode* node;
    char text[100];
}

%token INT FLOAT IF ELSE WHILE FOR RETURN
%token <text> NUMBER IDENTIFIER
%left '+' '-'
%left '*' '/'

%type <node> program statements statement declaration assignment ifstatement whilestatement function functioncall forstatement
%type <text> expression

%%

program:
        statements
        {
            root = $1;

            printf("\nAST GENERATED:\n\n");

            printAST(root, 0);

            printSymbolTable();

            printTAC();

            {
    FILE* astFile;
    FILE* symbolFile;
    FILE* tacFile;

    astFile = fopen("AST.txt", "w");

    symbolFile = fopen("SymbolTable.txt", "w");

    tacFile = fopen("TAC.txt", "w");

    saveAST(root, 0, astFile);

    saveSymbolTable(symbolFile);

    saveTAC(tacFile);

    fclose(astFile);

    fclose(symbolFile);

    fclose(tacFile);
}
        }
        ;

statements:
        statements statement
        {
            $$ = createNode("STATEMENTS");

            $$->left = $1;
            $$->right = $2;
        }

        |
        {
            $$ = NULL;
        }
        ;

statement:
        declaration
        {
            $$ = $1;
        }

        |

        assignment
        {
            $$ = $1;
        }

        |

        ifstatement
        {
            $$ = $1;
        }

        |

        whilestatement
        {
            $$ = $1;
        }

        |

        function
        {
            $$ = $1;
        }

        |

        functioncall
        {
            $$ = $1;
        }

        |

        forstatement
        {
           $$ = $1;
        }
        ;


declaration:
        INT IDENTIFIER ';'
        {
            insertSymbol($2,
                         "int",
                         "variable");

            $$ = createNode("DECLARATION");
        }
        ;

function:
        INT IDENTIFIER '(' ')'
        {
            insertSymbol($2,
                         "int",
                         "function");

            enterScope();
        }

        '{'
        statements
        '}'
        {
            exitScope();

            $$ = createNode("FUNCTION");
        }
        ;

functioncall:
        IDENTIFIER '(' ')' ';'
        {
            if(searchSymbol($1) == 0)
            {
                printf("UNDEFINED FUNCTION : %s\n", $1);
            }

            $$ = createNode("FUNCTION_CALL");
        }
        ;

assignment:
        IDENTIFIER '=' expression ';'
        {
            if(searchSymbol($1) == 0)
            {
                printf("ERROR : VARIABLE %s NOT DECLARED\n",
                        $1);
            }
            else
            {
                generateTACAssignment($1, $3);
            }

            $$ = createNode("ASSIGNMENT");
        }
        ;

ifstatement:
        IF '(' IDENTIFIER '<' IDENTIFIER ')'
        '{'
        assignment
        '}'
        {
            strcpy(ifLabel, generateLabel());

            strcpy(endLabel, generateLabel());

            generateIfTAC($3, "<", $5, ifLabel);

            generateGoto(endLabel);

            generateLabelCode(ifLabel);

            generateLabelCode(endLabel);

            $$ = createNode("IF");
        }
        ;

whilestatement:
        WHILE '(' IDENTIFIER '<' IDENTIFIER ')'
        '{'
        assignment
        '}'
        {
            char startLabel[20];
            char trueLabel[20];
            char falseLabel[20];

            strcpy(startLabel, generateLabel());

            strcpy(trueLabel, generateLabel());

            strcpy(falseLabel, generateLabel());

            generateLabelCode(startLabel);

            generateIfTAC($3, "<", $5, trueLabel);

            generateGoto(falseLabel);

            generateLabelCode(trueLabel);

            generateGoto(startLabel);

            generateLabelCode(falseLabel);

            $$ = createNode("WHILE");
        }
        ;

forstatement:
        FOR '('
        IDENTIFIER '=' NUMBER ';'
        IDENTIFIER '<' NUMBER ';'
        IDENTIFIER '=' IDENTIFIER '+' NUMBER
        ')'

        '{'
        assignment
        '}'
        {
            char startLabel[20];
            char trueLabel[20];
            char falseLabel[20];

            generateTACAssignment($3, $5);

            strcpy(startLabel, generateLabel());

            strcpy(trueLabel, generateLabel());

            strcpy(falseLabel, generateLabel());

            generateLabelCode(startLabel);

            generateIfTAC($7, "<", $9, trueLabel);

            generateGoto(falseLabel);

            generateLabelCode(trueLabel);

            generateTACTemp($11, "+", $13);

            generateGoto(startLabel);

            generateLabelCode(falseLabel);

            $$ = createNode("FOR");
        }
        ;

expression:
        NUMBER
        {
            strcpy($$, $1);
        }

        |

        IDENTIFIER
        {
            strcpy($$, $1);
        }

        |

        expression '+' expression
        {
            strcpy($$,
                    optimizeConstantFolding($1, "+", $3));
        }

        |

        expression '-' expression
        {
            strcpy($$,
                   optimizeConstantFolding($1, "-", $3));
        }

        |

        expression '*' expression
        {
            strcpy($$,
                   optimizeConstantFolding($1, "*", $3));
        }

        |

        expression '/' expression
        {
            strcpy($$,
                   optimizeConstantFolding($1, "/", $3));
        }

        |

        '(' expression ')'
        {
            strcpy($$, $2);
        }
        ;

%%

void yyerror(const char *s)
{
    printf("SYNTAX ERROR : %s\n", s);
}

