#include "Parser.h"

void Parser::_gen(string str)
{
	cout << str << endl;
}

AstNode* Parser::_parsePR()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Id)
		||CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE_VALUE(token, Keyword, "if")
		|| CHECK_TYPE_VALUE(token, Keyword, "while")
		|| CHECK_TYPE_VALUE(token, Keyword, "for")
		|| CHECK_TYPE_VALUE(token, Bracket, "{"))
	{
		first = _parseS();
	}
	else if (CHECK_TYPE(token, Type))
	{
		first = _parseFD();
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseS()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Type))
	{
		first = _parseVD();
		token = _lexer.peek();
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
	}
	else if (CHECK_TYPE(token, Id))
	{
		first = _parseLV();
		second = _parseSLV();
		token = _lexer.peek();
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "if"))
	{
		token = _lexer.nextToken();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
		first = _parseBE();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
		second = _parseS();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		third = _parseSIF();
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "while"))
	{
		token = _lexer.nextToken();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
		first = _parseBE();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
		second = _parseS();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "for"))
	{
		token = _lexer.nextToken();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Type);
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Operator, "=");
		first = _parseRV();
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		second = _parseBE();
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		third = _parseE();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
		second = _parseS();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "{"))
	{
		token = _lexer.nextToken();
		first = _parseS();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
	}
	else if (NOT(
		CHECK_TYPE_VALUE(token, Bracket, "}")
		|| CHECK_TYPE(token, EndToken)))
	{
		exit((int)token->line);
	}
	return nullptr;
}

AstNode* Parser::_parseSIF()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Keyword, "else"))
	{
		token = _lexer.nextToken();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
		first = _parseS();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE_VALUE(token, Bracket, "}")))
	{
		exit((int)token->line);
	}
	return nullptr;
}

AstNode* Parser::_parseSLV()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Operator, "="))
	{
		token = _lexer.nextToken();
		first = _parse_SLV();
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		token = _lexer.nextToken();
		first = _parseCL();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE_VALUE(token, Bracket, "}")))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_SLV()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal)
		|| CHECK_TYPE(token, Id)
		|| CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		first = _parseRV();
	}
	else
	{
		exit((int)token->line);
	}
	return nullptr;
}

AstNode* Parser::_parseVD()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Type))
	{
		token = _lexer.nextToken();
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		first = _parse_VD();
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_VD()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Operator, "="))
	{
		token = _lexer.nextToken();
		first = _parseRV();
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "["))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "]");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Operator, "=");
		second = _parseRV();
	}
	else if (NOT(CHECK_TYPE(token, EndToken)))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseFD()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Type))
	{
		token = _lexer.nextToken();
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
		first = _parseCL();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		second = _parse_FD();
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_FD()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Semicolon))
	{
		token = _lexer.nextToken();
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "{"))
	{
		token = _lexer.nextToken();
		first = _parseS();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
	}

	return nullptr;
}

AstNode* Parser::_parseLV()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Id))
	{
		token = _lexer.nextToken();
		first = _parse_LV();
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_LV()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Bracket, "["))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "]");
	}
	else if (NOT(
		CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE_VALUE(token, Bracket, "(")
		|| CHECK_TYPE_VALUE(token, Operator, "=")))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseRV()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal)
		|| CHECK_TYPE(token, Id)
		|| CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		first = _parseBE();
		second = _parse_RV();
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_RV()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Bracket, "["))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "]");
	}
	else if (NOT(
		CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE_VALUE(token, Bracket, "]")
		|| CHECK_TYPE_VALUE(token, Bracket, "}")))
	{
		exit((int)token->line);
	}
	return nullptr;
}

AstNode* Parser::_parseBE()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal)
		|| CHECK_TYPE(token, Id)
		|| CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		first = _parseBF();
		second = _parse_BE();
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_BE()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Operator, "&&")
		|| CHECK_TYPE_VALUE(token, Operator, "||")
		|| CHECK_TYPE_VALUE(token, Operator, "==")
		|| CHECK_TYPE_VALUE(token, Operator, "!="))
	{
		token = _lexer.nextToken();
		first = _parseBF();
		second = _parse_BE();
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Bracket, ")")
		|| CHECK_TYPE_VALUE(token, Bracket, "[")
		|| CHECK_TYPE_VALUE(token, Bracket, "]")
		|| CHECK_TYPE_VALUE(token, Bracket, "}")))
	{
		exit((int)token->line);
	}
	return nullptr;
}

AstNode* Parser::_parseBF()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal)
		|| CHECK_TYPE(token, Id)
		|| CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		first = _parseE();
	}
	else
	{
		exit((int)token->line);
	}
	return nullptr;
}

AstNode* Parser::_parseE()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal)
		|| CHECK_TYPE(token, Id)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		first = _parseT();
		second = _parse_E();
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_E()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Operator, "+")
		|| CHECK_TYPE_VALUE(token, Operator, "-"))
	{
		token = _lexer.nextToken();
		first = _parseBF();
		second = _parse_BE();
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Operator, "&&")
		|| CHECK_TYPE_VALUE(token, Operator, "||")
		|| CHECK_TYPE_VALUE(token, Operator, "==")
		|| CHECK_TYPE_VALUE(token, Operator, "!=")
		|| CHECK_TYPE_VALUE(token, Bracket, "}")
		|| CHECK_TYPE_VALUE(token, Bracket, ")")
		|| CHECK_TYPE_VALUE(token, Bracket, "[")
		|| CHECK_TYPE_VALUE(token, Bracket, "]")))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseT()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal)
		|| CHECK_TYPE(token, Id)
		|| CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		first = _parseF();
		second = _parse_T();
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_T()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Operator, "*")
		|| CHECK_TYPE_VALUE(token, Operator, "/"))
	{
		token = _lexer.nextToken();
		first = _parseF();
		second = _parse_T();
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Operator, "+")
		|| CHECK_TYPE_VALUE(token, Operator, "-")
		|| CHECK_TYPE_VALUE(token, Operator, "&&")
		|| CHECK_TYPE_VALUE(token, Operator, "||")
		|| CHECK_TYPE_VALUE(token, Operator, "==")
		|| CHECK_TYPE_VALUE(token, Operator, "!=")
		|| CHECK_TYPE_VALUE(token, Bracket, ")")
		|| CHECK_TYPE_VALUE(token, Bracket, "[")
		|| CHECK_TYPE_VALUE(token, Bracket, "]")))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseF()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal))
	{
		token = _lexer.nextToken();
	}
	else if (CHECK_TYPE(token, Id))
	{
		token = _lexer.nextToken();
		first = _parse_F();
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		token = _lexer.nextToken();
		first = _parseE();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_F()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		token = _lexer.nextToken();
		first = _parseCL();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
	}
	else if (NOT(CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE_VALUE(token, Operator, "*")
		|| CHECK_TYPE_VALUE(token, Operator, "/")
		|| CHECK_TYPE_VALUE(token, Operator, "+")
		|| CHECK_TYPE_VALUE(token, Operator, "-")
		|| CHECK_TYPE_VALUE(token, Operator, "&&")
		|| CHECK_TYPE_VALUE(token, Operator, "||")
		|| CHECK_TYPE_VALUE(token, Operator, "==")
		|| CHECK_TYPE_VALUE(token, Operator, "!=")
		|| CHECK_TYPE_VALUE(token, Bracket, ")")
		|| CHECK_TYPE_VALUE(token, Bracket, "[")
		|| CHECK_TYPE_VALUE(token, Bracket, "]")))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseCL()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal)
		|| CHECK_TYPE(token, Id)
		|| CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		first = _parseBE();
		second = _parse_CL();
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE_VALUE(token, Bracket, ")")))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_CL()
{
	AstNode* p = nullptr;
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Comma))
	{
		token = _lexer.nextToken();
		first = _parseBE();
		second = _parse_CL();
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE_VALUE(token, Bracket, ")")))
	{
		exit((int)token->line);
	}

	return nullptr;
}



Parser::Parser(Lexer& lexer)
	:_lexer(lexer)
{
	_ast.root = _parsePR();
}