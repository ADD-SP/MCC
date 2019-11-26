#ifndef _AST_NODE_H_
#define _AST_NODE_H_ 0

#include <vector>
#include <cstdarg>

using std::vector;

class AstNode
{
private:
	vector<void*> _values;
	vector<AstNode*> _leaves;
public:
	AstNode();
	AstNode(size_t counts, ...);
	AstNode(const AstNode& astNode);
	void push_left(AstNode* astNode);
	void push_right(AstNode* astNode);
	// void insert(AstNode* astNode, size_t index);
	void push_back(void* value);
	void push_front(void* value);
	// void insert(void* value, size_t index);
	void* operator[](size_t index) const;
	void*& operator[](size_t index);
	AstNode* operator()(size_t index);

};

#endif // !_AST_NODE_H_



