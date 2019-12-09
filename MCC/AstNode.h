#ifndef _AST_NODE_H_
#define _AST_NODE_H_ 0

/*
	抽象语法树的结点
*/

#include <vector>
#include <string>
#include <cstdarg>

using std::vector;
using std::string;

class AstNode
{
private:
	// 存储结点的值
	vector<string> _values;
	// 存储子节点
	vector<AstNode*> _leaves;
public:
	// 遍历顺序
	size_t order;
	/*
		left：常规先序遍历
		mid：常规中序遍历（暂时未用）
		right：常规后序遍历
		eLeft（Express Left）：先序遍历，但是当前节点的第一个值会被忽略
		eMid（Express Middle：中序遍历，先访问第一个节点，忽略当前节点的第一个值，输出其他值后访问剩余的结点
		eRight（Express Rgiht）：后序遍历，但是当前节点的第一个值会被忽略
		sIf（Sentence if）：针对if语句的遍历方式
		sElse（Sentence else）：针对else语句的遍历方式
		sWhile（Sentence while）：针对while语句的遍历方式
		sFor（Sentence for）：针对for语句的遍历方式
		sVd（Sentence var declare）：针对变量声明语句的遍历方式
		notGen：只会按照先序遍历的顺序遍历节点，但是忽略当前节点的全部值
	*/
	static const size_t left, mid, right, eLeft, eMid, eRight, sIf, sElse, sWhile, sFor, sVd, notGen;
	AstNode();
	AstNode(size_t counts, ...);
	AstNode(const AstNode& astNode);
	
	// 在最左端插入子节点
	void push_left(AstNode* astNode);
	
	// 在最右端插入子节点
	void push_right(AstNode* astNode);

	// 返回当前节点有几个value
	size_t valueSize();

	// 返回当前节点有几个子节点
	size_t childSize();

	// 在最右端插入一个value
	void push_back(const string& value);

	// 在最左端插入一个value
	void push_front(const string& value);

	// 使用下标访问对应的value（下标0为最左端value）
	string operator[](size_t index) const;
	string& operator[](size_t index);

	// 使用()访问对应的子节点（下标0为最左端子节点）
	AstNode* operator()(size_t index);

};

#endif // !_AST_NODE_H_



