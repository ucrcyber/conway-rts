#ifndef CONWAY_INCLUDE_ROOM_HPP
#define CONWAY_INCLUDE_ROOM_HPP

#include <string>
#include <vector>

#include "ISerializable.hpp"
#include "Client.hpp"
#include "StructureProperties.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"

/// @brief game instance
class Room: public ISerializable<Room> {
  private:
    
  public:
    /// TODO: set up after other classes have been implemented

    friend std::ostream& operator<<(std::ostream &out, const Room &rhs);
    friend std::istream& operator>>(std::istream &in, Room &rhs);
    bool SerializeToOstream(std::ostream &out) const;
    bool ParseFromIstream(std::istream &in);
};

#endif // CONWAY_INCLUDE_ROOM_HPP