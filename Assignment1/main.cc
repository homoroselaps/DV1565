#include <iostream>
#include "binary.tab.h"
extern Node root;

void yy::parser::error(std::string const &err)
{
	std::cout << "It's one of the bad ones...  " << err << std::endl;
}

int main(int argc, char **argv)
{
	yy::parser parser;
	parser.set_debug_level(1);
	if( !parser.parse())
		std::cout << "It's a bingo! " <<std::endl;
	root.dump();
	return 0;
}
