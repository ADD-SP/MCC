#include "Parser.h"

void Parser::_gen(string str)
{
	cout << str << endl;
}

AstNode* Parser::_parseSE()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr;
	AstNode* second = nullptr;
	AstNode* third = nullptr;
	AstNode* fourth = nullptr;
	AstNode* fifth = nullptr;
	AstNode* sixth = nullptr;
	Token* token = _lexer.peek();

	if (token->getType() == Id::typeName
		|| token->getType() == Number::typeName
		|| token->getType() == Interger::typeName
		|| token->getType() ==  Decimal::typeName
		|| (token->getType() == Keyword::typeName && token->lexeme == "true")
		|| (token->getType() == Keyword::typeName && token->lexeme == "false")
		|| (token->getType() == Bracket::typeName && token->lexeme == "("))
	{
		first = _parseBE();
		second = _parse_SE();
	}
	else if (token->getType() == Keyword::typeName && token->lexeme == "if")
	{
		token = _lexer.nextToken();
		token = _lexer.peek();
		if (token->getType() == Bracket::typeName && token->lexeme == "(")
		{
			token = _lexer.nextToken();
			first = _parseBE();
			token = _lexer.peek();
			if (token->getType() == Bracket::typeName && token->lexeme == ")")
			{
				token = _lexer.nextToken();
				token = _lexer.peek();
				if (token->getType() == Bracket::typeName && token->lexeme == "{")
				{
					token = _lexer.nextToken();
					second = _parseSE();
					token = _lexer.peek();
					if (token->getType() == Bracket::typeName && token->lexeme == "}")
					{
						token = _lexer.nextToken();
					}
					else
					{
						exit(-100);
					}
				}
				else
				{
					exit(-100);
				}
			}
			else
			{
				exit(-100);
			}
		}
		else
		{
			exit(-100);
		}
	}
	else if (NOT((token->getType() == EndToken::typeName)
		|| (token->getType() == Bracket::typeName && token->lexeme == "}")))
	{
		exit(-100);
	}
	return nullptr;
}

AstNode* Parser::_parseSEIF()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr;
	AstNode* second = nullptr;
	AstNode* third = nullptr;
	AstNode* fourth = nullptr;
	AstNode* fifth = nullptr;
	AstNode* sixth = nullptr;
	Token* token = _lexer.peek();

	if (token->getType() == Keyword::typeName && token->lexeme == "else")
	{
		token = _lexer.nextToken();
		token = _lexer.peek();
		if (token->getType() == Bracket::typeName && token->lexeme == "{")
		{
			token = _lexer.nextToken();
			first = _parseSE();
			token = _lexer.peek();
			if (token->getType() == Bracket::typeName && token->lexeme == "}")
			{
				token = _lexer.nextToken();
			}
			else
			{
				exit(-100);
			}
		}
		else
		{
			exit(-100);
		}
	}
	else if (NOT(token->getType() == EndToken::typeName
		||(token->getType() == Bracket::typeName && token->lexeme == "}")))
	{
		exit(-100);
	}

	return nullptr;
}

AstNode* Parser::_parse_SE()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr;
	AstNode* second = nullptr;
	AstNode* third = nullptr;
	AstNode* fourth = nullptr;
	AstNode* fifth = nullptr;
	AstNode* sixth = nullptr;
	Token* token = _lexer.peek();

	if (token->getType() == Operator::typeName && token->lexeme == "=")
	{
		token = _lexer.nextToken();
		first = _parseBE();
		token = _lexer.peek();
		if (token->getType() == Semicolon::typeName)
		{
			token = _lexer.nextToken();
		}
		else
		{
			exit(-100);
		}
	}
	else if (token->getType() == Bracket::typeName && token->lexeme == "(")
	{
		token = _lexer.nextToken();
		first = _parseARGL();
		token = _lexer.peek();
		if (token->getType() == Bracket::typeName && token->lexeme == ")")
		{
			token = _lexer.nextToken();
			token = _lexer.peek();
			if (token->getType() == Semicolon::typeName)
			{
				token = _lexer.nextToken();
			}
			else
			{
				exit(-100);
			}
		}
		else
		{
			exit(-100);
		}
	}
	else if (token->getType() == Semicolon::typeName)
	{
		token = _lexer.nextToken();
	}
	else
	{
		exit(-100);
	}

	return nullptr;
}

AstNode* Parser::_parseARGL()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr;
	AstNode* second = nullptr;
	AstNode* third = nullptr;
	AstNode* fourth = nullptr;
	AstNode* fifth = nullptr;
	AstNode* sixth = nullptr;
	Token* token = _lexer.peek();

	if (token->getType() == Id::typeName
		|| token->getType() == Number::typeName
		|| token->getType() == Interger::typeName
		|| token->getType() == Decimal::typeName
		|| (token->getType() == Keyword::typeName && token->lexeme == "true")
		|| (token->getType() == Keyword::typeName && token->lexeme == "false")
		|| (token->getType() == Bracket::typeName && token->lexeme == "("))
	{
		token = _lexer.nextToken();
		first = _parseBE();
		second = _parse_ARGL();
	}
	else
	{
		exit(-100);
	}

	return nullptr;
}

AstNode* Parser::_parse_ARGL()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr;
	AstNode* second = nullptr;
	AstNode* third = nullptr;
	AstNode* fourth = nullptr;
	AstNode* fifth = nullptr;
	AstNode* sixth = nullptr;
	Token* token = _lexer.peek();

	if (token->getType() == Comma::typeName)
	{
		token = _lexer.nextToken();
		first = _parse_ARGL();
	}
	else if (token->getType() == Id::typeName
		|| token->getType() == Number::typeName
		|| token->getType() == Interger::typeName
		|| token->getType() == Decimal::typeName
		|| (token->getType() == Keyword::typeName && token->lexeme == "true")
		|| (token->getType() == Keyword::typeName && token->lexeme == "false")
		|| (token->getType() == Bracket::typeName && token->lexeme == "("))
	{
		token = _lexer.nextToken();
		first = _parseBE();
		second = _parse_ARGL();
	}
	else if (token->getType() == Bracket::typeName && token->lexeme == "(")
	{
		token = _lexer.nextToken();
		first = _parseARGL();
		token = _lexer.peek();
		if (token->getType() == Bracket::typeName && token->lexeme == ")")
		{
			token = _lexer.nextToken();
			second = _parse_ARGL();
		}
		else
		{
			exit(-100);
		}
	}
	else if (NOT((token->getType() == Bracket::typeName && token->lexeme == ")")
		|| token->getType() == EndToken::typeName))
	{
		exit(-100);
	}

	return nullptr;
}

AstNode* Parser::_parseBE()
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	Token* token = _lexer.peek();
	string type = token->getType();
	string lexeme = token->lexeme;

	if (type == Number::typeName
		|| type == Interger::typeName
		|| type == Decimal::typeName
		|| type == Id::typeName
		|| (type == Keyword::typeName && lexeme == "true")
		|| (type == Keyword::typeName && lexeme == "false")
		|| (type == Bracket::typeName && lexeme == "("))
	{
		left = _parseBF();
		p->push_right(left);
		right = _parse_BE(GET_VALUE(left, 0));
		p->push_right(right);

		if (right)
		{
			p->push_back(GET_VALUE(right, 0));
		}
		else
		{
			p->push_back(GET_VALUE(left, 0));
		}
	}
	else
	{
		exit(-100);
	}
	return p;
}

AstNode* Parser::_parse_BE(string lexeme)
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	Token* token = _lexer.peek();
	string var;
	string type = token->getType();

	if ((type == Operator::typeName && token->lexeme == "&&")
		|| (type == Operator::typeName && token->lexeme == "||")
		|| (type == Operator::typeName && token->lexeme == "==")
		|| (type == Operator::typeName && token->lexeme == "<")
		|| (type == Operator::typeName && token->lexeme == "<=")
		|| (type == Operator::typeName && token->lexeme == ">")
		|| (type == Operator::typeName && token->lexeme == ">="))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		left = _parseBF();
		p->push_right(left);

		_gen(var + "=" + lexeme + token->lexeme + GET_VALUE(left, 0));

		right = _parse_BE(GET_VALUE(left, 0));
		p->push_right(right);

		if (right)
		{
			p->push_back(GET_VALUE(right, 0));
		}
		else
		{
			p->push_back(GET_VALUE(left, 0));
		}

		return p;
	}
	else if (!((type == Bracket::typeName && token->lexeme == ")") || type == EndToken::typeName || type == Semicolon::typeName))
	{
		exit(-100);
	}


	return nullptr;
}

AstNode* Parser::_parseBF()
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	Token* token = _lexer.peek();
	string type = token->getType();
	string lexeme = token->lexeme;

	if (type == Number::typeName
		|| type == Interger::typeName
		|| type == Decimal::typeName
		|| type == Id::typeName)
	{
		left = _parseE();
		p->push_right(left);
		p->push_back(GET_VALUE(left, 0));
	}
	else if ((type == Keyword::typeName && lexeme == "true")
		|| (type == Keyword::typeName && lexeme == "false"))
	{
		token = _lexer.nextToken();
		p->push_back(lexeme);
	}
	else if (type == Bracket::typeName && lexeme == "(")
	{
		token = _lexer.nextToken();

		left = _parseBE();
		p->push_right(left);
		p->push_back(GET_VALUE(left, 0));

		token = _lexer.peek();

		if (type == Bracket::typeName && lexeme == "(")
		{
			token = _lexer.nextToken();
		}
		else
		{
			exit(-100);
		}
	}
	else
	{
		exit(-100);
	}

	return p;
}

AstNode* Parser::_parseE()
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	string value;
	string var;
	Token* token = _lexer.peek();
	string lexeme = token->lexeme;
	string type = token->getType();
	if (type == Number::typeName
		|| type == Decimal::typeName
		|| type == Interger::typeName
		|| type == Id::typeName
		|| (type == Bracket::typeName && lexeme == "("))
	{
		left = _parseT();
		right = _parse_E(GET_VALUE(left, 0));
		p->push_right(left);
		p->push_right(right);

		if (right)
		{
			p->push_back(GET_VALUE(right, 0));
		}
		else
		{
			p->push_back(GET_VALUE(left, 0));
		}

	}
	else
	{
		exit(-100);
	}
	return p;
}

AstNode* Parser::_parseT()
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	string value;
	string var;
	Token* token = _lexer.peek();
	string lexeme = token->lexeme;
	string type = token->getType();
	if (type == Number::typeName
		|| type == Decimal::typeName
		|| type == Interger::typeName
		|| type == Id::typeName
		|| (type == Bracket::typeName && lexeme == "("))
	{
		left = _parseF();
		right = _parse_T(GET_VALUE(left, 0));
		p->push_right(left);
		p->push_right(right);

		if (right)
		{
			p->push_back(GET_VALUE(right, 0));
		}
		else
		{
			p->push_back(GET_VALUE(left, 0));
		}

	}
	else
	{
		exit(-100);
	}
	return p;
}


AstNode* Parser::_parse_E(string number)
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	string value;
	string var;
	Token* token = _lexer.peek();
	string lexeme = token->lexeme;
	string type = token->getType();
	if (type == Operator::typeName)
	{
		if (token->lexeme == "+" || token->lexeme == "-")
		{
			var = g_getVar();
			token = _lexer.nextToken();
			left = _parseT();

			_gen(var + "=" + number + token->lexeme + GET_VALUE(left, 0));

			right = _parse_E(var);
			p->push_right(left);
			p->push_right(right);

			if (right)
			{
				p->push_back(GET_VALUE(right, 0));
			}
			else
			{
				p->push_back(var);
			}

			return p;
		}
	}
	else if (type != EndToken::typeName
		&& (type != Bracket::typeName && lexeme == ")")
		&& type != Semicolon::typeName)
	{
		exit(-100);
	}

	return nullptr;
}

AstNode* Parser::_parse_T(string number)
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	string value;
	string var;
	Token* token = _lexer.peek();
	string lexeme = token->lexeme;
	string type = token->getType();
	if (type == Operator::typeName)
	{
		if (token->lexeme == "*" || token->lexeme == "/")
		{
			var = g_getVar();
			token = _lexer.nextToken();
			left = _parseF();

			_gen(var + "=" + number + token->lexeme + GET_VALUE(left, 0));

			right = _parse_T(var);
			p->push_right(left);
			p->push_right(right);

			if (right)
			{
				p->push_back(GET_VALUE(right, 0));
			}
			else
			{
				p->push_back(var);
			}

			return p;
		}
	}
	else if (type != EndToken::typeName
		&& (type != Bracket::typeName && lexeme == ")")
		&& type != Semicolon::typeName)
	{
		exit(-100);
	}
	return nullptr;
}

AstNode* Parser::_parseF()
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	string var;
	Token* token = _lexer.peek();
	string lexeme = token->lexeme;
	string type = token->getType();
	if (type == Interger::typeName
		|| type == Decimal::typeName
		|| type == Number::typeName
		|| type == Id::typeName)
	{
		token = _lexer.nextToken();
		p->push_back(token->lexeme);
	}
	else if (type == Bracket::typeName && lexeme == "(")
	{
		token = _lexer.nextToken();
		left = _parseE();
		p->push_left(left);
		p->push_back(GET_VALUE(left, 0));

		token = _lexer.peek();
		type = token->getType();
		lexeme = token->lexeme;

		if (type == Bracket::typeName && lexeme == ")")
		{
			token = _lexer.nextToken();
		}
		else
		{
			exit(-100);
		}
	}
	else
	{
		exit(-100);
	}
	return p;
}

Parser::Parser(Lexer& lexer)
	:_lexer(lexer)
{
	parse();
}

void Parser::parse()
{
	_parseSE();
}
