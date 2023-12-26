#ifndef CONWAY_INCLUDE_ROOM_HPP
#define CONWAY_INCLUDE_ROOM_HPP

#include <iostream>
#include <string>
#include <vector>

#include "conway_rts/client.hh"
#include "conway_rts/team.hh"
#include "conway/structure_properties.hh"
#include "conway_rts/event.hh"
#include "conway_rts/event_queue.hh"

/// @brief game instance
class Room {
 public:
  Room();
  Room(const std::string& name);
  Room(const std::string& name, const Vector2& dimensions);

  /// @brief resets the grid and team statuses
  void Initialize();

  /// @brief update room name
  /// @param new_name 
  void SetName(const std::string& new_name);

  /// @brief updates structure_lookup vector
  /// @param new_structures 
  void LoadStructures(const std::vector<StructureProperties>& new_structures);

  /// @brief advances one tick (increments `_time`), pushes accepted events into `event_queue` to be broadcasted
  void Tick(EventQueue& next_queue);

  friend std::ostream& operator<<(std::ostream& out, const Room& rhs);
  friend std::istream& operator>>(std::istream& in, Room& rhs);
  bool SerializeToOstream(std::ostream& out) const;
  bool ParseFromIstream(std::istream& in);

  // accessor/mutators
  const std::string& name() const {
    return name_;
  }
  const std::vector<StructureProperties>& structure_lookup() const {
    return structure_lookup_;
  }
  int time() const {
    return time_;
  }
  const std::vector<Client>& clients() const {
    return clients_;
  }
  const std::vector<Team>& teams() const {
    return teams_;
  }
  const LifeGrid& grid() const {
    return grid_;
  }
  const EventQueue& event_queue() const {
    return event_queue_;
  }

 private:
  std::string name_;
  // TODO: room size limits

  std::vector<StructureProperties> structure_lookup_;
  int time_ = 0;
  std::vector<Client> clients_;
  std::vector<Team> teams_;
  LifeGrid grid_;
  EventQueue event_queue_;
};

#endif // CONWAY_INCLUDE_ROOM_HPP