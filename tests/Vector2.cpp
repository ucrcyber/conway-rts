#include "gtest/gtest.h"
#include "../include/Vector2.h"

TEST(Vector2, initialization) {
    Vector2 v, w(5, -5);
    EXPECT_EQ(v.getX(), 0);
    EXPECT_EQ(v.getY(), 0);
    EXPECT_EQ(w.getX(), 5);
    EXPECT_EQ(w.getY(), -5);
}

TEST(Vector2, additionOperators){
    Vector2 v(5, 6), w(1, 1);
    Vector2 x = v + w;
    EXPECT_EQ(x.getX(), 6);
    EXPECT_EQ(x.getY(), 7);
}

TEST(Vector2, ostreamInsertion){
    testing::internal::CaptureStdout();
    std::cout << Vector2(51, -42) << std::endl;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "(51, -42)\n");
}