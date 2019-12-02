#ifndef _MACRO_H_
#define _MACRO_H_ 0

#define DCAST(pvar, type) (dynamic_cast<type*>(pvar))
#define SCAST(pvar, type) (static_cast<type>(pvar))
#define GET_VALUE(pvar, index) ((*pvar)[index])
#define GET_LEAF(pvar, index) ((*pvar)(index))
#define CHECK_TYPE(pvar, type) (pvar->getType() == type::typeName)
#define CHECK_TYPE_VALUE(pvar, type, value) ((pvar->getType() == type::typeName) && (pvar->lexeme == value))

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

