#include "AstNode.h"

const size_t AstNode::eLeft = 0;
const size_t AstNode::eMid = 1;
const size_t AstNode::eRight = 2;
const size_t AstNode::left = 3;
const size_t AstNode::mid = 4;
const size_t AstNode::right = 5;
const size_t AstNode::sIf = 6;
const size_t AstNode::sElse = 7;
const size_t AstNode::sWhile = 8;
const size_t AstNode::sFor = 9;
const size_t AstNode::sVd = 10;
const size_t AstNode::notGen = 11;


AstNode::AstNode()
	:order(eLeft)
{
}

AstNode::AstNode(size_t counts, ...)
	:order(eLeft)
{
	va_list args;
	// 准备获取可变参数
	va_start(args, counts);

	for (int i = 0; i < counts; i++)
	{
		// 插入所有可变参数（value）
		_values.push_back(va_arg(args, string));
	}

	// 结束可变参数的只用
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
