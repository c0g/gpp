#include "gtest/gtest.h"
#include "parameters.hpp"

TEST(PositiveParameter, CreateSettingValue)
{
    positive_double a{1.0};
    ASSERT_DOUBLE_EQ(a.get_value(), 1.0);
    a.set_value(10);
    ASSERT_DOUBLE_EQ(a.get_value(), 10.0);
}
TEST(PositiveParameter, NaNWhenNegative)
{
    positive_double b {-1.0};
    ASSERT_NE(b.get_value(), b.get_value());
}
TEST(PositiveParameter, FDGradient)
{
    double delta = 1e-9;
    double start = 2.3;
    positive_double a {start};
    positive_double b = a;
    b.set_raw_value(a.get_raw_value() - delta);

    double abs_size = std::abs(a.val_d_raw());

    ASSERT_NEAR((a.get_value() - b.get_value()) / delta, a.val_d_raw(), abs_size * 1e-5);
    ASSERT_NEAR((a.get_value() - b.get_value()) / delta, b.val_d_raw(), abs_size * 1e-5);
}

TEST(NegativeParameter, CreateSettingValue)
{
    negative_double a{-1.0};
    ASSERT_DOUBLE_EQ(a.get_value(), -1.0);
    a.set_value(-10);
    ASSERT_DOUBLE_EQ(a.get_value(), -10.0);

}
TEST(NegativeParameter, NaNWhenPositive)
{
    negative_double b {1.0};
    ASSERT_NE(b.get_value(), b.get_value());
}
TEST(NegativeParameter, FDGradient)
{
    double delta = 1e-9;
    double start = -2.3;
    negative_double a {start};
    negative_double b = a;
    b.set_raw_value(a.get_raw_value() - delta);

    double abs_size = std::abs(a.val_d_raw());

    ASSERT_NEAR((a.get_value() - b.get_value()) / delta, a.val_d_raw(), abs_size * 1e-5);
    ASSERT_NEAR((a.get_value() - b.get_value()) / delta, b.val_d_raw(), abs_size * 1e-5);
}

TEST(BoundedParameter, CreateSettingValue)
{
    bounded_double a {1.0, -2.0, 2.0};
    ASSERT_DOUBLE_EQ(a.get_value(), 1.0);

    a = 2.0;
    ASSERT_DOUBLE_EQ(a.get_value(), 2.0);
    a = -2.0;
    ASSERT_DOUBLE_EQ(a.get_value(), -2.0);
}
TEST(BoundedParameter, NaNOutsideBounds) {
    bounded_double a {-2.1, -2.0, 2.0};
    ASSERT_NE(a.get_value(), a.get_value());

    a = 2.1;
    ASSERT_NE(a.get_value(), a.get_value());
}
TEST(BoundedParameter, FDGradient) {
    double delta = 1e-9;
    double start = 2.2;
    double ubound = 10;
    double lbound = -10;
    bounded_double a {start, ubound, lbound};
    bounded_double b = a;
    b.set_raw_value(a.get_raw_value() - delta);

    double abs_size = std::abs(a.val_d_raw());

    ASSERT_NEAR((a.get_value() - b.get_value()) / delta, a.val_d_raw(), abs_size * 1e-5);
    ASSERT_NEAR((a.get_value() - b.get_value()) / delta, b.val_d_raw(), abs_size * 1e-5);
}