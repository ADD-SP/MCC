#ifndef _AST_H_
#define _AST_H_ 0

/*
	³éÏóÓï·¨Ê÷
*/

#include "AstNode.h"

class Ast
{
private:
public:
	AstNode* root = nullptr;
	Ast();
	Ast(AstNode* root);
};

#endif // !_AST_H_

