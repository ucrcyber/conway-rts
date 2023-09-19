#include "Team.hpp"

#include <iostream>

#include "gtest/gtest.h"

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