#ifndef DELOG_H
#define DELOG_H

#if (defined(_MSC_VER))
#  define DELOG_COMPILER_MSVC 1
#else
#  define DELOG_COMPILER_MSVC 0
#endif

#if (defined(__GNUC__))
#  define DELOG_COMPILER_GCC 1
#else
#  define DELOG_COMPILER_GCC 0
#endif

#if (defined(__clang__) && (__clang__ == 1))
#  define DELOG_COMPILER_CLANG 1
#else
#  define DELOG_COMPILER_CLANG 0
#endif


#if (defined(_WIN32) || defined(_WIN64))
#  define DELOG_OS_WINDOWS 1
#else
#  define DELOG_OS_WINDOWS 0
#endif

#if (defined(__linux) || defined(__linux__))
#  define DELOG_OS_LINUX 1
#else
#  define DELOG_OS_LINUX 0
#endif

#if (defined(__APPLE__))
#  define DELOG_OS_MAC 1
#else
#  define DELOG_OS_MAC 0
#endif

#include <typeinfo>
#include <memory>
#include <ctime>
#include <sstream>
#include <chrono>


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

#if DELOG_OS_LINUX || DELOG_OS_MAC
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

    static Type s_default_color;

    // Only available in linux and mac os
    static std::unordered_map<Type, string_t> map; 

    static string_t default_color(string_t str)
    {
        string_t colored_str = map[s_default_color] + str + map[s_default_color];
        return colored_str;
    }

    static string_t red(string_t str)
    {
        string_t colored_str = map[RED] + str + map[s_default_color];
        return colored_str;
    }

    static string_t green(string_t str)
    {
        string_t colored_str = map[GREEN] + str + map[s_default_color];
        return colored_str;
    }

    static string_t yellow(string_t str)
    {
        string_t colored_str = map[YELLOW] + str + map[s_default_color];
        return colored_str;
    }

    static string_t blue(string_t str)
    {
        string_t colored_str = map[BLUE] + str + map[s_default_color];
        return colored_str;
    }
    static string_t magenta(string_t str)
    {
        string_t colored_str = map[MAGENTA] + str + map[s_default_color];
        return colored_str;
    }
    static string_t cyan(string_t str)
    {
        string_t colored_str = map[CYAN] + str + map[s_default_color];
        return colored_str;
    }
    static string_t white(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[WHITE] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        win_change_attributes( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
#endif // DELOG_OS_WINDOWS
        return colored_str;
    }

private:
#if DELOG_OS_WINDOWS
    inline void win_change_attributes(int foreground, int background = -1)
    {
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
#endif // DELOG_OS_WINDOWS
};

color::Type color::s_default_color = color::Type::CYAN;

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

#define RED(string) delog::color::red(string)
#define GREEN(string) delog::color::green(string)
#define YELLOW(string) delog::color::yellow(string)
#define BLUE(string) delog::color::blue(string)
#define MAGENTA(string) delog::color::magenta(string)
#define CYAN(string) delog::color::cyan(string)
#define WHITE(string) delog::color::white(string)
#define DEFAULT_COLOR(string) delog::color::default_color(string)



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
#if DELOG_COMPILER_GCC || DELOG_COMPILER_CLANG
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
    enum Measurement
    {
        HOUR,
        MINUTE,
        SECOND,
        MILLISECOND,
        MICROSECOND
    };

    Timer(const char* file, const char* func, size_t index, Measurement mt = MILLISECOND): 
        file_(file), func_(func), timer_idx_(index), mt_(mt){}

    void set_start_line(ulong_t line_num)
    {
        start_line_ = line_num;
    }

    void set_end_line(ulong_t line_num)
    {
        end_line_ = line_num;
    }

    string_t name()
    {
        return file_ + "-" + func_ + "-" + std::to_string(timer_idx_);
    }

    static string_t name(string_t file, string_t func, size_t index)
    {
        return file + "-" + func + "-" + std::to_string(index);
    }

    void start()
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    string_t elapse()
    {
        auto cur = std::chrono::high_resolution_clock::now();
        ulong_t c;
        string_t t;
        switch (mt_)
        {
        case HOUR:
            c = std::chrono::duration_cast<std::chrono::hours>(cur-start_).count();
            t = std::to_string(c) + "h";
            break;
        case MINUTE:
            c = std::chrono::duration_cast<std::chrono::minutes>(cur-start_).count();
            t = std::to_string(c) + "min";
            break;
        case SECOND:
            c = std::chrono::duration_cast<std::chrono::seconds>(cur-start_).count();
            t = std::to_string(c) + "s";
            break;
        case MILLISECOND:
            c = std::chrono::duration_cast<std::chrono::milliseconds>(cur-start_).count();
            t = std::to_string(c) + "ms";
            break;
        case MICROSECOND:
            c = std::chrono::duration_cast<std::chrono::microseconds>(cur-start_).count();
            t = std::to_string(c) + "us";
            break;
        default:
            c = std::chrono::duration_cast<std::chrono::milliseconds>(cur-start_).count();
            t = std::to_string(c) + "ms";
        }
        return t;
    }

    string_t record()
    {
        string_t time = elapse(); 
        char_t str[RECORD_MAX_LENGTH];
        sprintf(str, "[%s][%s][%s:%s:%d-%d]Timer: %d, Time-Cost: %s\n", Timer::datestamp().c_str(), Timer::timestamp().c_str(),
                                                    file_.c_str(), func_.c_str(), start_line_, end_line_, timer_idx_, time.c_str());
        return string_t(str);
    }

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
private:
    string_t file_;
    string_t func_;
    size_t timer_idx_;
    ulong_t start_line_;
    ulong_t end_line_;
    Measurement mt_;
    std::chrono::high_resolution_clock::time_point start_;
};


#define HOUR delog::Timer::Measurement::HOUR
#define MINUTE delog::Timer::Measurement::MINUTE
#define SECOND delog::Timer::Measurement::SECOND
#define MILLISECOND delog::Timer::Measurement::MILLISECOND
#define MICROSECOND delog::Timer::Measurement::MICROSECOND

class TimerPool
{
public:
    bool add(Timer* timer)
    {
        string_t timer_name = timer->name();
        if (pool_.find(timer_name) == pool_.end())
        {
            pool_[timer_name] = std::shared_ptr<Timer>(timer);
            return true;
        }
        else return false;
    }

    Timer* get(string_t name)
    {
        return pool_[name].get();
    }

private:
    std::unordered_map<string_t, std::shared_ptr<Timer>> pool_;
};

TimerPool timer_pool;

void start_timer(size_t index, Timer::Measurement m, const char_t* file, const char_t* func_name, ulong_t line_num)
{
    Timer* new_timer = new Timer(file, func_name, index, m);
    new_timer->set_start_line(line_num);
    timer_pool.add(new_timer);
    new_timer->start();
}

void stop_timer(size_t index, const char_t* file, const char_t* func_name, ulong_t line_num)
{
    string_t name = Timer::name(file, func_name, index);
    Timer* timer = timer_pool.get(name);
    timer->set_end_line(line_num);
    string_t record = timer->record();
    std::cout << record << std::endl;
}


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


inline string_t console_pause(const char_t* file, const ulong_t line, const char_t* func)
{
    std::cout << delog::record_format(file, line, func); 
    std::cout << "[PAUSED] Press ENTER to continue";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


#if (defined(DELOG_DISABLE_ALL))
#   define DELOG_DISABLE_LOG
#   define DELOG_DISABLE_PAUSE
#   define DELOG_DISABLE_TIMER
#endif // DELOG_DISABLE_ALL


#if (!defined(DELOG_DISABLE_LOG))
#  define DELOG_ENABLE_LOG 1
#else
#  define DELOG_ENABLE_LOG 0
#endif  // (!defined(DELOG_DISABLE_LOG))


#if (!defined(DELOG_DISABLE_PAUSE))
#  define DELOG_PAUSE 1
#else
#  define DELOG_PAUSE 0
#endif  // (!defined(DELOG_DISABLE_PAUSE))

#if (!defined(DELOG_DISABLE_TIMER))
#  define DELOG_TIMER 1
#else
#  define DELOG_TIMER 0
#endif  // (!defined(DELOG_DISABLE_TIMER))


#if DELOG_ENABLE_LOG
#   define DELOG(loggable, ...) \
    delog::record_format(__FILE__, __LINE__, __func__) + \
    delog::message(#loggable, loggable, ##__VA_ARGS__)
#else
#   define DELOG(loggable, ...) 
#endif // DELOG_ENABLE_LOG


#if DELOG_PAUSE
#   define PAUSE(...) delog::console_pause(__FILE__, __LINE__, __func__)
#else
#   define PAUSE(...) 
#endif // DELOG_PAUSE

#if DELOG_TIMER
#   define START_TIMER(idx, measurement) delog::start_timer(idx, measurement,  __FILE__, __func__, __LINE__)
#   define STOP_TIMER(idx) delog::stop_timer(idx, __FILE__, __func__, __LINE__)
#else
#   define START_TIMER(idx, measurement) 
#   define STOP_TIMER(idx) 
#endif // DELOG_TIMER


} // delog


#endif // DELOG_H
