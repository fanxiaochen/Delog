#ifndef DELOG_HPP
#define DELOG_HPP

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

#define __STDC_WANT_LIB_EXT1__ 1

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
#   include <cxxabi.h>
#endif

#if DELOG_OS_WINDOWS
#   include <windows.h>
#   include <versionhelpers.h>
#   include <stdio.h>
#   include <tchar.h>
#endif

#if DELOG_ENABLE_OPENCV
#   include <opencv2/core.hpp>
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

#if DELOG_OS_WINDOWS
//https://stackoverflow.com/questions/32193855/c-check-if-windows-10
typedef void (WINAPI * RtlGetVersion_FUNC) (OSVERSIONINFOEXW *);
BOOL GetWinVersion(OSVERSIONINFOEX * os) 
{
    HMODULE hMod;
    RtlGetVersion_FUNC func;
#ifdef UNICODE
    OSVERSIONINFOEXW * osw = os;
#else
    OSVERSIONINFOEXW o;
    OSVERSIONINFOEXW * osw = &o;
#endif

    hMod = LoadLibrary(TEXT("ntdll.dll"));
    if (hMod) 
    {
        func = (RtlGetVersion_FUNC)GetProcAddress(hMod, "RtlGetVersion");
        if (func == 0) {
            FreeLibrary(hMod);
            return FALSE;
        }
        ZeroMemory(osw, sizeof (*osw));
        osw->dwOSVersionInfoSize = sizeof (*osw);
        func(osw);
#ifndef UNICODE
        os->dwBuildNumber = osw->dwBuildNumber;
        os->dwMajorVersion = osw->dwMajorVersion;
        os->dwMinorVersion = osw->dwMinorVersion;
        os->dwPlatformId = osw->dwPlatformId;
        os->dwOSVersionInfoSize = sizeof (*os);
        DWORD sz = sizeof (os->szCSDVersion);
        WCHAR * src = osw->szCSDVersion;
        unsigned char * dtc = (unsigned char *)os->szCSDVersion;
        while (*src)
            * dtc++ = (unsigned char)* src++;
        *dtc = '\0';
#endif

    }
    else return FALSE;
    FreeLibrary(hMod);
    return TRUE;
}

static int_t win_major_number = 0;
static int_t win_minor_number = 0;
static int_t win_build_number = 0;

bool get_win_version() 
{
    if (win_major_number != 0) return true; 
    OSVERSIONINFOEX os;
    if (GetWinVersion(&os) == TRUE)
    {
        win_major_number = os.dwMajorVersion;
        win_minor_number = os.dwMinorVersion;
        win_build_number = os.dwBuildNumber;
        return true;
    }
    else return false;
}
#endif // DELOG_OS_WINDOWS


class Color
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
    static std::map<Type, string_t> map; 

    static string_t default_color(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[s_default_color] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        get_win_version();
//https://wpdev.uservoice.com/forums/266908-command-prompt-console-bash-on-ubuntu-on-windo/suggestions/6509361-provides-support-for-ansi-colors-like-in-bash
        if (win_major_number >= 10 && win_build_number >= 14931)
        {
            string_t colored_str = map[s_default_color] + str + map[s_default_color];
            return colored_str;
        }
        return str;
#endif // DELOG_OS_WINDOWS
    }

    static string_t red(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[RED] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        get_win_version();
        if (win_major_number >= 10 && win_build_number >= 14931)
        {
            string_t colored_str = map[RED] + str + map[s_default_color];
            return colored_str;
        }
        return str;
#endif // DELOG_OS_WINDOWS
    }

    static string_t green(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[GREEN] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        get_win_version();
        if (win_major_number >= 10 && win_build_number >= 14931)
        {
            string_t colored_str = map[GREEN] + str + map[s_default_color];
            return colored_str;
        }
        return str;
#endif // DELOG_OS_WINDOWS
    }

    static string_t yellow(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[YELLOW] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        get_win_version();
        if (win_major_number >= 10 && win_build_number >= 14931)
        {
            string_t colored_str = map[YELLOW] + str + map[s_default_color];
            return colored_str;
        }
        return str;
#endif // DELOG_OS_WINDOWS
    }

    static string_t blue(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[BLUE] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        get_win_version();
        if (win_major_number >= 10 && win_build_number >= 14931)
        {
            string_t colored_str = map[BLUE] + str + map[s_default_color];
            return colored_str;
        }
        return str;
#endif // DELOG_OS_WINDOWS
    }

    static string_t magenta(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[MAGENTA] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        get_win_version();
        if (win_major_number >= 10 && win_build_number >= 14931)
        {
            string_t colored_str = map[MAGENTA] + str + map[s_default_color];
            return colored_str;
        }
        return str;
#endif // DELOG_OS_WINDOWS
    }

    static string_t cyan(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[CYAN] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        get_win_version();
        if (win_major_number >= 10 && win_build_number >= 14931)
        {
            string_t colored_str = map[CYAN] + str + map[s_default_color];
            return colored_str;
        }
        return str;
#endif // DELOG_OS_WINDOWS
    }

    static string_t white(string_t str)
    {
#if DELOG_OS_LINUX || DELOG_OS_MAC
        string_t colored_str = map[WHITE] + str + map[s_default_color];
        return colored_str;
#elif DELOG_OS_WINDOWS
        get_win_version();
        if (win_major_number >= 10 && win_build_number >= 14931)
        {
            string_t colored_str = map[WHITE] + str + map[s_default_color];
            return colored_str;
        }
        return str;
#endif // DELOG_OS_WINDOWS
    }
};

Color::Type Color::s_default_color = Color::Type::CYAN;

std::map<Color::Type, string_t> Color::map = 
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

#define RED(string) delog::Color::red(string)
#define GREEN(string) delog::Color::green(string)
#define YELLOW(string) delog::Color::yellow(string)
#define BLUE(string) delog::Color::blue(string)
#define MAGENTA(string) delog::Color::magenta(string)
#define CYAN(string) delog::Color::cyan(string)
#define WHITE(string) delog::Color::white(string)
#define DEFAULT_COLOR(string) delog::Color::default_color(string)



typedef std::initializer_list<int_t>  Parameters;

struct ParameterList
{
    std::vector<int_t> v;
    ParameterList(Parameters parameters): v(parameters){}

    size_t size() const { return v.size(); }
    int_t operator[](size_t index) const { return v[index]; }
    void set(size_t index, int_t value) { v[index] = value; }
};

#if (!defined(DELOG_DISABLE_TYPE_LOG))
#  define DELOG_ENABLE_TYPE_LOG 1
#else
#  define DELOG_ENABLE_TYPE_LOG 0
#endif  // (!defined(DELOG_DISABLE_LOG))

#define GET_VARIABLE_NAME(Variable) (#Variable)

template <typename Type>
string_t GET_VARIABLE_TYPE(const Type& value)
{
    char_t* type = nullptr;
#if DELOG_COMPILER_GCC || DELOG_COMPILER_CLANG
    int status = 0;
    type = abi::__cxa_demangle(typeid(Type).name(), 0, 0, &status);
#else
    type = const_cast<char_t*>(typeid(Type).name());
#endif
    string_t str = string_t(type);
 //   free(type);
 #if DELOG_ENABLE_TYPE_LOG
    return str;
#else
    return "";
#endif
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

    Timer(const char_t* file, const char_t* func, size_t index, Measurement mt = MILLISECOND): 
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
        snprintf(str, RECORD_MAX_LENGTH, "[%s][%s][%s:%s:%ld-%ld]Timer: %ld, Time-Cost: %s\n", Timer::datestamp().c_str(), Timer::timestamp().c_str(),
                                                    file_.c_str(), func_.c_str(), start_line_, end_line_, timer_idx_, time.c_str());
        return string_t(str);
    }

    static string_t timestamp()
    {
        char_t str[9];

        // get the time, and convert it to struct tm format
        time_t a = time(0);
        struct tm b;
#if DELOG_COMPILER_MSVC
        localtime_s(&b, &a);
#else
        localtime_r(&a, &b);
#endif

        // print the time to the string
        strftime(str, 9, "%H:%M:%S", &b);

        return str;
    }

    static string_t datestamp()
    {
        char_t str[11];

        // get the time, and convert it to struct tm format
        time_t a = time(0);
        struct tm b;
#if DELOG_COMPILER_MSVC
        localtime_s(&b, &a);
#else
        localtime_r(&a, &b);
#endif

        // print the time to the string
        strftime(str, 11, "%Y-%m-%d", &b);

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

string_t stop_timer(size_t index, const char_t* file, const char_t* func_name, ulong_t line_num)
{
    string_t name = Timer::name(file, func_name, index);
    Timer* timer = timer_pool.get(name);
    timer->set_end_line(line_num);
    string_t record = timer->record();
    return record;
}


string_t basics_info(const char_t* file, const ulong_t line, const char_t* func)
{
    char_t str[RECORD_MAX_LENGTH];
    snprintf(str, RECORD_MAX_LENGTH, "[%s][%s][%s:%s:%ld]", Timer::datestamp().c_str(), Timer::timestamp().c_str(),
                                                file, func, line);
    return string_t(str);
}

static std::unordered_map<const char_t*, bool> default_basic_types({
    {typeid(char_t).name(),   1},
    {typeid(int_t).name(),    1},
    {typeid(long_t).name(),   1},
    {typeid(uchar_t).name(),  1},
    {typeid(uint_t).name(),   1},
    {typeid(ulong_t).name(),  1},
    {typeid(float_t).name(),  1},
    {typeid(double_t).name(), 1},
    {typeid(string_t).name(), 1},
});


namespace basics
{
/// Basic data type
static std::unordered_map<const char_t*, string_t> formats_verbose({ 
    {typeid(char_t).name(),   "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%c") + "%s"},
    {typeid(int_t).name(),    "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%d") + "%s"},
    {typeid(long_t).name(),   "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%d") + "%s"},
    {typeid(uchar_t).name(),  "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%c") + "%s"},
    {typeid(uint_t).name(),   "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%d") + "%s"},
    {typeid(ulong_t).name(),  "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%d") + "%s"},
    {typeid(float_t).name(),  "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%f") + "%s"},
    {typeid(double_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%f") + "%s"},
    {typeid(string_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%s") + "%s"},
});

static std::unordered_map<const char_t*, string_t> formats_simple({ 
    {typeid(char_t).name(),   "%s" + YELLOW("%c") + "%s"},
    {typeid(int_t).name(),    "%s" + YELLOW("%d") + "%s"},
    {typeid(long_t).name(),   "%s" + YELLOW("%d") + "%s"},
    {typeid(uchar_t).name(),  "%s" + YELLOW("%c") + "%s"},
    {typeid(uint_t).name(),   "%s" + YELLOW("%d") + "%s"},
    {typeid(ulong_t).name(),  "%s" + YELLOW("%d") + "%s"},
    {typeid(float_t).name(),  "%s" + YELLOW("%f") + "%s"},
    {typeid(double_t).name(), "%s" + YELLOW("%f") + "%s"},
    {typeid(string_t).name(), "%s" + YELLOW("%s") + "%s"},
});



class Primitive
{
public:
    Primitive(const string_t& log_prefix, const string_t& log_suffix): log_prefix_(log_prefix), log_suffix_(log_suffix){}

    template <typename Type>
    string_t generate(const char_t* name, const Type& value, const Parameters& args={})
    {
        // No parameters for basic types
        return build(log_prefix_.c_str(), log_suffix_.c_str(), name, value);
    }
private:
    template <typename Type>
    string_t build(const char_t* log_prefix, const char_t* log_suffix, const char_t* name, const Type& value)
    {
        string_t type = GET_VARIABLE_TYPE(value);
        char_t str[RECORD_MAX_LENGTH];
        if (!string_t(log_prefix).empty() && !string_t(log_suffix).empty())
            snprintf(str, RECORD_MAX_LENGTH, formats_verbose.at(typeid(Type).name()).c_str(), log_prefix, type.c_str(), name, value, log_suffix);
        else
            snprintf(str, RECORD_MAX_LENGTH, formats_simple.at(typeid(Type).name()).c_str(), log_prefix, value, log_suffix);
        return string_t(str); 
    }

    string_t build(const char_t* log_prefix, const char_t* log_suffix, const char_t* name, const string_t& value)
    {
        string_t type = GET_VARIABLE_TYPE(value);
        char_t str[RECORD_MAX_LENGTH];
        if (!string_t(log_prefix).empty() && !string_t(log_suffix).empty())
            snprintf(str, RECORD_MAX_LENGTH, formats_verbose.at(typeid(string_t).name()).c_str(), log_prefix, type.c_str(), name, value.c_str(), log_suffix);
        else
            snprintf(str, RECORD_MAX_LENGTH, formats_simple.at(typeid(string_t).name()).c_str(), log_prefix, value.c_str(), log_suffix);
        return string_t(str); 
    }
private:
    string_t log_prefix_;
    string_t log_suffix_;
};

}

#define REGISTER_BASICS(Type)                                                                                   \
template <typename... Args>                                                                                     \
string_t message(const string_t& prefix, const string_t& suffix, const char_t* name, const Type& type, const std::initializer_list<Args>&... args)              \
{                                                                                                               \
    return delog::basics::Primitive(prefix, suffix).generate(name, type, args...);                                            \
}                                                                                                               \
string_t message(const string_t& prefix, const string_t& suffix, const char_t* name, const Type& type, const Parameters& args)                                  \
{                                                                                                               \
    return delog::basics::Primitive(prefix, suffix).generate(name, type, args);                                               \
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

namespace pointer
{
namespace formats
{
template <typename Type>
string_t format(const char_t* log_prefix, const char_t* log_suffix, const char_t* name, const Type* type, const ParameterList& type_args)
{
    auto format_simple = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t start = type_args[0];                   
        size_t end = type_args[1];                     
        for (size_t i = start; i <= end; ++ i)              
        {                                                   
            ss << delog::message("", "", ("var["+std::to_string(i)+"]").c_str(), type[i], {}); 
            if (i != end) ss << " ";
        }                                                   
        ss << "]" << log_suffix;
        return ss.str();                                    
    };

    return format_simple();
}
} // formats


class Primitive
{
public:
    Primitive(const string_t& log_prefix, const string_t& log_suffix): log_prefix_(log_prefix), log_suffix_(log_suffix){}

    template <typename Type>
    string_t generate(const char_t* name, const Type* value, const Parameters& args={})
    {
        ParameterList args_list = ParameterList(args);
        ParameterList args_default = {0, 0}; 

        for (size_t i = 0; i < args_list.size(); ++ i) 
        {
            args_default.set(i, args_list[i]);
        }
        
        return formats::format(log_prefix_.c_str(), log_suffix_.c_str(), name, value, args_default);
    }
private:
    string_t log_prefix_;
    string_t log_suffix_;
};

} // pointer

#define REGISTER_POINTERS(Type)                                                           \
template <typename... Args>                                                                                     \
string_t message(const string_t& prefix, const string_t& suffix, const char_t* name, const Type* type, const std::initializer_list<Args>&... args)              \
{                                                                                                               \
    return delog::pointer::Primitive(prefix, suffix).generate(name, type, args...);                                            \
}                                                                                                               \
string_t message(const string_t& prefix, const string_t& suffix,const char_t* name, const Type* type, const Parameters& args)                   \
{                                                                                                \
    return delog::pointer::Primitive(prefix, suffix).generate(name, type, args);                               \
}

REGISTER_POINTERS(int_t)
REGISTER_POINTERS(long_t)
REGISTER_POINTERS(char_t)
REGISTER_POINTERS(uint_t)
REGISTER_POINTERS(ulong_t)
REGISTER_POINTERS(uchar_t)
REGISTER_POINTERS(float_t)
REGISTER_POINTERS(double_t)
REGISTER_POINTERS(string_t)

#if DELOG_ENABLE_OPENCV
namespace opencv
{
namespace formats
{
string_t format_mat(const char_t* name, const cv::Mat& type, const Parameters& type_args)
{
    auto access_by_type = [&](size_t i, size_t j)
    {
        switch (type.type())
        {
        case CV_8U:
            return type.at<uchar_t>(i, j);
        case CV_8S:
            return type.at<short_t>(i, j);
        case CV_16U:
            return type.at<uchar_t>(i, j);
        case CV_16S:
            return type.at<uchar_t>(i, j);
        case CV_32S:
            return type.at<int_t>(i, j);
        case CV_32F:
            return type.at<float_t>(i, j);
        case CV_32F:
            return type.at<long_t>(i, j);
        default:
            break;
        }
    };
    
    string_t type_str = GET_VARIABLE_TYPE(type);            
    size_t start_row = type_args[0];                   
    size_t start_col = type_args[1];                     
    size_t block_rows = type_args[2];                   
    size_t block_cols = type_args[3];                     

    std::stringstream ss;                               
    ss << string_t("Name: ") << GREEN(name) << "\n";        
    ss << string_t("Type: ") << MAGENTA(type_str) << "\n";         
    ss << string_t("Rows: ") << type.rows << "\n";             
    ss << string_t("Cols: ") << type.cols << "\n";             
    ss << string_t("Start Row: ") << start_row << "\n";             
    ss << string_t("Start Col: ") << start_col << "\n";             
    ss << string_t("Block Rows: ") << block_rows << "\n";             
    ss << string_t("Block Cols: ") << block_cols << "\n";             

    ss << string_t("<---------------->") << "\n";              

    for (size_t i = start_row; i < block_rows; ++ i)              
    {                                                   
        for (size_t j = start_col; j < block_cols; ++ j)              
        {
            ss << access_by_type(i, j) << " "; 
        }
        ss << "\n"; 
    }                                                   
    ss << string_t("<---------------->") << "\n";              

    return ss.str();                                    
}
} // formats

class Primitive
{
public:
    string_t generate(const char_t* name, const cv::Mat& value, const Parameters& args={})
    {
        ParameterList args_list = ParameterList(args);
        ParameterList args_default = {0, 0, value.rows, values.cols}; 

        for (size_t i = 0; i < args_list.size(); ++ i) 
        {
            args_default.set(i, args_list[i]);
        }
        
        return formats::format_mat(name, value, args_default);
    }
};

} // opencv

#define REGISTER_OPENCV_MAT(Type)                                                                \
string_t message(const char_t* name, const Type& type, const Parameters& args)                   \
{                                                                                                \
    return delog::opencv::Primitive().generate(name, type, args);                                \
}

REGISTER_OPENCV_MAT(cv::Mat)

#endif // DELOG_ENABLE_OPENCV

namespace stl
{
namespace basics
{
namespace formats
{
template <typename Type1, typename Type2>
string_t format_pair(const char_t* log_prefix, const char_t* log_suffix, const char_t* name, const std::pair<Type1, Type2>& type, const Parameters& type2_args)
{
    auto format_simple = [&]()
    {
        std::stringstream ss;                               
        ss << "(" << delog::message("", "", "pair.first", type.first, {}) << ","; 
        ss << delog::message("", "", "pair.second", type.second, {}) << ")"; 
        return ss.str();
    };

    auto format_complex = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "(" << delog::message("", "", "pair.first", type.first, {}) << ","; 
        ss << delog::message("", "", "pair.second", type.second, {}) << ")"; 
        ss << log_suffix;
        return ss.str();
    };

    auto format_verbose = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;        
        ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;         
        ss << log_prefix << string_t("First:") << log_suffix;            
        ss << log_prefix << "{" << log_suffix; 
        ss << delog::message(log_prefix, log_suffix, "pair.first", type.first, {}); 
        ss << log_prefix << "}" << log_suffix; 
        ss << log_prefix << string_t("Second:") << log_suffix;            
        ss << log_prefix << "{" << log_suffix; 
        ss << delog::message(log_prefix, log_suffix, "pair.second", type.second, type2_args); 
        ss << log_prefix << "}" << log_suffix; 
        return ss.str();
    };
    
    if (default_basic_types.find(typeid(Type1).name()) != default_basic_types.end() && 
        default_basic_types.find(typeid(Type2).name()) != default_basic_types.end())
        {
            if (!string_t(log_prefix).empty() && !string_t(log_suffix).empty())
                return format_complex();
            else
                return format_simple();
        }
    else
        return format_verbose();
}

} // formats


class Primitive
{
public:
    Primitive(const string_t& log_prefix, const string_t& log_suffix): log_prefix_(log_prefix), log_suffix_(log_suffix){}
    // pair
    template <typename Type1, typename Type2>
    string_t generate(const char_t* name, const std::pair<Type1, Type2>& value, const Parameters& type2_args={})
    {
        return build(log_prefix_.c_str(), log_suffix_.c_str(), name, value, type2_args);
    }
private:
    template <typename Type1, typename Type2>
    string_t build(const char_t* log_prefix, const char_t* log_suffix, const char_t* name, const std::pair<Type1, Type2>& type, const Parameters& type2_args)
    {
        return formats::format_pair(log_prefix, log_suffix, name, type, type2_args);
    }
private:
    string_t log_prefix_;
    string_t log_suffix_;
};

} // basics 
} // stl


#define REGISTER_STL_BASICS_TWO_PARAMETER(ContainerType)                                                                    \
template <typename T1, typename T2, typename... Args>                                                                       \
string_t message(const string_t& prefix, const string_t& suffix, const char_t* name, const ContainerType<T1,T2>& type, const std::initializer_list<Args>&... args)          \
{                                                                                                                           \
    return delog::stl::basics::Primitive(prefix, suffix).generate(name, type, args...);                                                   \
}                                                                                                                           \
template <typename T1, typename T2>                                                                                         \
string_t message(const string_t& prefix, const string_t& suffix, const char_t* name, const ContainerType<T1,T2>& type, const Parameters& type2_args)                        \
{                                                                                                                           \
    return delog::stl::basics::Primitive(prefix, suffix).generate(name, type, type2_args);                                                \
}                                                                                  

REGISTER_STL_BASICS_TWO_PARAMETER(std::pair)

namespace stl
{
namespace container
{
namespace formats
{
template <typename Type>
string_t format_range(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const Type& type, const ParameterList& container_args, const Parameters& type_args)
{
    auto format_simple = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t start = container_args[0];                   
        size_t end = container_args[1];                     
        for (size_t i = start; i <= end; ++ i)              
        {                                                   
            ss << delog::message("", "", ("var["+std::to_string(i)+"]").c_str(), type[i], type_args); 
            if (i != end) ss << " ";
        }                                                   
        ss << "]" << log_suffix;
        return ss.str();                                    
    };

    auto format_verbose = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;        
        ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;         
        ss << log_prefix << string_t("Length: ") << type.size() << log_suffix;              
        size_t start = container_args[0];                   
        size_t end = container_args[1];                     
        for (size_t i = start; i <= end; ++ i)              
        {                                                   
            ss << log_prefix << "<--[" << i << "]-->" << log_suffix;                  
            ss << log_prefix << "{" << log_suffix;
            ss << delog::message(log_prefix, log_suffix, ("var["+std::to_string(i)+"]").c_str(), type[i], type_args); 
            ss << log_prefix << "}" << log_suffix;
        }                                                   
        return ss.str();                                    
    };

    if (default_basic_types.find(typeid(type[0]).name()) != default_basic_types.end())
        return format_simple();
    else
        return format_verbose();
}

template <typename Type1, typename Type2>
string_t format_iterator(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::map<Type1, Type2>& type, const ParameterList& container_args, const Parameters& type_args)
{
    auto format_simple = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t length = container_args[0];                   
        auto itr = type.begin();
        size_t count = 0;
        for (auto itr = type.begin(); itr != type.end(); ++ itr)
        {
            ss << delog::message("", "", ("var["+std::to_string(count)+"]").c_str(), *itr, type_args); 
            count ++;
            if (count == length) 
                break;
            else ss << " ";
        }
        ss << "]" << log_suffix;
        return ss.str();                                    
    };

    auto format_verbose = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;        
        ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;         
        ss << log_prefix << string_t("Length: ") << type.size() << log_suffix;              
        size_t length = container_args[0];                   

        auto itr = type.begin();
        size_t count = 0;
        for (auto itr = type.begin(); itr != type.end(); ++ itr)
        {
            if (count == length) break;
            ss << log_prefix << "<--[" << count << "]-->" << log_suffix;                 
            ss << log_prefix << "{" << log_suffix;
            ss << delog::message(log_prefix, log_suffix, ("var["+std::to_string(count)+"]").c_str(), *itr, type_args);
            ss << log_prefix << "}" << log_suffix;
            count ++;
        }
        return ss.str();                                    
    };

    if (default_basic_types.find(typeid(Type1).name()) != default_basic_types.end() && 
        default_basic_types.find(typeid(Type2).name()) != default_basic_types.end())
        return format_simple();
    else
        return format_verbose();
}

template <typename Type1, typename Type2>
string_t format_iterator(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::unordered_map<Type1, Type2>& type, const ParameterList& container_args, const Parameters& type_args)
{
    auto format_simple = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t length = container_args[0];                   
        auto itr = type.begin();
        size_t count = 0;
        for (auto itr = type.begin(); itr != type.end(); ++ itr)
        {
            ss << delog::message("", "", ("var["+std::to_string(count)+"]").c_str(), *itr, type_args); 
            count ++;
            if (count == length) 
                break;
            else ss << " ";
        }
        ss << "]" << log_suffix;
        return ss.str();                                    
    };

    auto format_verbose = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;        
        ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;         
        ss << log_prefix << string_t("Length: ") << type.size() << log_suffix;              
        size_t length = container_args[0];                   

        auto itr = type.begin();
        size_t count = 0;
        for (auto itr = type.begin(); itr != type.end(); ++ itr)
        {
            if (count == length) break;
            ss << log_prefix << "<--[" << count << "]-->" << log_suffix;                 
            ss << log_prefix << "{" << log_suffix;
            ss << delog::message(log_prefix, log_suffix, ("var["+std::to_string(count)+"]").c_str(), *itr, type_args);
            ss << log_prefix << "}" << log_suffix;
            count ++;
        }
        return ss.str();                                    
    };

    if (default_basic_types.find(typeid(Type1).name()) != default_basic_types.end() && 
        default_basic_types.find(typeid(Type2).name()) != default_basic_types.end())
        return format_simple();
    else
        return format_verbose();
}

template <typename Type>
string_t format_iterator(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const Type& type, const ParameterList& container_args, const Parameters& type_args)
{
    auto format_simple = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t length = container_args[0];                   
        auto itr = type.begin();
        size_t count = 0;
        for (auto itr = type.begin(); itr != type.end(); ++ itr)
        {
            ss << delog::message("", "", ("var["+std::to_string(count)+"]").c_str(), *itr, type_args); 
            count ++;
            if (count == length) 
                break;
            else ss << " ";
        }
        ss << "]" << log_suffix;
        return ss.str();                                    
    };

    auto format_verbose = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;        
        ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;         
        ss << log_prefix << string_t("Length: ") << type.size() << log_suffix;              
        size_t length = container_args[0];                   

        auto itr = type.begin();
        size_t count = 0;
        for (auto itr = type.begin(); itr != type.end(); ++ itr)
        {
            if (count == length) break;
            ss << log_prefix << "<--[" << count << "]-->" << log_suffix;                 
            ss << log_prefix << "{" << log_suffix;
            ss << delog::message(log_prefix, log_suffix, ("var["+std::to_string(count)+"]").c_str(), *itr, type_args);
            ss << log_prefix << "}" << log_suffix;
            count ++;
        }
        return ss.str();                                    
    };

    if (default_basic_types.find(typeid(*(type.begin())).name()) != default_basic_types.end())
        return format_simple();
    else
        return format_verbose();
}


template <typename Type>
string_t format_stack(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const Type& type, const ParameterList& container_args, const Parameters& type_args)
{
    auto format_simple = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t length = container_args[0];                   

        Type copied = type;
        size_t count = 0;
        while (!copied.empty())
        {
            ss << delog::message("", "", ("var["+std::to_string(count)+"]").c_str(), copied.top(), type_args); 
            copied.pop();
            count ++;
            if (count == length) break;
            else ss << " ";
        }
        ss << "]" << log_suffix;
        return ss.str();                                    
    };

    auto format_verbose = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;        
        ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;         
        ss << log_prefix << string_t("Length: ") << type.size() << log_suffix;              
        size_t length = container_args[0];                   

        Type copied = type;
        size_t count = 0;
        while (!copied.empty())
        {
            if (count == length) break;
            ss << log_prefix << "<--[" << count << "]-->" << log_suffix;                 
            ss << log_prefix << "{" << log_suffix;
            ss << delog::message(log_prefix, log_suffix, ("var["+std::to_string(count)+"]").c_str(), copied.top(), type_args); 
            ss << log_prefix << "}" << log_suffix;
            copied.pop();
            count ++;
        }
        return ss.str();                                    
    };

    if (default_basic_types.find(typeid(type.top()).name()) != default_basic_types.end())
        return format_simple();
    else
        return format_verbose();
}

template <typename Type>
string_t format_queue(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const Type& type, const ParameterList& container_args, const Parameters& type_args)
{
    auto format_simple = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t length = container_args[0];                   

        Type copied = type;
        size_t count = 0;
        while (!copied.empty())
        {
            ss << delog::message("", "", ("var["+std::to_string(count)+"]").c_str(), copied.front(), type_args); 
            copied.pop();
            count ++;
            if (count == length) break;
            else ss << " ";
        }
        ss << "]" << log_suffix;
        return ss.str();                                    
    };

    auto format_verbose = [&]()
    {
        string_t type_str = GET_VARIABLE_TYPE(type);            
        std::stringstream ss;                               
        ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;        
        ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;         
        ss << log_prefix << string_t("Length: ") << type.size() << log_suffix;              
        size_t length = container_args[0];                   

        Type copied = type;
        size_t count = 0;
        while (!copied.empty())
        {
            if (count == length) break;
            ss << log_prefix << "<--[" << count << "]-->" << log_suffix;                 
            ss << log_prefix << "{" << log_suffix;
            ss << delog::message(log_prefix, log_suffix, ("var["+std::to_string(count)+"]").c_str(), copied.front(), type_args); 
            ss << log_prefix << "}" << log_suffix;
            copied.pop();
            count ++;
        }
        return ss.str();                                    
    };

    if (default_basic_types.find(typeid(type.front()).name()) != default_basic_types.end())
        return format_simple();
    else
        return format_verbose();
}


template <typename Type>
ParameterList parameters_to_range(const Type& type, const Parameters& container_args)
{
    ParameterList cargs = ParameterList(container_args);
    ParameterList cargs_default({0, (int)type.size()-1});

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
    ParameterList cargs_default({(int)type.size()});

    for (size_t i = 0; i < cargs.size(); ++ i) 
    {
        if (cargs[i] >= 0 && cargs[i] <= type.size())
            cargs_default.set(i, cargs[i]);
    }

    return cargs_default;
}

} // formats


class Primitive
{
public:
    Primitive(const string_t& log_prefix, const string_t& log_suffix): log_prefix_(log_prefix), log_suffix_(log_suffix){}

    // vector, list, deque, stack, queue
    template <template<typename, typename> class Container, typename Type1, typename Type2>
    string_t generate(const char_t* name, const Container<Type1, Type2>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(log_prefix_.c_str(), log_suffix_.c_str(), name, value, container_args, type_args);
    }

    // set
    template <template<typename, typename, typename> class Container, typename Type1, typename Type2, typename Type3>
    string_t generate(const char_t* name, const Container<Type1, Type2, Type3>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(log_prefix_.c_str(), log_suffix_.c_str(), name, value, container_args, type_args);
    }

    // unordered_set, map
    template <template<typename, typename, typename, typename> class Container, typename Type1, typename Type2, typename Type3, typename Type4>
    string_t generate(const char_t* name, const Container<Type1, Type2, Type3, Type4>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(log_prefix_.c_str(), log_suffix_.c_str(), name, value, container_args, type_args);
    }

    // unordered_map
    template <template<typename, typename, typename, typename, typename> class Container, typename Type1, typename Type2, typename Type3, typename Type4, typename Type5>
    string_t generate(const char_t* name, const Container<Type1, Type2, Type3, Type4, Type5>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(log_prefix_.c_str(), log_suffix_.c_str(), name, value, container_args, type_args);
    }

    // array 
    template <typename Type, size_t N>
    string_t generate(const char_t* name, const std::array<Type, N>& value, const Parameters& container_args={}, const Parameters& type_args={})
    {
        return build(log_prefix_.c_str(), log_suffix_.c_str(), name, value, container_args, type_args);
    }

private:
    template <typename Type>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::vector<Type>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_range(type, container_args);
        return formats::format_range(log_prefix, log_suffix, name, type, cargs, type_args);
    }

    template <typename Type>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::deque<Type>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_range(type, container_args);
        return formats::format_range(log_prefix, log_suffix,name, type, cargs, type_args);
    }

    template <typename Type, size_t N>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::array<Type, N>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_range(type, container_args);
        return formats::format_range(log_prefix, log_suffix,name, type, cargs, type_args);
    }

    template <typename Type>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::list<Type>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_length(type, container_args);
        return formats::format_iterator(log_prefix, log_suffix,name, type, cargs, type_args);
    }

    template <typename Type>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::set<Type>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_length(type, container_args);
        return formats::format_iterator(log_prefix, log_suffix,name, type, cargs, type_args);
    }

    template <typename Type>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::unordered_set<Type>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_length(type, container_args);
        return formats::format_iterator(log_prefix, log_suffix,name, type, cargs, type_args);
    }

    template <typename Type1, typename Type2>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::map<Type1, Type2>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_length(type, container_args);
        return formats::format_iterator(log_prefix, log_suffix,name, type, cargs, type_args);
    }

    template <typename Type1, typename Type2>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::unordered_map<Type1, Type2>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_length(type, container_args);
        return formats::format_iterator(log_prefix, log_suffix,name, type, cargs, type_args);
    }

    template <typename Type>
    string_t build(const char_t* log_prefix, const char_t* log_suffix,const char_t* name, const std::stack<Type>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_length(type, container_args);
        return formats::format_stack(log_prefix, log_suffix,name, type, cargs, type_args);
    }

    template <typename Type>
    string_t build(const char_t* log_prefix, const char_t* log_suffix, const char_t* name, const std::queue<Type>& type, const Parameters& container_args, const Parameters& type_args)
    {
        auto cargs = formats::parameters_to_length(type, container_args);
        return formats::format_queue(log_prefix, log_suffix,name, type, cargs, type_args);
    }


private:
    string_t log_prefix_;
    string_t log_suffix_;
};
} // container
} // stl



#define REGISTER_STL_CONTAINER_ONE_PARAMETER(ContainerType)                                                                                     \
template <typename Type, typename... Args>                                                                                                      \
string_t message(const string_t& prefix, const string_t& suffix, const char_t* name, const ContainerType<Type>& type, const std::initializer_list<Args>&... args)                               \
{                                                                                                                                               \
    return delog::stl::container::Primitive(prefix, suffix).generate(name, type, args...);                                                                    \
}                                                                                                                                               \
template <typename Type>                                                                                                                        \
string_t message(const string_t& prefix, const string_t& suffix,const char_t* name, const ContainerType<Type>& type, const Parameters& container_args, const Parameters& type_args)            \
{                                                                                                                                               \
    return delog::stl::container::Primitive(prefix, suffix).generate(name, type, container_args, type_args);                                                  \
}

#define REGISTER_STL_CONTAINER_TWO_PARAMETER(ContainerType)                                                                                     \
template <typename T1, typename T2, typename... Args>                                                                                           \
string_t message(const string_t& prefix, const string_t& suffix,const char_t* name, const ContainerType<T1,T2>& type, const std::initializer_list<Args>&... args)                              \
{                                                                                                                                               \
    return delog::stl::container::Primitive(prefix, suffix).generate(name, type, args...);                                                                    \
}                                                                                                                                               \
template <typename T1, typename T2>                                                                                                             \
string_t message(const string_t& prefix, const string_t& suffix,const char_t* name, const ContainerType<T1,T2>& type, const Parameters& container_args, const Parameters& type_args)           \
{                                                                                                                                               \
    return delog::stl::container::Primitive(prefix, suffix).generate(name, type, container_args, type_args);                                                  \
}                                                                                  

#define REGISTER_STL_CONTAINER_TWO_PARAMETER_WITH_N(ContainerType)                                                                              \
template <typename T1, size_t N, typename... Args>                                                                                              \
string_t message(const string_t& prefix, const string_t& suffix,const char_t* name, const ContainerType<T1,N>& type, const std::initializer_list<Args>&... args)                               \
{                                                                                                                                               \
    return delog::stl::container::Primitive(prefix, suffix).generate(name, type, args...);                                                                    \
}                                                                                                                                               \
template <typename T1, size_t N>                                                                                                                \
string_t message(const string_t& prefix, const string_t& suffix,const char_t* name, const ContainerType<T1,N>& type, const Parameters& container_args, const Parameters& type_args)            \
{                                                                                                                                               \
    return delog::stl::container::Primitive(prefix, suffix).generate(name, type, container_args, type_args);                                                  \
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


void console_pause(const char_t* file, const ulong_t line, const char_t* func)
{
    std::cout << delog::basics_info(file, line, func); 
    std::cout << "[PAUSED] Press ENTER to continue";
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}


//#ifdef DELOG_ENABLE_EIGEN
//#include "eigen.hpp"
//#endif


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
#  define DELOG_ENABLE_PAUSE 1
#else
#  define DELOG_ENABLE_PAUSE 0
#endif  // (!defined(DELOG_DISABLE_PAUSE))

#if (!defined(DELOG_DISABLE_TIMER))
#  define DELOG_ENABLE_TIMER 1
#else
#  define DELOG_ENABLE_TIMER 0
#endif  // (!defined(DELOG_DISABLE_TIMER))


//#if DELOG_ENABLE_LOG
//#   define DELOG(loggable, ...) \
//    std::cout << DEFAULT_COLOR("")+(delog::basics_info(__FILE__, __LINE__, __func__) + delog::message(#loggable, loggable, ##__VA_ARGS__))
//#else
//#   define DELOG(loggable, ...) 
//#endif // DELOG_ENABLE_LOG

#if DELOG_ENABLE_LOG
#   define DELOG(loggable, ...) \
    std::cout << DEFAULT_COLOR("") + delog::message(delog::basics_info(__FILE__, __LINE__, __func__), delog::string_t("\n"), #loggable, loggable, ##__VA_ARGS__)
#else
#   define DELOG(loggable, ...) 
#endif // DELOG_ENABLE_LOG


#if DELOG_ENABLE_PAUSE
#   define PAUSE(...) delog::console_pause(__FILE__, __LINE__, __func__)
#else
#   define PAUSE(...) 
#endif // DELOG_PAUSE

#if DELOG_ENABLE_TIMER
#   define START_TIMER(idx, measurement) delog::start_timer(idx, measurement,  __FILE__, __func__, __LINE__)
#   define STOP_TIMER(idx) std::cout << delog::stop_timer(idx, __FILE__, __func__, __LINE__)
#else
#   define START_TIMER(idx, measurement) 
#   define STOP_TIMER(idx) 
#endif // DELOG_TIMER


} // delog


#endif // DELOG_HPP
