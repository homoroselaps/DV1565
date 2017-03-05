int: lex.yy.c binary.tab.o main.cc source/Function.cpp source/Value.cpp source/MultiValue.cpp source/Table.cpp
	g++ -std=c++1y -g -o int binary.tab.o lex.yy.c main.cc source/Function.cpp source/Value.cpp source/MultiValue.cpp source/Table.cpp
binary.tab.o: binary.tab.c
	g++ -std=c++1y -g -c binary.tab.c
binary.tab.c: binary.y
	bison binary.y --verbose
lex.yy.c: binary.l binary.tab.c
	flex binary.l
clean:
	rm -f binary.tab.* lex.yy.c* int *.output
