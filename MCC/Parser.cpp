#include "Parser.h"

void Parser::_gen(string str)
{
	cout << str << endl;
}

void Parser::_isDeclare(Id* id)
{
	if (id == nullptr || !(envir.find(id->lexeme).isVaild()))
	{
		exit((int)id->line);
	}
}

void Parser::_pushValue(AstNode* left, AstNode* right, size_t start)
{
	for (size_t i = start; i < right->valueSize(); i++)
	{
		left->push_back(GET_VALUE(right, i));
	}
}

void Parser::_reGenTAC(AstNode* root)
{
	if (!root)
	{
		return;
	}

	if (root->order == AstNode::left)
	{
		for (size_t i = 1; i < root->valueSize(); i++)
		{
			_gen(GET_VALUE(root, i));
		}
		for (size_t i = 0; i < root->childSize(); i++)
		{
			_reGenTAC(GET_LEAF(root, i));
		}
	}
	else if (root->order == AstNode::mid)
	{
		_reGenTAC(GET_LEAF(root, 0));
		for (size_t i = 1; i < root->valueSize(); i++)
		{
			_gen(GET_VALUE(root, i));
		}
		for (size_t i = 1; i < root->childSize(); i++)
		{
			_reGenTAC(GET_LEAF(root, i));
		}
	}
	else if (root->order == AstNode::right)
	{
		for (size_t i = 0; i < root->childSize(); i++)
		{
			_reGenTAC(GET_LEAF(root, i));
		}
		for (size_t i = 1; i < root->valueSize(); i++)
		{
			_gen(GET_VALUE(root, i));
		}
	}
	else
	{
		throw exception();
	}
}

AstNode* Parser::_parsePR()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	while (!CHECK_TYPE(_lexer.peek(), EndToken))
	{
		if (CHECK_TYPE(token, Id)
			|| CHECK_TYPE(token, EndToken)
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
	}

	return nullptr;
}

AstNode* Parser::_parseS()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	while (!CHECK_TYPE(token, EndToken))
	{
		if (CHECK_TYPE(token, Type))
		{
			first = _parseVD();
			p->push_right(first);
			token = _lexer.peek();
			TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		}
		else if (CHECK_TYPE(token, Id))
		{
			first = _parseLV();
			p->push_right(first);
			second = _parseSLV(GET_VALUE(first, 0));
			token = _lexer.peek();
			p->push_right(second);
			TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		}
		else if (CHECK_TYPE_VALUE(token, Keyword, "if"))
		{
			token = _lexer.nextToken();
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
			first = _parseBE();
			p->push_right(first);
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
			envir.createNewEnvironment();
			envir.goNextEnvitonment();
			string labelElse = g_getLabel(), labelEnd = g_getLabel();
			_gen("CNJMP " + GET_VALUE(first, 0) + " " + labelElse);
			second = _parseS();
			p->push_right(second);
			_gen("JMP " + labelEnd);
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
			envir.backPreviouEnvironment();
			_gen(labelElse + ":");
			third = _parseSIF();
			p->push_right(third);
			_gen(labelEnd + ":");
		}
		else if (CHECK_TYPE_VALUE(token, Keyword, "while"))
		{
			token = _lexer.nextToken();
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
			first = _parseBE();
			p->push_right(first);
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
			envir.createNewEnvironment();
			envir.goNextEnvitonment();
			string labelWhile = g_getLabel(), labelEnd = g_getLabel();
			_gen(labelWhile + ":");
			_gen("CNJMP " + GET_VALUE(first, 0) + " " + labelEnd);
			second = _parseS();
			p->push_right(second);
			_reGenTAC(first);
			_gen("JMP " + labelWhile);
			_gen(labelEnd + ":");
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
			envir.backPreviouEnvironment();
		}
		else if (CHECK_TYPE_VALUE(token, Keyword, "for"))
		{
			token = _lexer.nextToken();
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
			TRY_MATCH_TOKEN_TYPE(_lexer, token, Type);
			TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Operator, "=");
			first = _parseRV();
			p->push_right(first);
			TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
			second = _parseBE();
			p->push_right(second);
			TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
			third = _parseE();
			p->push_right(third);
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
			envir.createNewEnvironment();
			envir.goNextEnvitonment();
			fourth = _parseS();
			p->push_right(fourth);
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
			envir.backPreviouEnvironment();
		}
		else if (CHECK_TYPE_VALUE(token, Bracket, "{"))
		{
			envir.createNewEnvironment();
			envir.goNextEnvitonment();
			token = _lexer.nextToken();
			first = _parseS();
			p->push_right(first);
			TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
			envir.backPreviouEnvironment();
		}
		else if (NOT(
			CHECK_TYPE_VALUE(token, Bracket, "}")
			|| CHECK_TYPE(token, EndToken)))
		{
			exit((int)token->line);
		}
		else
		{
			break;
		}
		token = _lexer.peek();
	}
	return nullptr;
}

AstNode* Parser::_parseSIF()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Keyword, "else"))
	{
		token = _lexer.nextToken();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
		envir.createNewEnvironment();
		envir.goNextEnvitonment();
		first = _parseS();
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		envir.backPreviouEnvironment();
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE_VALUE(token, Bracket, "}")))
	{
		exit((int)token->line);
	}
	return nullptr;
}

AstNode* Parser::_parseSLV(const string& id)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var, expr;

	if (CHECK_TYPE_VALUE(token, Operator, "="))
	{
		token = _lexer.nextToken();
		first = _parse_SLV();
		p->push_right(first);
		p->push_back("");
		expr = id + " = " + GET_VALUE(first, 0);
		p->push_back(expr);
		_gen(expr);
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		token = _lexer.nextToken();
		first = _parseCL();
		p->push_right(first);
		p->push_back("");
		expr = id + "(" + GET_VALUE(first, 0) + ")";
		p->push_back(expr);
		_gen(expr);
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
	AstNode* p = new AstNode();
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
		p->push_right(first);
		p->push_back(GET_VALUE(first, 0));
	}
	else
	{
		exit((int)token->line);
	}
	return p;
}

AstNode* Parser::_parseVD()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Type))
	{
		token = _lexer.nextToken();
		Type* type = DCAST(token, Type);
		SymbolTableItem symbolTableItem;
		symbolTableItem.type = *type;
		symbolTableItem.address = g_getVar();
		symbolTableItem.attribute = SymbolTableItem::read | SymbolTableItem::write;
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		symbolTableItem.id = token->lexeme;
		if (!envir.insert(symbolTableItem.id, symbolTableItem))
		{
			exit((int)token->line);
		}
		first = _parse_VD(type, token->lexeme);
		p->push_right(first);
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_VD(Type* type, const string& id)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Operator, "="))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		p->push_right(first);
		_gen(id + " = " + GET_VALUE(first, 0));
		second = _parse_VD(type, "");
		p->push_right(second);
	}
	else if (CHECK_TYPE(token, Comma))
	{
		token = _lexer.nextToken();
		SymbolTableItem symbolTableItem;
		symbolTableItem.type = *type;
		symbolTableItem.address = g_getVar();
		symbolTableItem.attribute = SymbolTableItem::read | SymbolTableItem::write;
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		symbolTableItem.id = token->lexeme;
		if (!envir.insert(symbolTableItem.id, symbolTableItem))
		{
			exit((int)token->line);
		}
		first = _parse_VD(type, token->lexeme);
	}
	else if (NOT(
		CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE_VALUE(token, Bracket, "}")
	))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseFD()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Type))
	{
		token = _lexer.nextToken();
		Type* type = DCAST(token, Type);
		SymbolTableItem symbolTableItem;
		symbolTableItem.type = *type;
		symbolTableItem.address = g_getVar();
		symbolTableItem.attribute = SymbolTableItem::read | SymbolTableItem::write;
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		symbolTableItem.id = token->lexeme;
		envir.insert(symbolTableItem.id, symbolTableItem);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
		first = _parsePL();
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		_gen(symbolTableItem.id + ":");
		second = _parse_FD();
		p->push_right(second);
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_FD()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Semicolon))
	{
		token = _lexer.nextToken();
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "{"))
	{
		envir.createNewEnvironment();
		envir.goNextEnvitonment();
		token = _lexer.nextToken();
		first = _parseS();
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		envir.backPreviouEnvironment();
	}

	return nullptr;
}

AstNode* Parser::_parsePL()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Type))
	{
		token = _lexer.nextToken();
		Type* type = DCAST(token, Type);
		SymbolTableItem symbolTableItem;
		symbolTableItem.type = *type;
		symbolTableItem.address = g_getVar();
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		symbolTableItem.id = token->lexeme;
		first = _parse_PL();
		p->push_right(first);
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE_VALUE(token, Bracket, ")")))
	{

	}

	return nullptr;
}

AstNode* Parser::_parse_PL()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Comma))
	{
		token = _lexer.nextToken();
		first = _parsePL();
		p->push_right(first);
	}
	else if (NOT(
		CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE_VALUE(token, Bracket, ")")))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseLV()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Id))
	{
		token = _lexer.nextToken();
		_isDeclare(DCAST(token, Id));
		first = _parse_LV(token->lexeme);

		if (first)
		{
			p->push_back(GET_VALUE(first, 0));
			p->push_right(first);
		}
		else
		{
			p->push_back(token->lexeme);
		}
	}
	else
	{
		exit((int)token->line);
	}

	return p;
}

AstNode* Parser::_parse_LV(const string& id)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Bracket, "["))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "]");
		p->push_back(id + "[" + GET_VALUE(first, 0) + "]");
		return p;
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
	AstNode* p = new AstNode();
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
		p->push_right(first);
		second = _parse_RV(GET_VALUE(first, 0));

		if (second)
		{
			p->push_back(GET_VALUE(second, 0));
			p->push_right(second);
		}
		else
		{
			p->push_back(GET_VALUE(first, 0));
		}
	}
	else
	{
		exit((int)token->line);
	}

	return p;
}

AstNode* Parser::_parse_RV(const string& id)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE_VALUE(token, Bracket, "["))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "]");
		p->push_back(id + "[" + GET_VALUE(first, 0) + "]");
		return p;
	}
	else if (NOT(
		CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Bracket, "]")
		|| CHECK_TYPE_VALUE(token, Bracket, "}")))
	{
		exit((int)token->line);
	}
	return nullptr;
}

AstNode* Parser::_parseBE()
{
	AstNode* p = new AstNode();
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
		p->push_right(first);
		second = _parse_BE(GET_VALUE(first, 0));

		if (second)
		{
			p->push_back(GET_VALUE(second, 0));
			p->push_right(second);
		}
		else
		{
			p->push_back(GET_VALUE(first, 0));
		}
		return p;
	}
	else
	{
		exit((int)token->line);
	}

	return p;
}

AstNode* Parser::_parse_BE(const string& number)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var, expr;

	if (CHECK_TYPE_VALUE(token, Operator, "&&")
		|| CHECK_TYPE_VALUE(token, Operator, "||")
		|| CHECK_TYPE_VALUE(token, Operator, "==")
		|| CHECK_TYPE_VALUE(token, Operator, "!=")
		|| CHECK_TYPE_VALUE(token, Operator, ">")
			|| CHECK_TYPE_VALUE(token, Operator, "<")
			|| CHECK_TYPE_VALUE(token, Operator, ">=")
			|| CHECK_TYPE_VALUE(token, Operator, "<="))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		first = _parseBF();
		p->push_right(first);
		expr = var + " = " + number + " " + token->lexeme + " " + GET_VALUE(first, 0);
		_gen(expr);
		second = _parse_BE(var);
		p->order = AstNode::mid;

		if (second)
		{
			p->push_back(GET_VALUE(second, 0));
			p->push_back(expr);
			p->push_right(second);
		}
		else
		{
			p->push_back(var);
			p->push_back(expr);
		}
		return p;
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
	AstNode* p = new AstNode();
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
		p->push_right(first);
		p->push_back(GET_VALUE(first, 0));
	}
	else
	{
		exit((int)token->line);
	}
	return p;
}

AstNode* Parser::_parseE()
{
	AstNode* p = new AstNode();
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
		p->push_right(first);
		second = _parse_E(GET_VALUE(first, 0));

		if (second)
		{
			p->push_back(GET_VALUE(second, 0));
			p->push_right(second);
		}
		else
		{
			p->push_back(GET_VALUE(first, 0));
		}
		return p;
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_E(const string& number)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var, expr;

	if (CHECK_TYPE_VALUE(token, Operator, "+")
		|| CHECK_TYPE_VALUE(token, Operator, "-"))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		first = _parseT();
		p->push_right(first);
		expr = var + " = " + number + " " + token->lexeme + " " + GET_VALUE(first, 0);
		_gen(expr);
		second = _parse_E(var);
		p->order = AstNode::mid;

		if (second)
		{
			p->push_back(GET_VALUE(second, 0));
			p->push_back(expr);
			p->push_right(second);
		}
		else
		{
			p->push_back(var);
			p->push_back(expr);
		}

		return p;
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Operator, "&&")
		|| CHECK_TYPE_VALUE(token, Operator, "||")
		|| CHECK_TYPE_VALUE(token, Operator, "==")
		|| CHECK_TYPE_VALUE(token, Operator, "!=")
		|| CHECK_TYPE_VALUE(token, Operator, ">")
		|| CHECK_TYPE_VALUE(token, Operator, ">=")
		|| CHECK_TYPE_VALUE(token, Operator, "<")
		|| CHECK_TYPE_VALUE(token, Operator, "<=")
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
	AstNode* p = new AstNode();
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
		p->push_right(first);
		second = _parse_T(GET_VALUE(first, 0));

		if (second)
		{
			p->push_back(GET_VALUE(second, 0));
			p->push_right(second);
		}
		else
		{
			p->push_back(GET_VALUE(first, 0));
		}
		return p;
	}
	else
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parse_T(const string& number)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var, expr;

	if (CHECK_TYPE_VALUE(token, Operator, "*")
		|| CHECK_TYPE_VALUE(token, Operator, "/"))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		first = _parseF();
		p->push_right(first);
		expr = var + " = " + number + " " + token->lexeme + " " + GET_VALUE(first, 0);
		_gen(expr);
		second = _parse_T(var);
		p->order = AstNode::mid;

		if (second)
		{
			p->push_back(GET_VALUE(second, 0));
			p->push_back(expr);
			p->push_right(second);
		}
		else
		{
			p->push_back(var);
			p->push_back(expr);
		}

		return p;
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
		|| CHECK_TYPE_VALUE(token, Operator, ">")
		|| CHECK_TYPE_VALUE(token, Operator, ">=")
		|| CHECK_TYPE_VALUE(token, Operator, "<")
		|| CHECK_TYPE_VALUE(token, Operator, "<=")
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
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var;

	if (CHECK_TYPE(token, Number)
		|| CHECK_TYPE(token, Interger)
		|| CHECK_TYPE(token, Decimal))
	{
		token = _lexer.nextToken();
		p->push_back(token->lexeme);
	}
	else if (CHECK_TYPE(token, Id))
	{
		token = _lexer.nextToken();
		_isDeclare(DCAST(token, Id));
		first = _parse_F(token->lexeme);

		if (first)
		{
			p->push_back(GET_VALUE(first, 0));
			p->push_right(first);
		}
		else
		{
			p->push_back(token->lexeme);
		}
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

	return p;
}

AstNode* Parser::_parse_F(const string& id)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var, expr;

	if (CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		token = _lexer.nextToken();
		first = _parseCL();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		var = g_getVar();
		expr = var + " = " + id + "(" + GET_VALUE(first, 0) + ")";
		_gen(expr);
		p->order = AstNode::right;
		p->push_back(var);
		p->push_back(expr);
		p->push_right(first);
		return p;
	}
	else if (NOT(CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Operator, "*")
		|| CHECK_TYPE_VALUE(token, Operator, "/")
		|| CHECK_TYPE_VALUE(token, Operator, "+")
		|| CHECK_TYPE_VALUE(token, Operator, "-")
		|| CHECK_TYPE_VALUE(token, Operator, "&&")
		|| CHECK_TYPE_VALUE(token, Operator, "||")
		|| CHECK_TYPE_VALUE(token, Operator, "==")
		|| CHECK_TYPE_VALUE(token, Operator, "!=")
		|| CHECK_TYPE_VALUE(token, Operator, ">")
		|| CHECK_TYPE_VALUE(token, Operator, ">=")
		|| CHECK_TYPE_VALUE(token, Operator, "<")
		|| CHECK_TYPE_VALUE(token, Operator, "<=")
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
	AstNode* p = new AstNode();;
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
		var = GET_VALUE(first, 0);
		second = _parse_CL();
		if (second)
		{
			var += GET_VALUE(second, 0);
		}
		p->push_back(var);
		return p;
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
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr;
	Token* token = _lexer.peek();
	string var = ",";

	if (CHECK_TYPE(token, Comma))
	{
		token = _lexer.nextToken();
		first = _parseBE();
		var += GET_VALUE(first, 0);
		second = _parse_CL();

		if (second)
		{
			var += "," + GET_VALUE(second, 0);
		}
		p->push_back(var);
		return p;
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