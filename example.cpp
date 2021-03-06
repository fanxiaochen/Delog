#include <iostream>
#include "delog/delog.h"

void test_basis()
{
    int a = -10;
    unsigned int b = 233;
    long c = -2342;
    unsigned long d = 42;
    short e = -67;
    unsigned short f = 55;
    char g = 'y';
    unsigned char h = 'n';
    float i = 23.4f;
    double j = 563.9;
    std::string k("hello");

    DELOG(a);
    DELOG(b);
    DELOG(c);
    DELOG(d);
    DELOG(e);
    DELOG(f);
    DELOG(g);
    DELOG(i);
    DELOG(j);
    DELOG(k);

    // directly print unnamed variables
    DELOG("str");
    DELOG(10.1f);
    DELOG(99);
    DELOG(false); // convert into type 'int'
}

void test_vector()
{
    std::vector<int> vector = {2, 3, 2, 5, 62, 1, 5, 34};
    DELOG(vector);

    // Usage: DELOG(vector, {start_idx, end_idx}, {parameters for type in container})
    DELOG(vector, {2, 5});
}

void test_list()
{
    std::list<int> list = {2, 3, 5};
    DELOG(list);

    // Usage: DELOG(list, {front n elements}, {parameters for type in container})
    DELOG(list, {2});
}

void test_deque()
{
    std::deque<int> deque = {1, 2, 3, 5};
    DELOG(deque);

    // Usage: DELOG(deque, {start_idx, end_idx}, {parameters for type in container})
    DELOG(deque, {1, 3});
}

void test_set()
{
    std::set<int> set;
    set.insert(88);
    DELOG(set);

    // Usage: DELOG(set, {front n elements}, {parameters for type in container})
    DELOG(set, {1});
}

void test_unordered_set()
{
    std::unordered_set<int> uset;
    uset.insert(78);
    uset.insert(8);
    DELOG(uset);

    // Usage: DELOG(uset, {front n elements}, {parameters for type in container})
    DELOG(uset, {1});
}

void test_map()
{
    std::map<int, int> map;
    map[898] = 233;
    map[98] = 3;
    map[13] = 2;
    map[200] = 38;
    DELOG(map);

    // Usage: DELOG(map, {front n elements}, {parameters for type in container})
    DELOG(map, {3});
}

void test_unordered_map()
{
    std::unordered_map<int, double> umap;
    umap[8] = 23.3;
    umap[18] = 13.3;
    DELOG(umap);

    // Usage: DELOG(umap, {front n elements}, {parameters for type in container})
    DELOG(umap, {1});
}

void test_array()
{
    std::array<int, 5> array = {1};
    DELOG(array);

    // Usage: DELOG(deque, {start_idx, end_idx}, {parameters for type in container})
    DELOG(array, {0, 0});
}

void test_stack()
{
    std::stack<int> stack;
    stack.push(2);
    stack.push(200);
    DELOG(stack);

    // Usage: DELOG(stack, {front n elements}, {parameters for type in container})
    DELOG(stack, {1});
}

void test_queue()
{
    std::queue<int> queue;
    queue.push(29);
    DELOG(queue);

    // Usage: DELOG(queue, {front n elements}, {parameters for type in container})
    DELOG(queue, {1});
}

void test_pair()
{
    std::pair<int, int> pair = {1, 2};
    DELOG(pair);

    // Usage: DELOG(pair, {parameters for second type in pair})
    DELOG(pair, {});
}

void test_pointers()
{
    int pointer[5] = {3, 2, 56, 6, 8};
    DELOG(pointer); // print the first element in the pointer array
    // Usage: DELOG(pointer, {start_idx, end_idx})
    DELOG(pointer, {1, 3});

    float pf[3] = {5.06f, 16.1f, 8.4f};
    DELOG(pf);

    // other basic types are also supported

    // pointer of basic types could also be used in stl container
    std::vector<int *> vec;
    vec.push_back(pointer);
    DELOG(vec);
    // Usage: DELOG(vector, {start_idx, end_idx}, {parameters for type in container})
    DELOG(vec, {}, {1, 3});
}

#ifdef DELOG_ENABLE_EIGEN
void test_eigen()
{
    Eigen::Vector3f vec3;
    vec3 << 1, 0, 0;
    DELOG(vec3);

    Eigen::Matrix4d mat4 = Eigen::Matrix4d::Identity();
    DELOG(mat4);

    // Usage: DELOG(eigen_mat, {start_row, start_col, block_rows, block_cols})
    DELOG(mat4, {0, 0, 3, 1});
    DELOG(mat4, {1, 1, 2, 1});

    std::vector<Eigen::Matrix3f> mat_vec(3, Eigen::Matrix3f::Identity());
    DELOG(mat_vec);
    // Usage: DELOG(mat_vec, {paramters for container}, {paramters for type in container})
    DELOG(mat_vec, {1, 1});
}
#endif

#ifdef DELOG_ENABLE_OPENCV
void test_opencv()
{
    cv::Vec2f vec2f(1, 5);
    cv::Vec3i vec3i(4, 20, 33);
    DELOG(vec2f);
    // Usage: DELOG(cv_vec, {start_idx, end_idx})
    DELOG(vec3i, {4, 1});

    float dummy_query_data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    cv::Mat mat_32FC2 = cv::Mat(2, 3, CV_32FC2, dummy_query_data);
    DELOG(mat_32FC2);
    // Usage: DELOG(cv_mat, {start_row, start_col, block_rows, block_cols})
    DELOG(mat_32FC2, {0, 0, 2, 2});

    std::vector<cv::Mat> mat_vec(3, mat_32FC2);
    DELOG(mat_vec);
    // Usage: DELOG(mat_vec, {paramters for container}, {paramters for type in container})
    DELOG(mat_vec, {0, 0}, {1, 1, 3, 3});
}
#endif

int main()
{
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
#ifdef DELOG_ENABLE_EIGEN
    test_eigen();
#endif
#ifdef DELOG_ENABLE_OPENCV
    test_opencv();
#endif
    //	STOP_TIMER(0);

    return 0;
}
