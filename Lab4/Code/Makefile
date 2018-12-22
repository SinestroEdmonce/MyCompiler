parser:
	bison -d syntax.y
	flex lexical.l
	gcc main.c syntax.tab.c Common.c SyntaxTree.c ErrorReport.c IRgeneration.c SymbolType.c SymbolTable.c Semantic.c DAGoptimization.c Translate.c MIPS_ASMgeneration.c -lfl -ly -g -o ./../parser

debug:
	bison -d -t -v syntax.y
	flex lexical.l
	gcc main.c syntax.tab.c Common.c SyntaxTree.c ErrorReport.c IRgeneration.c SymbolType.c SymbolTable.c Semantic.c DAGoptimization.c Translate.c MIPS_ASMgeneration.c -lfl -ly -g -o ./../parser

lexical:
	flex lexical.l

syntax:
	bison -d syntax.y

scanner:
	gcc main.c lex.yy.c -lfl -o scanner

clean:
	rm -rf lex.yy.c syntax.tab.* ./../parser scanner ./../*.txt ./../Test_IR ./../Test_ASM ./../Test_ST ./../Test_SA ./../Test_ST_SA syntax.output
