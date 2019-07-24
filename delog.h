#ifndef DELOG_H
#define DELOG_H

#include <vector>

namespace delog
{
typedef char char_t;
typedef int int_t;
typedef long long_t;
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
   UNDEFINED = 0,
   STL = 1 
};

template <typename LogType>
class Logger: public LogType
{
 public:
  // Behavior method.
  template <typename T, typename ...Args>
  char_t* dispatch(const T& t, const Args& ...args) const
  {
    std::cout << build(t, args...) << std::endl; 
    return build(t, args...);
  }

 private:
  using LogType::build;
};

// Data
class Loggable
{
public:
    virtual LogDataType type() const { return LogDataType::UNDEFINED; }
};

class LogContainer
{
public:
    virtual LogContainerType type() const { return LogContainerType::UNDEFINED; }
};

class LogString: public Loggable
{
public:
    virtual LogDataType type() const { return LogDataType::STRING; }
};

class LogVariable: public Loggable
{
public:
    virtual LogDataType type() const { return LogDataType::VARIABLE; }
};

class LogClass: public Loggable
{
public:
    virtual LogDataType type() const { return LogDataType::CLASS; }
};

class LogCustom: public Loggable
{
public:
    virtual LogDataType type() const { return LogDataType::CUSTOM; }
};

class LogStlContainer: public LogContainer
{
public:
    virtual LogContainerType type() const { return LogContainerType::STL; }
};

class LogStlVector: public LogStlContainer
{
public:
    template <typename T, typename ...Args>
    char_t* build(const std::vector<T>& t, const Args& ...args) const
    {
        return "container";
    }
};

// String 
class LogStdString: public LogString
{
public:
    template <typename ...Args>
    char_t* build(const std::string& str, const Args& ...args) const
    {
//        size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
//        std::unique_ptr<char[]> buf( new char[ size ] ); 
//
//    snprintf( buf.get(), size, format.c_str(), args ... );
//    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
        return "sss";
    }
};

class LogCharArray: public LogString
{
public:
    template <typename ...Args>
    char_t* build(const char_t*& str, const Args& ...args) const
    {
        return "sss";
    }
};

// Variable
class LogInt: public LogVariable
{
public:
    template <typename ...Args>
    char_t* build(const int_t& n, const Args& ...)
    {
        return "sss";
    }
};

class LogLong: public LogVariable
{
public:
    template <typename ...Args>
    char_t* build(const long_t& n, const Args& ...)
    {
        return "sss";
    }
};

class LogFloat: public LogVariable
{
public:
    template <typename ...Args>
    char_t* build(const float_t& n, const Args& ...)
    {
        return "sss";
    }
};

class LogDouble: public LogVariable
{
public:
    template <typename ...Args>
    char_t* build(const double_t& n, const Args& ...)
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


//// Container
//template <typename T, typename ...Args>
//class LogStlVector: public LogContainer<std::vector, T, Args...>
//{
//public:
//    char_t* build(const std::vector<T, std::allocator<T>>& container, const Args& ...)
//    {
//        return "ssssss";
//    }
//};
//
//
//#define LOG_STDSTRING(loggable, length) delog::LogStdString<int>().build(loggable, length)
//#define LOG_CHARARRAY(loggable, length) delog::LogCharArray<int>().build(loggable, length)
//#define LOG_INT(loggable, length) delog::LogInt<int>().build(loggable, length)
//#define LOG_FLOAT(loggable, length) delog::LogFloat<int>().build(loggable, length)

#define LOG_INT(loggable, ...) delog::Logger<delog::LogInt>().dispatch(loggable, __VA_ARGS__)
#define LOG_FLOAT(loggable, ...) delog::Logger<delog::LogFloat>().dispatch(loggable, __VA_ARGS__)
#define LOG_STDSTRING(loggable, ...) delog::Logger<delog::LogStdString>().dispatch(loggable, __VA_ARGS__)
#define LOG_STLVECTOR(loggable, ...) delog::Logger<delog::LogStlVector>().dispatch(loggable, __VA_ARGS__)


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
