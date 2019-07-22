#include <iostream>
#include "delog.h"

int main()
{
	delog::StdString<int> str;
	std::cout << str.build(10) << std::endl;
	return 0;
}
