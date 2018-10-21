%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<stdbool.h>
    #include "SyntaxTree.h"
    #include "lex.yy.c"
    #define MAXLENGTH 128

%}

%union{
    struct TreeNode* tree_node;
}

/* Declared tokens */
%token <tree_node> INT
%token <tree_node> FLOAT
%token <tree_node> ID
 
%token <tree_node> SEMI
%token <tree_node> COMMA
%token <tree_node> ASSIGNOP
%token <tree_node> RELOP
%token <tree_node> PLUS
%token <tree_node> MINUS
%token <tree_node> STAR
%token <tree_node> DIV
%token <tree_node> AND
%token <tree_node> OR
%token <tree_node> DOT
%token <tree_node> NOT
%token <tree_node> TYPE
%token <tree_node> LP
%token <tree_node> RP
%token <tree_node> LB
%token <tree_node> RB
%token <tree_node> LC
%token <tree_node> RC
%token <tree_node> STRUCT
%token <tree_node> RETURN
%token <tree_node> IF
%token <tree_node> ELSE
%token <tree_node> WHILE

/* Declared combination and priority */
%right ASSIGNOP
%left  OR
%left  AND
%left  RELOP
%left  PLUS MINUS 
%left  STAR  DIV
%right NOT
%left  DOT LB RB LP RP

/* Handle if-else reduce/shift conflict */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* Non-ternimal signs */
%type <tree_node> Program ExtDefList ExtDef ExtDecList Specifier 
%type <tree_node> StructSpecifier OptTag Tag VarDec FunDec VarList
%type <tree_node> ParamDec CompSt StmtList Stmt DefList Def 
%type <tree_node> DecList Dec Exp Args

%%

/* High-level Definitions */
Program: ExtDefList {$$=Node_Initializer("Program", "", true); Insert_Child($$,$1); root=$$;}
    ;
ExtDefList: ExtDef ExtDefList {$$=Node_Initializer("ExtDefList", "", true); Insert_Child($$, $1);Insert_Child($$, $2);}
    | /* empty */ { $$=NULL; }
    ;
ExtDef: Specifier ExtDecList SEMI {$$=Node_Initializer("ExtDef", "", true); Insert_Child($$,$1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Specifier SEMI {$$=Node_Initializer("ExtDef", "", true); Insert_Child($$, $1); Insert_Child($$, $2);}
    | Specifier FunDec CompSt {$$=Node_Initializer("ExtDef", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    /* Error Recovery */
    | error ExtDecList SEMI {$$=Node_Initializer("ExtDef", "", true); char str[MAXLENGTH] = "Wrong with Specifier"; syn_error=true; yyerror(str);}
    | Specifier error SEMI {$$=Node_Initializer("ExtDef", "", true); char str[MAXLENGTH] = "Wrong ExtDecList between Specifier and \";\""; syn_error=true; yyerror(str);}
    | error SEMI {$$=Node_Initializer("ExtDef", "", true); char str[MAXLENGTH] = "Unnecessary \";\""; syn_error=true; yyerror(str);}
    | Specifier FunDec error{$$=Node_Initializer("ExtDef", "", true); char str[MAXLENGTH] = "Missing CompSt"; syn_error=true; yyerror(str);}
    ;
ExtDecList: VarDec {$$=Node_Initializer("ExtDecList", "", true); Insert_Child($$, $1);}
    | VarDec COMMA ExtDecList {$$=Node_Initializer("ExtDecList", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    /* Error Recovery */
    | error COMMA ExtDecList {$$=Node_Initializer("ExtDecList", "", true); char str[MAXLENGTH] = "Unnecessary \",\""; syn_error=true; yyerror(str);}
    | VarDec COMMA error {$$=Node_Initializer("ExtDecList", "", true); char str[MAXLENGTH] = "Unnecessary \",\", maybe change to \";\""; syn_error=true; yyerror(str);}
    ;

/* Specifiers */
Specifier: TYPE {$$=Node_Initializer("Specifier", "", true); Insert_Child($$, $1);}
    | StructSpecifier {$$=Node_Initializer("Specifier", "", true); Insert_Child($$, $1);}
    ;
StructSpecifier: STRUCT OptTag LC DefList RC {$$=Node_Initializer("StructSpecifier", "", true); Insert_Child($$,$1); Insert_Child($$, $2); Insert_Child($$, $3); Insert_Child($$, $4); Insert_Child($$, $5);}
    | STRUCT Tag {$$=Node_Initializer("StructSpecifier", "", true); Insert_Child($$, $1); Insert_Child($$, $2);}
    /* Error Recovery */
    | STRUCT OptTag LC DefList error {$$=Node_Initializer("StructSpecifier", "", true); char str[MAXLENGTH] = "Missing \"}\""; syn_error=true; yyerror(str);}
    ;
OptTag: ID {$$=Node_Initializer("OptTag", "", true); Insert_Child($$, $1);}
    | /* empty */ {$$=NULL;}
    ;
Tag: ID {$$=Node_Initializer("Tag", "", true); Insert_Child($$, $1);}
    ;

/* Declarators */
VarDec: ID {$$=Node_Initializer("VarDec", "", true); Insert_Child($$, $1);}
    | VarDec LB INT RB {$$=Node_Initializer("VarDec", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); Insert_Child($$, $4);}
    /* Error Recovery */
    | error LB INT RB {$$=Node_Initializer("VarDec", "", true); char str[MAXLENGTH] = "Wrong VarDec"; syn_error=true; yyerror(str);}
    | VarDec LB error RB {$$=Node_Initializer("VarDec", "", true); char str[MAXLENGTH] = "Complicated INT between \"[\" and \"]\""; syn_error=true; yyerror(str);}
    | VarDec LB INT error {$$=Node_Initializer("VarDec", "", true); char str[MAXLENGTH] = "Missing \"]\""; syn_error=true; yyerror(str);}
    ;
FunDec: ID LP VarList RP {$$=Node_Initializer("FunDec", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); Insert_Child($$, $4);}
    | ID LP RP {$$=Node_Initializer("FunDec", "", true); Insert_Child($$,$1); Insert_Child($$, $2); Insert_Child($$, $3);}
    /* Error Recovery */
    | ID LP error RP {$$=Node_Initializer("FunDec", "", true); char str[MAXLENGTH] = "Complicated VarList between \"(\" and \")\""; syn_error=true; yyerror(str);}
    | ID LP VarList error {$$=Node_Initializer("FunDec", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
    | ID error RP  {$$=Node_Initializer("FunDec", "", true); char str[MAXLENGTH] = "Missing \"(\""; syn_error=true; yyerror(str);}
    ;
VarList: ParamDec COMMA VarList {$$=Node_Initializer("VarList", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | ParamDec {$$=Node_Initializer("VarList", "", true); Insert_Child($$, $1);}
    /* Error Recovery */
    | ParamDec COMMA error {$$=Node_Initializer("VarList", "", true); char str[MAXLENGTH] = "Wrong \",\""; syn_error=true; yyerror(str);}
    | error COMMA VarList {$$=Node_Initializer("VarList", "", true); char str[MAXLENGTH] = "Wrong ParamDec"; syn_error=true; yyerror(str);}
    ;
ParamDec: Specifier VarDec {$$=Node_Initializer("ParamDec", "", true); Insert_Child($$, $1); Insert_Child($$, $2);}
    /* Error Recovery */
    | Specifier error {$$=Node_Initializer("ParamDec", "", true); char str[MAXLENGTH] = "Wrong VarDec"; syn_error=true; yyerror(str);}   
    ;

/* Statements */
CompSt: LC DefList StmtList RC {$$=Node_Initializer("CompSt", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$,$3); Insert_Child($$, $4);}
    | error RC {$$=Node_Initializer("CompSt", "", true); char str[MAXLENGTH] = "Missing \";\""; syn_error=true; yyerror(str);}
    ;
StmtList: Stmt StmtList  {$$=Node_Initializer("StmtList", "", true); Insert_Child($$, $1); Insert_Child($$, $2);}
    | /* empty */ {$$=NULL;}
    ;
Stmt: Exp SEMI {$$=Node_Initializer("Stmt", "", true); Insert_Child($$, $1); Insert_Child($$, $2); }
    | CompSt {$$=Node_Initializer("Stmt", "", true); Insert_Child($$, $1);}
    | RETURN Exp SEMI {$$=Node_Initializer("Stmt", "", true); Insert_Child($$, $1); Insert_Child($$,$2); Insert_Child($$, $3);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$=Node_Initializer("Stmt", "", true); Insert_Child($$, $1); Insert_Child($$, $2);Insert_Child($$, $3); Insert_Child($$, $4); Insert_Child($$, $5); }
    | IF LP Exp RP Stmt ELSE Stmt {$$=Node_Initializer("Stmt", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$,$3); Insert_Child($$, $4); Insert_Child($$, $5); Insert_Child($$, $6); Insert_Child($$, $7);}
    | WHILE LP Exp RP Stmt {$$=Node_Initializer("Stmt", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); Insert_Child($$, $4); Insert_Child($$, $5); }
    /* Error Recovery */
    | error SEMI {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Expression"; syn_error=true; /*yyerror(str);*/}
    | RETURN error SEMI {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Exp"; syn_error=true; yyerror(str);}
    | RETURN Exp error {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \";\""; syn_error=true; yyerror(str);}
    | IF LP error RP Stmt {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Exp"; syn_error=true; yyerror(str);}
    | IF error Exp RP Stmt {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \"(\""; syn_error=true; yyerror(str);}
    | IF LP Exp error Stmt {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
    | WHILE error Exp RP Stmt {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \"(\""; syn_error=true; yyerror(str);}
    | WHILE LP error RP Stmt {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Exp"; syn_error=true; yyerror(str);}
    | WHILE LP Exp error Stmt {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
    | IF LP Exp RP error ELSE Stmt {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \";\""; syn_error=true; yyerror(str);}
    | IF LP Exp RP error %prec LOWER_THAN_ELSE {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Stmt"; syn_error=true; yyerror(str);}
    | IF LP Exp RP Stmt ELSE error {$$=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Stmt"; syn_error=true; yyerror(str);}
    ;

/* Local Definitions */
DefList: Def DefList {$$=Node_Initializer("DefList", "", true); Insert_Child($$, $1); Insert_Child($$, $2); }
    | /* empty */ {$$=NULL;}
    ;
Def: Specifier DecList SEMI {$$=Node_Initializer("Def", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); }
    /* Error Recovery */
	| Specifier error SEMI {$$=Node_Initializer("Def", "", true); char str[MAXLENGTH] = "Wrong DefList"; syn_error=true; yyerror(str);}
    ;
DecList: Dec {$$=Node_Initializer("DecList", "", true); Insert_Child($$, $1); }
    | Dec COMMA DecList {$$=Node_Initializer("DecList", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); }
    /* Error Recovery */
    | error COMMA DecList {$$=Node_Initializer("DecList", "", true); char str[MAXLENGTH] = "Wrong Declaration"; syn_error=true; yyerror(str);}
    | Dec COMMA error {$$=Node_Initializer("DecList", "", true); char str[MAXLENGTH] = "Unnecessary \",\",maybe change to \";\""; syn_error=true; yyerror(str);}
    ;
Dec: VarDec {$$=Node_Initializer("Dec", "", true); Insert_Child($$,$1); }
    | VarDec ASSIGNOP Exp {$$=Node_Initializer("Dec", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); }
    /* Error Recovery */
    | error ASSIGNOP Exp{$$=Node_Initializer("Dec", "", true); char str[MAXLENGTH] = "Wrong VarDec"; syn_error=true; yyerror(str);}
    | VarDec ASSIGNOP error{$$=Node_Initializer("Dec", "", true); char str[MAXLENGTH] = "COmplicated \"=\""; syn_error=true; yyerror(str);}
    ;

/* Expressions */
Exp: Exp ASSIGNOP Exp {$$=Node_Initializer("Exp", "", true ); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Exp AND Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Exp OR Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Exp RELOP Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Exp PLUS Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Exp MINUS Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Exp STAR Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Exp DIV Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | LP Exp RP {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | MINUS Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2);}
    | NOT Exp {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2);}
    | ID LP Args RP {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); Insert_Child($$, $4);}
    | ID LP RP {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | Exp LB Exp RB {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); Insert_Child($$, $4); }
    | Exp DOT ID {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3);}
    | ID {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1);}
    | INT {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1);}
    | FLOAT {$$=Node_Initializer("Exp", "", true); Insert_Child($$, $1);}
    /* Error Recovery */
    | Exp STAR error {$$=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Syntax Errors"; syn_error=true; yyerror(str);}
    | ID LP Args error {$$=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
    | ID LP  error {$$=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
    | Exp LB error RB {$$=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Wrong Exp"; syn_error=true; yyerror(str);}
    | Exp LB Exp error {$$=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Missing \"]\""; syn_error=true; yyerror(str);}
    ;
Args: Exp COMMA Args {$$=Node_Initializer("Args", "", true); Insert_Child($$, $1); Insert_Child($$, $2); Insert_Child($$, $3); }
    | Exp {$$=Node_Initializer("Args", "", true); Insert_Child($$, $1); }
    /* Error Recovery */
    | Exp COMMA error {$$=Node_Initializer("Args", "", true); char str[MAXLENGTH] = "Wrong Args"; syn_error=true; yyerror(str);}
    ;
%%

yyerror(char *msg){
        
    if(syn_error==true && strcmp(msg,"syntax error") != 0){
        if(last_syn_error_lineno==-1){
            last_syn_error_lineno = yylineno;
            fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
        }
        else{
            if(last_syn_error_lineno != yylineno)
                fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
        }
    }
    else if (syn_error==false){
        fprintf(stderr, "Error type B at line %d: %s\n", yylineno, "Syntax Errors");
    }

}
