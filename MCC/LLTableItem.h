#ifndef _LLATABLE_ITEM_H_
#define _LLATABLE_ITEM_H_ 0

#include <vector>
#include <unordered_map>
#include "TokenSequence.h"
#include "Token.h"

using std::vector;
using std::unordered_map;

class LLTableItem
{
private:
	unordered_map <Token*, TokenSequence> _map;
public:
	LLTableItem();
	LLTableItem(const LLTableItem& item);
	void insert(Token* token, const TokenSequence& tokenSequence);
	void erase(Token* token);
	const TokenSequence* find(Token* token) const;
	size_t size();
};

#endif

