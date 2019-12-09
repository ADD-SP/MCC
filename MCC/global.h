#ifndef _GLOBAL_H_
#define _GLOBAL_H_ 0

/*
	这里放一些全局函数的声明
*/

#include <string>

using std::string;
using std::reverse;

// 获取一个临时变量
string g_getVar();

// 获取一个标签
string g_getLabel();


#endif // !_GLOBAL_H_

