#include "AstNode.h"

AstNode::AstNode()
{
}

AstNode::AstNode(size_t counts, ...)
{
	va_list args;
	va_start(args, counts);

	for (int i = 0; i < counts; i++)
	{
		_values.push_back(va_arg(args, string));
	}

	va_end(args);
}

void AstNode::push_left(AstNode* astNode)
{
	_leaves.insert(_leaves.begin(), astNode);
}

void AstNode::push_right(AstNode* astNode)
{
	_leaves.push_back(astNode);
}

void AstNode::push_back(const string& value)
{
	_values.push_back(value);
}

void AstNode::push_front(const string& value)
{
	_values.insert(_values.begin(), value);
}

string AstNode::operator[](size_t index) const
{
	return _values[index];
}

string& AstNode::operator[](size_t index)
{
	return _values[index];
}

AstNode* AstNode::operator()(size_t index)
{
	return _leaves[index];
}
