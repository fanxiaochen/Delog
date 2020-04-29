#include "delog/delog.hpp"
#include <Eigen/Core>

namespace delog
{
namespace eigen
{
namespace formats
{
template <typename Scalar, int Rows, int Cols>
string_t format_matrix(const char_t *log_prefix, const char_t *log_suffix, const char_t *name, const Eigen::Matrix<Scalar, Rows, Cols> &type, const ParameterList &type_args)
{
    string_t type_str = GET_VARIABLE_TYPE(type);
    size_t start_row = type_args[0];
    size_t start_col = type_args[1];
    size_t block_rows = type_args[2];
    size_t block_cols = type_args[3];

    size_t rows = type.rows();
    size_t cols = type.cols();

    std::stringstream ss;
    ss << log_prefix << string_t("Name: ") << GREEN(name) << log_suffix;
    ss << log_prefix << string_t("Type: ") << MAGENTA(type_str) << log_suffix;
    ss << log_prefix << string_t("Shape: ") << "(" << YELLOW(std::to_string(rows)) << "," << YELLOW(std::to_string(cols)) << ")" << log_suffix;
    ss << log_prefix << string_t("Block: ") << "(" << YELLOW(std::to_string(start_row)) << "," << YELLOW(std::to_string(start_col))
       << "," << YELLOW(std::to_string(block_rows)) << "," << YELLOW(std::to_string(block_cols)) << ")" << log_suffix;

    ss << log_prefix << string_t("[") << log_suffix;

    for (size_t i = start_row; i < block_rows; ++i)
    {
        ss << log_prefix;
        for (size_t j = start_col; j < block_cols; ++j)
        {
            ss << delog::message("", "", "type(i,j)", type(i, j), {}) << " ";
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

    template <typename Scalar, int Rows, int Cols>
    string_t generate(const char_t *name, const Eigen::Matrix<Scalar, Rows, Cols> &value, const Parameters &args = {})
    {
        ParameterList args_list = ParameterList(args);
        ParameterList args_default = {0, 0, Rows, Cols};

        for (size_t i = 0; i < args_list.size(); ++i)
        {
            args_default.set(i, args_list[i]);
        }

        return formats::format_matrix(log_prefix_.c_str(), log_suffix_.c_str(), name, value, args_default);
    }

private:
    string_t log_prefix_;
    string_t log_suffix_;
};

} // namespace eigen

#define REGISTER_EIGEN_MATRIX(Type)                                                                                                                     \
    template <typename... Args>                                                                                                                         \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Type &type, const std::initializer_list<Args> &... args) \
    {                                                                                                                                                   \
        return delog::eigen::Primitive(prefix, suffix).generate(name, type, args...);                                                                   \
    }                                                                                                                                                   \
    string_t message(const string_t &prefix, const string_t &suffix, const char_t *name, const Type &type, const Parameters &args)                      \
    {                                                                                                                                                   \
        return delog::eigen::Primitive(prefix, suffix).generate(name, type, args);                                                                      \
    }

REGISTER_EIGEN_MATRIX(Eigen::Matrix2d)
REGISTER_EIGEN_MATRIX(Eigen::Matrix3d)
REGISTER_EIGEN_MATRIX(Eigen::Matrix4d)
REGISTER_EIGEN_MATRIX(Eigen::Vector2d)
REGISTER_EIGEN_MATRIX(Eigen::Vector3d)
REGISTER_EIGEN_MATRIX(Eigen::Vector4d)

REGISTER_EIGEN_MATRIX(Eigen::Matrix2f)
REGISTER_EIGEN_MATRIX(Eigen::Matrix3f)
REGISTER_EIGEN_MATRIX(Eigen::Matrix4f)
REGISTER_EIGEN_MATRIX(Eigen::Vector2f)
REGISTER_EIGEN_MATRIX(Eigen::Vector3f)
REGISTER_EIGEN_MATRIX(Eigen::Vector4f)

REGISTER_EIGEN_MATRIX(Eigen::Matrix2i)
REGISTER_EIGEN_MATRIX(Eigen::Matrix3i)
REGISTER_EIGEN_MATRIX(Eigen::Matrix4i)
REGISTER_EIGEN_MATRIX(Eigen::Vector2i)
REGISTER_EIGEN_MATRIX(Eigen::Vector3i)
REGISTER_EIGEN_MATRIX(Eigen::Vector4i)

} // namespace delog