#include "vector2.hh"

#include <array>
#include <cstdlib>

#include <gtest/gtest.h>
#include "utility/vector2.pb.h"

TEST(Vector2, initialization) {
  Vector2 v, w(5, -5);
  EXPECT_EQ(v.x(), 0);
  EXPECT_EQ(v.y(), 0);
  EXPECT_EQ(w.x(), 5);
  EXPECT_EQ(w.y(), -5);
  EXPECT_NE(v, w);

  Vector2 a(1, 2), b(a);
  EXPECT_EQ(a, b);
  EXPECT_EQ(a, a);
  EXPECT_EQ(b, b);
}

TEST(Vector2, operator) {
  Vector2 v(5, 6), w(1, 1);
  Vector2 sum = v + w;
  Vector2 difference = v - w;
  EXPECT_EQ(sum.x(), 6);
  EXPECT_EQ(sum.y(), 7);
  EXPECT_EQ(difference.x(), 4);
  EXPECT_EQ(difference.y(), 5);
  EXPECT_EQ(v + w, Vector2(6, 7));
  EXPECT_EQ(v - w, Vector2(4, 5));
}

TEST(Vector2, comparison) {
  // p < q < r
  Vector2 p(1, 2), q(1, 3), r(2, 1);
  EXPECT_EQ(p, p);
  EXPECT_LE(p, p);
  EXPECT_GE(p, p);

  EXPECT_LT(p, q);
  EXPECT_LE(p, q);
  
  EXPECT_LT(p, r);
  EXPECT_LE(p, r);

  EXPECT_GT(q, p);
  EXPECT_GE(q, p);
  
  EXPECT_EQ(q, q);
  EXPECT_LE(q, q);
  EXPECT_GE(q, q);

  EXPECT_LT(q, r);
  EXPECT_LE(q, r);

  EXPECT_GT(r, p);
  EXPECT_GE(r, p);

  EXPECT_GT(r, q);
  EXPECT_GE(r, q);

  EXPECT_EQ(r, r);
  EXPECT_LE(r, r);
  EXPECT_GE(r, r);
}

TEST(Vector2, ostreamInsertion) {
  testing::internal::CaptureStdout();
  std::cout << Vector2(51, -42) << std::flush;
  EXPECT_EQ(testing::internal::GetCapturedStdout(), "(51 -42)");
}

TEST(Vector2, istreamExtraction) {
  std::istringstream in("(10 20) (-5 0) (7 27)");
  std::array<Vector2, 3> a;
  std::array<Vector2, 3> b {Vector2(10, 20), Vector2(-5, 0), Vector2(7, 27)};
  for(auto &x : a) in >> x;
  for(int i = 0; i < 3; i ++) EXPECT_EQ(a[i], b[i]);
}

TEST(Vector2, cc_proto) {
  conway::Vector2 protobuf;
  protobuf.set_x(5);
  protobuf.set_y(10);
  EXPECT_EQ(protobuf.x(), 5) << "protobuf vector2 x should've been set to 5";
  EXPECT_EQ(protobuf.y(), 10) << "protobuf vector2 y should've been set to 10";

  size_t size = protobuf.ByteSizeLong(); 
  void *buffer = malloc(size);
  protobuf.SerializeToArray(buffer, size);

  conway::Vector2 decoded;
  decoded.ParseFromArray(buffer, size);
  EXPECT_EQ(protobuf.x(), decoded.x()) << "protobuf vector2 x should match source after being encoded and decoded";
  EXPECT_EQ(protobuf.y(), decoded.y()) << "protobuf vector2 y should match source after being encoded and decoded";
  
  free(buffer);
}

TEST(Vector2, copy_into_proto) {
  conway::Vector2 protobuf;
  Vector2 vector(1234, 5678);
  vector.CopyToProtobuf(protobuf);

  EXPECT_EQ(protobuf.x(), vector.x()) << "x value should've been copied to protobuf";
  EXPECT_EQ(protobuf.y(), vector.y()) << "y value should've been copied to protobuf";
}