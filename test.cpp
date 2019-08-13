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
//	int test = 3;
//	std::cout << delog::GET_VARIABLE_TYPE(test) << std::endl;
//	delog::start_timer(0, __FILE__, __func__, __LINE__);
	START_TIMER(1, MICROSECOND);
	int cc = 5;
	std::cout << DELOG(cc, {}) << std::endl;
////
	std::cout << delog::message("vector", t) << std::endl;
	std::cout << delog::message("vector", t, {1}, {1, 3}) << std::endl;
	std::cout << delog::message("vector", t, {}, {1, 3}) << std::endl;
	std::cout << delog::message("vector", t, {3, 6}) << std::endl;

	std::list<int> list = {2,3,5};
	std::cout << delog::message("list", list, {3}) << std::endl;

	std::deque<int> deque = {2,3,5};
	std::cout << delog::message("deque", deque, {3,4}) << std::endl;

	std::set<int> set;
	set.insert(88);
	//std::cout << delog::message("set", set, {}, {}) << std::endl;
	std::cout << delog::message("set", set) << std::endl;

	std::unordered_set<int> uset;
	uset.insert(898);
	//std::cout << delog::message("set", set, {}, {}) << std::endl;
	std::cout << delog::message("uset", uset) << std::endl;

	std::map<int, int> map;
	map[898] = 233;
	std::cout << delog::message("map", map, {31}, {3}) << std::endl;

	std::unordered_map<int, double> umap;
	map[8] = 23.3;
	std::cout << delog::message("umap", umap, {31}, {3}) << std::endl;

	std::array<int, 5> array = {1};
	std::cout << delog::message("array", array) << std::endl;

	std::stack<int> stack;
	stack.push(2);
	std::cout << delog::message("stack", stack, {31}, {3}) << std::endl;

	std::queue<int> queue;
	queue.push(29);
	std::cout << delog::message("queue", queue, {31}, {3}) << std::endl;

	std::pair<int, int > pair = {1,2};
	std::cout << delog::message("pair", pair, {3}) << std::endl;
	
	std::cout << __LINE__ << std::endl;
	std::cout << __FUNCTION__ << std::endl;
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	std::cout << __func__ << std::endl;
	std::cout << __FILE__ << std::endl;
	std::cout << delog::record_format(__FILE__, __LINE__, __func__) << std::endl;
	std::cout << DELOG(pair, {3}) << std::endl;
	std::cout << DELOG(pair) << std::endl;
	std::cout << DELOG(t) << std::endl;

	std::string red("\033[0;31m");
	std::string green("\033[0;32m");
	std::string reset("\033[0m");
	std::cout << red +"red" + reset  << std::endl;
	std::cout << green + "red" + reset  << std::endl;
	std::cout << "red" << std::endl;
	std::cout << delog::color::red("This is red!") << std::endl;
	std::cout << delog::color::blue("This is red!") << std::endl;
	std::cout << delog::color::cyan("This is red!") << std::endl;
	std::cout << delog::color::yellow("This is red!") << std::endl;
	std::cout << delog::color::green("This is red!") << std::endl;
	std::cout << delog::color::magenta("This is red!") << std::endl;
	auto mm = delog::color::magenta("This is different!");
	auto rr = delog::color::red("This is reddd!");
	auto gg = delog::color::green("This is ggg!");
	STOP_TIMER(1);
//	delog::end_timer(0, __FILE__, __func__, __LINE__);
	PAUSE();
	std::cout << DEFAULT_COLOR(YELLOW("yeeellooww")+"we are " +mm + gg + "is red!" + rr +"wow") << std::endl;

	




	//std::cout << delog::message("test", t, std::tuple(4, 5), std::tuple(2)) << std::endl;
//	std::cout << delog::message("test", t, {1}) << std::endl;


//	std::unordered_set<int> sset;
//	sset.insert(32);
//	std::cout << delog::message("test", sset, 1) << std::endl;
//	std::cout << delog::message("test", sset) << std::endl;
//	std::cout << DELOG_ALL(sset, 1) << std::endl;

	return 0;
}
