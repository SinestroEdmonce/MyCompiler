#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "SyntaxTree.h"
#include "syntax.tab.h"

extern FILE* yyin;
extern void yyrestart(FILE *input_file);
extern bool lex_error;
extern bool syn_error;

/* Variable that determines debugging */
//#define YYDEBUG 1

int main(int argc, char** argv){
    if(argc > 1){
        FILE* file = fopen(argv[1],"r");
        /* Cannot open the file */
        if(!file){
            perror(argv[1]);
            return 1;
        }
        yyrestart(file);
        //yydebug=1;
        yyparse();
        fclose(file);

        /* If no errors, traverse the whole tree */
        if(syn_error==false && lex_error==false)
            Preorder_Traversal(root, 0);

        return 0;
    }
    else{
        printf("Error: Parameter missing.\n");
        return -1;
    }
}