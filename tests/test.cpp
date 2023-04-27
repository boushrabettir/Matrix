#include "../matrix.h"
#include <./googletest/googletest/include/gtest/gtest.h>
/* Learn how to make a basic makefile or use GoogleTest */

TEST(SizeTest, HandlesAllSizes) {
    Matrix testing(4, 3);
    EXPECT_EQ(testing.GetRows(), 4);
    testing.SetColumns(3);
    EXPECT_EQ(testing.GetColumns(), 3);
}

TEST(ScalarTest, HandleScalarMultiplication) {
    Matrix testing;
    double scalar = 3;
    EXPECT_EQ(testing.ScalarMultiplication(testing, scalar), testing.GetMatrix());
    scalar = -3.2;
    EXPECT_EQ(testing.ScalarMultiplication(testing, scalar), testing.GetMatrix());
    scalar = 0;
    EXPECT_EQ(testing.ScalarMultiplication(testing, scalar), testing.GetMatrix());
    scalar = 1.345;
    EXPECT_EQ(testing.ScalarMultiplication(testing, scalar), testing.GetMatrix());
}

TEST(TransposeTest, TransposeSizesTest) {
    Matrix testing({{2, 5}, {3, -2}}); // fix this error
    EXPECT_EQ(testing.Transpose(testing), testing.GetMatrix());
    testing.SetNewValues({{0, 0}, {0, 0}});
    EXPECT_EQ(testing.Transpose(testing), testing.GetMatrix());
}

TEST(InverseTest, TestingInverseLimitations) {
    Matrix testing({{2, 4}, {8, 0}}); // fix this error
    EXPECT_EQ(testing.Inverse(testing), testing.GetMatrix());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
