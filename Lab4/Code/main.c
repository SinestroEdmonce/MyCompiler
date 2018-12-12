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

/* Flag for counting the semantic errors */
unsigned int semantic_errors = 0;
/* Variable that determines debugging */
// #define YYDEBUG 1

typedef struct Args_{
    /* Input and output files */
    char* in_file;
    char* out_file;

    struct {
        bool flag_print_syntax_tree;
        bool flag_only_semantic_check;
        bool flag_enable_dag_optimized;
        bool flag_only_translate_ir_code;
        bool flag_generate_assembly_code;
    } mode;    
} Args;

void Args_Initializer(Args* args){
    args->in_file = NULL;
    args->out_file = NULL;

    args->mode.flag_print_syntax_tree = false;
    args->mode.flag_only_semantic_check = false;
    args->mode.flag_enable_dag_optimized = true;
    args->mode.flag_only_translate_ir_code = false;
    args->mode.flag_generate_assembly_code = false;
}

/* A function used for parsing the given arguments */
Args* Args_Parser(int argc, char** argv){
    if (argc<=1){
        printf("Usage: ./parser [-p] [-s] [-dag] [-ir] -[a] source [result]\n");
        printf("       -p  print the syntax tree\n");
        printf("       -s  only process semantic checking\n");
        printf("     -dag  enable dag optimizing\n");
        printf("      -ir  only process generating IR code\n");
        printf("       -a  process generating assembly code\n");
        printf("   result  the folder that stores results\n");
        printf("Copyright: Qiaoyi Yin @NJU\n");
        return NULL;
    }
    
    Args* args = malloc(sizeof(Args));
    Args_Initializer(args);

    /* Parsing the arguments */
    int idx = 0;
    for (idx=1;idx<argc;++idx){
        if (strcmp(argv[idx], "-p") == 0)
            args->mode.flag_print_syntax_tree = true;
        else if (strcmp(argv[idx], "-s") == 0)
            args->mode.flag_only_semantic_check = true;
        else if (strcmp(argv[idx], "-dag") == 0)
            args->mode.flag_enable_dag_optimized = true;
        else if (strcmp(argv[idx], "-ir") == 0)
            args->mode.flag_only_translate_ir_code = true;
        else if (strcmp(argv[idx], "-p") == 0)
            args->mode.flag_generate_assembly_code = true;
        else if (argv[idx][0] != '-'){
            if (args->in_file == NULL)
                args->in_file = argv[idx];
            else if (args->out_file == NULL)
                args->out_file = argv[idx];
        }
        else{
            printf("Invalid parameters, please check your input!\n");
            return NULL;
        }
    }

    return args;
}

int main(int argc, char** argv){
    Args* args = Args_Parser(argc, argv);

    if(args != NULL){
        FILE* file = fopen(args->in_file, "r");
        /* Cannot open the file */
        if(!file){
            perror(args->in_file);
            return 1;
        }

        yyrestart(file);
        //yydebug=1;
        yyparse();
        fclose(file);

        /* If no errors, do different processes */
        if(syn_error==false && lex_error==false){
            if (args->mode.flag_print_syntax_tree){
                if (args->out_file != NULL){
                    FILE* out = fopen(args->out_file, "a+");
                    Preorder_Traversal(out, root, 0);
                    fclose(out);
                }
                else
                    Preorder_Traversal(NULL, root, 0);
            }
            if (args->mode.flag_only_semantic_check){
                semantic_errors = 0;
                Semantic_Analysis();
                Check_Declared_Func();
            }
            if (args->mode.flag_only_translate_ir_code){
                semantic_errors = 0;
                Semantic_Analysis();
                Check_Declared_Func();
                if (semantic_errors == 0){
                    Reset_All();   
                    Translate_Analysis();
                    if (args->out_file != NULL){
                        FILE* out = fopen(args->out_file, "a+");
                        Print_IR_Code_List(out);
                        fclose(out);
                    }
                    else
                        Print_IR_Code_List(NULL);
                }
            }
            if (args->mode.flag_generate_assembly_code){
                semantic_errors = 0;
                Semantic_Analysis();
                Check_Declared_Func();
                
                printf("Error: Assembly Code Generation has not been completed yet.");
            }
        }      
        return 0;
    }
    else{
        printf("Error: Parameters missing.\n");
        return -1;
    } 
}

