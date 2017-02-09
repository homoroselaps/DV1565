parser: lex.yy.c binary.tab.o main.cc Function.cpp Value.cpp MultiValue.cpp Table.cpp
	g++ -std=c++14 -g -oparser binary.tab.o lex.yy.c main.cc Function.cpp Value.cpp MultiValue.cpp Table.cpp
binary.tab.o: binary.tab.c
	g++ -std=c++14 -g -c binary.tab.c
binary.tab.c: binary.y
	bison binary.y --verbose
lex.yy.c: binary.l binary.tab.c
	flex binary.l
clean:
	rm -f binary.tab.* lex.yy.c* parser
