#ifndef DELOG_H
#define DELOG_H

#include <vector>
#include <list>
#include <tuple>
#include <deque>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <sstream>
#include <typeinfo>
#ifndef _MSC_VER
    #include <cxxabi.h>
#endif

namespace delog
{
typedef char char_t;
typedef int int_t;
typedef long long_t;
typedef float float_t;
typedef double double_t;
typedef std::string string_t;


#define GET_VARIABLE_NAME(Variable) (#Variable)

typedef std::initializer_list<int_t>  Parameters;

struct ParameterList
{
    std::vector<int_t> v;
    ParameterList(Parameters parameters): v(parameters){}

    size_t size() const { return v.size(); }
    int_t& operator[](size_t index) { return v[index]; }
    int_t operator[](size_t index) const { return v[index]; }
};


namespace basics
{

#define FORMAT_MAX_LENGTH   1000

/// Basic data type
static std::unordered_map<const char_t*, const char_t*> formats({ 
    {typeid(char_t).name(),    "%s  %s = %c"},
    {typeid(int_t).name(),     "%s  %s = %d"},
    {typeid(long_t).name(),    "%s  %s = %d"},
    {typeid(float_t).name(),   "%s  %s = %f"},
    {typeid(double_t).name(),  "%s  %s = %f"},
    {typeid(string_t).name(),  "%s  %s = %s"},
});


template <typename Type>
string_t build(const char_t* name, const Type& value)
{
    char_t* type = nullptr;
#ifndef _MSC_VER
    int status = 0;
    type = abi::__cxa_demangle(typeid(Type).name(), 0, 0, &status);
//    std::cout << type << std::endl;
#else
    type = typeid(Type).name();
#endif

    char_t str[FORMAT_MAX_LENGTH];
    sprintf(str, formats.at(typeid(Type).name()), type, name, value);
 //   std::cout << str << std::endl;
    
    std::stringstream ss;
    ss << str << "\n";
    
    free(type);

    return ss.str(); 
}

string_t build(const char_t* name, const string_t& value)
{
    char* type = nullptr;
#ifndef _MSC_VER
    int status = 0;
    type = abi::__cxa_demangle(typeid(string_t).name(), 0, 0, &status);
//    std::cout << type << std::endl;
#else
    type = typeid(Type).name();
#endif

    char_t str[FORMAT_MAX_LENGTH];
    sprintf(str, formats.at(typeid(string_t).name()), type, name, value.c_str());
//    std::cout << str << std::endl;

    free(type);
    return str;
}

class Primitive
{
public:
    template <typename Type>
    string_t generate(const char_t* name, const Type& value, const Parameters& args={})
    {
//        auto parameters = ParameterVector(args);
//        for (size_t i = 0; i < parameters.size(); ++ i)
//        {
//            std::cout << parameters[i] << std::endl;
//        }
        return build(name, value);
    }
};

}

#define EXPORT_BASICS(Type)                                                   \
template <typename... Args>                                                        \
string_t message(const char_t* name, const Type& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::basics::Primitive().generate(name, type, args...);                           \
}                                                                               \                                                                                                                                                                  
string_t message(const char_t* name, const Type& type, const Parameters& args={})     \
{                                                                               \
    return delog::basics::Primitive().generate(name, type, args);                           \
}                                                                                                                                                                  

EXPORT_BASICS(int_t)
EXPORT_BASICS(long_t)
EXPORT_BASICS(char_t)
EXPORT_BASICS(float_t)
EXPORT_BASICS(double_t)
EXPORT_BASICS(string_t)

namespace stl
{

template <typename Type>
string_t build(const char_t* name, const std::vector<Type>& type, const ParameterList& container_args, const Parameters& type_args)
{
    char_t* type_str = nullptr;
#ifndef _MSC_VER
    int status = 0;
    type_str = abi::__cxa_demangle(typeid(std::vector<Type>).name(), 0, 0, &status);
//    std::cout << type << std::endl;
#else
    type_str = typeid(std::vector<Type>).name();
#endif

    std::stringstream ss;
    ss << string_t(type_str) << "\n";

    size_t start = container_args[0];
    size_t end = container_args[1];
    for (size_t i = start; i <= end; ++ i)
    {
       ss << "<--[" << i << "]-->\n";
       ss << "{" << delog::message(("type["+std::to_string(i)+"]").c_str(), type[i], type_args) << "}\n";
    }

    free(type_str);

    return ss.str();
}

template <typename Type, size_t N>
string_t build(const char_t* name, const std::array<Type, N>& type, const ParameterList& container_args, const Parameters& type_args)
{
    char_t* type_str = nullptr;
#ifndef _MSC_VER
    int status = 0;
    type_str = abi::__cxa_demangle(typeid(std::array<Type, N>).name(), 0, 0, &status);
//    std::cout << type << std::endl;
#else
    type_str = typeid(std::vector<Type>).name();
#endif

    std::stringstream ss;
    ss << string_t(type_str) << "\n";

    size_t start = container_args[0];
    size_t end = container_args[1];
    for (size_t i = start; i <= end; ++ i)
    {
       ss << "<--[" << i << "]-->\n";
       ss << "{" << delog::message(("type["+std::to_string(i)+"]").c_str(), type[i], type_args) << "}\n";
    }

    free(type_str);

    return ss.str();
}

template <typename Type>
string_t build(const char_t* name, const std::list<Type>& type, const ParameterList& container_args, const Parameters& type_args)
{
    return string_t("list");
}

template <typename Type>
string_t build(const char_t* name, const std::unordered_set<Type>& type, const ParameterList& container_args, const Parameters& type_args)
{
    return string_t("settt");
}

template <typename Type1, typename Type2>
string_t build(const char_t* name, const std::unordered_map<Type1, Type2>& type, const ParameterList& container_args, const Parameters& type_args)
{
    return string_t("mappp");
}

template <typename Type>
string_t build(const char_t* name, const std::stack<Type>& type, const ParameterList& container_args, const Parameters& type_args)
{
    return string_t("stack");
}

template <typename Type>
string_t build(const char_t* name, const std::queue<Type>& type, const ParameterList& container_args, const Parameters& type_args)
{
    return string_t("queue");
}

class Container
{
public:

    // vector, list, deque, set, unordered_set, stack, queue
    template <template<typename> typename Container, typename Type>
    string_t generate(const char_t* name, const Container<Type>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        ParameterList cargs = ParameterList(container_args);
        ParameterList cargs_default({0, value.size()});

        for (size_t i = 0; i < cargs.size(); ++ i) cargs_default[i] = cargs[i];

        return build(name, value, cargs_default, type_args);
    }

    // map, unordered_map
    template <template<typename, typename> typename Container, typename Type1, typename Type2>
    string_t generate(const char_t* name, const Container<Type1, Type2>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        ParameterList cargs = ParameterList(container_args);
        ParameterList cargs_default({0, value.size()});

        for (size_t i = 0; i < cargs.size(); ++ i) cargs_default[i] = cargs[i];

        return build(name, value, cargs_default, type_args);
    }

    // array 
    template <typename Type, size_t N>
    string_t generate(const char_t* name, const std::array<Type, N>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        ParameterList cargs = ParameterList(container_args);
        ParameterList cargs_default({0, value.size()});

        for (size_t i = 0; i < cargs.size(); ++ i) cargs_default[i] = cargs[i];

        return build(name, value, cargs_default, type_args);
    }



//    // Associative containers: set, unordered_set
//    template <template<typename, typename, typename> typename Container, typename Type>
//    string_t generate(const char_t* name, const Container<Type, std::less<Type>, std::allocator<Type>>& value, 
//    const Parameters& container_args={}, const Parameters& type_args={})
//    {
//        ParameterList cargs = ParameterList(container_args);
//        ParameterList cargs_default({0, value.size()});
//
//        for (size_t i = 0; i < cargs.size(); ++ i) cargs_default[i] = cargs[i];
//
//        return build(name, value, cargs_default, type_args);
//    }

 //   // Associative containers: map, unordered_map
 //   template <template<typename, typename, typename, typename> typename Container, typename Key, typename T>
 //   string_t generate(const char_t* name, const Container<Key, T, std::less<Key>, std::allocator<std::pair<const Key, T>>>& value, 
 //   const Parameters& container_args={}, const Parameters& type_args={})
 //   {
 //       ParameterList cargs = ParameterList(container_args);
 //       ParameterList cargs_default({0, value.size()});

 //       for (size_t i = 0; i < cargs.size(); ++ i) cargs_default[i] = cargs[i];

 //       return build(name, value, cargs_default, type_args);
 //   }

};

}




#define EXPORT_STL_ONE_PARAMETER(ContainerType)                                                   \
template <typename Type, typename... Args>                                                     \
string_t message(const char_t* name, const ContainerType<Type>& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::stl::Container().generate(name, type, args...);                           \
}   \                                                                               
template <typename Type>  \
string_t message(const char_t* name, const ContainerType<Type>& type, const Parameters& container_args={}, const Parameters& type_args={})     \
{                                                                                                                   \
    return delog::stl::Container().generate(name, type, container_args, type_args);                           \
}                                                                                  

#define EXPORT_STL_TWO_PARAMETER(ContainerType)                                                   \
template <typename T1, typename T2, typename... Args>                                                     \
string_t message(const char_t* name, const ContainerType<T1,T2>& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::stl::Container().generate(name, type, args...);                           \
}   \                                                                               
template <typename T1, typename T2>  \
string_t message(const char_t* name, const ContainerType<T1,T2>& type, const Parameters& container_args={}, const Parameters& type_args={})     \
{                                                                                                                   \
    return delog::stl::Container().generate(name, type, container_args, type_args);                           \
}                                                                                  

#define EXPORT_STL_TWO_PARAMETER_WITH_N(ContainerType)                                                   \
template <typename T1, size_t N, typename... Args>                                                     \
string_t message(const char_t* name, const ContainerType<T1,N>& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::stl::Container().generate(name, type, args...);                           \
}   \                                                                               
template <typename T1, size_t N>  \
string_t message(const char_t* name, const ContainerType<T1,N>& type, const Parameters& container_args={}, const Parameters& type_args={})     \
{                                                                                                                   \
    return delog::stl::Container().generate(name, type, container_args, type_args);                           \
}                                                                                  


//template <typename T, typename... Args>                                              \
//string_t message(const char_t* name, const Type<T>& type, const Args&... args)       \
//{                                                                                    \
//    return delog::stl::build(name, type, args...);                                   \
//}                                                                               
//
//#define REGISTER_STL_TWO_PARAMETER(Type)                                             \
//template <typename T1, typename T2, typename... Args>                                \
//string_t message(const char_t* name, const Type<T1,T2>& type, const Args&... args)   \
//{                                                                                    \
//    return delog::stl::build(name, type, args...);                                   \
//}                                                                               
//
//#define REGISTER_STL_ONE_PARAMETER_TEST(Type, S)                                             \
//template <typename T, typename... Args>                                              \
//string_t message(const char_t* name, const Type<T>& type, const Args&... args)       \
//{                                                                                    \
//    return delog::stl::build(name, type, args...);                                   \
//}                                                                               


EXPORT_STL_ONE_PARAMETER(std::vector)
EXPORT_STL_ONE_PARAMETER(std::list)
EXPORT_STL_ONE_PARAMETER(std::deque)
EXPORT_STL_ONE_PARAMETER(std::set)
EXPORT_STL_ONE_PARAMETER(std::unordered_set)
EXPORT_STL_ONE_PARAMETER(std::stack)
EXPORT_STL_ONE_PARAMETER(std::queue)

EXPORT_STL_TWO_PARAMETER_WITH_N(std::array)
EXPORT_STL_TWO_PARAMETER(std::map)
EXPORT_STL_TWO_PARAMETER(std::unordered_map)

#define DELOG_ALL(loggable, ...) delog::message(#loggable, loggable, __VA_ARGS__)

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
