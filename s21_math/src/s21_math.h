
#include <ctype.h>
#include <stdint.h>

#define S21_EPS 1e-17
#define S21_PI 3.14159265358979324
#define S21_EXP 2.71828182845904523
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0
#define S21_MAX_DOUBLE 1.7976931348623157e308
#define S21_ADOMAIN 1

typedef long double s21_long_double;  // with high precision
typedef double s21_double;
typedef long int s21_long_int;

/// @brief This function is a series expansion of math function arcsin(x)
/// @param source is a real number - an argue for arcsin function
/// @return a value of the function arcsin(x)
s21_long_double s21_asin(s21_double source);

/// @brief This function is a series expansion of math function arcsin(x).
///        It's easy to calculate this value using function asin(x) like PI -
///        asin(x).
/// @param source is a real number - an argue for arccos function
/// @return a vlue of the function arccos(x)
s21_long_double s21_acos(s21_double source);

/// @brief This functions is a series expansion of math function arctg(x).
/// @param source is a real number - an argue for arctg function
/// @return a value of the function arctg(x)
s21_long_double s21_atan(s21_double source);

/// @brief This function is for checking real numbers close to zero
/// @param source is a real number
/// @return true or false(bool)
int8_t s21_is_zero(s21_double source);

/// @brief This function is for getting an absolute value of the real number
/// @param source is a real number
/// @return an absolute value of the real number
s21_long_double s21_fabs(s21_double source);

/// @brief This function is for getting an absolute value of the integer number
/// @param source is a integer number
/// @return an absolute value of the integet number
s21_long_int s21_abs(s21_long_int source);

/// @brief This function is for getting value of the sqrt(x) function
/// @param source is a real number
/// @return a value of the function sqrt(x)
s21_long_double s21_sqrt(s21_double source);

/// @brief This function is for getting value of the sin(x) function
/// @param source is a real number
/// @return a value of the functions sin(x)
s21_long_double s21_sin(s21_double source);

/// @brief This function is for getting value of the cos(x) function
/// @param source is a real number
/// @return a value of the functions cos(x)
s21_long_double s21_cos(s21_double source);

/// @brief This function is for getting value of the tan(x) function
/// @param source is a real number
/// @return a value of the functions tan(x)
s21_long_double s21_tan(s21_double source);

/// @brief This function is for getting value of the ceil(x) function
/// @param source is a real number
/// @return a value of the functions ceil(x)
s21_long_double s21_ceil(s21_double source);

/// @brief This function is for getting value of the fmod(x, y) function
/// @param source is a real number
/// @return a value of the functions fmod(x, y)
s21_long_double s21_fmod(s21_double x, s21_double y);

/// @brief This function is for getting value of the floor(x) function
/// @param source is a real number
/// @return a value of the functions floor(x)
s21_long_double s21_floor(s21_double source);
s21_long_double s21_tan(s21_double source);

s21_long_double s21_exp(s21_double x);
s21_long_double s21_log(s21_double x);
s21_long_double s21_pow(s21_double base, s21_double exp);
