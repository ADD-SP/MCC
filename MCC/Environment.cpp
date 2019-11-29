#include "Environment.h"

Environment::Environment()
{
	createNewEnvironment();
}

Environment::Environment(const Environment& envirment)
	:_currentEnvirment(envirment._currentEnvirment), _symbolTables(envirment._symbolTables)
{
}

void Environment::createNewEnvironment()
{
	++_currentEnvirment;
	_symbolTables.push_back(SymbolTable());
}

void Environment::exitCurrentEnvironment()
{
	if (_currentEnvirment - 1 < 0)
	{
		throw std::out_of_range("environment not exists");
	}
	--_currentEnvirment;
}

void Environment::insert(const char* id, const SymbolTableItem& symbolTableItem)
{
	_symbolTables[_currentEnvirment].insert(id, symbolTableItem);
}

void Environment::insert(const string& id, const SymbolTableItem& symbolTableItem)
{
	_symbolTables[_currentEnvirment].insert(id, symbolTableItem);
}

SymbolTableItem Environment::find(const char* id)
{
	for (Index i = _currentEnvirment; i >= 0; i--)
	{
		SymbolTableItem symbolTableItem = _symbolTables[_currentEnvirment].find(id);

		if (symbolTableItem.isVaild())
		{
			return symbolTableItem;
		}
	}
	return SymbolTableItem(false);
}

SymbolTableItem Environment::find(const string& id)
{
	for (Index i = _currentEnvirment; i >= 0; i--)
	{
		SymbolTableItem symbolTableItem = _symbolTables[_currentEnvirment].find(id);

		if (symbolTableItem.isVaild())
		{
			return symbolTableItem;
		}
	}
	return SymbolTableItem(false);
}

void Environment::modify(const char* id, const SymbolTableItem& newSymbolTableItem)
{
	_symbolTables[_currentEnvirment].modify(id, newSymbolTableItem);
}

void Environment::modify(const string& id, const SymbolTableItem& newSymbolTableItem)
{
	_symbolTables[_currentEnvirment].modify(id, newSymbolTableItem);
}

void Environment::erase(const char* id)
{
	for (Index i = _currentEnvirment; i >= 0; i--)
	{
		SymbolTableItem symbolTableItem = _symbolTables[_currentEnvirment].find(id);

		if (symbolTableItem.isVaild())
		{
			_symbolTables[_currentEnvirment].erase(id);
			break;
		}
	}
}

void Environment::erase(const string& id)
{
	for (Index i = _currentEnvirment; i >= 0; i--)
	{
		SymbolTableItem symbolTableItem = _symbolTables[_currentEnvirment].find(id);

		if (symbolTableItem.isVaild())
		{
			_symbolTables[_currentEnvirment].erase(id);
			break;
		}
	}
}

void Environment::backToTopEnvironment()
{
	_currentEnvirment = 0;
}
