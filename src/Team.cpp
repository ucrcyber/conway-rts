#include "../include/Team.h"

#include <vector>

Team::Team(int id_, Player* leader_, std::vector<Player> players_, std::vector<Structure> structures_, int resources_, int resourceIncome_)
    : id(id_), leader(leader_), players(players_), structures(structures_), resources(resources_), resourceIncome(resourceIncome_) {
}

Player* Team::getLeader() const {
  return leader;
}

std::vector<Player> Team::getPlayers() const {
  return players;
}

// std::vector<Structure> Team::getStructures() const {
//   return structures;
// }

int Team::getResources() const {
  return resources;
}

void processTick() {
  // FIXME
}