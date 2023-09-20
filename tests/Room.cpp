#include "Room.hpp"

#include "gtest/gtest.h"

#include "Structure.hpp"
#include "StructureProperties.hpp"

TEST(Room, initialization) {
  Room room("kitchen");
  EXPECT_EQ(room.name, "kitchen");
  // std::cout << room;
}

TEST(Room, updating_grid_from_events) {
  EventQueue events;
  Client client(1, "c1");
  Team team(9999, 1000);
  team.AddMember(client);

  
}