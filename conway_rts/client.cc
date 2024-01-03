#include "conway_rts/client.hh"

Client::Client(): Client::Client(0, "")
{}

Client::Client(const int id, const std::string& name):
  id_(id), name_(name)
{}

Client::Client(const Client& other): Client() {
  *this = other;
}

Client& Client::operator=(const Client& other) {
  if(this != &other) {
    id_ = other.id();
    name_ = other.name();
  }
  return *this;
}

bool Client::operator==(const Client& other) const {
  if(this == &other) return true;
  if(id() != other.id()) return false;
  if(name() != other.name()) return false;
  return true;
}

bool Client::operator!=(const Client& other) const {
  return !(*this == other);
}

const Event Client::CreateBuildEvent(
  const int time, const int building_id, const Vector2& position
) const {
  ArrayBuffer payload {id(), position.x(), position.y(), building_id};
  Event event(time, 0, payload);
  return event;
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
  out << rhs.id() << " " << rhs.name();
  return out;
}

std::istream& operator>>(std::istream& in, Client& rhs) {
  in >> rhs.id_;
  in.ignore(1);
  std::getline(in, rhs.name_);
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

conway::Client& Client::CopyToProtobuf(conway::Client &pb) const {
  pb.set_name(name());
  pb.set_id(id());
  return pb;
}

Client Client::placeholder = Client(-1, "");
