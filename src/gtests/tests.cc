#include <gtest/gtest.h>
#include "../Model/s21_model.h"


TEST(Test_1, calculation) {
    s21::result got;
    got.start("15+25-(25*3)", 0);
    double want = 15+25-(25*3);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
    got.start("15^2/3 mod 2", 0);
    want = fmod(pow(15, 2) / 3,  2);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
}

TEST(Test_2, math_operation) {
    s21::result got;
    got.start("sin(x)", 3);
    double want = sin(3);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
    got.start("cos(x)", 4);
    want = cos(4);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
    got.start("tan(x)", 5);
    want = tan(5);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
    got.start("asin(x)", 1);
    want = asin(1);
    EXPECT_DOUBLE_EQ(got.getResult(), want);
    got.start("acos(x)", 1);
    want = acos(1);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
    got.start("atan(x)", 2);
    want = atan(2);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
    got.start("ln(x)", 2);
    want = log(2);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
    got.start("log(x)", 2);
    want = log10(2);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
    got.start("sqrt(x)", 9);
    want = sqrt(9);
    EXPECT_DOUBLE_EQ(got.getResult() , want);
}

TEST(Test_3, ERRORS) {
    s21::result got;
    got.start("125++15", 0);
    EXPECT_TRUE(got.getError());
    got.start("125+()", 0);
    EXPECT_TRUE(got.getError());
    got.start("125..25-4", 0);
    EXPECT_TRUE(got.getError());
    got.start("10//3)(", 0);
    EXPECT_TRUE(got.getError());
}



int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

