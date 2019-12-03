#ifndef _AST_NODE_H_
#define _AST_NODE_H_ 0

#include <vector>
#include <string>
#include <cstdarg>

using std::vector;
using std::string;

class AstNode
{
private:
	vector<string> _values;
	vector<AstNode*> _leaves;
public:
	size_t order;
	static const size_t left, mid, right, eLeft, eMid, eRight, sIf, sElse, sWhile, sFor, _vd, notGen;
	AstNode();
	AstNode(size_t counts, ...);
	AstNode(const AstNode& astNode);
	void push_left(AstNode* astNode);
	void push_right(AstNode* astNode);
	size_t valueSize();
	size_t childSize();
	// void insert(AstNode* astNode, size_t index);
	void push_back(const string& value);
	void push_front(const string& value);
	// void insert(void* value, size_t index);
	string operator[](size_t index) const;
	string& operator[](size_t index);
	AstNode* operator()(size_t index);

};

#endif // !_AST_NODE_H_



