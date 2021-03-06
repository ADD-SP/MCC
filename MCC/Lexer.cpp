#include "Lexer.h"

unordered_set<string> Lexer::_keywords;
unordered_set<string> Lexer::_types;

void Lexer::_iniKeyWordsAndTypes()
{
	if (_keywords.size() == 0)
	{
		_keywords.insert("const");
		_keywords.insert("if");
		_keywords.insert("else");
		_keywords.insert("while");
		_keywords.insert("for");
		_keywords.insert("return");
		_keywords.insert("switch");
		_keywords.insert("case");
		_keywords.insert("break");
		_keywords.insert("continue");
		_keywords.insert("goto");
		_keywords.insert("true");
		_keywords.insert("false");

		_types.insert("int");
		_types.insert("float");
		_types.insert("bool");
		_types.insert("void");
	}
}

void Lexer::_handle(const string& filename)
{
	fstream fs(filename, ios::in);

	char c;

	while (fs.peek() != EOF)
	{
		c = fs.peek();
		while (c == ' ' || c == '\n' || c == '\t')
		{
			if (c == '\n')
			{
				_line++;
			}
			fs.get(c);
			c = fs.peek();
		}

		if (c == EOF)
		{
			break;
		}

		if (_matchIdOrKeyWord(fs))
		{
			continue;
		}

		if (_matchOperator(fs))
		{
			continue;
		}

		if (_matchNumber(fs))
		{
			continue;
		}

		if (_matchOther(fs))
		{
			continue;
		}
	}

	fs.close();
	_tokens.push_back(new EndToken());
}

bool Lexer::_matchOther(fstream& fs)
{
	char c = fs.peek();
	bool isFound = false;
	string lexeme;
	
	switch (c)
	{
	case '(':
	case ')':
	case '[':
	case ']':
		fs.get(c);
		lexeme.push_back(c);
		_tokens.push_back(new Bracket(lexeme, _line));
		isFound = true;
		break;
	case '{':
		// environment.createNewEnvironment();
		// environment.goNextEnvitonment();
		fs.get(c);
		lexeme.push_back(c);
		_tokens.push_back(new Bracket(lexeme, _line));
		isFound = true;
		break;
	case '}':
		// environment.backPreviouEnvironment();
		fs.get(c);
		lexeme.push_back(c);
		_tokens.push_back(new Bracket(lexeme, _line));
		isFound = true;
		break;
	case ';':
		fs.get(c);
		lexeme.push_back(c);
		_tokens.push_back(new Semicolon(lexeme, _line));
		isFound = true;
		break;
	case ',':
		fs.get(c);
		lexeme.push_back(c);
		_tokens.push_back(new Comma(lexeme, _line));
		isFound = true;
		break;
	default:
		isFound = false;
		break;
	}
	return isFound;
}

bool Lexer::_matchOperator(fstream& fs)
{
	char c = fs.peek();

	switch (c)
	{
	case '+':
		fs.get(c);
		if (fs.peek() == '+')
		{
			fs.get(c);
			_tokens.push_back(new Operator(Operator::inc, _line));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::plus, _line));
		}
		break;
	case '-':
		fs.get(c);
		if (fs.peek() == '-')
		{
			fs.get(c);
			_tokens.push_back(new Operator(Operator::dec, _line));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::minus, _line));
		}
		break;
	case '*':
		fs.get(c);
		_tokens.push_back(new Operator(Operator::star, _line));
		break;
	case '/':
		fs.get(c);
		_tokens.push_back(new Operator(Operator::div, _line));
		break;
	case '%':
		fs.get(c);
		_tokens.push_back(new Operator(Operator::mod, _line));
		break;
	case '&':
		fs.get(c);
		if (fs.peek() == '&')
		{
			fs.get(c);
			_tokens.push_back(new Operator(Operator::logicalAnd, _line));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::bitAnd, _line));
		}
		break;
	case '|':
		fs.get(c);
		if (fs.peek() == '|')
		{
			fs.get(c);
			_tokens.push_back(new Operator(Operator::logicalOr, _line));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::bitOr, _line));
		}
		break;

	case '<':
		fs.get(c);
		if (fs.peek() == '=')
		{
			fs.get(c);
			_tokens.push_back(new Operator(Operator::lessEqual, _line));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::less, _line));
		}
		break;
	case '>':
		fs.get(c);
		if (fs.peek() == '=')
		{
			fs.get(c);
			_tokens.push_back(new Operator(Operator::greateEqual, _line));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::greate, _line));
		}
		break;
	case '=':
		fs.get(c);
		if (fs.peek() == '=')
		{
			fs.get(c);
			_tokens.push_back(new Operator(Operator::equal, _line));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::assign, _line));
		}
		break;
	case '!':
		fs.get(c);
		if (fs.peek() == '=')
		{
			fs.get(c);
			_tokens.push_back(new Operator(Operator::notEqual, _line));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::no, _line));
		}
		break;

	default:
		return false;
		break;
	}

	return true;
}

bool Lexer::_matchNumber(fstream& fs)
{
	char c = fs.peek();
	bool isInterget = true;
	string lexeme;

	if (c >= '0' && c <= '9')
	{
		do
		{
			fs.get(c);
			if (c != '.')
			{
				lexeme.push_back(c);
			}
			else
			{
				isInterget = false;
				lexeme.push_back('.');
			}
			c = fs.peek();
		} while ((c >= '0' && c <= '9') || c == '.');

		if (isInterget)
		{
			_tokens.push_back(new Interger(lexeme, _line));
		}
		else
		{
			_tokens.push_back(new Decimal(lexeme, _line));
		}
	}

	return lexeme.size() == 0 ? false : true;
}

bool Lexer::_matchIdOrKeyWord(fstream& fs)
{
	char c = fs.peek();
	string lexeme;
	bool isIdOrKeyWord = false;

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
	{
		isIdOrKeyWord = true;

		do
		{
			fs.get(c);
			lexeme.push_back(c);
			c = fs.peek();

		} while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));

		if (_keywords.find(lexeme) != _keywords.end())
		{
			_tokens.push_back(new Keyword(lexeme, _line));
		}
		else if (_types.find(lexeme) != _types.end())
		{
			_tokens.push_back(new Type(lexeme, _line));
		}
		else
		{
			// environment.insert(lexeme, SymbolTableItem(lexeme, g_getVar(), "", 0));
			_tokens.push_back(new Id(lexeme, _line));
		}
	}
	return isIdOrKeyWord;
}

Lexer::Lexer(const char* filename)
{
	_iniKeyWordsAndTypes();
	string str(filename);
	_handle(str);
	_index = -1;
}

Lexer::Lexer(const string& filename)
{
	_iniKeyWordsAndTypes();
	_handle(filename);
	_index = -1;
}

Token* Lexer::nextToken()
{
	if (_index + 1 == (Index)_tokens.size() - 1)
	{
		return _tokens[_index + 1];
	}
	else if (_index + 1 < (Index)_tokens.size())
	{
		return _tokens[++_index];
	}
	else
	{
		return nullptr;
	}
}

Token* Lexer::peek()
{
	if (_index + 1 < (Index)_tokens.size())
	{
		return _tokens[_index + 1];
	}
	else
	{
		return nullptr;
	}
}

void Lexer::seek(Index offset)
{
	bool f1 = _index + offset >= -1;
	bool f2 = (_index + offset) < (Index)_tokens.size();
	if (f1 && f2)
	{
		_index += offset;
	}
	else
	{
		throw out_of_range("seek error");
	}
	
}
