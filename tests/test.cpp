#include "../matrix.cpp"
#include <gtest/gtest.h>
/* Learn how to make a basic makefile or use GoogleTest */




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}