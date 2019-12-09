#ifndef _AST_NODE_H_
#define _AST_NODE_H_ 0

/*
	�����﷨���Ľ��
*/

#include <vector>
#include <string>
#include <cstdarg>

using std::vector;
using std::string;

class AstNode
{
private:
	// �洢����ֵ
	vector<string> _values;
	// �洢�ӽڵ�
	vector<AstNode*> _leaves;
public:
	// ����˳��
	size_t order;
	/*
		left�������������
		mid�����������������ʱδ�ã�
		right������������
		eLeft��Express Left����������������ǵ�ǰ�ڵ�ĵ�һ��ֵ�ᱻ����
		eMid��Express Middle������������ȷ��ʵ�һ���ڵ㣬���Ե�ǰ�ڵ�ĵ�һ��ֵ���������ֵ�����ʣ��Ľ��
		eRight��Express Rgiht����������������ǵ�ǰ�ڵ�ĵ�һ��ֵ�ᱻ����
		sIf��Sentence if�������if���ı�����ʽ
		sElse��Sentence else�������else���ı�����ʽ
		sWhile��Sentence while�������while���ı�����ʽ
		sFor��Sentence for�������for���ı�����ʽ
		sVd��Sentence var declare������Ա����������ı�����ʽ
		notGen��ֻ�ᰴ�����������˳������ڵ㣬���Ǻ��Ե�ǰ�ڵ��ȫ��ֵ
	*/
	static const size_t left, mid, right, eLeft, eMid, eRight, sIf, sElse, sWhile, sFor, sVd, notGen;
	AstNode();
	AstNode(size_t counts, ...);
	AstNode(const AstNode& astNode);
	
	// ������˲����ӽڵ�
	void push_left(AstNode* astNode);
	
	// �����Ҷ˲����ӽڵ�
	void push_right(AstNode* astNode);

	// ���ص�ǰ�ڵ��м���value
	size_t valueSize();

	// ���ص�ǰ�ڵ��м����ӽڵ�
	size_t childSize();

	// �����Ҷ˲���һ��value
	void push_back(const string& value);

	// ������˲���һ��value
	void push_front(const string& value);

	// ʹ���±���ʶ�Ӧ��value���±�0Ϊ�����value��
	string operator[](size_t index) const;
	string& operator[](size_t index);

	// ʹ��()���ʶ�Ӧ���ӽڵ㣨�±�0Ϊ������ӽڵ㣩
	AstNode* operator()(size_t index);

};

#endif // !_AST_NODE_H_



