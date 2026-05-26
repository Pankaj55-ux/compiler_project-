#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;

int yyparse();

int main(int argc, char* argv[])
{
    int i;

    if(argc < 2)
    {
        printf("NO INPUT FILES\n");
        return 1;
    }

    for(i = 1; i < argc; i++)
    {
        yyin = fopen(argv[i], "r");

        if(yyin == NULL)
        {
            printf("CANNOT OPEN FILE : %s\n", argv[i]);
            continue;
        }

        printf("\nPARSING FILE : %s\n\n", argv[i]);

        yyparse();

        fclose(yyin);
    }

    return 0;
}