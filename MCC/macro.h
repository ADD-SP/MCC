#ifndef _MACRO_H_
#define _MACRO_H_ 0

/*
	这里放一些常用的宏过程
*/

// 指针的动态类型转换
#define DCAST(pvar, type) (dynamic_cast<type*>(pvar))

// 静态类型转换
#define SCAST(pvar, type) (static_cast<type>(pvar))

// 获取AstNode的某个value
#define GET_VALUE(pvar, index) ((*pvar)[index])

// 获取AstNode的某个子节点
#define GET_LEAF(pvar, index) ((*pvar)(index))

// 检查Token的类型
#define CHECK_TYPE(pvar, type) (pvar->getType() == type::typeName)

// 检查Token的类型和值
#define CHECK_TYPE_VALUE(pvar, type, value) ((pvar->getType() == type::typeName) && (pvar->lexeme == value))

// 试图匹配一个指定类型的Token，如果匹配成功则将读取到的Token存入pvar，且输入指针前进一位，反之则报错
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

// 试图匹配一个指定类型和value的Token，如果匹配成功则将读取到的Token存入pvar，且输入指针前进一位，反之则报错
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

