#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
}

SymbolTable::SymbolTable(const SymbolTable& symbolTabel)
	:_map(symbolTabel._map)
{

}

bool SymbolTable::insert(const char* id, const SymbolTableItem& symbolTableItem)
{
	size_t oldSize = _map.size();
	_map.insert(std::pair<string, SymbolTableItem>(id, symbolTableItem));
	return !(oldSize == _map.size());
}

bool SymbolTable::insert(const string& id, const SymbolTableItem& symbolTableItem)
{
	size_t oldSize = _map.size();
	_map.insert(std::pair<string, SymbolTableItem>(id, symbolTableItem));
	return !(oldSize == _map.size());
}

SymbolTableItem SymbolTable::find(const char* id)
{
	auto itor = _map.find(id);
	if (itor != _map.end())
	{
		return SymbolTableItem(itor->second);
	}
	else
	{
		return SymbolTableItem(false);
	}
}

SymbolTableItem SymbolTable::find(const string& id)
{
	auto itor = _map.find(id);
	if (itor != _map.end())
	{
		return SymbolTableItem(itor->second);
	}
	else
	{
		return SymbolTableItem(false);
	}
}

void SymbolTable::modify(const char* id, const SymbolTableItem& newSymbolTableItem)
{
	auto itor = _map.find(id);

	if (itor == _map.end())
	{
		throw std::invalid_argument(id);
	}

	_map.erase(id);
	this->insert(id, newSymbolTableItem);
}

void SymbolTable::modify(const string& id, const SymbolTableItem& newSymbolTableItem)
{
	auto itor = _map.find(id);

	if (itor == _map.end())
	{
		throw std::invalid_argument(id);
	}

	_map.erase(id);
	this->insert(id, newSymbolTableItem);
}

bool SymbolTable::erase(const char* id)
{
	return !(_map.erase(id) == 0);
}

bool SymbolTable::erase(const string& id)
{
	return !(_map.erase(id) == 0);
}

void SymbolTable::clear()
{
	_map.clear();
}
