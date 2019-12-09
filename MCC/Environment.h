#ifndef _ENVIRMENT_H_
#define _ENVIRMENT_H_ 0

/*
	����/��ʶ��������������¼�͹������/��ʶ�����������ڡ�
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

	// ����һ���µı���������
	void createNewEnvironment();

	// ������һ������������
	void goNextEnvitonment();

	// ���˵���һ������������
	void backPreviouEnvironment();

	// ����һ����������ǰ������
	bool insert(const char* id, const SymbolTableItem& symbolTableItem);
	bool insert(const string& id, const SymbolTableItem& symbolTableItem);

	// ���ұ��������ȴӵ�ǰ��������ң����û�ҵ���ص���һ����������˼�����ȥ��ֱ���ҵ������Ѿ����ҹ�����������
	SymbolTableItem find(const char* id);
	SymbolTableItem find(const string& id);

	// �޸ı�����Ϣ��˳��ͬfind
	void modify(const char* id, const SymbolTableItem& newSymbolTableItem);
	void modify(const string& id, const SymbolTableItem& newSymbolTableItem);

	// ɾ��������˳��ͬfind
	bool erase(const char* id);
	bool erase(const string& id);

	// �ص����ⲿ������
	void backToTopEnvironment();

};

#endif // !_ENVIRMENT_H_



