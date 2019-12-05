#include "Parser.h"

void Parser::_gen(string str)
{
	cout << str << endl;
}

void Parser::_gen(AstNode* root)
{
	if (!root)
	{
		return;
	}

	if (root->order == AstNode::left)
	{
		for (size_t i = 0; i < root->valueSize(); i++)
		{
			_gen(GET_VALUE(root, i));
		}
		for (size_t i = 0; i < root->childSize(); i++)
		{
			_gen(GET_LEAF(root, i));
		}
	}
	else if (root->order == AstNode::mid)
	{
		throw exception();
	}
	else if (root->order == AstNode::right)
	{
		for (size_t i = 0; i < root->childSize(); i++)
		{
			_gen(GET_LEAF(root, i));
		}
		for (size_t i = 0; i < root->valueSize(); i++)
		{
			_gen(GET_VALUE(root, i));
		}
	}
	else if (root->order == AstNode::eLeft)
	{
		for (size_t i = 1; i < root->valueSize(); i++)
		{
			_gen(GET_VALUE(root, i));
		}
		for (size_t i = 0; i < root->childSize(); i++)
		{
			_gen(GET_LEAF(root, i));
		}
	}
	else if (root->order == AstNode::eMid)
	{
		_gen(GET_LEAF(root, 0));
		for (size_t i = 1; i < root->valueSize(); i++)
		{
			_gen(GET_VALUE(root, i));
		}
		for (size_t i = 1; i < root->childSize(); i++)
		{
			_gen(GET_LEAF(root, i));
		}
	}
	else if (root->order == AstNode::eRight)
	{
		for (size_t i = 0; i < root->childSize(); i++)
		{
			_gen(GET_LEAF(root, i));
		}
		for (size_t i = 1; i < root->valueSize(); i++)
		{
			_gen(GET_VALUE(root, i));
		}
	}
	else if (root->order == AstNode::sIf)
	{
		// BE
		_gen(GET_LEAF(root, 0));
		// CNJMP
		_gen(GET_VALUE(root, 0));
		// S
		for (size_t i = 1; i < root->childSize() - 1; i++)
		{
			_gen(GET_LEAF(root, i));
		}
		// JMP
		_gen(GET_VALUE(root, 1));
		// labelElse
		_gen(GET_VALUE(root, 2));
		// SIF
		_gen(GET_LEAF(root, root->childSize() - 1));
		// labelEnd
		_gen(GET_VALUE(root, 3));
	}
	else if (root->order == AstNode::sWhile)
	{
		// labelBool
		_gen(GET_VALUE(root, 0));
		// BE
		_gen(GET_LEAF(root, 0));
		// labelWhile
		// _gen(GET_VALUE(root, 1));
		// CNJMP
		_gen(GET_VALUE(root, 2));
		// S
		for (size_t i = 1; i < root->childSize(); i++)
		{
			_gen(GET_LEAF(root, i));
		}
		// JMP
		_gen(GET_VALUE(root, 3));
		// labelEnd
		_gen(GET_VALUE(root, 4));
	}
	else if (root->order == AstNode::sFor)
	{
		// LV
		_gen(GET_LEAF(root, 0));
		// id = 
		_gen(GET_VALUE(root, 0));
		// labelBool
		_gen(GET_VALUE(root, 1));
		// BE
		_gen(GET_LEAF(root, 1));
		// CNJMP
		_gen(GET_VALUE(root, 2));
		// labelFor
		// _gen(GET_VALUE(root, 3));
		// S
		for (size_t i = 3; i < root->childSize(); i++)
		{
			_gen(GET_LEAF(root, i));
		}
		// LV
		_gen(GET_LEAF(root, 2));
		// JMP
		_gen(GET_VALUE(root, 4));
		// labelEnd
		_gen(GET_VALUE(root, 5));
	}
	else if (root->order == AstNode::_vd)
	{
		// RV
		// _gen(GET_LEAF(root, 0));
		// id = 
		_gen(GET_VALUE(root, 0));
		// _vd
		_gen(GET_LEAF(root, 1));
	}
	else if (root->order == AstNode::notGen)
	{
		for (size_t i = 0; i < root->childSize(); i++)
		{
			_gen(GET_LEAF(root, i));
		}
	}
	else
	{
		throw exception();
	}
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
			_gen(first);
		}
		else if (CHECK_TYPE(token, Type))
		{
			first = _parseFD();
			_gen(first);
		}
		else
		{
			exit((int)token->line);
		}
	}

	return nullptr;
}

AstNode* Parser::_parseFE()
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr, * fifth = nullptr;
	Token* token = _lexer.peek();
	bool flag = false;
	string var, expr;

	if (CHECK_TYPE(token, Id))
	{
		token = _lexer.nextToken();
		first = _parse_FE(token->lexeme);
		p->push_right(first);
	}
	else if (CHECK_TYPE_VALUE(token, Operator, "++"))
	{
		token = _lexer.nextToken();
		first = _parse_FE(token->lexeme);
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		// p->push_right(first);
		var = g_getVar();

		if (first)
		{
			expr = var + " = " + GET_VALUE(first, 0) + " + 1";
			p->push_back(var);
			p->push_back(expr);
			p->push_right(first);
		}
		else
		{
			expr = var + " = " + token->lexeme + " + 1";
			p->push_back(var);
			p->push_back(expr);
		}
		p->order = AstNode::eRight;
	}
	else if (CHECK_TYPE_VALUE(token, Operator, "--"))
	{
		token = _lexer.nextToken();
		first = _parse_FE(token->lexeme);
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		// p->push_right(first);
		var = g_getVar();

		if (first)
		{
			expr = var + " = " + GET_VALUE(first, 0) + " - 1";
			p->push_back(var);
			p->push_back(expr);
			p->push_right(first);
		}
		else
		{
			expr = var + " = " + token->lexeme + " - 1";
			p->push_back(var);
			p->push_back(expr);
		}
		p->order = AstNode::eRight;
	}

	return p;
}

AstNode* Parser::_parse_FE(const string& id)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr, * fifth = nullptr;
	Token* token = _lexer.peek();
	bool flag = false;
	string var, var1, expr;

	if (CHECK_TYPE_VALUE(token, Operator, "="))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		p->push_right(first);
		expr = id + " = " + GET_VALUE(first, 0);
		p->push_back(expr);
		p->order = AstNode::right;
		// _gen(expr);
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Operator, "++"))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		var1 = g_getVar();
		p->push_back(var);
		p->push_back(var +" = " + id);
		p->push_back(var1 + " = " + id + " + 1");
		p->push_back(id + " = " + var1);
		p->order = AstNode::eRight;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Operator, "--"))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		var1 = g_getVar();
		p->push_back(var);
		p->push_back(var +" = " + id);
		p->push_back(var1 + " = " + id + " - 1");
		p->push_back(id + " = " + var1);
		p->order = AstNode::eRight;
		return p;
	}
	else if (NOT(CHECK_TYPE(token, EndToken)))
	{
		exit((int)token->line);
	}

	return nullptr;
}

AstNode* Parser::_parseS(bool canGen)
{
	AstNode* p = new AstNode();
	AstNode* first = nullptr, * second = nullptr, * third = nullptr, * fourth = nullptr, * fifth = nullptr;
	Token* token = _lexer.peek();
	bool flag = false;
	string var;
	if (CHECK_TYPE(token, Type))
	{
		first = _parseVD();
		p->push_right(first);
		token = _lexer.peek();
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		p->order = AstNode::notGen;
		return p;
	}
	else if (CHECK_TYPE(token, Id))
	{
		first = _parseLV();
		p->push_right(first);
		second = _parseSLV(GET_VALUE(first, 0));
		token = _lexer.peek();
		p->push_right(second);
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		p->order = AstNode::notGen;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "return"))
	{
		token = _lexer.nextToken();
		token = _lexer.peek();
		if (CHECK_TYPE(token, Number)
			|| CHECK_TYPE(token, Decimal)
			|| CHECK_TYPE(token, Interger)
			|| CHECK_TYPE(token, Id)
			|| CHECK_TYPE_VALUE(token, Bracket, "("))
		{
			first = _parseRV();
			p->push_back("RET " + GET_VALUE(first, 0));
		}
		else if (CHECK_TYPE_VALUE(token, Keyword, "true")
			|| CHECK_TYPE_VALUE(token, Keyword, "false"))
		{
			token = _lexer.nextToken();
			p->push_back("RET " + token->lexeme);
		}
		else
		{
			p->push_back("RET");
		}
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		p->order = AstNode::right;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "break"))
	{
		token = _lexer.nextToken();
		// _gen("JMP " + _loopEndLabel.top());
		p->push_back("JMP " + _loopEndLabel.top());
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		p->order = AstNode::left;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "continue"))
	{
		token = _lexer.nextToken();
		// _gen("JMP " + _loopBoolLabel.top());
		p->push_back("JMP " + _loopBoolLabel.top());
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		p->order = AstNode::left;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "if"))
	{
		token = _lexer.nextToken();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
		first = _parseBE();
		// _gen(first);
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
		envir.createNewEnvironment();
		envir.goNextEnvitonment();
		string labelElse = g_getLabel(), labelEnd = g_getLabel();
		// _gen("CNJMP " + GET_VALUE(first, 0) + " " + labelElse);
		p->push_back("CNJMP " + GET_VALUE(first, 0) + " " + labelElse);
		second = _parseS();
		while (second)
		{
			p->push_right(second);
			second = _parseS();
		}
		// _gen(second);
		// _gen("JMP " + labelEnd);
		p->push_back("JMP " + labelEnd);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		envir.backPreviouEnvironment();
		// _gen(labelElse + ":");
		p->push_back(labelElse + ":");
		third = _parseSIF();
		p->push_right(third);
		// _gen(labelEnd + ":");
		p->push_back(labelEnd + ":");
		p->order = AstNode::sIf;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "while"))
	{
		token = _lexer.nextToken();
		string labelBool = g_getLabel(), labelWhile = g_getLabel(), labelEnd = g_getLabel();
		_loopEndLabel.push(labelEnd);
		_loopBoolLabel.push(labelBool);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
		first = _parseBE();
		// _gen(labelBool + ":");
		p->push_back(labelBool + ":");
		// _gen(first);
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
		envir.createNewEnvironment();
		envir.goNextEnvitonment();

		// _gen(labelWhile + ":");
		p->push_back(labelWhile + ":");
		// _gen("CNJMP " + GET_VALUE(first, 0) + " " + labelEnd);
		p->push_back("CNJMP " + GET_VALUE(first, 0) + " " + labelEnd);
		second = _parseS();
		while (second)
		{
			p->push_right(second);
			second = _parseS();
		}
		// _gen(second);
		p->push_right(second);
		// _gen("JMP " + labelBool);
		p->push_back("JMP " + labelBool);
		//_gen(labelEnd + ":");
		p->push_back(labelEnd + ":");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		_loopEndLabel.pop();
		_loopBoolLabel.pop();
		envir.backPreviouEnvironment();
		p->order = AstNode::sWhile;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Keyword, "for"))
	{
		token = _lexer.nextToken();
		envir.createNewEnvironment();
		envir.goNextEnvitonment();
		string labelBool = g_getLabel(), labelFor = g_getLabel(), labelEnd = g_getLabel();
		_loopEndLabel.push(labelEnd);
		_loopBoolLabel.push(labelBool);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "(");
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Type);
		Type* type = DCAST(token, Type);
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Id);
		string id = token->lexeme;
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Operator, "=");
		first = _parseRV();
		// _gen(first);
		envir.insert(id, SymbolTableItem(id, g_getVar(), *type, SymbolTableItem::read | SymbolTableItem::write));
		// _gen(id + " = " + GET_VALUE(first, 0));
		p->push_back(id + " = " + GET_VALUE(first, 0));
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		second = _parseBE();
		// _gen(labelBool + ":");
		p->push_back(labelBool + ":");
		// _gen(second);
		// _gen("CNJMP " + GET_VALUE(second, 0) + " " + labelEnd);
		p->push_back("CNJMP " + GET_VALUE(second, 0) + " " + labelEnd);
		p->push_right(second);
		TRY_MATCH_TOKEN_TYPE(_lexer, token, Semicolon);
		// third = _parseLV();
		// fourth = _parseSLV(GET_VALUE(third, 0));
		third = _parseFE();
		p->push_right(third);
		// p->push_right(fourth);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "{");
		// _gen(labelFor + ":");
		p->push_back(labelFor + ":");
		fourth = _parseS();
		while (fourth)
		{
			p->push_right(fourth);
			fourth = _parseS();
		}
		// _gen(fourth);
		// _gen(third);
		// _gen("JMP " + labelBool);
		p->push_back("JMP " + labelBool);
		// _gen(labelEnd + ":");
		p->push_back(labelEnd + ":");
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		_loopEndLabel.pop();
		_loopBoolLabel.pop();
		envir.backPreviouEnvironment();
		p->order = AstNode::sFor;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "{"))
	{
		envir.createNewEnvironment();
		envir.goNextEnvitonment();
		token = _lexer.nextToken();
		first = _parseS();
		_gen(first);
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		envir.backPreviouEnvironment();
		p->order = AstNode::notGen;
		return p;
	}
	else if (NOT(CHECK_TYPE_VALUE(token, Bracket, "}") || CHECK_TYPE(token, EndToken)))
	{
		exit((int)token->line);
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
		while (first)
		{
			p->push_right(first);
			first = _parseS();
		}
		// _gen(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		envir.backPreviouEnvironment();
		p->order = AstNode::notGen;
		return p;
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
		// p->push_back("");
		expr = id + " = " + GET_VALUE(first, 0);
		p->push_back(expr);
		p->order = AstNode::right;
		// _gen(expr);
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		token = _lexer.nextToken();
		first = _parseCL();
		p->push_right(first);
		// p->push_back("");
		expr = id + "(" + GET_VALUE(first, 0) + ")";
		p->push_back(expr);
		p->order = AstNode::right;
		// _gen(expr);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		return p;
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
		p->order = AstNode::notGen;
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
		p->order = AstNode::notGen;
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
		// _gen(id + " = " + GET_VALUE(first, 0));
		p->push_back(id + " = " + GET_VALUE(first, 0));
		second = _parse_VD(type, "");
		p->push_right(second);
		p->order = AstNode::_vd;
		return p;
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
		p->push_right(first);
		p->order = AstNode::notGen;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "["))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "]");
		second = _parse_VD(type, id + "[" + GET_VALUE(first, 0) + "]");
		p->push_right(second);
		p->order = AstNode::left;
		p->order = AstNode::notGen;
		return p;
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
		envir.createNewEnvironment();
		envir.goNextEnvitonment();
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

	return p;
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
		token = _lexer.nextToken();
		first = _parseS();
		while (first)
		{
			p->push_right(first);
			first = _parseS();
		}
		
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "}");
		envir.backPreviouEnvironment();
	}

	return p;
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
		envir.insert(symbolTableItem.id, symbolTableItem);
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
		p->order = AstNode::notGen;
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
		p->order = AstNode::notGen;
		return p;
	}
	else if (NOT(
		CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE_VALUE(token, Operator, "++")
		|| CHECK_TYPE_VALUE(token, Operator, "--")
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
	string var, expr;

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
		p->order = AstNode::notGen;
	}
	else if (CHECK_TYPE_VALUE(token, Operator, "++"))
	{
		first = _parseLV();
		p->push_right(first);
		second = _parse_RV(GET_VALUE(first, 0));
		var = g_getVar();

		if (second)
		{
			expr = var + " = " + GET_VALUE(second, 0) + " + 1";
			p->push_back(var);
			p->push_back(expr);
			p->push_right(second);
		}
		else
		{
			expr = var + " = " + GET_VALUE(first, 0) + " + 1";
			p->push_back(var);
			p->push_back(expr);
		}
		p->order = AstNode::eRight;
	}
	else if (CHECK_TYPE_VALUE(token, Operator, "--"))
	{
		first = _parseLV();
		p->push_right(first);
		second = _parse_RV(GET_VALUE(first, 0));
		var = g_getVar();

		if (second)
		{
			expr = var + " = " + GET_VALUE(second, 0) + " - 1";
			p->push_back(var);
			p->push_back(expr);
			p->push_right(second);
		}
		else
		{
			expr = var + " = " + GET_VALUE(first, 0) + " - 1";
			p->push_back(var);
			p->push_back(expr);
		}
		p->order = AstNode::eRight;
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
	string var, var1;

	if (CHECK_TYPE_VALUE(token, Bracket, "["))
	{
		token = _lexer.nextToken();
		first = _parseRV();
		p->push_right(first);
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, "]");
		p->push_back(id + "[" + GET_VALUE(first, 0) + "]");
		p->order = AstNode::notGen;
		return p;
	}
	else if(CHECK_TYPE_VALUE(token, Operator, "++"))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		var1 = g_getVar();
		p->push_back(var);
		p->push_back(var + " = " + id);
		p->push_back(var1 + " = " + id + " + 1");
		p->push_back(id + " = " + var1);
		p->order = AstNode::eRight;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Operator, "--"))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		var1 = g_getVar();
		p->push_back(var);
		p->push_back(var + " = " + id);
		p->push_back(var1 + " = " + id + " - 1");
		p->push_back(id + " = " + var1);
		p->order = AstNode::eRight;
		return p;
	}
	else if (NOT(
		CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Bracket, ")")
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
	string var, expr;

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
		p->order = AstNode::notGen;
		return p;
	}
	else if (CHECK_TYPE_VALUE(token, Operator, "!"))
	{
		token = _lexer.nextToken();
		first = _parseBF();
		p->push_right(first);
		second = _parse_BE(GET_VALUE(first, 0));
		var = g_getVar();
		if (second)
		{
			expr = var + " = !" + GET_VALUE(second, 0);
			p->push_back(var);
			p->push_back(expr);
			p->push_right(second);
		}
		else
		{
			expr = var + " = !" + GET_VALUE(first, 0);
			p->push_back(var);
			p->push_back(expr);
		}
		p->order = AstNode::eRight;
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
		// _gen(expr);
		second = _parse_BE(var);
		p->order = AstNode::eMid;

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
		|| CHECK_TYPE_VALUE(token, Operator, "++")
		|| CHECK_TYPE_VALUE(token, Operator, "--")
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
		p->order = AstNode::notGen;
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
		p->order = AstNode::notGen;
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
		// _gen(expr);
		second = _parse_E(var);
		p->order = AstNode::eMid;

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
		|| CHECK_TYPE_VALUE(token, Operator, "++")
		|| CHECK_TYPE_VALUE(token, Operator, "--")
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
		p->order = AstNode::notGen;
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
		|| CHECK_TYPE_VALUE(token, Operator, "/")
		|| CHECK_TYPE_VALUE(token, Operator, "%"))
	{
		token = _lexer.nextToken();
		var = g_getVar();
		first = _parseF();
		p->push_right(first);
		expr = var + " = " + number + " " + token->lexeme + " " + GET_VALUE(first, 0);
		// _gen(expr);
		second = _parse_T(var);
		p->order = AstNode::eMid;

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
		p->order = AstNode::eMid;
		return p;
	}
	else if (NOT(
		CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Operator, "+")
		|| CHECK_TYPE_VALUE(token, Operator, "-")
		|| CHECK_TYPE_VALUE(token, Operator, "++")
		|| CHECK_TYPE_VALUE(token, Operator, "--")
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
		p->order = AstNode::notGen;
	}
	else if (CHECK_TYPE_VALUE(token, Bracket, "("))
	{
		token = _lexer.nextToken();
		first = _parseE();
		TRY_MATCH_TOKEN_TYPE_VALUE(_lexer, token, Bracket, ")");
		p->order = AstNode::notGen;
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
		// _gen(expr);
		p->order = AstNode::eRight;
		p->push_back(var);
		p->push_back(expr);
		p->push_right(first);
		p->order = AstNode::eLeft;
		return p;
	}
	else if (NOT(CHECK_TYPE(token, EndToken)
		|| CHECK_TYPE(token, Semicolon)
		|| CHECK_TYPE(token, Comma)
		|| CHECK_TYPE_VALUE(token, Operator, "*")
		|| CHECK_TYPE_VALUE(token, Operator, "/")
		|| CHECK_TYPE_VALUE(token, Operator, "%")
		|| CHECK_TYPE_VALUE(token, Operator, "+")
		|| CHECK_TYPE_VALUE(token, Operator, "-")
		|| CHECK_TYPE_VALUE(token, Operator, "++")
		|| CHECK_TYPE_VALUE(token, Operator, "--")
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
		first = _parseRV();
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