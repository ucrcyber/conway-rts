#include "conway_rts/team.hh"

#include <utility>

Team::Team(): Team::Team(0)
{}

Team::Team(const int id): Team::Team(id, std::vector<Client>())
{}

Team::Team(const int id, const std::vector<Client>& members):
  id_(id), members_(members), income_(0), resources_(0)
{}

Team::Team(const int id, const int initial_resources): Team::Team(id) {
  resources_ = initial_resources;
}

// Team::Team(const Team& other): Team() {
//   *this = other;
// }

// Team& Team::operator=(const Team& other) {
//   if(this != &other) {
//     grid = other.grid;
//   }
//   return *this;
// }

bool Team::operator==(const Team& other) const {
  if (this == &other) return true;
  if (id() != other.id()) return false;
  if (members() != other.members()) return false;
  return true;
}

bool Team::operator!=(const Team& other) const {
  return !(*this == other);
}

bool Team::AddMember(const Client& new_member) {
  for (const auto& member : members()) {
    // should be fine since there won't be that many people per team (<10?, <<100?)
    if (new_member == member) return false;
  }
  members_.push_back(new_member);
  return true;
}

const Client& Team::GetLeader() const {
  if(members().empty()) {
#ifdef __cpp_exceptions
    throw std::logic_error("cannot Team::GetLeader(), no members in team");
#else
    return Client::placeholder;
#endif // __cpp_exceptions
  }
  return members().front();
}

bool Team::SetLeader(const Client& new_leader) {
  if (members().empty()) return false;
  if (GetLeader() == new_leader) return true;
  for (auto& member : members_) {
    if (new_leader == member) {
      std::swap(member, members_.front());
      return true;
    }
  }
  return false;
}

void Team::AddEventToQueue(const Event& event) {
  event_queue_.push_back(event);
}

void Team::Tick(const int current_time, EventQueue& next_queue, const LifeGrid& grid, const std::vector<StructureProperties>& structure_lookup) {
  CheckStructureIntegrity(grid);
  if (current_time > last_income_update()) {
    resources_ += (current_time - last_income_update()) * income();
    last_income_update_ = current_time;
  }
  while (!event_queue().empty() && event_queue().front().time() <= current_time) {
    const Event event = std::move(event_queue_.front());
    event_queue_.pop_front();
    // client event validation before passing to the next queue (room)
    
    if(event.data().size() != 4) {
#ifdef __cpp_exceptions
      throw std::logic_error("invalid event data");
#else
      continue;
#endif // __cpp_exceptions
    }
    const int building_id = event.data()[3];
    if(building_id < 0 || building_id >= event.data().size()) {
#ifdef __cpp_exceptions
      throw std::logic_error("invalid event building_id");
#else
      continue;
#endif // __cpp_exceptions
    }
    const StructureProperties& props = structure_lookup[building_id];
    const int cost = props.grid().dimensions().x() * props.grid().dimensions().y() + props.activation_cost();
    const Structure new_structure(props, Vector2(event.data()[1], event.data()[2]));
    if(resources() >= cost && structures().count(new_structure.GetKey()) == 0){
      resources_ -= cost;
      next_queue.push_back(event);
      // TODO: add some easier way of determining whether it is static (does not need to be tracked) or dynamic structure (needs to be tracked)
      if(!props.checks().empty()) AddStructure(new_structure);
    }
  }
}

void Team::CheckStructureIntegrity(const LifeGrid& grid) { 
  for (auto& [k, structure] : structures_) {
    int before = structure.active();
    int after = structure.CheckIntegrity(grid);
    income_ += (after - before) * structure.properties().income();
  }
}

void Team::AddStructure(const Structure& new_structure) {
  structures_[new_structure.GetKey()] = new_structure;
}

// ### Format
// ```
//     [id] [# members] []
//     [...members, each on a new line]
// ```
// ### Example
// ```
//     5 2
//     1 member-1
//     2 member-2
// ```
std::ostream& operator<<(std::ostream& out, const Team& rhs) {
  out << rhs.id() << " " << rhs.members().size() << "\n";
  for (const auto& member : rhs.members()) out << member << "\n";
  // for(const auto& event : rhs.event_queue) out << event << "\n";
  return out;
}

std::istream& operator>>(std::istream& in, Team& rhs) {
  int members_size;
  in >> rhs.id_ >> members_size;
  std::vector<Client> members(members_size);
  for (auto& member : members) in >> member;
  rhs.members_ = members;
  return in;
}

bool Team::SerializeToOstream(std::ostream& out) const {
  out << *this;
  return true;
}

bool Team::ParseFromIstream(std::istream& in) {
  in >> *this;
  return true;
}

conway::Team& Team::CopyToProtobuf(conway::Team& pb) const {
  pb.set_id(id());
  // pb.set_name(name());
  pb.clear_name();
  pb.set_resources(resources());
  pb.set_income(income());
  pb.clear_members();
  for (const Client& member : members()) {
    conway::Client *client_pb = pb.add_members();
    member.CopyToProtobuf(*client_pb);
  }
  pb.clear_structures();
  /// TODO: no way to know what the structure_lookup table
  /// is supposed to be??
  return pb;
}
