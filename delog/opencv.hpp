#include "delog/delog.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/matx.hpp>

namespace delog
{
namespace opencv
{
namespace formats
{
template <typename Type, int N>
string_t format_vec(const char_t *log_prefix, const char_t *log_suffix, const char_t *name, const cv::Vec<Type, N> &type, const ParameterList &type_args)
{
    auto format_simple = [&]() {
        std::stringstream ss;
        ss << "[";
        size_t length = N;
        size_t start = type_args[0];
        size_t end = type_args[1];
        for (size_t i = start; i <= end; ++i)
        {
            ss << delog::message("", "", ("var[" + std::to_string(i) + "]").c_str(), type[i], {});
            if (i == end)
                break;
            else
                ss << " ";
        }
        ss << "]";
        return ss.str();
    };

    auto format_complex = [&]() {
        string_t type_str = GET_VARIABLE_TYPE(type);
        std::stringstream ss;
        ss << log_prefix;
        ss << MAGENTA(type_str) + " " + GREEN(name) + " = ";
        ss << "[";
        size_t length = N;
        size_t start = type_args[0];
        size_t end = type_args[1];
        for (size_t i = start; i <= end; ++i)
        {
            ss << delog::message("", "", ("var[" + std::to_string(i) + "]").c_str(), type[i], {});
            if (i == end)
                break;
            else
                ss << " ";
        }
        ss << "]" << log_suffix;
        return ss.str();
    };

    if (default_basic_types.find(typeid(Type).name()) != default_basic_types.end())
    {
        if (!string_t(log_prefix).empty() && !string_t(log_suffix).empty())
            return format_complex();
        else
            return format_simple();
    }
    else
        return "";
}

template <typename Type>
string_t format_vec(const char_t *log_prefix, const char_t *log_suffix, const char_t *name, const cv::Mat &type, const int row, const int col)
{
    std::stringstream ss;
    size_t channels = type.channels();

    ss << "[";
    for (int i = 0; i < channels; ++i)
    {
        ss << delog::message("", "", ("var[" + std::to_string(i) + "]").c_str(), type.ptr<Type>(row)[col * channels + i], {});
        if (i == (channels - 1))
            break;
        else
            ss << " ";
    }
    ss << "]";
    return ss.str();
}

string_t format_mat(const char_t *log_prefix, const char_t *log_suffix, const char_t *name, const cv::Mat &type, const ParameterList &type_args)
{
    auto access_by_type = [&](size_t i, size_t j) {
        switch (type.depth())
        {
        case CV_8U:
            return format_vec<uchar_t>("", "", name, type, i, j);
        case CV_8S:
            return format_vec<char_t>("", "", name, type, i, j);
        case CV_16U:
            return format_vec<ushort_t>("", "", name, type, i, j);
        case CV_16S:
            return format_vec<short_t>("", "", name, type, i, j);
        case CV_32S:
            return format_vec<int_t>("", "", name, type, i, j);
        case CV_32F:
            return format_vec<float_t>("", "", name, type, i, j);
        case CV_64F:
            return format_vec<double_t>("", "", name, type, i, j);
        default:
            return string_t("");
        }
        return string_t("");
    };

    string_t type_str = GET_VARIABLE_TYPE(type);
    size_t start_row = type_args[0];
    size_t start_col = type_args[1];
    size_t block_rows = type_args[2];
    size_t block_cols = type_args[3];

    size_t rows = type.rows;
    size_t cols = type.cols;

    std::stringstream ss;
    ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;
    ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;
    ss << log_prefix << string_t("Shape: ") << "(" << YELLOW(std::to_string(rows)) << "," << YELLOW(std::to_string(cols)) << ")" << log_suffix;
    ss << log_prefix << string_t("Block: ") << "(" << YELLOW(std::to_string(start_row)) << "," << YELLOW(std::to_string(start_col))
       << "," << YELLOW(std::to_string(block_rows)) << "," << YELLOW(std::to_string(block_cols)) << ")" << log_suffix;

    ss << log_prefix << string_t("[") << log_suffix;

    for (size_t i = start_row; i < start_row + block_rows; ++i)
    {
        ss << log_prefix;
        for (size_t j = start_col; j < start_col + block_cols; ++j)
        {
            ss << access_by_type(i, j) << " ";
        }
        ss << log_suffix;
    }
    ss << log_prefix << string_t("]") << log_suffix;

    return ss.str();
}
} // namespace formats

class Primitive
{
public:
    Primitive(const string_t &log_prefix, const string_t &log_suffix) : log_prefix_(log_prefix), log_suffix_(log_suffix) {}

    string_t generate(const char_t *name, const cv::Mat &value, const Parameters &args = {})
    {
        ParameterList args_list = ParameterList(args);
        ParameterList args_default = {0, 0, value.rows, value.cols};

        for (size_t i = 0; i < args_list.size(); ++i)
        {
            args_default.set(i, args_list[i]);
        }

        return formats::format_mat(log_prefix_.c_str(), log_suffix_.c_str(), name, value, args_default);
    }

    template <typename Type, int N>
    string_t generate(const char_t *name, const cv::Vec<Type, N> &value, const Parameters &args = {})
    {
        ParameterList args_list = ParameterList(args);
        ParameterList args_default = {0, N - 1};

        for (size_t i = 0; i < args_list.size(); ++i)
        {
            args_default.set(i, args_list[i]);
        }

        return formats::format_vec(log_prefix_.c_str(), log_suffix_.c_str(), name, value, args_default);
    }

private:
    string_t log_prefix_;
    string_t log_suffix_;
};

} // namespace opencv

#define REGISTER_OPENCV_VEC(Vector)                                                                                                                                \
    template <typename Type, int N, typename... Args>                                                                                                              \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Vector<Type, N> &type, const std::initializer_list<Args> &... args) \
    {                                                                                                                                                              \
        return delog::opencv::Primitive(prefix, suffix).generate(name, type, args...);                                                                             \
    }                                                                                                                                                              \
    template <typename Type, int N>                                                                                                                                \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Vector<Type, N> &type, const Parameters &args)                      \
    {                                                                                                                                                              \
        return delog::opencv::Primitive(prefix, suffix).generate(name, type, args);                                                                                \
    }

#define REGISTER_OPENCV_MAT(Matrix)                                                                                                                       \
    template <typename... Args>                                                                                                                           \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Matrix &type, const std::initializer_list<Args> &... args) \
    {                                                                                                                                                     \
        return delog::opencv::Primitive(prefix, suffix).generate(name, type, args...);                                                                    \
    }                                                                                                                                                     \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Matrix &type, const Parameters &args)                      \
    {                                                                                                                                                     \
        return delog::opencv::Primitive(prefix, suffix).generate(name, type, args);                                                                       \
    }

REGISTER_OPENCV_VEC(cv::Vec)
REGISTER_OPENCV_MAT(cv::Mat)

} // namespace delog