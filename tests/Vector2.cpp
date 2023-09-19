#include "Vector2.hpp"

#include <array>

#include "gtest/gtest.h"

TEST(Vector2, initialization) {
  Vector2 v, w(5, -5);
  EXPECT_EQ(v.x, 0);
  EXPECT_EQ(v.y, 0);
  EXPECT_EQ(w.x, 5);
  EXPECT_EQ(w.y, -5);
  EXPECT_NE(v, w);

  Vector2 a(1, 2), b(a);
  EXPECT_EQ(a, b);
  EXPECT_EQ(a, a);
  EXPECT_EQ(b, b);
}

TEST(Vector2, operator){
  Vector2 v(5, 6), w(1, 1);
  Vector2 sum = v + w;
  Vector2 difference = v - w;
  EXPECT_EQ(sum.x, 6);
  EXPECT_EQ(sum.y, 7);
  EXPECT_EQ(difference.x, 4);
  EXPECT_EQ(difference.y, 5);
  EXPECT_EQ(v + w, Vector2(6, 7));
  EXPECT_EQ(v - w, Vector2(4, 5));
}

TEST(Vector2, ostreamInsertion){
  testing::internal::CaptureStdout();
  std::cout << Vector2(51, -42) << std::flush;
  EXPECT_EQ(testing::internal::GetCapturedStdout(), "(51 -42)");
}

TEST(Vector2, istreamExtraction){
  std::istringstream in("(10 20) (-5 0) (7 27)");
  std::array<Vector2, 3> a;
  std::array<Vector2, 3> b {Vector2(10, 20), Vector2(-5, 0), Vector2(7, 27)};
  for(auto &x : a) in >> x;
  for(int i = 0; i < 3; i ++) EXPECT_EQ(a[i], b[i]);
}