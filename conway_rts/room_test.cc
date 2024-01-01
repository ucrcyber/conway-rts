#include "conway_rts/room.hh"

#include "gtest/gtest.h"

#include "conway/structure.hh"
#include "conway/structure_properties.hh"

TEST(Room, initialization) {
  Room room("kitchen");
  EXPECT_EQ(room.name(), "kitchen");
  EXPECT_TRUE(room.clients().empty())
      << "Room client list should initially be empty.";
  EXPECT_TRUE(room.teams().empty())
      << "Room team list should initially be empty.";
  // std::cout << room;
}

TEST(Room, room_join) {
  Room room;
  Client client1(1, "c1");
  Client client2(2, "c2");
  Client client3(3, "c3");
  Client client4(4, "c4");

  room.AddClient(client1);
  EXPECT_EQ(room.clients().count(1), 1) << "client 1 should be added";
  const int team_id_client1 = room.AddTeam({client1});
  const Team *team_client1_ptr = room.GetTeam(team_id_client1);
  EXPECT_NE(team_client1_ptr, nullptr) << "a team should be created for client1";

  room.AddTeam({client2, client3});
  EXPECT_EQ(room.clients().count(2), 1) << "client 2 should be added after adding team {2,3}";
  EXPECT_EQ(room.clients().count(3), 1) << "client 3 should be added after adding team {2,3}";
}

TEST(Room, updating_grid_from_events) {
  EventQueue events;
  Client client(1, "c1");
  Team team(9999, 1000);
  team.AddMember(client);
}