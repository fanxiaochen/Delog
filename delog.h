#ifndef DELOG_H
#define DELOG_H

#include <vector>
#include <list>
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
#include <ctime>

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

class color
{
public:
    enum Type
    {
        RESET,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    // Only available in linux and mac os
    static std::unordered_map<Type, string_t> map; 

    static string_t red(string_t str)
    {
        string_t colored_str = map[RED] + str + map[RESET];
        return colored_str;
    }

    static string_t green(string_t str)
    {
        string_t colored_str = map[GREEN] + str + map[RESET];
        return colored_str;
    }

    static string_t yellow(string_t str)
    {
        string_t colored_str = map[YELLOW] + str + map[RESET];
        return colored_str;
    }

    static string_t blue(string_t str)
    {
        string_t colored_str = map[BLUE] + str + map[RESET];
        return colored_str;
    }
    static string_t magenta(string_t str)
    {
        string_t colored_str = map[MAGENTA] + str + map[RESET];
        return colored_str;
    }
    static string_t cyan(string_t str)
    {
        string_t colored_str = map[CYAN] + str + map[RESET];
        return colored_str;
    }
    static string_t white(string_t str)
    {
        string_t colored_str = map[WHITE] + str + map[RESET];

        #ifdef WINDOWS
        win_change_attributes( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        #endif
        return colored_str;
    }

private:
#ifdef WINDOWS
    inline void win_change_attributes(int foreground, int background = -1)
    {
        // yeah, i know.. it's ugly, it's windows.
        static WORD defaultAttributes = 0;

        // get terminal handle
        HANDLE hTerminal = INVALID_HANDLE_VALUE;
        hTerminal = GetStdHandle(STD_OUTPUT_HANDLE);

        // save default terminal attributes if it unsaved
        if (!defaultAttributes)
        {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                return;
            defaultAttributes = info.wAttributes;
        }

        // restore all default settings
        if (foreground == -1 && background == -1)
        {
            SetConsoleTextAttribute(hTerminal, defaultAttributes);
            return;
        }

        // get current settings
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(hTerminal, &info))
            return;

        if (foreground != -1)
        {
            info.wAttributes &= ~(info.wAttributes & 0x0F);
            info.wAttributes |= static_cast<WORD>(foreground);
        }

        if (background != -1)
        {
            info.wAttributes &= ~(info.wAttributes & 0xF0);
            info.wAttributes |= static_cast<WORD>(background);
        }

        SetConsoleTextAttribute(hTerminal, info.wAttributes);
    }
#endif
};

std::unordered_map<color::Type, string_t> color::map = 
{
    {RESET,     "\033[0m"},
    {RED,       "\033[31m"},
    {GREEN,     "\033[32m"},
    {YELLOW,    "\033[33m"},
    {BLUE,      "\033[34m"},
    {MAGENTA,   "\033[35m"},
    {CYAN,      "\033[36m"},
    {WHITE,     "\033[37m"},
};

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

#define RECORD_MAX_LENGTH 1000

class Timer
{
public:
static string_t timestamp()
{
	char str[9];

	// get the time, and convert it to struct tm format
	time_t a = time(0);
	struct tm* b = localtime(&a);

	// print the time to the string
	strftime(str, 9, "%H:%M:%S", b);

	return str;
}

static string_t datestamp()
{
	char str[11];

	// get the time, and convert it to struct tm format
	time_t a = time(0);
	struct tm* b = localtime(&a);

	// print the time to the string
	strftime(str, 11, "%Y-%m-%d", b);

	return str;
}

};

string_t record_format(const char_t* file, const ulong_t line, const char_t* func)
{
    char_t str[RECORD_MAX_LENGTH];
    sprintf(str, "[%s][%s][%s:%s:%d]\n", Timer::datestamp().c_str(), Timer::timestamp().c_str(),
                                                file, func, line);
    return string_t(str);
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

#define REGISTER_BASICS(Type)                                                   \
template <typename... Args>                                                        \
string_t message(const char_t* name, const Type& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::basics::Primitive().generate(name, type, args...);                           \
}                                                                               \                                                                                                                                                                  
string_t message(const char_t* name, const Type& type, const Parameters& args={})     \
{                                                                               \
    return delog::basics::Primitive().generate(name, type, args);                           \
}                                                                                                                                                                  

REGISTER_BASICS(int_t)
REGISTER_BASICS(long_t)
REGISTER_BASICS(char_t)
REGISTER_BASICS(uint_t)
REGISTER_BASICS(ulong_t)
REGISTER_BASICS(uchar_t)
REGISTER_BASICS(float_t)
REGISTER_BASICS(double_t)
REGISTER_BASICS(string_t)

namespace stl
{
namespace basics
{
namespace formats
{
template <typename Type1, typename Type2>
string_t format_pair(const char_t* name, const std::pair<Type1, Type2>& type, const Parameters& type2_args)
{
    string_t type_str = GET_VARIABLE_TYPE(type);            
    std::stringstream ss;                               
    ss << string_t("Name: ") << string_t(name) << "\n";        
    ss << string_t("Type: ") << string_t(type_str) << "\n";         
    ss << string_t("First: \n");             
    ss << "{\n" << delog::message("pair.first", type.first, {}) << "}\n"; 
    ss << string_t("Second: \n");             
    ss << "{\n" << delog::message("pair.second", type.second, type2_args) << "}\n"; 
    return ss.str();
}

} // formats

template <typename Type1, typename Type2>
string_t build(const char_t* name, const std::pair<Type1, Type2>& type, const Parameters& type2_args)
{
    return formats::format_pair(name, type, type2_args);
}

class Primitive
{
public:
    // pair
    template <typename Type1, typename Type2>
    string_t generate(const char_t* name, const std::pair<Type1, Type2>& value, const Parameters& type2_args={})
    {
        return build(name, value, type2_args);
    }
};

} // basics 
} // stl


#define REGISTER_STL_BASICS_TWO_PARAMETER(ContainerType)                                                   \
template <typename T1, typename T2, typename... Args>                                                     \
string_t message(const char_t* name, const ContainerType<T1,T2>& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::stl::basics::Primitive().generate(name, type, args...);                           \
}   \                                                                               
template <typename T1, typename T2>  \
string_t message(const char_t* name, const ContainerType<T1,T2>& type, const Parameters& type2_args={})     \
{                                                                                                                   \
    return delog::stl::basics::Primitive().generate(name, type, type2_args);                           \
}                                                                                  

REGISTER_STL_BASICS_TWO_PARAMETER(std::pair)

namespace stl
{
namespace container
{
namespace formats
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
ParameterList parameters_to_length(const Type& type, const Parameters& container_args)
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

} // formats

template <typename Type>
string_t build(const char_t* name, const std::vector<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_range(type, container_args);
    return formats::format_range(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::deque<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_range(type, container_args);
    return formats::format_range(name, type, cargs, type_args);
}

template <typename Type, size_t N>
string_t build(const char_t* name, const std::array<Type, N>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_range(type, container_args);
    return formats::format_range(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::list<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_length(type, container_args);
    return formats::format_iterator(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::set<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_length(type, container_args);
    return formats::format_iterator(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::unordered_set<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_length(type, container_args);
    return formats::format_iterator(name, type, cargs, type_args);
}

template <typename Type1, typename Type2>
string_t build(const char_t* name, const std::map<Type1, Type2>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_length(type, container_args);
    return formats::format_iterator(name, type, cargs, type_args);
}

template <typename Type1, typename Type2>
string_t build(const char_t* name, const std::unordered_map<Type1, Type2>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_length(type, container_args);
    return formats::format_iterator(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::stack<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_length(type, container_args);
    return formats::format_stack(name, type, cargs, type_args);
}

template <typename Type>
string_t build(const char_t* name, const std::queue<Type>& type, const Parameters& container_args, const Parameters& type_args)
{
    auto cargs = formats::parameters_to_length(type, container_args);
    return formats::format_queue(name, type, cargs, type_args);
}


class Primitive
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
    string_t generate(const char_t* name, const Container<Type1, Type2>& value, const Parameters& container_args={}, const Parameters& type2_args={})
    {
        return build(name, value, container_args, type2_args);
    }

    // array 
    template <typename Type, size_t N>
    string_t generate(const char_t* name, const std::array<Type, N>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(name, value, container_args, type_args);
    }

};
} // container
} // stl



#define REGISTER_STL_CONTAINER_ONE_PARAMETER(ContainerType)                                                   \
template <typename Type, typename... Args>                                                     \
string_t message(const char_t* name, const ContainerType<Type>& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::stl::container::Primitive().generate(name, type, args...);                           \
}   \                                                                               
template <typename Type>  \
string_t message(const char_t* name, const ContainerType<Type>& type, const Parameters& container_args={}, const Parameters& type_args={})     \
{                                                                                                                   \
    return delog::stl::container::Primitive().generate(name, type, container_args, type_args);                           \
}                                                                                  

#define REGISTER_STL_CONTAINER_TWO_PARAMETER(ContainerType)                                                   \
template <typename T1, typename T2, typename... Args>                                                     \
string_t message(const char_t* name, const ContainerType<T1,T2>& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::stl::container::Primitive().generate(name, type, args...);                           \
}   \                                                                               
template <typename T1, typename T2>  \
string_t message(const char_t* name, const ContainerType<T1,T2>& type, const Parameters& container_args={}, const Parameters& type_args={})     \
{                                                                                                                   \
    return delog::stl::container::Primitive().generate(name, type, container_args, type_args);                           \
}                                                                                  

#define REGISTER_STL_CONTAINER_TWO_PARAMETER_WITH_N(ContainerType)                                                   \
template <typename T1, size_t N, typename... Args>                                                     \
string_t message(const char_t* name, const ContainerType<T1,N>& type, const std::initializer_list<Args>&... args)     \
{                                                                               \
    return delog::stl::container::Primitive().generate(name, type, args...);                           \
}   \                                                                               
template <typename T1, size_t N>  \
string_t message(const char_t* name, const ContainerType<T1,N>& type, const Parameters& container_args={}, const Parameters& type_args={})     \
{                                                                                                                   \
    return delog::stl::container::Primitive().generate(name, type, container_args, type_args);                           \
}                                                                                  


REGISTER_STL_CONTAINER_ONE_PARAMETER(std::vector)
REGISTER_STL_CONTAINER_ONE_PARAMETER(std::list)
REGISTER_STL_CONTAINER_ONE_PARAMETER(std::deque)
REGISTER_STL_CONTAINER_ONE_PARAMETER(std::set)
REGISTER_STL_CONTAINER_ONE_PARAMETER(std::unordered_set)
REGISTER_STL_CONTAINER_ONE_PARAMETER(std::stack)
REGISTER_STL_CONTAINER_ONE_PARAMETER(std::queue)

REGISTER_STL_CONTAINER_TWO_PARAMETER_WITH_N(std::array)
REGISTER_STL_CONTAINER_TWO_PARAMETER(std::map)
REGISTER_STL_CONTAINER_TWO_PARAMETER(std::unordered_map)

#define DELOG_ALL(loggable, ...) \
delog::record_format(__FILE__, __LINE__, __func__) + \
delog::message(#loggable, loggable, ##__VA_ARGS__)

} // delog


#endif // DELOG_H
