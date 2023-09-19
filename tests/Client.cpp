#include "Client.hpp"

#include <iostream>

#include "gtest/gtest.h"

TEST(Client, initialization) {
  Client client;
  EXPECT_EQ(client.id, 0);
  EXPECT_EQ(client.name, "");

  Client client_params(65535, "qwerty");
  EXPECT_EQ(client_params.id, 65535);
  EXPECT_EQ(client_params.name, "qwerty");
}

TEST(Client, iostream) {
  Client client(65535, "qwerty uiop");
  std::ostringstream o_buffer;
  o_buffer << client;
  std::istringstream i_buffer(o_buffer.str());
  Client client2;
  i_buffer >> client2;
  EXPECT_EQ(client.id, client2.id);
  EXPECT_EQ(client.name, client2.name);
}
