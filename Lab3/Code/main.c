#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdarg.h>
#include "SyntaxTree.h"
#include "syntax.tab.h"
#include "ErrorReport.h"
#include "SymbolTable.h"
#include "Semantic.h"
#include "Translate.h"

extern FILE* yyin;
extern void yyrestart(FILE *input_file);
extern bool lex_error;
extern bool syn_error;

unsigned int errors = 0;
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
        if(syn_error==false && lex_error==false){
            //Preorder_Traversal(root, 0);
            Semantic_Analysis();
            Check_Declared_Func();
            Reset_All();
            Translate_Analysis();
        }      

        return 0;
    }
    else{
        printf("Error: Parameter missing.\n");
        return -1;
    } 
}