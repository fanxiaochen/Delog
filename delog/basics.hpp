#include "delog/delog.hpp"

namespace delog
{
static std::unordered_map<const char_t *, bool> default_basic_types({
    {typeid(char_t).name(), 1},
    {typeid(int_t).name(), 1},
    {typeid(long_t).name(), 1},
    {typeid(short_t).name(), 1},
    {typeid(uchar_t).name(), 1},
    {typeid(uint_t).name(), 1},
    {typeid(ulong_t).name(), 1},
    {typeid(ushort_t).name(), 1},
    {typeid(float_t).name(), 1},
    {typeid(double_t).name(), 1},
    {typeid(string_t).name(), 1},
});

namespace basics
{
/// Basic data type
static std::unordered_map<const char_t *, string_t> formats_verbose({
    {typeid(char_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%c") + "%s"},
    {typeid(int_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%d") + "%s"},
    {typeid(long_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%ld") + "%s"},
    {typeid(short_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%d") + "%s"},
    {typeid(uchar_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%c") + "%s"},
    {typeid(uint_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%u") + "%s"},
    {typeid(ulong_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%lu") + "%s"},
    {typeid(ushort_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%u") + "%s"},
    {typeid(float_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%f") + "%s"},
    {typeid(double_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%lf") + "%s"},
    {typeid(string_t).name(), "%s" + MAGENTA("%s") + " " + GREEN("%s") + " = " + YELLOW("%s") + "%s"},
});

static std::unordered_map<const char_t *, string_t> formats_simple({
    {typeid(char_t).name(), "%s" + YELLOW("%c") + "%s"},
    {typeid(int_t).name(), "%s" + YELLOW("%d") + "%s"},
    {typeid(long_t).name(), "%s" + YELLOW("%ld") + "%s"},
    {typeid(short_t).name(), "%s" + YELLOW("%d") + "%s"},
    {typeid(uchar_t).name(), "%s" + YELLOW("%c") + "%s"},
    {typeid(uint_t).name(), "%s" + YELLOW("%u") + "%s"},
    {typeid(ulong_t).name(), "%s" + YELLOW("%lu") + "%s"},
    {typeid(ushort_t).name(), "%s" + YELLOW("%u") + "%s"},
    {typeid(float_t).name(), "%s" + YELLOW("%f") + "%s"},
    {typeid(double_t).name(), "%s" + YELLOW("%lf") + "%s"},
    {typeid(string_t).name(), "%s" + YELLOW("%s") + "%s"},
});

class Primitive
{
public:
    Primitive(const string_t &log_prefix, const string_t &log_suffix) : log_prefix_(log_prefix), log_suffix_(log_suffix) {}

    template <typename Type>
    string_t generate(const char_t *name, const Type &value, const Parameters &args = {})
    {
        // No parameters for basic types
        return build(log_prefix_.c_str(), log_suffix_.c_str(), name, value);
    }

private:
    template <typename Type>
    string_t build(const char_t *log_prefix, const char_t *log_suffix, const char_t *name, const Type &value)
    {
        string_t type = GET_VARIABLE_TYPE(value);
        char_t str[RECORD_MAX_LENGTH];
        if (!string_t(log_prefix).empty() && !string_t(log_suffix).empty())
            snprintf(str, RECORD_MAX_LENGTH, formats_verbose.at(typeid(Type).name()).c_str(), log_prefix, type.c_str(), name, value, log_suffix);
        else
            snprintf(str, RECORD_MAX_LENGTH, formats_simple.at(typeid(Type).name()).c_str(), log_prefix, value, log_suffix);
        return string_t(str);
    }

    string_t build(const char_t *log_prefix, const char_t *log_suffix, const char_t *name, const string_t &value)
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

} // namespace basics

#define REGISTER_BASICS(Type)                                                                                                                           \
    template <typename... Args>                                                                                                                         \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Type &type, const std::initializer_list<Args> &... args) \
    {                                                                                                                                                   \
        return delog::basics::Primitive(prefix, suffix).generate(name, type, args...);                                                                  \
    }                                                                                                                                                   \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Type &type, const Parameters &args)                      \
    {                                                                                                                                                   \
        return delog::basics::Primitive(prefix, suffix).generate(name, type, args);                                                                     \
    }

REGISTER_BASICS(int_t)
REGISTER_BASICS(long_t)
REGISTER_BASICS(short_t)
REGISTER_BASICS(char_t)
REGISTER_BASICS(uint_t)
REGISTER_BASICS(ulong_t)
REGISTER_BASICS(ushort_t)
REGISTER_BASICS(uchar_t)
REGISTER_BASICS(float_t)
REGISTER_BASICS(double_t)
REGISTER_BASICS(string_t)

namespace pointer
{
namespace formats
{
template <typename Type>
string_t format(const char_t *log_prefix, const char_t *log_suffix, const char_t *name, const Type *type, const ParameterList &type_args)
{
    auto format_simple = [&]() {
        string_t type_str = GET_VARIABLE_TYPE(type);
        std::stringstream ss;
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t start = type_args[0];
        size_t end = type_args[1];
        for (size_t i = start; i <= end; ++i)
        {
            ss << delog::message("", "", ("var[" + std::to_string(i) + "]").c_str(), type[i], {});
            if (i != end)
                ss << " ";
        }
        ss << "]" << log_suffix;
        return ss.str();
    };

    return format_simple();
}
} // namespace formats

class Primitive
{
public:
    Primitive(const string_t &log_prefix, const string_t &log_suffix) : log_prefix_(log_prefix), log_suffix_(log_suffix) {}

    template <typename Type>
    string_t generate(const char_t *name, const Type *value, const Parameters &args = {})
    {
        ParameterList args_list = ParameterList(args);
        ParameterList args_default = {0, 0};

        for (size_t i = 0; i < args_list.size(); ++i)
        {
            args_default.set(i, args_list[i]);
        }

        return formats::format(log_prefix_.c_str(), log_suffix_.c_str(), name, value, args_default);
    }

private:
    string_t log_prefix_;
    string_t log_suffix_;
};

} // namespace pointer

#define REGISTER_POINTERS(Type)                                                                                                                         \
    template <typename... Args>                                                                                                                         \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Type *type, const std::initializer_list<Args> &... args) \
    {                                                                                                                                                   \
        return delog::pointer::Primitive(prefix, suffix).generate(name, type, args...);                                                                 \
    }                                                                                                                                                   \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Type *type, const Parameters &args)                      \
    {                                                                                                                                                   \
        return delog::pointer::Primitive(prefix, suffix).generate(name, type, args);                                                                    \
    }

REGISTER_POINTERS(int_t)
REGISTER_POINTERS(long_t)
REGISTER_POINTERS(short_t)
REGISTER_POINTERS(char_t)
REGISTER_POINTERS(uint_t)
REGISTER_POINTERS(ulong_t)
REGISTER_POINTERS(ushort_t)
REGISTER_POINTERS(uchar_t)
REGISTER_POINTERS(float_t)
REGISTER_POINTERS(double_t)
REGISTER_POINTERS(string_t)
} // namespace delog