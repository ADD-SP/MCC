#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_ 0

#include <unordered_map>
#include <stdexcept>
#include "SymbolTableItem.h"

using std::unordered_map;

class SymbolTable
{
private:
	unordered_map<string, SymbolTableItem> _map;
public:
	SymbolTable();
	SymbolTable(const SymbolTable& symbolTabel);
	bool insert(const char* id, const SymbolTableItem& symbolTableItem);
	bool insert(const string& id, const SymbolTableItem& symbolTableItem);
	SymbolTableItem find(const char* id);
	SymbolTableItem find(const string& id);
	void modify(const char* id, const SymbolTableItem& newSymbolTableItem);
	void modify(const string& id, const SymbolTableItem& newSymbolTableItem);
	bool erase(const char* id);
	bool erase(const string& id);
	void clear();
};

#endif // !_SYMBOL_TABLE_H_



