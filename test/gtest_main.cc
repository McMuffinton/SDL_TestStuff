#include <stdio.h>
#include <gtest/gtest.h>
#include "test_Keyboard.cc"

GTEST_API_ int main(int argc, char** argv) {
    printf("Running unittests from test/gtest_main.cc\n");

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
