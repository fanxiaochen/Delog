#include "delog.hpp"

namespace delog
{
namespace opencv
{
namespace formats
{
string_t format_mat(const char_t *name, const cv::Mat &type, const Parameters &type_args)
{
    auto access_by_type = [&](size_t i, size_t j) {
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

    for (size_t i = start_row; i < block_rows; ++i)
    {
        for (size_t j = start_col; j < block_cols; ++j)
        {
            ss << access_by_type(i, j) << " ";
        }
        ss << "\n";
    }
    ss << string_t("<---------------->") << "\n";

    return ss.str();
}
} // namespace formats

class Primitive
{
public:
    string_t generate(const char_t *name, const cv::Mat &value, const Parameters &args = {})
    {
        ParameterList args_list = ParameterList(args);
        ParameterList args_default = {0, 0, value.rows, values.cols};

        for (size_t i = 0; i < args_list.size(); ++i)
        {
            args_default.set(i, args_list[i]);
        }

        return formats::format_mat(name, value, args_default);
    }
};

} // namespace opencv

#define REGISTER_OPENCV_MAT(Type)                                                  \
    string_t message(const char_t *name, const Type &type, const Parameters &args) \
    {                                                                              \
        return delog::opencv::Primitive().generate(name, type, args);              \
    }

REGISTER_OPENCV_MAT(cv::Mat)

} // namespace delog