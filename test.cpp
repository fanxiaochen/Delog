#include <iostream>
#include "delog.h"

int main()
{
	std::cout << LOG_STDSTRING("SSSSSS", 3) << std::endl;

	std::vector<int> t;
	t.push_back(1);
	std::cout << LOG_STLVECTOR(t, 3, 3, 1) << std::endl;
	return 0;
}
