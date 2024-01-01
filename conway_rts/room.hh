#ifndef CONWAY_INCLUDE_ROOM_HPP
#define CONWAY_INCLUDE_ROOM_HPP

#include <iostream>
#include <string>
#include <vector>

#include "conway/structure_properties.hh"
#include "conway_rts/client.hh"
#include "conway_rts/event_queue.hh"
#include "conway_rts/team.hh"

/// @brief game instance
class Room {
public:
  Room();
  Room(const std::string &name);
  Room(const std::string &name, const Vector2 &dimensions);

  /// @brief resets the grid and team statuses
  void Initialize();

  /// @brief update room name
  /// @param new_name
  void SetName(const std::string &new_name);

  /// Adds a client to the room so that they are tracked, if not
  /// in a team, they are implicitly a spectator.
  /// Returns true if successful.
  bool AddClient(const Client &client);

  /// Add a set of clients (team members) as a team to the room.
  /// (outside *-> player)
  /// If a player is already in the room or in a team, they will
  /// be removed from that status.
  /// Returns the team_id.
  int AddTeam(const std::vector<Client> &team_members);

  /// Adds a client to a team specified by team id. (spectator -> player)
  /// If a player isn't in the room, they'll be added to the room.
  /// If a player is already in a team, they'll be removed from that team.
  /// Returns true if successful
  bool AddToTeam(int team_id, const Client &client);

  /// Removes a client from a team specified by team id. (player -> spectator)
  /// Returns true if successful
  bool RemoveFromTeam(int team_id, const Client &client);

  /// Removes the client from the room; removes from the team if they are
  /// playing. (spectator -> outside) Returns true if successful
  bool RemoveClient(const Client &client);

  /// Returns a pointer to a team (or nullptr if it doesn't exist)
  /// Used to modify the team input queue.
  /// TODO: pass EventQueue around instead of the entire team object?
  Team *GetTeam(int team_id);

  /// @brief updates structure_lookup vector
  /// @param new_structures
  void LoadStructures(const std::vector<StructureProperties> &new_structures);

  /// @brief advances one tick (increments `_time`), pushes accepted events into
  /// `event_queue` to be broadcasted
  void Tick(EventQueue &next_queue);

  friend std::ostream &operator<<(std::ostream &out, const Room &rhs);
  friend std::istream &operator>>(std::istream &in, Room &rhs);
  bool SerializeToOstream(std::ostream &out) const;
  bool ParseFromIstream(std::istream &in);

  // accessor/mutators
  const std::string &name() const { return name_; }
  const std::vector<StructureProperties> &structure_lookup() const {
    return structure_lookup_;
  }
  int time() const { return time_; }
  const std::map<int, Client> &clients() const { return clients_; }
  const std::map<int, Team> &teams() const { return teams_; }
  const LifeGrid &grid() const { return grid_; }
  const EventQueue &event_queue() const { return event_queue_; }

private:
  std::string name_;
  // TODO: room size limits

  std::vector<StructureProperties> structure_lookup_;
  int time_ = 0;
  std::map<int, Client> clients_;
  std::map<int, Team> teams_;
  LifeGrid grid_;
  EventQueue event_queue_;
  
  /// used to assign a unique team id
  int team_instance_count = 0;
};

#endif // CONWAY_INCLUDE_ROOM_HPP