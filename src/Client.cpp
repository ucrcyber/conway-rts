#include "Client.hpp"

Client::Client(): Client::Client(0, "")
{}

Client::Client(const int id, const std::string& name):
  _id(id), _name(name)
{}

Client::Client(const Client& other): Client() {
  *this = other;
}

Client& Client::operator=(const Client& other) {
  if(this != &other) {
    _id = other.id;
    _name = other.name;
  }
  return *this;
}

void Client::AddBuildEvent(
  EventQueue& queue, const int time, const int building_id,
  const Vector2& position
) {
  std::vector<char> payload;
  Event event(time, 0, payload);
  queue.push(EventWithTime(time, event));
}

// ### Format
// ```
//     [id] [name]
// ```
// `name` should not have newlines
// ### Example
// ```
//     5 Hello world
// ```
std::ostream& operator<<(std::ostream& out, const Client& rhs) {
  out << rhs.id << " " << rhs.name;
  return out;
}

std::istream& operator>>(std::istream& in, Client& rhs) {
  in >> rhs._id;
  in.ignore(1);
  std::getline(in, rhs._name);
  return in;
}

bool Client::SerializeToOstream(std::ostream& out) const {
  out << *this;
  return true;
}

bool Client::ParseFromIstream(std::istream& in) {
  in >> *this;
  return true;
}