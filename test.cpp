#include <iostream>
#include "delog.h"

int main()
{
	delog::LogStdString<int> str;
	std::cout << str.build("fff", 10) << std::endl;

	delog::LogStlVector<int> vec;
	std::vector<int> t;
	t.push_back(1);
	std::cout << vec.build(t) << std::endl;
	return 0;
}
