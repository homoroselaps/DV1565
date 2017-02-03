#include <iostream>
#include "binary.tab.hh"
extern std::vector<int> nums;

void yy::parser::error(std::string const &err)
{
	std::cout << "It's one of the bad ones...  " << err << std::endl;
}

int main(int argc, char **argv)
{
	yy::parser parser;
	if( !parser.parse())
		std::cout << "It's a bingo! ";
		for(int i : nums)
			std::cout << i << " ";
		std::cout << std::endl;
	return 0;
}