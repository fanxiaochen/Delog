#ifndef DELOG_H
#define DELOG_H

#include <vector>

namespace delog
{
typedef char char_t;
typedef int int_t;
typedef float float_t;
typedef double double_t;

enum class LogDataType
{
    UNDEFINED = 0,
    STRING = 1,
    VARIABLE = 2,
    CLASS = 3,
    CUSTOM = 4,
};

enum class LogContainerType
{
   STL = 0 
};

template <typename T, typename ...Args>
class Loggable
{
public:
    virtual LogDataType type() const { return LogDataType::UNDEFINED; }
    virtual char_t* build(const T& t, const Args& ...) = 0;
};

template <typename T, typename ...Args>
class LogString: public Loggable<T, Args...>
{
public:
    virtual LogDataType type() const { return LogDataType::STRING; }
};

template <typename T, typename ...Args>
class LogVariable: public Loggable<T, Args...>
{
public:
    virtual LogDataType type() const { return LogDataType::VARIABLE; }
};

template <typename T, typename ...Args>
class LogClass: public Loggable<T, Args...>
{
public:
    virtual LogDataType type() const { return LogDataType::CLASS; }
};

template <typename T, typename ...Args>
class LogCustom: public Loggable<T, Args...>
{
public:
    virtual LogDataType type() const { return LogDataType::CUSTOM; }
};


// Container
template <template<typename, typename> class Container, typename T, typename ...Args>
class LogContainer
{
public:
    virtual LogContainerType type() const { return LogContainerType::STL; }
    virtual char_t* build(const Container<T, std::allocator<T>>& container, const Args& ...) = 0;
};



//#define REGISTER_STRING(OBJECT)                         \
//                                                        \
//template <typename ...Args>                             \
//class OBJECT: public LogString<...Args>                 \    
//{                                                       \
//    char_t* build(const Args& ...)                      \
//    {                                                   \
//                                                        \
//    }                                                   \
//};                                                      \
//
//


// String 
template <typename ...Args>
class LogStdString: public LogString<std::string, Args...>
{
public:
    char_t* build(const std::string& str, const Args& ...)
    {
        return "sss";
    }
};

template <typename ...Args>
class LogCharArray: public LogString<char_t*, Args...>
{
public:
    char_t* build(const char_t*& char_array, const Args& ...)
    {
        return "sss";
    }
};

// Variable
template <typename ...Args>
class LogInt: public LogVariable<int_t, Args...>
{
public:
    char_t* build(const int_t& n, const Args& ...)
    {
        return "sss";
    }
};

template <typename ...Args>
class LogFloat: public LogVariable<float_t, Args...>
{
public:
    char_t* build(const float_t& n, const Args& ...)
    {
        return "sss";
    }
};

// Class
//template <typename ...Args>
//class LogEigenMatrix: public LogClass<Eigen::Matrix, Args...>
//{
//public:
//    char_t* build(const Eigen::Matrix& n, const Args& ...)
//    {
//        return "sss";
//    }
//};

// Custom


// Container
template <typename T, typename ...Args>
class LogStlVector: public LogContainer<std::vector, T, Args...>
{
public:
    char_t* build(const std::vector<T, std::allocator<T>>& container, const Args& ...)
    {
        return "ssssss";
    }
};



//
//template <typename ...Args>
//class Int: public LogVariable<...Args>
//{
//    char_t* build(const Args& ...)
//    {
//
//    }
//};
//
//
//template <typename Type>
//class TypedValue 
//{
//public:
//    char_t* build()
//    {
//        if (t_ != nullptr) return t_.build();
//        else return "";
//    }
//private:
//    Type*  t_;
//};
//
//class LogFormat
//{
//public:
//    static char_t* time(char_t* year, char_t* month, char_t* day, char_t* hour, char_t* minute, char_t* second);
//    static char_t* file(char_t* file_name);
//    static char_t* line(char_t* line_num);
//    static char_t* function(char_t* function_name);
//
//
//    static char_t* value();
//};
//
//
//
//class Delogger
//{
//};

}


#endif // DELOG_H
