#ifndef _ENVIRMENT_H_
#define _ENVIRMENT_H_ 0

#ifndef _WIN64
typedef int Index;
#else
typedef long long Index;
#endif

#include <vector>
#include <stdexcept>
#include "SymbolTable.h"

using std::vector;

class Environment
{
private:
	Index _currentEnvirment = -1;
	vector<SymbolTable> _symbolTables;
public:
	Environment();
	Environment(const Environment& envirment);
	void createNewEnvironment();
	void goNextEnvitonment();
	void backPreviouEnvironment();
	bool insert(const char* id, const SymbolTableItem& symbolTableItem);
	bool insert(const string& id, const SymbolTableItem& symbolTableItem);
	SymbolTableItem find(const char* id);
	SymbolTableItem find(const string& id);
	void modify(const char* id, const SymbolTableItem& newSymbolTableItem);
	void modify(const string& id, const SymbolTableItem& newSymbolTableItem);
	bool erase(const char* id);
	bool erase(const string& id);
	void backToTopEnvironment();

};

#endif // !_ENVIRMENT_H_



