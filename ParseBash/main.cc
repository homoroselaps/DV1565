#include <iostream>
#include "binary.tab.hh"
#include "Node.hpp"
extern Node root;

void yy::parser::error(std::string const &err)
{
	std::cout << "EEK, parse error! Message: " << err << std::endl;
}

int main(int argc, char **argv)
{
	yy::parser parser;
	parser.set_debug_level(1);
	if(parser.parse() == 0)
		std::cout << "Success" << std::endl;
	root.dump();
	return 0;
}
