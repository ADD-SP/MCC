#ifndef _ENVIRMENT_H_
#define _ENVIRMENT_H_ 0

/*
	变量/标识符作用域，用来记录和管理变量/标识符的生命周期。
*/

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

	// 创建一个新的变量作用域
	void createNewEnvironment();

	// 进入下一个变量作用域
	void goNextEnvitonment();

	// 回退到上一个变量作用域
	void backPreviouEnvironment();

	// 插入一个变量到当前作用域
	bool insert(const char* id, const SymbolTableItem& symbolTableItem);
	bool insert(const string& id, const SymbolTableItem& symbolTableItem);

	// 查找变量，优先从当前作用域查找，如果没找到则回到上一层作用域，如此继续下去，直到找到或者已经查找过所有作用域
	SymbolTableItem find(const char* id);
	SymbolTableItem find(const string& id);

	// 修改变量信息，顺序同find
	void modify(const char* id, const SymbolTableItem& newSymbolTableItem);
	void modify(const string& id, const SymbolTableItem& newSymbolTableItem);

	// 删除变量，顺序同find
	bool erase(const char* id);
	bool erase(const string& id);

	// 回到最外部作用域
	void backToTopEnvironment();

};

#endif // !_ENVIRMENT_H_



