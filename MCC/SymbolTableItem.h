#ifndef _SYMBOL_TABLE_ITEM_H_
#define _SYMBOL_TABLE_ITEM_H_ 0

#include <string>
#include "all_token.h"

using std::string;

class SymbolTableItem
{
private:
	const bool _isVaild;
public:
	static const int read, write;
	string id, address, type;
	int attribute;
	SymbolTableItem(bool isVaild);
	SymbolTableItem(const char* id, const char* address, const char* type, int attribute);
	SymbolTableItem(const string& id, const string& address, const string& type, int attribute);
	SymbolTableItem(const SymbolTableItem& symbolTabelItem);
	bool isVaild();
	bool canRead();
	bool canWrite();
};

#endif // !_SYMBOL_TABLE_ITEM_H_

