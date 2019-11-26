#include "LLTableItem.h"

LLTableItem::LLTableItem()
{
}

LLTableItem::LLTableItem(const LLTableItem& item)
{
	this->_map = item._map;

	for (auto itor = _map.begin(); itor != _map.end(); itor++)
	{
		auto b = itor->second;
	}
}

void LLTableItem::insert(Token* token, const TokenSequence& tokenSequence)
{
	_map.insert(std::pair<Token*, TokenSequence>(token, tokenSequence));
}

void LLTableItem::erase(Token* token)
{
	_map.erase(token);
}

const TokenSequence* LLTableItem::find(Token* token) const
{
	auto itor = _map.find(token);

	if (itor == _map.end())
	{
		return nullptr;
	}

	return &(itor->second);
}

size_t LLTableItem::size()
{
	return _map.size();
}
