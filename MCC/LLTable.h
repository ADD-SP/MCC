#ifndef _LLTABLE_H_
#define _LLTABLE_H_ 0

#include "GS.h"
#include "LLTableItem.h"
#include "TokenSequence.h"
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class LLTable
{
private:
	unordered_map<GS, LLTableItem> _map;
public:
	LLTable();
	void insert(const GS& gs, const LLTableItem& item);
	const TokenSequence* find(const GS* gs, Token* token) const;
	void erase(const GS* gs);
	void erase(const GS* gs, Token* token);

};

#endif // !_LLTABLE_H_



