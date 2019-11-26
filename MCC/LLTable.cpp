#include "LLTable.h"

LLTable::LLTable()
{
}

void LLTable::insert(const GS& gs, const LLTableItem& item)
{
	_map.insert(std::pair<GS, LLTableItem>(gs, item));
}

const TokenSequence* LLTable::find(const GS* gs, Token* token) const
{
	auto itor = _map.find(*gs);

	if (itor == _map.end())
	{
		return nullptr;
	}

	return itor->second.find(token);

}

void LLTable::erase(const GS* gs, Token* token)
{
	auto itor = _map.find(*gs);

	if (itor != _map.end())
	{
		itor->second.erase(token);
	}
}

void LLTable::erase(const GS* gs)
{
	_map.erase(*gs);
}
