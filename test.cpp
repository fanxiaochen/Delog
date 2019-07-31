#include <iostream>
#include "delog.h"

int main()
{
//	std::cout << LOG_STDSTRING("SSSSSS", 3) << std::endl;
//
	std::vector<int> t = {2,3,2,5,62,1,5,34};
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
//	std::unordered_map<int,int> m;
//	std::cout << DELOG(a,1) << std::endl;
//	std::cout << DELOG(12.5f,1) << std::endl;
//	std::cout << DELOG(12.5,1) << std::endl;
//	std::cout << delog::message("test", 23) << std::endl;
//	std::cout << delog::message("test", 23.9f) << std::endl;
//	std::cout << DELOG_ALL(a,1) << std::endl;
//	std::cout << DELOG_ALL(90.3f, 1) << std::endl;
//	std::cout << DELOG_ALL(34.0, 1) << std::endl;
//	std::cout << DELOG_ALL(std::string("ss"), 1) << std::endl;
//	std::cout << DELOG_ALL(t, 1,2,3) << std::endl;
//	std::cout << DELOG_ALL(m, 1) << std::endl;
//	std::cout << delog::message("test", t, 3, 32) << std::endl;

//	delog::basics::Primitive_int_t tt;
//	std::cout << tt.generate("dfsd", 1) << std::endl;
//	std::cout << delog::message("test", 3) << std::endl;
//	std::cout << delog::message("test", std::string("dfdf")) << std::endl;
//
//	delog::stl::ContainerOneParameter_std_vector v;
//	std::cout << v.generate("dfsd", t, 0, 4) << std::endl;
//	auto aa = {3, 2, 2};
//	auto bb = {3, 2, 5};
//	std::cout << delog::message("test", 12) << std::endl;
//	std::cout << delog::message("test", 12, {}) << std::endl;
//	std::cout << delog::message("test", 12, {1,3}) << std::endl;
//	std::cout << delog::message("test", 12, aa) << std::endl;
//
//	int cc = 5;
//	std::cout << DELOG_ALL(cc, {}) << std::endl;
//
//	std::cout << delog::message("vector", t) << std::endl;
//	std::cout << delog::message("vector", t, {}, {1, 3}) << std::endl;
	std::cout << delog::message("vector", t, {3, 6}) << std::endl;

	std::unordered_set<int> set;
	set.insert(898);
	std::cout << delog::message("set", set, {31}, {3}) << std::endl;

	//std::cout << delog::message("test", t, std::tuple(4, 5), std::tuple(2)) << std::endl;
//	std::cout << delog::message("test", t, {1}) << std::endl;


//	std::unordered_set<int> sset;
//	sset.insert(32);
//	std::cout << delog::message("test", sset, 1) << std::endl;
//	std::cout << delog::message("test", sset) << std::endl;
//	std::cout << DELOG_ALL(sset, 1) << std::endl;

	return 0;
}
