#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cq.h"

TEST(simpleTest, returnSize) {
    cq<int> newcq;
    EXPECT_EQ(1, 1);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
