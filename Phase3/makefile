all:    flex lexical.l
	bison -y -d semantics.y
	g++ -std=c++11 lex.yy.c y.tab.c
	./a.out program.txt
	java -jar jasmin.jar javaByteCode.j
	java result

