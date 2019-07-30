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
    {typeid(char_t).name(),    "%s  %s = %c\n"},
    {typeid(int_t).name(),     "%s  %s = %d\n"},
    {typeid(long_t).name(),    "%s  %s = %d\n"},
    {typeid(float_t).name(),   "%s  %s = %f\n"},
    {typeid(double_t).name(),  "%s  %s = %f\n"},
    {typeid(string_t).name(),  "%s  %s = %s\n"},
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
    
    free(type);

    return str;
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
    std::cout << delog::message("Test", type[0], type_args) << std::endl;
    for (size_t i = 0; i < container_args.size(); ++ i)
    {
        std::cout << "container" << std::endl;
        std::cout << container_args[i] << std::endl;
    }
    return string_t("vector");
}

template <typename Type, typename... TypeArgs>
string_t build(const char_t* name, const std::list<Type>& type, size_t start, size_t end, const TypeArgs& ...args)
{
    return string_t("list");
}

template <typename Type, typename... TypeArgs>
string_t build(const char_t* name, const std::unordered_set<Type>& type, size_t length, const TypeArgs& ...args)
{
    return string_t("settt");
}

template <typename Type1, typename Type2, typename... TypeArgs>
string_t build(const char_t* name, const std::unordered_map<Type1, Type2>& type, size_t length, const TypeArgs& ...args)
{
    return string_t("mappp");
}

class Container
{
public:

    // Sequence containers: vector, list, deque
    template <template<typename> typename Container, typename Type>
    string_t generate(const char_t* name, const Container<Type>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        ParameterList cargs = ParameterList(container_args);
        ParameterList cargs_default({0, value.size()});
        std::cout << "Length" << cargs_default.size() << std::endl;

        for (size_t i = 0; i < cargs.size(); ++ i)
        {
            cargs_default[i] = cargs[i];
            std::cout << "container" << std::endl;
            std::cout << cargs_default[i] << std::endl;
        }

        return build(name, value, cargs_default, type_args);
    }

 //   // Sequence containers: array 
 //   template <typename Type, size_t N>
 //   string_t generate(const char_t* name, const std::array<Type, N>& value, const Parameters& container_args={}, const Parameters& type_args={})
 //   {
 //       auto parameters = ParameterVector(container_args);
 //       for (size_t i = 0; i < parameters.size(); ++ i)
 //       {
 //           std::cout << "container" << std::endl;
 //           std::cout << parameters[i] << std::endl;
 //       }

 //       parameters = ParameterVector(type_args);
 //       for (size_t i = 0; i < parameters.size(); ++ i)
 //       {
 //           std::cout << "type" << std::endl;
 //           std::cout << parameters[i] << std::endl;
 //       }
 //       return build(name, value, container_args, type_args);
 //   }
//    
//    // Associative containers: set, unordered_set
//    template <template<typename> typename Container, typename Type>
//    string_t generate(const char_t* name, const Container<Type>& value, const Parameters& container_args={}, const Parameters& type_args={})
//    {
//        auto parameters = ParameterVector(container_args);
//        for (size_t i = 0; i < parameters.size(); ++ i)
//        {
//            std::cout << "container" << std::endl;
//            std::cout << parameters[i] << std::endl;
//        }
//
//        parameters = ParameterVector(type_args);
//        for (size_t i = 0; i < parameters.size(); ++ i)
//        {
//            std::cout << "type" << std::endl;
//            std::cout << parameters[i] << std::endl;
//        }
//        return build(name, value, container_args, type_args);
//    }
//
    // Associative containers: map, unordered_map
    template <template<typename, typename> typename Container, typename Key, typename T>
    string_t generate(const char_t* name, const Container<Key, T>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        auto parameters = ParameterList(container_args);
        for (size_t i = 0; i < parameters.size(); ++ i)
        {
            std::cout << "container" << std::endl;
            std::cout << parameters[i] << std::endl;
        }

        parameters = ParameterList(type_args);
        for (size_t i = 0; i < parameters.size(); ++ i)
        {
            std::cout << "type" << std::endl;
            std::cout << parameters[i] << std::endl;
        }
        return build(name, value, container_args, type_args);
    }
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

//EXPORT_STL_TWO_PARAMETER(std::array)
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
