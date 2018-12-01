parser:
	bison -d syntax.y
	flex lexical.l
	gcc main.c syntax.tab.c Common.c SyntaxTree.c ErrorReport.c IRgeneration.c SymbolType.c SymbolTable.c  Semantic.c -lfl -ly -g -o ./../parser

debug:
	bison -d -t -v syntax.y
	flex lexical.l
	gcc main.c syntax.tab.c Common.c SyntaxTree.c ErrorReport.c IRgeneration.c SymbolType.c SymbolTable.c Semantic.c -lfl -ly -g -o ./../parser

lexical:
	flex lexical.l

syntax:
	bison -d syntax.y

scanner:
	gcc main.c lex.yy.c -lfl -o scanner

clean:
	rm lex.yy.c syntax.tab.* ./../parser scanner ./../*.txt syntax.output
