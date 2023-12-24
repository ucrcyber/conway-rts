#include "proto/vector2.pb.h"

#include <string>

#include "gtest/gtest.h"

// this is just to make sure that protobuf is working
TEST(ProtoBuf, initialization) {
  conway::Vector2 u, v;
  u.set_x(1);
  u.set_y(2);
  EXPECT_EQ(u.x(), 1);
  EXPECT_EQ(u.y(), 2);

  std::string buffer;
  u.SerializeToString(&buffer);
  v.ParseFromString(buffer);
  EXPECT_EQ(v.x(), 1);
  EXPECT_EQ(v.y(), 2);
}