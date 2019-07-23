#include <iostream>
#include "delog.h"

int main()
{
	delog::LogStdString<int, float> str;
	std::cout << str.build("fff", 4, 2.2) << std::endl;
	std::cout << LOG_STDSTRING("SSSSSS", 3) << std::endl;

	delog::LogStlVector<int> vec;
	std::vector<int> t;
	t.push_back(1);
	std::cout << vec.build(t) << std::endl;
	return 0;
}
