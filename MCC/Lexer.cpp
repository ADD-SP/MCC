#include "Lexer.h"

void Lexer::_handle(const string& filename)
{
	fstream fs(filename, ios::in);

	char c;

	while (fs.peek() != EOF)
	{
		c = fs.peek();
		while (c == ' ' || c == '\n' || c == '\t')
		{
			fs.get(c);
			c = fs.peek();
		}

		if (c == EOF)
		{
			break;
		}

		if (_matchOperator(fs))
		{
			continue;
		}

		if (_matchNumber(fs))
		{
			continue;
		}
	}

	fs.close();
	_tokens.push_back(new EndToken());
}

bool Lexer::_matchOperator(fstream& fs)
{
	char c = fs.peek();

	switch (c)
	{
	case '+':
		fs.get(c);
		_tokens.push_back(new Operator(Operator::plus));
		break;
	case '-':
		fs.get(c);
		_tokens.push_back(new Operator(Operator::minus));
		break;
	case '*':
		fs.get(c);
		_tokens.push_back(new Operator(Operator::star));
		break;
	case '/':
		fs.get(c);
		_tokens.push_back(new Operator(Operator::div));
		break;
	case '=':
		fs.get(c);
		c = fs.peek();
		if (fs.peek() == '=')
		{
			fs >> c;
			_tokens.push_back(new Operator(Operator::equal));
		}
		else
		{
			_tokens.push_back(new Operator(Operator::assign));
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

	while ((c >= '0' && c <= '9') || c == '.')
	{
		fs >> c;
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
	}

	// fs.seekg(-1, ios::cur);

	if (isInterget)
	{
		_tokens.push_back(new Interger(lexeme));
	}
	else
	{
		_tokens.push_back(new Decimal(lexeme));
	}

	return lexeme.size() == 0 ? false : true;
}

Lexer::Lexer(const char* filename)
{
	string str(filename);
	_handle(str);
	_index = -1;
}

Lexer::Lexer(const string& filename)
{
	_handle(filename);
	_index = -1;
}

Token* Lexer::nextToken()
{
	if (_index + 1 == _tokens.size() - 1)
	{
		return _tokens[_index + 1];
	}
	else if (_index + 1 < _tokens.size())
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
	if (_index + 1 < _tokens.size())
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
	if (_index + offset >= -1 && _index + offset < _tokens.size())
	{
		_index += offset;
	}
	else
	{
		throw out_of_range("seek error");
	}
	
}
