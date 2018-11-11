%option yylineno

%{
    /* Libraries included */
    #include<stdbool.h>
    #include<math.h>
    #include<stdlib.h>
    #include "Common.h"
    #include "syntax.tab.h"
    #include "SyntaxTree.h"

    bool lex_error = false;
    bool syn_error = false;

    int last_syn_error_lineno = -1;
%}

SEMI ";"
COMMA ","
ASSIGNOP "="
RELOP >|<|>=|<=|==|!=
PLUS "+"
MINUS "-"
STAR "*"
DIV "/"
AND "&&"
OR "||"
DOT "."
NOT "!"
TYPE int|float
LP "("
RP ")"
LB "["
RB "]"
LC "{"
RC "}"
STRUCT "struct"
RETURN "return"
IF "if"
ELSE "else"
WHILE "while"
WHILESPACE [ \t]+
DIGIT [0-9]
LETTER [a-zA-Z_]
INTDEC 0|([1-9]{DIGIT}*)
INTOCT 0|(0[1-7][0-7]*)
INTHEX 0|((0x|0X)[1-9a-fA-F][0-9a-fA-F]*)
FLOATCOMMON ([0-9]*\.[0-9]+)|([0-9]+\.)
FLOATEXP (([0-9]*\.[0-9]+)|([0-9]+\.))[eE][+-]?(([1-9][0-9]*)|0)
ID {LETTER}({LETTER}|{DIGIT})*
COMMENTS \/\/.*|(\/\*(([^*]*)|(([^*]*)[*]([^/]*)))\*\/)
%%

{COMMENTS} {;} //Comments here
{WHILESPACE} {;} //Do nothing here
{COMMA} {
    yylval.tree_node = Node_Initializer("COMMA", yytext, false);
    return COMMA;
    }
{SEMI} { 
    yylval.tree_node = Node_Initializer("SEMI", yytext, false);
    return SEMI;
    }
{WHILE} { 
    yylval.tree_node = Node_Initializer("WHILE", yytext, false);
    return WHILE;
    }
{ELSE} { 
    yylval.tree_node = Node_Initializer("ELSE", yytext, false);
    return ELSE;
    }
{IF} { 
    yylval.tree_node = Node_Initializer("IF", yytext, false);
    return IF;
    }
{RETURN} { 
    yylval.tree_node = Node_Initializer("RETURN", yytext, false);
    return RETURN;
    }
{STRUCT} { 
    yylval.tree_node = Node_Initializer("STRUCT", yytext, false);
    return STRUCT;
    }
{RC} { 
    yylval.tree_node = Node_Initializer("RC", yytext, false);
    return RC;
    }
{LC} { 
    yylval.tree_node = Node_Initializer("LC", yytext, false);
    return LC;
    }
{RB} { 
    yylval.tree_node = Node_Initializer("RB", yytext, false);
    return RB;
    }
{LB} { 
    yylval.tree_node = Node_Initializer("LB", yytext, false);
    return LB;
    }
{RP} { 
    yylval.tree_node = Node_Initializer("RP", yytext, false);
    return RP;
    }
{LP} { 
    yylval.tree_node = Node_Initializer("LP", yytext, false);
    return LP;
    }
{TYPE} { 
    yylval.tree_node = Node_Initializer("TYPE", yytext, false);
    return TYPE;
    }
{NOT} { 
    yylval.tree_node = Node_Initializer("NOT", yytext, false);
    return NOT;
    }
{DOT} { 
    yylval.tree_node = Node_Initializer("DOT", yytext, false);
    return DOT;
    }
{OR} { 
    yylval.tree_node = Node_Initializer("OR", yytext, false);
    return OR;
    }
{AND} { 
    yylval.tree_node = Node_Initializer("AND", yytext, false);
    return AND;
    }
{DIV} { 
    yylval.tree_node = Node_Initializer("DIV", yytext, false);
    return DIV;
    }
{STAR} { 
    yylval.tree_node = Node_Initializer("STAR", yytext, false);
    return STAR;
    }
{MINUS} { 
    yylval.tree_node = Node_Initializer("MINUS", yytext, false);
    return MINUS;
    }
{PLUS} { 
    yylval.tree_node = Node_Initializer("PLUS", yytext, false);
    return PLUS;
    }
{RELOP} { 
    yylval.tree_node = Node_Initializer("RELOP", yytext, false);
    return RELOP;
    }
{ASSIGNOP} { 
    yylval.tree_node = Node_Initializer("ASSIGNOP", yytext, false);
    return ASSIGNOP;
    }
{FLOATEXP} {
    float value = FloatExp_2_FloatCommon(yytext);
    char content[128];
    memset(content, '\0', sizeof(content));
    sprintf(content, "%f", value); 

    yylval.tree_node = Node_Initializer("FLOAT", content, false);
    return FLOAT;
    }
{FLOATCOMMON} {
    yylval.tree_node = Node_Initializer("FLOAT", yytext, false);
    return FLOAT;
    }
{INTHEX} {
    int value = Hex_2_Dec(yytext);
    char content[128];
    memset(content, '\0', sizeof(content));
    sprintf(content, "%d", value);

    yylval.tree_node = Node_Initializer("INT", content, false);
    return INT;
    }
{INTOCT} { 
    int value = Oct_2_Dec(yytext);
    char content[128];
    memset(content, '\0', sizeof(content));
    sprintf(content, "%d", value);

    yylval.tree_node = Node_Initializer("INT", content, false);
    return INT;
    }
{INTDEC} { 
    yylval.tree_node = Node_Initializer("INT", yytext, false);
    return INT;
    }
{ID} { 
    yylval.tree_node = Node_Initializer("ID", yytext, false);
    return ID;
    }
\n {
    ;
    }
. {
    printf("Error type A at Line %d: Unrecognized Identifiers \'%s\'\n", yylineno, yytext, false);
    lex_error = true;
    }
