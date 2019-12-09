#ifndef _MACRO_H_
#define _MACRO_H_ 0

/*
	�����һЩ���õĺ����
*/

// ָ��Ķ�̬����ת��
#define DCAST(pvar, type) (dynamic_cast<type*>(pvar))

// ��̬����ת��
#define SCAST(pvar, type) (static_cast<type>(pvar))

// ��ȡAstNode��ĳ��value
#define GET_VALUE(pvar, index) ((*pvar)[index])

// ��ȡAstNode��ĳ���ӽڵ�
#define GET_LEAF(pvar, index) ((*pvar)(index))

// ���Token������
#define CHECK_TYPE(pvar, type) (pvar->getType() == type::typeName)

// ���Token�����ͺ�ֵ
#define CHECK_TYPE_VALUE(pvar, type, value) ((pvar->getType() == type::typeName) && (pvar->lexeme == value))

// ��ͼƥ��һ��ָ�����͵�Token�����ƥ��ɹ��򽫶�ȡ����Token����pvar��������ָ��ǰ��һλ����֮�򱨴�
#define TRY_MATCH_TOKEN_TYPE(lexer, pvar, type) { \
	if (CHECK_TYPE(lexer.peek(), type)) \
	{ \
		pvar = lexer.nextToken(); \
	} \
	else \
	{ \
		exit((int)(lexer.peek()->line)); \
	} \
}

// ��ͼƥ��һ��ָ�����ͺ�value��Token�����ƥ��ɹ��򽫶�ȡ����Token����pvar��������ָ��ǰ��һλ����֮�򱨴�
#define TRY_MATCH_TOKEN_TYPE_VALUE(lexer, pvar, type, value) { \
	if (CHECK_TYPE_VALUE(lexer.peek(), type, value)) \
	{ \
		pvar = lexer.nextToken(); \
	} \
	else \
	{ \
		exit((int)(lexer.peek()->line)); \
	} \
}

#define NOT(var) (!(var))

#endif // !_MACRO_H_

