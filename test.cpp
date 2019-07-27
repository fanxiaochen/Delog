#include <iostream>
#include "delog.h"

int main()
{
	std::cout << LOG_STDSTRING("SSSSSS", 3) << std::endl;

	std::vector<int> t;
	t.push_back(1);
	std::cout << LOG_STLVECTOR(t, 3, 3, 1) << std::endl;
	//delog::mapping(std::string("DFDS"));
	int a = 3;
	std::cout << typeid(int).name() << std::endl;
	std::cout << typeid(a).name() << std::endl;
	std::cout << typeid(9).name() << std::endl;
	std::cout << DELOG(12, 34) << std::endl;
	return 0;
}
