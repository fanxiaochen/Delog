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
typedef unsigned char uchar_t;
typedef unsigned int uint_t;
typedef unsigned long ulong_t;
typedef float float_t;
typedef double double_t;
typedef std::string string_t;


typedef std::initializer_list<int_t>  Parameters;

struct ParameterList
{
    std::vector<int_t> v;
    ParameterList(Parameters parameters): v(parameters){}

    size_t size() const { return v.size(); }
    int_t operator[](size_t index) const { return v[index]; }
    void set(size_t index, int_t value) { v[index] = value; }
};

#define GET_VARIABLE_NAME(Variable) (#Variable)

template <typename Type>
string_t GET_VARIABLE_TYPE(const Type& value)
{
    char_t* type = nullptr;
#ifndef _MSC_VER
    int status = 0;
    type = abi::__cxa_demangle(typeid(Type).name(), 0, 0, &status);
#else
    type = typeid(Type).name();
#endif
    string_t str = type;
    free(type);
    return str;
}

namespace basics
{

#define FORMAT_MAX_LENGTH   1000

/// Basic data type
static std::unordered_map<const char_t*, const char_t*> formats({ 
    {typeid(char_t).name(),    "%s  %s = %c\n"},
    {typeid(int_t).name(),     "%s  %s = %d\n"},
    {typeid(long_t).name(),    "%s  %s = %d\n"},
    {typeid(uchar_t).name(),   "%s  %s = %c\n"},
    {typeid(uint_t).name(),    "%s  %s = %d\n"},
    {typeid(ulong_t).name(),   "%s  %s = %d\n"},
    {typeid(float_t).name(),   "%s  %s = %f\n"},
    {typeid(double_t).name(),  "%s  %s = %f\n"},
    {typeid(string_t).name(),  "%s  %s = %s\n"},
});


template <typename Type>
string_t build(const char_t* name, const Type& value)
{
    string_t type = GET_VARIABLE_TYPE(value);
    char_t str[FORMAT_MAX_LENGTH];
    sprintf(str, formats.at(typeid(Type).name()), type.c_str(), name, value);

    return string_t(str); 
}

string_t build(const char_t* name, const string_t& value)
{
    string_t type = GET_VARIABLE_TYPE(value);
    char_t str[FORMAT_MAX_LENGTH];
    sprintf(str, formats.at(typeid(string_t).name()), type.c_str(), name, value.c_str());

    return string_t(str); 
}

class Primitive
{
public:
    template <typename Type>
    string_t generate(const char_t* name, const Type& value, const Parameters& args={})
    {
        // No parameters for basic types
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
EXPORT_BASICS(uint_t)
EXPORT_BASICS(ulong_t)
EXPORT_BASICS(uchar_t)
EXPORT_BASICS(float_t)
EXPORT_BASICS(double_t)
EXPORT_BASICS(string_t)

namespace stl
{

template <typename Type>
string_t format_range(const char_t* name, const Type& type, const ParameterList& container_args, const Parameters& type_args)
{
    string_t type_str = GET_VARIABLE_TYPE(type);            
    std::stringstream ss;                               
    ss << string_t("Name: ") << string_t(name) << "\n";        
    ss << string_t("Type: ") << string_t(type_str) << "\n";         
    ss << string_t("Length: ") << type.size() << "\n";              
    size_t start = container_args[0];                   
    size_t end = container_args[1];                     
    for (size_t i = start; i <= end; ++ i)              
    {                                                   
        ss << "<--[" << i << "]-->\n";                  
        ss << "{\n" << delog::message(("var["+std::to_string(i)+"]").c_str(), type[i], type_args) << "}\n"; 
    }                                                   
    return ss.str();                                    
}

template <typename Type>
string_t format_iterator(const char_t* name, const Type& type, const ParameterList& container_args, const Parameters& type_args)
{
    string_t type_str = GET_VARIABLE_TYPE(type);            
    std::stringstream ss;                               
    ss << string_t("Name: ") << string_t(name) << "\n";        
    ss << string_t("Type: ") << string_t(type_str) << "\n";         
    ss << string_t("Length: ") << type.size() << "\n";              
    size_t length = container_args[0];                   

    auto itr = type.begin();
    size_t count = 0;
    for (auto itr = type.begin(); itr != type.end(); ++ itr)
    {
        if (count == length) break;
        ss << "<--[" << count << "]-->\n";                  
        ss << "{\n" << delog::message(("var["+std::to_string(count)+"]").c_str(), *itr, type_args) << "}\n"; 
        count ++;
    }
    return ss.str();                                    
}

template <typename Type>
string_t format_stack(const char_t* name, const Type& type, const ParameterList& container_args, const Parameters& type_args)
{
    string_t type_str = GET_VARIABLE_TYPE(type);            
    std::stringstream ss;                               
    ss << string_t("Name: ") << string_t(name) << "\n";        
    ss << string_t("Type: ") << string_t(type_str) << "\n";         
    ss << string_t("Length: ") << type.size() << "\n";              
    size_t length = container_args[0];                   

    Type copied = type;
    size_t count = 0;
    while (!copied.empty())
    {
        if (count == length) break;
        ss << "<--[" << count << "]-->\n";                  
        ss << "{\n" << delog::message(("var["+std::to_string(count)+"]").c_str(), copied.top(), type_args) << "}\n"; 
        copied.pop();
        count ++;
    }
    return ss.str();                                    
}

template <typename Type>
string_t format_queue(const char_t* name, const Type& type, const ParameterList& container_args, const Parameters& type_args)
{
    string_t type_str = GET_VARIABLE_TYPE(type);            
    std::stringstream ss;                               
    ss << string_t("Name: ") << string_t(name) << "\n";        
    ss << string_t("Type: ") << string_t(type_str) << "\n";         
    ss << string_t("Length: ") << type.size() << "\n";              
    size_t length = container_args[0];                   

    Type copied = type;
    size_t count = 0;
    while (!copied.empty())
    {
        if (count == length) break;
        ss << "<--[" << count << "]-->\n";                  
        ss << "{\n" << delog::message(("var["+std::to_string(count)+"]").c_str(), copied.front(), type_args) << "}\n"; 
        copied.pop();
        count ++;
    }
    return ss.str();                                    
}

template <typename Type1, typename Type2>
string_t format_pair(const char_t* name, const std::pair<Type1, Type2>& type, const Parameters& type1_args, const Parameters& type2_args)
{
    string_t type_str = GET_VARIABLE_TYPE(type);            
    std::stringstream ss;                               
    ss << string_t("Name: ") << string_t(name) << "\n";        
    ss << string_t("Type: ") << string_t(type_str) << "\n";         
    ss << string_t("First: \n");             
    ss << "{\n" << delog::message("var.first", type.first, type1_args) << "}\n"; 
    ss << string_t("Second: \n");             
    ss << "{\n" << delog::message("var.second", type.second, type2_args) << "}\n"; 
    return ss.str();
}

template <typename Type>
ParameterList parameters_to_range(const Type& type, const Parameters& container_args)
{
    ParameterList cargs = ParameterList(container_args);
    ParameterList cargs_default({0, type.size()-1});

    for (size_t i = 0; i < cargs.size(); ++ i) 
    {
        if (cargs[i] >= 0 && cargs[i] <= type.size()-1)
            cargs_default.set(i, cargs[i]);
    }

    return cargs_default;
}

template <typename Type>
ParameterList parameters_to_iterator(const Type& type, const Parameters& container_args)
{
    ParameterList cargs = ParameterList(container_args);
    ParameterList cargs_default({type.size()});

    for (size_t i = 0; i < cargs.size(); ++ i) 
    {
        if (cargs[i] >= 0 && cargs[i] <= type.size())
            cargs_default.set(i, cargs[i]);
    }

    return cargs_default;
}

template <typename Type>
string_t build(const char_t* name, const std::vector<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_range(type, container_args);
    return format_range(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::deque<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_range(type, container_args);
    return format_range(name, type, cargs, type_args);
}

template <typename Type, size_t N>
string_t build(const char_t* name, const std::array<Type, N>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_range(type, container_args);
    return format_range(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::list<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_iterator(type, container_args);
    return format_iterator(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::set<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_iterator(type, container_args);
    return format_iterator(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::unordered_set<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_iterator(type, container_args);
    return format_iterator(name, type, cargs, type_args);
}

template <typename Type1, typename Type2>
string_t build(const char_t* name, const std::map<Type1, Type2>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_iterator(type, container_args);
    return format_iterator(name, type, cargs, type_args);
}

template <typename Type1, typename Type2>
string_t build(const char_t* name, const std::unordered_map<Type1, Type2>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_iterator(type, container_args);
    return format_iterator(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::stack<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_iterator(type, container_args);
    return format_stack(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::queue<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = parameters_to_iterator(type, container_args);
    return format_queue(name, type, cargs, type_args);
}

template <typename Type1, typename Type2>
string_t build(const char_t*& name, const std::pair<Type1, Type2>& type, const Parameters& type1_args, const Parameters& type2_args)
{
    return format_pair(name, type, type1_args, type2_args);
}

class Container
{
public:
    // vector, list, deque, set, unordered_set, stack, queue
    template <template<typename> typename Container, typename Type>
    string_t generate(const char_t* name, const Container<Type>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(name, value, container_args, type_args);
    }

    // map, unordered_map
    template <template<typename, typename> typename Container, typename Type1, typename Type2>
    string_t generate(const char_t* name, const Container<Type1, Type2>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(name, value, container_args, type_args);
    }

    // array 
    template <typename Type, size_t N>
    string_t generate(const char_t* name, const std::array<Type, N>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(name, value, container_args, type_args);
    }

    // pair
    template <typename Type1, typename Type2>
    string_t generate(const char_t* name, const std::pair<Type1, Type2>& value, const Parameters& type1_args={}, const Parameters& type2_args={})
    {
        return build(name, value, type1_args, type2_args);
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

#define EXPORT_STL_TWO_PARAMETER_WITH_PAIR(ContainerType)                                                   \
template <typename T1, typename T2, typename... Args>                                                     \
string_t message(const char_t* name, const ContainerType<T1,T2>& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::stl::Container().generate(name, type, args...);                           \
}   \                                                                               
template <typename T1, typename T2>  \
string_t message(const char_t* name, const ContainerType<T1,T2>& type, const Parameters& type1_args={}, const Parameters& type2_args={})     \
{                                                                                                                   \
    return delog::stl::Container().generate(name, type, type1_args, type2_args);                           \
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

EXPORT_STL_TWO_PARAMETER_WITH_PAIR(std::pair)

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
