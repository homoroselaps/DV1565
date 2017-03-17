#include <iostream>
#include <fstream>
#include "binary.tab.h"
#include "source/LibraryStd.h"
#include "source/LibraryIO.h"
#include "source/Compiler.h"

extern std::shared_ptr<Node> root;
extern FILE* yyin;

void yy::parser::error(std::string const &err)
{
	std::cout << "It's one of the bad ones...  " << err << std::endl;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cout << "No input file specified!" << std::endl;
		return 1;
	}


	yyin = fopen(argv[1], "r");

	yy::parser parser;
	//parser.set_debug_level(1);
	if( !parser.parse()) {
		std::cout << "It's a bingo! " <<std::endl;
	} else {
		return 1;
	}
	root->dump();
	
	auto chunk = std::dynamic_pointer_cast<Chunk>(root);
	assert(chunk);
	try {
		auto cmpl = Compiler{ chunk };
		auto out = cmpl.compile();
		
		std::ofstream asmfile{ "target.cc", std::ios::out | std::ios::trunc };
		asmfile << std::get<0>(out);
		asmfile.close();

		std::ofstream graphvizfile{ "parse.txt", std::ios::out | std::ios::trunc };
		graphvizfile << std::get<1>(out);
		graphvizfile.close();
	}	
	catch(const std::exception &e) {
		std::cout << "Exception caught: ";
		std::cout << e.what() << std::endl;
	}

	return 0;
}
