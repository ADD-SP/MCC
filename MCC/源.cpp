#include <iostream>
#include "Parser.h"

Lexer lexer("1.txt");

int main()
{
	Parser par(lexer);
	return 0;
}


