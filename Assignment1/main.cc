#include <iostream>
#include "binary.tab.h"
#include "Library.h"
extern std::shared_ptr<Node> root;

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
	root->dump();

	auto env = std::make_shared<Table>();
	Library::load(env);
	bool isBreak = false;
	auto chunk = std::dynamic_pointer_cast<Chunk>(root);
	chunk->execute(env, isBreak);
	return 0;
}
