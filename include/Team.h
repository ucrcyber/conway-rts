#ifndef CW_TEAM_H
#define CW_TEAM_H

#include <vector>

#include "../include/Player.h"
// TODO: Uncomment this when merging with structure branch
// #include "../include/Structure.h"

/// an actual player with resources and existing structures, but might have multiple operators aka Player
class Team {
 private:
  int id;

  Player* leader;
  std::vector<Player> players;

  // std::vector<Structure> structures;

  int resources;
  int resourceIncome;

 public:
  /// @brief generates Team from...
  /// @param  int team id
  /// @param  Player* leader
  /// @param  vector<Player> of operators
  /// @param  vector<Structure> of owned structures
  /// @param  int starting resources
  /// @param  int resource income
  Team(int, Player*, std::vector<Player>, std::vector<Structure>, int, int);

  //--------------------------------------------------------------
  // Accessors

  /// @return leader of team
  Player* getLeader() const;

  /// @return array of team's operators
  std::vector<Player> getPlayers() const;

  /// @return array of team's structures
  // Structure[] getStructures() const;

  /// @return team's total resources
  int getResources() const;

  //--------------------------------------------------------------

  /// @brief FIXME
  void processTick();
}

#endif