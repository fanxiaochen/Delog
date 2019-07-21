#ifndef DELOG_H
#define DELOG_H

namespace delog
{
typedef char char_t;
typedef int int_t;
typedef float float_t;
typedef double double_t;

enum class LogType
{
    UNDEFINED = 0,
    STRING = 1,
    VARIABLE = 2,
    CLASS = 4
};

class LogValue
{
public:
    LogValue(LogType type): type_(type) {}
    LogType type() const { return type_; }
    virtual char_t* toLog() = 0;
protected:
    LogType type_;
};

template <typename String>
class LogString: public LogValue
{
public:
    LogString():LogValue(LogType::STRING){}
    char_t* toLog() { return string_.toLog(); }
private:
    String string_;
};

template <typename Variable>
class LogVariable: public LogValue
{
public:
    LogVariable():LogValue(LogType::VARIABLE){}
    char_t* toLog() { return variable_.toLog(); }
private:
    Variable variable_;
};

template <typename Class>
class LogClass: public LogValue
{
public:
    LogClass():LogValue(LogType::CLASS){}
    char_t* toLog() { return class_.toLog(); }
private:
    Class class_;
};


template <typename ...Args>
class Loggable
{
public:
    virtual LogType type() const { return LogType::UNDEFINED; }
    virtual char_t* build(const Args& ...) = 0;
};

template <typename ...Args>
class LogString: public Loggable<...Args>
{
    virtual LogType type() const { return LogType::STRING; }
};

template <typename ...Args>
class LogVariable: public Loggable<...Args>
{
    virtual LogType type() const { return LogType::VARIABLE; }
};

template <typename ...Args>
class LogClass: public Loggable<...Args>
{
    virtual LogType type() const { return LogType::CLASS; }
};


#define REGISTER_STRING(OBJECT)                        \
                                                \
template <typename ...Args>                     \
class StdString: public LogString<...Args>      
{
    char_t* build(const Args& ...)
    {

    }
};


template <typename ...Args>
class StdString: public LogString<...Args>
{
    char_t* build(const Args& ...)
    {

    }
};

template <typename ...Args>
class Int: public LogVariable<...Args>
{
    char_t* build(const Args& ...)
    {

    }
};


template <typename Type>
class TypedValue 
{
public:
    char_t* build()
    {
        if (t_ != nullptr) return t_.build();
        else return "";
    }
private:
    Type*  t_;
};

class LogFormat
{
public:
    static char_t* time(char_t* year, char_t* month, char_t* day, char_t* hour, char_t* minute, char_t* second);
    static char_t* file(char_t* file_name);
    static char_t* line(char_t* line_num);
    static char_t* function(char_t* function_name);


    static char_t* value();
};



class Delogger
{
};

}



#endif // DELOG_H
