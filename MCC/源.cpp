#include <iostream>
#include "Parser.h"

Lexer lexer("1.c");

int main()
{
	Parser par(lexer);
	return 0;
}


