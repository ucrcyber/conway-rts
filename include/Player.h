#ifndef CW_PLAYER_H
#define CW_PLAYER_H

#include <string>

class Player {
 private:
  std::string name;
  int id;

 public:
  // Constructor
  Player(int, std::string);

  // Accessors
  std::string getName();
  int getId();
};

#endif