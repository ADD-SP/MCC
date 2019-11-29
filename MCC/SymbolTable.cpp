#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
}

SymbolTable::SymbolTable(const SymbolTable& symbolTabel)
	:_map(symbolTabel._map)
{

}

void SymbolTable::insert(const char* id, const SymbolTableItem& symbolTableItem)
{
	_map.insert(std::pair<string, SymbolTableItem>(id, symbolTableItem));
}

void SymbolTable::insert(const string& id, const SymbolTableItem& symbolTableItem)
{
	_map.insert(std::pair<string, SymbolTableItem>(id, symbolTableItem));
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
}

void SymbolTable::modify(const string& id, const SymbolTableItem& newSymbolTableItem)
{
	auto itor = _map.find(id);

	if (itor == _map.end())
	{
		throw std::invalid_argument(id);
	}
}

void SymbolTable::erase(const char* id)
{
	_map.erase(id);
}

void SymbolTable::erase(const string& id)
{
	_map.erase(id);
}

void SymbolTable::clear()
{
	_map.clear();
}
