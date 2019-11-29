#include "global.h"

string g_getVar()
{
	static size_t num = 0;
	string var;
	size_t temp = ++num;

	while (temp != 0)
	{
		var.push_back((temp % 10) + '0');
		temp /= 10;
	}

	var += "rav";

	reverse(var.begin(), var.end());
	return var;
}

