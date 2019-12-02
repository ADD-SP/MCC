#include "Environment.h"

Environment::Environment()
{
	createNewEnvironment();
	goNextEnvitonment();
}

Environment::Environment(const Environment& envirment)
	:_currentEnvirment(envirment._currentEnvirment), _symbolTables(envirment._symbolTables)
{
}

void Environment::createNewEnvironment()
{
	_symbolTables.push_back(SymbolTable());
}

void Environment::goNextEnvitonment()
{
	if (_currentEnvirment + 1 >= (Index)_symbolTables.size())
	{
		throw std::out_of_range("environment not exists");
	}
	++_currentEnvirment;
}

void Environment::backPreviouEnvironment()
{
	if (_currentEnvirment - 1 < 0)
	{
		throw std::out_of_range("environment not exists");
	}
	--_currentEnvirment;
}

bool Environment::insert(const char* id, const SymbolTableItem& symbolTableItem)
{
	return _symbolTables[_currentEnvirment].insert(id, symbolTableItem);
}

bool Environment::insert(const string& id, const SymbolTableItem& symbolTableItem)
{
	return _symbolTables[_currentEnvirment].insert(id, symbolTableItem);
}

SymbolTableItem Environment::find(const char* id)
{
	for (Index i = _currentEnvirment; i >= 0; i--)
	{
		SymbolTableItem symbolTableItem = _symbolTables[i].find(id);

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
		SymbolTableItem symbolTableItem = _symbolTables[i].find(id);

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

bool Environment::erase(const char* id)
{
	for (Index i = _currentEnvirment; i >= 0; i--)
	{
		SymbolTableItem symbolTableItem = _symbolTables[_currentEnvirment].find(id);

		if (symbolTableItem.isVaild())
		{
			return _symbolTables[_currentEnvirment].erase(id);
			break;
		}
	}
	return false;
}

bool Environment::erase(const string& id)
{
	for (Index i = _currentEnvirment; i >= 0; i--)
	{
		SymbolTableItem symbolTableItem = _symbolTables[_currentEnvirment].find(id);

		if (symbolTableItem.isVaild())
		{
			return _symbolTables[_currentEnvirment].erase(id);
			break;
		}
	}
	return false;
}

void Environment::backToTopEnvironment()
{
	_currentEnvirment = 0;
}
