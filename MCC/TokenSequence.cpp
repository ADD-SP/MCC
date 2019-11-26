#include "TokenSequence.h"

TokenSequence::TokenSequence()
{
}

TokenSequence::TokenSequence(size_t num, ...)
{
	va_list args;
	va_start(args, num);

	Token* token = nullptr;

	for (int i = 0; i < num; i++)
	{
		token = va_arg(args, Token*);
		_tokens.push_back(token);
	}

	va_end(args);
}

TokenSequence::TokenSequence(const TokenSequence& tokenSequence)
{
	this->clear();
	for (int i = 0; i < tokenSequence.size(); i++)
	{
		this->push_back(1 ,tokenSequence[i]);
	}
}

Token*& TokenSequence::operator[](int index)
{
	return _tokens[index];
}

Token* TokenSequence::operator[](int index) const
{
	return _tokens[index];
}

void TokenSequence::push_back(size_t num, ...)
{
	va_list args;
	va_start(args, num);

	Token* token = nullptr;

	for (int i = 0; i < num; i++)
	{
		token = va_arg(args, Token*);
		_tokens.push_back(token);
	}

	va_end(args);
}

void TokenSequence::clear()
{
	_tokens.clear();
}

size_t TokenSequence::size() const
{
	return _tokens.size();
}

size_t TokenSequence::getHashCode() const
{
	size_t hash = 0;
	for (int i = 0; i < size(); i++)
	{
		hash += std::hash<Token*>()(_tokens[i]);
	}
	return hash;
}

bool TokenSequence::operator==(const TokenSequence& tokenSequence) const
{
	if (this->size() != tokenSequence.size())
	{
		return false;
	}

	for (int i = 0; i < this->size(); i++)
	{
		if (*(this->operator[](i)) != *(tokenSequence[i]))
		{
			return false;
		}
	}

	return true;
}
