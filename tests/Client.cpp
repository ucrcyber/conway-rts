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
  EXPECT_EQ(client, client2);
}

TEST(Client, AddBuildEvent_format) {
  Client client(10000, "qwerty uiop");
  EventQueue q;
  const int time = 10, building_id = 49;
  client.AddBuildEvent(q, time, building_id, Vector2(1234, 5678));

  ArrayBuffer expected_data {10000, 1234, 5678, building_id};
  Event expected_event(time, 0, expected_data);
  const auto [result_time, result_event] = q.top();
  EXPECT_EQ(result_time, time);
  EXPECT_EQ(result_event, expected_event);
}