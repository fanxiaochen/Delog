#include <iostream>
#include "delog.h"

int main()
{
//	std::cout << LOG_STDSTRING("SSSSSS", 3) << std::endl;
//
	std::vector<int> t;
	t.push_back(1);
//	std::cout << LOG_STLVECTOR(t, 3, 3, 1) << std::endl;
//	//delog::mapping(std::string("DFDS"));
	int a = 3;
//	char c = 's';
//	std::cout << typeid(int).name() << std::endl;
//	std::cout << typeid(a).name() << std::endl;
//	std::cout << typeid(9).name() << std::endl;
//	std::cout << DELOG(12) << std::endl;
//	std::cout << DELOG(a, 2) << std::endl;
//	std::cout << DELOG('c') << std::endl;
//	std::cout << DELOG(c) << std::endl;
//	std::cout << DELOG(0.4) << std::endl;
//	std::cout << DELOG(std::string("dfdfdf"), 3) << std::endl;
//	std::cout << DELOG("dfdfdf", 34,1) << std::endl;
//	std::cout << DELOG_STL(t, 34,1) << std::endl;

//	delog::addRegistry(1, delog::LogType::TYPE_BASICS);
//	std::cout << delog::logging(a) << std::endl;

//	int a = 10;

//	DELOG_ALL(a,1);
	std::unordered_map<int,int> m;
	std::cout << DELOG(a,1) << std::endl;
	std::cout << DELOG(12.5f,1) << std::endl;
	std::cout << DELOG(12.5,1) << std::endl;
	std::cout << delog::message("test", 23) << std::endl;
	std::cout << delog::message("test", 23.9f) << std::endl;
	std::cout << DELOG_ALL(a, 1) << std::endl;
	std::cout << DELOG_ALL(90.3f, 1) << std::endl;
	std::cout << DELOG_ALL(34.0, 1) << std::endl;
	std::cout << DELOG_ALL(std::string("ss"), 1) << std::endl;
	std::cout << DELOG_ALL(t, 1) << std::endl;
	std::cout << DELOG_ALL(m, 1) << std::endl;
	return 0;
}
