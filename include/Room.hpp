#ifndef CONWAY_INCLUDE_ROOM_HPP
#define CONWAY_INCLUDE_ROOM_HPP

#include <string>
#include <vector>

#include "ISerializable.hpp"
#include "Client.hpp"
#include "Team.hpp"
#include "StructureProperties.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"

/// @brief game instance
class Room: public ISerializable<Room> {
  private:
    std::string _name;
    // TODO: room size limits

    std::vector<StructureProperties> _structure_lookup;
    int _time = 0;
    std::vector<Client> _clients;
    std::vector<Team> _teams;
    LifeGrid _grid;
    EventQueue _event_queue;

  public:
    const std::string& name = _name;
    const std::vector<StructureProperties>& structure_lookup = _structure_lookup;
    const std::vector<Client>& clients = _clients;
    const std::vector<Team>& teams = _teams;
    const LifeGrid& grid = _grid;
    const EventQueue& event_queue = _event_queue;

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
};

#endif // CONWAY_INCLUDE_ROOM_HPP