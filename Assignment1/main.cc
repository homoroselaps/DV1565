#include <iostream>
#include "binary.tab.h"
#include "StdLibrary.h"
#include "IoLibrary.h"
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
	parser.set_debug_level(1);
	if( !parser.parse())
		std::cout << "It's a bingo! " <<std::endl;
	root->dump();

	auto env = std::make_shared<Value>();
	reinterpret_cast<Table*>(env.get())->Create();
	StdLibrary::load(env);
	IoLibrary::load(env);
	ExecControl control = ExecControl::NONE;
	auto chunk = std::dynamic_pointer_cast<Chunk>(root);
	chunk->execute(env, control);
	return 0;
}
