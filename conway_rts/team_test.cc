#include "conway_rts/team.hh"

#include <iostream>

#include "gtest/gtest.h"

#include "conway/structure.hh"
#include "conway/structure_properties.hh"

TEST(Team, initialization) {
  Team team;
  EXPECT_EQ(team.id, 0);
  EXPECT_EQ(team.members.size(), 0);
}

TEST(Team, iostream) {
  Team team(9999, std::vector<Client>{
    Client(1, "client1"),
    Client(2, "client2"),
    Client(3, "client3"),
    Client(4, "client with spaces"),
  });
  std::ostringstream o_buffer;
  o_buffer << team;
  std::istringstream i_buffer(o_buffer.str());
  Team team2;
  i_buffer >> team2;
  EXPECT_EQ(team.id, team2.id);
  EXPECT_EQ(team.members, team2.members);
  EXPECT_EQ(team, team2);
}

TEST(Team, member_management) {
  Team team;
  Client client1(1, "client 1"), client2(2, "client 2"), client3(3, "client 3");
  EXPECT_EQ(team.members.size(), 0) << "no members added yet";

  team.AddMember(client1);
  EXPECT_EQ(team.members.size(), 1) << "added client 1";
  EXPECT_EQ(team.GetLeader(), client1) << "only client should be leader";

  team.AddMember(client2);
  EXPECT_EQ(team.members.size(), 2) << "added client 2";
  EXPECT_EQ(team.GetLeader(), client1)
    << "leader should still be the same after adding client 2";
  
  team.AddMember(client2);
  EXPECT_EQ(team.members.size(), 2)
    << "added client 2 (again), shouldn't cause duplicates";
  EXPECT_EQ(team.GetLeader(), client1)
    << "leader should remain the same after adding client 2 twice";
  
  team.AddMember(client3);
  EXPECT_EQ(team.members.size(), 3) << "added client 3";
  EXPECT_EQ(team.GetLeader(), client1)
    << "leader should still be the same after adding client 3";
  
  team.SetLeader(client1);
  EXPECT_EQ(team.members.size(), 3)
    << "no change made after setting client 1 to leader (client 1 already leader)";
  EXPECT_EQ(team.GetLeader(), client1)
    << "no change made after setting client 1 to leader (client 1 already leader)";

  team.SetLeader(client3);
  EXPECT_EQ(team.members.size(), 3) << "members should'nt've been removed";
  EXPECT_EQ(team.GetLeader(), client3) << "client 3 reassigned as leader";
}

TEST(Team, client_event_processing_static_structures) {
  const LifeGrid grid;
  constexpr int INITIAL_RESOURCES = 2; // 2 since we build 2, then fail the third
  EventQueue events;
  Client client1(1, "c1"), client2(2, "c2");
  Team team(9999, INITIAL_RESOURCES);
  team.AddMember(client1);
  team.AddMember(client2);

  constexpr int OFF = 0, ON = 1;
  const std::vector<StructureProperties> props = {
    StructureProperties("OFF 1x1", LifeGrid(1, 1)),
    StructureProperties("ON 1x1", LifeGrid(std::vector<std::vector<bool>>{{true}})),
  };
  Vector2 pos1(1, 0), pos2(1, 2);
  team.AddEventToQueue(client1.CreateBuildEvent(0, OFF, pos1));
  team.AddEventToQueue(client2.CreateBuildEvent(1, OFF, pos2));
  team.AddEventToQueue(client2.CreateBuildEvent(9, ON, pos1));
  EXPECT_EQ(team.event_queue.size(), 3)
    << "events should be added but not yet processed";

  team.Tick(0, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 2)
    << "of the three added events, one should be processed, leaving two left";
  ASSERT_EQ(events.size(), 1)
    << "the initial build event at time=0 should've been accepted (it does nothing)";
  EXPECT_EQ(team.resources, INITIAL_RESOURCES-1)
    << "1 resource has been spent in building 1 'OFF 1x1' (to be refunded)";
  EXPECT_EQ(events.front(), Event(0, 0, ArrayBuffer{client1.id, pos1.x, pos1.y, OFF}))
    << "the processed placement event should be from client1";

  team.Tick(0, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 2)
    << "of the three added events, two still should be left (time did not change)";
  EXPECT_EQ(events.size(), 1)
    << "no events were processed, so the processed events should stay the same";
  EXPECT_EQ(team.resources, INITIAL_RESOURCES-1)
    << "1 resource has been spent in building 1 'OFF 1x1' (to be refunded)";

  team.Tick(2, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 1)
    << "of the three added events, one is left";
  EXPECT_EQ(events.size(), 2)
    << "of the two added events, both should be processed (both were valid, doing nothing)";
  EXPECT_EQ(team.resources, INITIAL_RESOURCES-2)
    << "2 resource has been spent in building 2 'OFF 1x1' (to be refunded)";
  EXPECT_EQ(events.back(), Event(1, 0, ArrayBuffer{client2.id, pos2.x, pos2.y, OFF}))
    << "the 2nd placement should be processed and from client2";
  
  // events.clear();
  // ASSERT_EQ(events.size(), 0) << "event list should be cleared";

  team.Tick(9, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 0)
    << "of the three added events, all of them should be processed by now";
  EXPECT_EQ(team.resources, 0)
    << "the team has expended all of its resources (though 2 should be refunded, tested in tests/Room.cpp)";
  EXPECT_EQ(events.size(), 2)
    << "the last processed event should have been rejected due to insufficient funds";
}

TEST(Team, client_event_processing_dynamic_structures) {
  LifeGrid grid(10, 10);
  constexpr int INCOME_RATE = 42;
  constexpr int INITIAL_RESOURCES = 9;
  EventQueue events;
  Client client(1, "c1");
  Team team(9999, INITIAL_RESOURCES);
  team.AddMember(client);

  constexpr int GENERATOR = 0, EXPENSIVE = 1;
  const LifeGrid block(std::vector<std::vector<bool>>{{true, true}, {true, true}});
  const std::vector<Vector2> checks(1, Vector2(0, 0));
  const std::vector<StructureProperties> props = {
    StructureProperties("GENERATOR", 0, INCOME_RATE, 0, block, checks),
    StructureProperties("EXPENSIVE", 420, 0, 0, block, checks),
  };
  Vector2 pos1(1, 2), pos2(2, 3), pos3(3, 4);
  
  team.AddEventToQueue(client.CreateBuildEvent(0, GENERATOR, pos1));
  team.AddEventToQueue(client.CreateBuildEvent(1, GENERATOR, pos1));
  team.AddEventToQueue(client.CreateBuildEvent(5, EXPENSIVE, pos2));
  team.AddEventToQueue(client.CreateBuildEvent(15, EXPENSIVE, pos3));
  EXPECT_EQ(team.event_queue.size(), 4)
    << "events should be added but not yet processed";

  team.Tick(0, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 3)
    << "1 of 4 events have been processed";
  EXPECT_EQ(events.size(), 1)
    << "1 of 1 processed events have been accepted";
  EXPECT_EQ(team.income, 0)
    << "income has not been updated yet";
  
  // load template as if you built it (this is handled in Room:Tick)
  grid.Load(block, pos1);

  team.Tick(1, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 2)
    << "2 of 4 events have been processed";
  EXPECT_EQ(events.size(), 1)
    << "1 of 2 processed events have been accepted (rejected since duplicate location)";
  EXPECT_EQ(team.income, INCOME_RATE)
    << "income rate should have been updated (structure is active)";
  EXPECT_EQ(team.resources, INCOME_RATE + INITIAL_RESOURCES-4)
    << "resources should have been granted (-4 for the initial build cost)";
  
  team.Tick(5, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 1)
    << "3 of 4 events have been processed";
  EXPECT_EQ(events.size(), 1)
    << "1 of 3 processed events have been accepted (rejected since duplicate location)";
  EXPECT_EQ(team.income, INCOME_RATE)
    << "income rate should have been updated (structure is active)";
  EXPECT_EQ(team.resources, 5*INCOME_RATE + INITIAL_RESOURCES-4)
    << "generator has lasted for 5 ticks";

  team.Tick(10, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 1)
    << "3 of 4 events have been processed";
  EXPECT_EQ(events.size(), 1)
    << "1 of 3 processed events have been accepted (rejected since duplicate location)";
  EXPECT_EQ(team.income, INCOME_RATE)
    << "income rate should be the same";
  EXPECT_EQ(team.resources, 10*INCOME_RATE + INITIAL_RESOURCES-4)
    << "generator has lasted for 10 ticks";
  
  team.Tick(15, events, grid, props);
  EXPECT_EQ(team.event_queue.size(), 0)
    << "4 of 4 events have been processed";
  EXPECT_EQ(events.size(), 2)
    << "2 of 4 processed events have been accepted (rejected since duplicate location)";
  EXPECT_EQ(team.income, INCOME_RATE)
    << "income rate should be the same";
  EXPECT_EQ(team.resources, 15*INCOME_RATE + INITIAL_RESOURCES - 420 -8)
    << "generator has lasted for 15 ticks, and purchased one expensive (1000) item";
}
