#include <iostream>
#include "Parser.h"

Lexer lexer("1.cpp");

int main()
{
	Parser par(lexer);
	return 0;
}


