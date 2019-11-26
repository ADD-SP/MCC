#include "AstNode.h"

AstNode::AstNode()
{
}

AstNode::AstNode(size_t counts, ...)
{
	va_list args;
	va_start(args, counts);

	void* value = nullptr;

	for (int i = 0; i < counts; i++)
	{
		value = va_arg(args, void*);
		_values.push_back(value);
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

void AstNode::push_back(void* value)
{
	_values.push_back(value);
}

void AstNode::push_front(void* value)
{
	_values.insert(_values.begin(), value);
}

void* AstNode::operator[](size_t index) const
{
	return _leaves[index];
}

void*& AstNode::operator[](size_t index)
{
	return _values[index];
}

AstNode* AstNode::operator()(size_t index)
{
	return _leaves[index];
}
