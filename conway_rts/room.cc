#include "conway_rts/room.hh"

// stl includes

// lib includes

// other includes

Room::Room(): Room::Room("a room")
{}

Room::Room(const std::string& name):
  Room::Room(name, Vector2(50, 50))
{}

Room::Room(const std::string& name, const Vector2& dimensions): name_(name)
{
  grid_ = LifeGrid(dimensions);
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

void Room::Initialize() {
  grid_ = LifeGrid(grid().dimensions());
  
}

void Room::SetName(const std::string& new_name) {
  name_ = new_name;
}

void Room::LoadStructures(const std::vector<StructureProperties>& new_structures) {
  structure_lookup_ = new_structures;
}

void Room::Tick(EventQueue& next_queue) {
  // this processes events that have been filtered by Team::Tick
  while (!event_queue().empty() && event_queue().front().time() <= time()) {
    const Event event = std::move(event_queue_.front());
    event_queue_.pop_front();
    
    if(event.data().size() != 4) throw std::logic_error("invalid event data");
    const int building_id = event.data()[3];
    if(building_id < 0 || building_id >= event.data().size()) throw std::logic_error("invalid event building_id");
    
    const StructureProperties& props = structure_lookup()[building_id];
    const Vector2 position(event.data()[1], event.data()[2]);
    const int refund = props.grid().dimensions().x() * props.grid().dimensions().y() - grid().Compare(props.grid(), position);
    grid_.Load(props.grid(), position);

    next_queue.push_back(event);
  }
  ++time_;
}

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
  out << rhs.name() << "\n" << rhs.grid() << "\n"
    << rhs.teams().size() << " " << rhs.clients().size() << "\n";
  for(const auto& team : rhs.teams()) out << team << "\n";
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