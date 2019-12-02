#include "AstNode.h"

const size_t AstNode::left = 0;
const size_t AstNode::mid = 1;
const size_t AstNode::right = 2;

AstNode::AstNode()
	:order(left)
{
}

AstNode::AstNode(size_t counts, ...)
	:order(left)
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

size_t AstNode::valueSize()
{
	return _values.size();
}

size_t AstNode::childSize()
{
	return _leaves.size();
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
