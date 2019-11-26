#include "Lexer.h"
#include "GS.h"
#include "LLTable.h"
#include <iostream>
#include <stack>
#include <typeinfo>
#include <unordered_map>


using std::cout;
using std::cin;
using std::endl;
using std::stack;

LLTable table;
Lexer lexer("1.txt");

void LL(Lexer& lexer);

void parseE();

void parseT();

void parse_E();

void parse_T();

void parseF();

void fillTable();

int main()
{
	fillTable();
	LL(lexer);
	parseE();
	/*fstream fs("1.txt", ios::in);

	while (fs.peek() != EOF)
	{
		string str;
		char c;
		fs.get(c);
		std::cout << c;
	}

	while (1);*/
	return 0;
}

void LL(Lexer& lexer)
{
	stack<Token*> stack;

	stack.push(new GS("E"));

	Token* top = nullptr;
	Token* temp = nullptr;
	const TokenSequence* seq = nullptr;

	while (!stack.empty())
	{
		top = stack.top();
		temp = lexer.peek();
		if (top->getType() != "GS" && top->lexeme == temp->lexeme)
		{
			temp = lexer.nextToken();
			stack.pop();
		}
		else if (top->getType() == "GS")
		{
			GS* gs = dynamic_cast<GS*>(top);
			seq = table.find(gs, temp);
			if (seq == nullptr)
			{
				exit(-1);
			}
			stack.pop();
			for (int i = seq->size() - 1; i >= 0; i--)
			{
				stack.push((*seq)[i]);
			}
		}
		else
		{
			exit(-1);
		}
	}
}

void parseE()
{
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Number" || type == "Decimal" || type == "Interger")
	{
		// printf("\t\tE -> T E\'\n");
		parseT();
		parse_E();
	}
	else
	{
		exit(-100);
	}
}

void parseT()
{
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Number" || type == "Decimal" || type == "Interger")
	{
		// printf("\t\tT -> F T\'\n");
		parseF();
		parse_T();
	}
	else
	{
		exit(-100);
	}
}

void parse_E()
{
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Operator")
	{
		if (token->lexeme == "+" || token->lexeme == "-")
		{
			// printf("Match£º%s\t", token->lexeme.c_str());
			// printf("E\' -> %s T E\'\n", token->lexeme.c_str());
			token = lexer.nextToken();
			parseT();
			printf("%s  ", token->lexeme.c_str());
			parse_E();
		}
	}
	else if (type != "EndToken")
	{
		exit(-100);
	}
	else
	{
		// printf("\t\tE\' -> &\n");
	}
}

void parse_T()
{
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Operator")
	{
		if (token->lexeme == "*" || token->lexeme == "/")
		{
			// printf("Match£º%s\t", token->lexeme.c_str());
			// printf("T\' -> %s F T\'\n", token->lexeme.c_str());
			token = lexer.nextToken();
			parseF();
			printf("%s  ", token->lexeme.c_str());
			parse_T();
		}
	}
	else if (type != "EndToken")
	{
		exit(-100);
	}
	else
	{
		// printf("\t\tT\' -> &\n");
	}
}

void parseF()
{
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Interger" || type == "Decimal")
	{
		token = lexer.nextToken();
		// printf("Match: %s\t", token->lexeme.c_str());
		// printf("F -> Number\n");
		printf("%s  ", token->lexeme.c_str());
	}
	else
	{
		exit(-100);
	}
}

void fillTable()
{
	GS* E = new GS("E");
	GS* T = new GS("T");
	GS* _E = new GS("E\'");
	GS* _T = new GS("T'");
	GS* F = new GS("F");

	Operator* plus = new Operator(Operator::plus);
	Operator* minus = new Operator(Operator::minus);
	Operator* star = new Operator(Operator::star);
	Operator* div = new Operator(Operator::div);

	Number* num = new Number("num");
	Interger* interger = new Interger("int");
	Decimal* decimal = new Decimal("decimal");

	TokenSequence* ES = new TokenSequence(2, T, _E);
	TokenSequence* _ES0 = new TokenSequence(3, plus, T, _E);
	TokenSequence* _ES1 = new TokenSequence(3, minus, T, _E);
	TokenSequence* _ES2 = new TokenSequence();

	TokenSequence* TS = new TokenSequence(2, F, _T);
	TokenSequence* _TS0 = new TokenSequence(3, star, F, _T);
	TokenSequence* _TS1 = new TokenSequence(3, div, F, _T);
	TokenSequence* _TS2 = new TokenSequence();

	TokenSequence* FS0 = new TokenSequence(1, num);
	TokenSequence* FS1 = new TokenSequence(1, interger);
	TokenSequence* FS2 = new TokenSequence(1, decimal);

	LLTableItem Eitem;
	Eitem.insert(num, *ES);
	Eitem.insert(interger, *ES);
	Eitem.insert(decimal, *ES);
	table.insert(*E, Eitem);

	LLTableItem _Eitem;
	_Eitem.insert(plus, *_ES0);
	_Eitem.insert(minus, *_ES1);
	table.insert(*_E, _Eitem);

	LLTableItem Titem;
	Titem.insert(num, *TS);
	Titem.insert(interger, *TS);
	Titem.insert(decimal, *TS);
	table.insert(*T, Titem);

	LLTableItem _Titem;
	_Titem.insert(star, *_TS0);
	_Titem.insert(div, *_TS1);
	table.insert(*_T, _Titem);

	LLTableItem Fitem;
	Fitem.insert(num, *FS0);
	Fitem.insert(interger, *FS0);
	Fitem.insert(decimal, *FS0);
	table.insert(*F, Fitem);
}
