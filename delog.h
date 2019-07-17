#ifndef DELOG_H
#define DELOG_H

#include <string>

namespace delog
{

typedef char char_t;
typedef int int_t;
typedef float float_t;
typedef double double_t;

enum class LogType
{
    STRING = 0,
    VALUE = 1,
    CLASS = 2
};

template <typename Type>
class TypedMessage 
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


class Delogger
{
};

}



#endif
