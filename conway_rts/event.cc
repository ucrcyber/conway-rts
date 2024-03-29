#include "conway_rts/event.hh"

#include <limits>
#include <vector>

Event::Event(): Event(0, 0, ArrayBuffer())
{}

Event::Event(const int time, const int id, const ArrayBuffer& data):
  time_(time), id_(id), data_(data)
{}

Event::Event(const Event& other): Event() {
  *this = other;
}

Event& Event::operator=(const Event& other) {
  if(this != &other) {
    id_ = other.id();
    time_ = other.time();
    data_ = other.data();
  }
  return *this;
}

bool Event::operator<(const Event& other) const {
  if(*this == other) return false;
  if(id() != other.id()) return id() < other.id();
  else if(time() != other.time()) return time() < other.time();
  else return false;
}

bool Event::operator>(const Event& other) const {
  if(*this == other) return false;
  return !(*this < other);
}

bool Event::operator==(const Event& other) const {
  if(this == &other) return true;
  if(id() != other.id()) return false;
  if(time() != other.time()) return false;
  if(data() != other.data()) return false;
  return true;
}

bool Event::operator!=(const Event& other) const {
  return !(*this == other);
}

// ### Format
// ```
//     [data size] [time] [id]
//     [... data]
// ```
// ### Example
// ```
//     5 10 10
//     1 2 3 4 5
// ```
std::ostream& operator<<(std::ostream& out, const Event& rhs) {
  out << rhs.data().size() << " " << rhs.time() << " " << rhs.id() << "\n";
  for(const auto c : rhs.data()) out << c << " ";
  return out;
}

std::istream& operator>>(std::istream& in, Event& rhs) {
  int data_size;
  in >> data_size >> rhs.time_ >> rhs.id_;
  ArrayBuffer new_data(data_size);
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for(auto &c : new_data) in >> c; // in.get(c);
  rhs.data_ = new_data;
  return in;
}

bool Event::SerializeToOstream(std::ostream& out) const {
  out << *this;
  return true;
}

bool Event::ParseFromIstream(std::istream& in) {
  in >> *this;
  return true;
}