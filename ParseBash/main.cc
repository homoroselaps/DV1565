#include <iostream>
#include "binary.tab.hh"
#include "Node.hpp"
extern Node root;

void yy::parser::error(std::string const &err)
{
	std::cout << "It's one of the bad ones...  " << err << std::endl;
}

int main(int argc, char **argv)
{
	yy::parser parser;
	parser.set_debug_level(1);
	if(!parser.parse())
		std::cout << "Nope" << std::endl;
	root.dump();
	return 0;
}
