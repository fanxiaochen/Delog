#include <iostream>
#include "delog/delog.h"

void test_basis()
{
	int a = 10;
	DELOG(a);
	DELOG(-100);
	double b = 12.5;
	DELOG(b);
	DELOG('s');
	DELOG("str");
	DELOG(true);
	DELOG(false);
	bool flag = true; // convert into type 'int'
	DELOG(flag);
	unsigned int c = 39;
	DELOG(c);
}

void test_vector()
{
	std::vector<int> vector = {2, 3, 2, 5, 62, 1, 5, 34};
	DELOG(vector);
}

void test_list()
{
	std::list<int> list = {2, 3, 5};
	DELOG(list);
}

void test_deque()
{
	std::deque<int> deque = {1, 2, 3, 5};
	DELOG(deque);
}

void test_set()
{
	std::set<int> set;
	set.insert(88);
	DELOG(set);
}

void test_unordered_set()
{
	std::unordered_set<int> uset;
	uset.insert(78);
	DELOG(uset);
}

void test_map()
{
	std::map<int, int> map;
	map[898] = 233;
	map[98] = 3;
	map[13] = 2;
	map[200] = 38;
	DELOG(map);
}

void test_unordered_map()
{
	std::unordered_map<int, double> umap;
	umap[8] = 23.3;
	umap[18] = 13.3;
	DELOG(umap);
}

void test_array()
{
	std::array<int, 5> array = {1};
	DELOG(array);
}

void test_stack()
{
	std::stack<int> stack;
	stack.push(2);
	DELOG(stack);
}

void test_queue()
{
	std::queue<int> queue;
	queue.push(29);
	DELOG(queue);
}

void test_pair()
{
	std::pair<int, int> pair = {1, 2};
	DELOG(pair);
}

void test_pointers()
{
	int pointer[5] = {3, 2, 56, 6, 8};
	float pf[3] = {5.06f, 16.1f, 8.4f};
	DELOG(pointer, {1, 3});
	DELOG(pf);
}

void test_eigen()
{
	Eigen::Vector3f vec3;
	vec3 << 1, 0, 0;
	DELOG(vec3);
	Eigen::Matrix4d mat4 = Eigen::Matrix4d::Identity();
	DELOG(mat4);
	DELOG(mat4, {0, 0, 3, 1});
	DELOG(mat4, {1, 1, 2, 1});
	//std::cout << vec3 << std::endl;
	std::vector<Eigen::Matrix3f> mat_vec(3, Eigen::Matrix3f::Identity());
	DELOG(mat_vec);
}

void test_opencv()
{
	cv::Vec2f vec2f(1, 5);
	cv::Vec3i vec3i(4, 20, 33);
	DELOG(vec2f);
	DELOG(vec3i, {4, 1});

	float dummy_query_data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	cv::Mat mat_32FC2 = cv::Mat(2, 3, CV_32FC2, dummy_query_data);
	DELOG(mat_32FC2);

	std::vector<cv::Mat> mat_vec(3, mat_32FC2);
	DELOG(mat_vec);
}

int main()
{
	//	std::cout << LOG_STDSTRING("SSSSSS", 3) << std::endl;
	//
	//   delog::get_win_version();
	//	std::vector<int> t = {2,3,2,5,62,1,5,34};
	//	DELOG(t);
	//	std::cout << LOG_STLVECTOR(t, 3, 3, 1) << std::endl;
	//	//delog::mapping(std::string("DFDS"));
	//	int a = 3;
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
	//	START_TIMER(1, MICROSECOND);
	//	int cc = 5;
	//	DELOG(cc, {});
	////
	//    std::cout << delog::message("vector", t) << std::endl;
	//    std::cout << delog::message("vector", t, {3}) << std::endl;
	//	std::cout << delog::message("vector", t, {1}, {1, 3}) << std::endl;
	//	std::cout << delog::message("vector", t, {}, {1, 3}) << std::endl;
	//	std::cout << delog::message("vector", t, {3, 6}) << std::endl;
	//
	//	std::list<int> list = {2,3,5};
	//	std::cout << delog::message("list", list, {3}) << std::endl;
	//
	//	std::deque<int> deque = {2,3,5};
	//	std::cout << delog::message("deque", deque, {3,4}) << std::endl;
	//
	//	std::set<int> set;
	//	set.insert(88);
	//	//std::cout << delog::message("set", set, {}, {}) << std::endl;
	//    std::cout << delog::message("set", set) << std::endl;
	//
	//	std::unordered_set<int> uset;
	//	uset.insert(898);
	//	//std::cout << delog::message("set", set, {}, {}) << std::endl;
	//    std::cout << delog::message("uset", uset) << std::endl;
	//
	//	std::map<int, int> map;
	//	map[898] = 233;
	//	std::cout << delog::message("map", map, {31}, {3}) << std::endl;
	//
	//	std::unordered_map<int, double> umap;
	//	umap[8] = 23.3;
	//	std::cout << delog::message("umap", umap, {31}, {3}) << std::endl;
	//
	//	std::array<int, 5> array = {1};
	//    std::cout << delog::message("array", array) << std::endl;
	//
	//	std::stack<int> stack;
	//	stack.push(2);
	//	std::cout << delog::message("stack", stack, {31}, {3}) << std::endl;
	//
	//	std::queue<int> queue;
	//	queue.push(29);
	//	std::cout << delog::message("queue", queue, {31}, {3}) << std::endl;
	//
	//	std::pair<int, int > pair = {1,2};
	//	std::cout << delog::message("pair", pair, {3}) << std::endl;

	//	std::cout << __LINE__ << std::endl;
	//	std::cout << __FUNCTION__ << std::endl;
	////	std::cout << __PRETTY_FUNCTION__ << std::endl;
	//	std::cout << __func__ << std::endl;
	//	std::cout << __FILE__ << std::endl;
	//	std::cout << delog::basics_info(__FILE__, __LINE__, __func__) << std::endl;
	//	DELOG(pair, {3});
	//    DELOG(pair, {});
	//    DELOG(t);

	//	std::string red("\033[0;31m");
	//	std::string green("\033[0;32m");
	//	std::string reset("\033[0m");
	//	std::cout << red +"red" + reset  << std::endl;
	//	std::cout << green + "red" + reset  << std::endl;
	//	std::cout << "red" << std::endl;
	//	std::cout << delog::Color::red("This is red!") << std::endl;
	//	std::cout << delog::Color::blue("This is red!") << std::endl;
	//	std::cout << delog::Color::cyan("This is red!") << std::endl;
	//	std::cout << delog::Color::yellow("This is red!") << std::endl;
	//	std::cout << delog::Color::green("This is red!") << std::endl;
	//	std::cout << delog::Color::magenta("This is red!") << std::endl;
	//	auto mm = delog::Color::magenta("This is different!");
	//	auto rr = delog::Color::red("This is reddd!");
	//	auto gg = delog::Color::green("This is ggg!");
	//	STOP_TIMER(1);
	//	delog::end_timer(0, __FILE__, __func__, __LINE__);
	//	PAUSE();
	//	std::cout << DEFAULT_COLOR(YELLOW("yeeellooww")+"we are " +mm + gg + "is red!" + rr +"wow") << std::endl;

	//	int ttt = 22;
	//	DELOG(ttt);
	//	std::string testt = (MAGENTA("%s") + "  " + GREEN("%s") + " = " + YELLOW("%d") + "\n");
	//	printf(testt.c_str(), "fff", "sss", 23);
	//
	//    DELOG(3.14);
	//    DELOG(3.14f);
	//    DELOG(4 == 4);
	//    DELOG(4u);
	//    DELOG(4l);
	//    DELOG("FANXIAOCHEN");
	//
	//	int aa[3] = {1,4,6};

	//	DELOG(aa, {1,3});

	//std::cout << delog::message("test", t, std::tuple(4, 5), std::tuple(2)) << std::endl;
	//	std::cout << delog::message("test", t, {1}) << std::endl;

	//	std::unordered_set<int> sset;
	//	sset.insert(32);
	//	std::cout << delog::message("test", sset, 1) << std::endl;
	//	std::cout << delog::message("test", sset) << std::endl;
	//	std::cout << DELOG_ALL(sset, 1) << std::endl;

	//	DELOG(pair);

	//	START_TIMER(0, MILLISECOND);
	test_basis();
	test_vector();
	test_list();
	test_map();
	test_unordered_map();
	//	PAUSE();
	test_set();
	test_unordered_set();
	//	STOP_TIMER(0);
	test_stack();
	test_queue();
	test_deque();
	test_array();
	//	PAUSE();
	test_pair();
	test_pointers();
	test_eigen();
	test_opencv();
	//	STOP_TIMER(0);

	return 0;
}
