#include "conway_rts/room.hh"

// stl includes

// lib includes

// other includes

Room::Room() : Room::Room("a room") {}

Room::Room(const std::string &name) : Room::Room(name, Vector2(50, 50)) {}

Room::Room(const std::string &name, const Vector2 &dimensions) : name_(name) {
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

void Room::Initialize() { grid_ = LifeGrid(grid().dimensions()); }

void Room::SetName(const std::string &new_name) { name_ = new_name; }

bool Room::AddClient(const Client &client) {
  if (clients_.count(client.id())) {
    return false;
  }
  clients_[client.id()] = client;
  return true;
}

int Room::AddTeam(const std::vector<Client> &team_members) {
  ++team_instance_count;
  Team new_team(team_instance_count);
  if (teams_.count(new_team.id())) {
    throw std::runtime_error("team id exists");
  }

  const int new_team_id = new_team.id();
  teams_[new_team.id()] = std::move(new_team);

  // Add players using Room::AddToTeam which automatically
  // removes players who are already in a team.
  for (const Client &team_member : team_members) {
    AddToTeam(new_team_id, team_member);
  }
  return new_team_id;
}

bool Room::AddToTeam(int team_id, const Client &client) {
  if (teams_.count(team_id) == 0) {
    return false;
  }
  const bool added_successfully = teams_[team_id].AddMember(client);
  if (added_successfully) {
    AddClient(client);
    /// TODO: Remove from other teams.
  }
  return added_successfully;
}

bool Room::RemoveFromTeam(int team_id, const Client &client) {
  if (teams_.count(team_id) == 0) {
    return false;
  }
  throw std::exception("not implemented, depends on Team::RemoveMember but "
                       "this doesn't exist yet");
  // return teams_[team_id].RemoveMember(client);
}

bool Room::RemoveClient(const Client &client) {
  if (!clients_.count(client.id())) {
    return false;
  }
  clients_.erase(client.id());
  return true;
}

Team *Room::GetTeam(int team_id) {
  if (teams_.count(team_id)) {
    return &teams_.at(team_id);
  }
  return nullptr;
}

void Room::LoadStructures(
    const std::vector<StructureProperties> &new_structures) {
  structure_lookup_ = new_structures;
}

void Room::Tick(EventQueue &next_queue) {
  // this processes events that have been filtered by Team::Tick
  while (!event_queue().empty() && event_queue().front().time() <= time()) {
    const Event event = std::move(event_queue_.front());
    event_queue_.pop_front();
    if (event.data().size() != 4) {
      throw std::logic_error("invalid event data");
    }

    const int building_id = event.data()[3];
    if (building_id < 0 || building_id >= event.data().size()) {
      throw std::logic_error("invalid event building_id");
    }

    const StructureProperties &props = structure_lookup()[building_id];
    const Vector2 position(event.data()[1], event.data()[2]);
    const int refund =
        props.grid().dimensions().x() * props.grid().dimensions().y() -
        grid().Compare(props.grid(), position);
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
std::ostream &operator<<(std::ostream &out, const Room &rhs) {
  // TODO: make no trailing whitespace
  out << rhs.name() << "\n"
      << rhs.grid() << "\n"
      << rhs.teams().size() << " " << rhs.clients().size() << "\n";
  for (const std::pair<const int, Team> &team_entry : rhs.teams())
    out << team_entry.second << "\n";
  return out;
}

std::istream &operator>>(std::istream &in, Room &rhs) {
  throw "not implemented";
  return in;
}

bool Room::SerializeToOstream(std::ostream &out) const {
  out << *this;
  return true;
}

bool Room::ParseFromIstream(std::istream &in) {
  in >> *this;
  return true;
}