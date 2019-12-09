#include <iostream>
#include "Parser.h"
#include <fstream>

using std::fstream;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "no input file" << endl;
		getchar();
		return -1;
	}

	Lexer lexer(argv[1]);

	Parser parser(lexer);

	fstream fs;
	fs.open("out.txt", std::ios::out);

	if (!fs)
	{
		cout << "can't create out.txt" << endl;
		getchar();
		return -1;
	}

	for (auto itor = parser.fourTuples.begin(); itor != parser.fourTuples.end(); ++itor)
	{
		fs << (*itor).toString() << endl;
	}

	fs.close();

	cout << "success£¡" << endl;

	return 0;
}


