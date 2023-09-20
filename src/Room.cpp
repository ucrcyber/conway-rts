#include "Room.hpp"

// stl includes

// lib includes

// other includes

Room::Room(): Room::Room("a room")
{}

Room::Room(const std::string& name):
  Room::Room(name, Vector2(50, 50))
{}

Room::Room(const std::string& name, const Vector2& dimensions): _name(name)
{
  _grid = LifeGrid(dimensions.x, dimensions.y);
}

// Room::Room(const Room& other): Room() {
//   *this = other;
// }

// Room& Room::operator=(const Room& other) {
//   if(this != &other) {
//     grid = other.grid;
//   }
//   return *this;
// }

// bool Room::operator==(const Room& other) const {
//   if(this == &other) return true;
  
//   return true;
// }

// bool Room::operator!=(const Room& other) const {
//   return !(*this == other);
// }

// ### Format
// ```
//     [room name]
//     [height] [width]
//     [... grid]
//     [# teams] [# players]
//     [...teams on new lines]
// ```
// ### Example
// ```
//     kitchen
//     2 5
//     .....
//     .....
//     1 1
//     0 2
//     1 member-1
//     2 member-2
// ```
std::ostream& operator<<(std::ostream& out, const Room& rhs) {
  // TODO: make no trailing whitespace
  out << rhs.name << "\n" << rhs.grid << "\n"
    << rhs.teams.size() << " " << rhs.clients.size() << "\n";
  for(const auto& team : rhs.teams) out << team << "\n";
  return out;
}

std::istream& operator>>(std::istream& in, Room& rhs) {
  throw "not implemented";
  return in;
}

bool Room::SerializeToOstream(std::ostream& out) const {
  out << *this;
  return true;
}

bool Room::ParseFromIstream(std::istream& in) {
  in >> *this;
  return true;
}