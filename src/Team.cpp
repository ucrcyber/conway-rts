#include "Team.hpp"

#include <utility>

Team::Team(): Team::Team(0)
{}

Team::Team(const int id): Team::Team(id, std::vector<Client>())
{}

Team::Team(const int id, const std::vector<Client>& members):
  _id(id), _members(members)
{}

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
  if (id != other.id) return false;
  if (members != other.members) return false;
  return true;
}

bool Team::operator!=(const Team& other) const {
  return !(*this == other);
}

bool Team::AddMember(const Client& new_member) {
  for (const auto& member : members) {
    // should be fine since there won't be that many people per team (<10?, <<100?)
    if (new_member == member) return false;
  }
  _members.push_back(new_member);
  return true;
}

const Client& Team::GetLeader() const {
  if(members.empty()) throw std::logic_error("cannot Team::GetLeader(), no members in team");
  return members.front();
}

bool Team::SetLeader(const Client& new_leader) {
  if (members.empty()) return false;
  if (GetLeader() == new_leader) return true;
  for (auto& member : _members) {
    if (new_leader == member) {
      std::swap(member, _members.front());
      return true;
    }
  }
  return false;
}

void Team::AddEventToQueue(const Event& event) {
  event_queue.push({event.time, event});
}

void Team::Tick(const int time, const EventQueue& event_queue) {

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
  out << rhs.id << " " << rhs.members.size() << "\n";
  for (const auto& member : rhs.members) out << member << "\n";
  // for(const auto& event : rhs.event_queue) out << event << "\n";
  return out;
}

std::istream& operator>>(std::istream& in, Team& rhs) {
  int members_size;
  in >> rhs._id >> members_size;
  std::vector<Client> members(members_size);
  for (auto& member : members) in >> member;
  rhs._members = members;
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