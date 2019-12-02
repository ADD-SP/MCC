#include "SymbolTableItem.h"

const int SymbolTableItem::read = 1;
const int SymbolTableItem::write = 2;

SymbolTableItem::SymbolTableItem()
	:type("", -100),_isVaild(true), attribute(read | write)
{
}

SymbolTableItem::SymbolTableItem(bool isVaild)
	:_isVaild(isVaild), attribute(0), type("", -100)
{
}

SymbolTableItem::SymbolTableItem(const char* id, const char* address, const Type& type, int attribute)
	:id(id),address(address),type(type),attribute(attribute), _isVaild(true)
{
}

SymbolTableItem::SymbolTableItem(const string& id, const string& address, const Type& type, int attribute)
	: id(id), address(address), type(type), attribute(attribute), _isVaild(true)
{
}

SymbolTableItem::SymbolTableItem(const SymbolTableItem& symbolTabelItem)
	:id(symbolTabelItem.id), address(symbolTabelItem.address), type(symbolTabelItem.type), attribute(symbolTabelItem.attribute), _isVaild(symbolTabelItem._isVaild)
{
}

bool SymbolTableItem::isVaild()
{
	return _isVaild;
}

bool SymbolTableItem::canRead()
{
	return (this->attribute & SymbolTableItem::read) != 0;
}

bool SymbolTableItem::canWrite()
{
	return (this->attribute & SymbolTableItem::write) != 0;
}
