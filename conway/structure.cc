#include "conway/structure.hh"

#include "conway/structure_properties.hh"

Structure::Structure(): Structure::Structure(StructureProperties(), Vector2(0, 0))
{}

Structure::Structure(const StructureProperties& structure_properties, const Vector2& position):
  active_(false),
  position_(position),
  properties_(structure_properties)
{}

Structure::Structure(const Structure& other): Structure() {
  *this = other;
}

Structure& Structure::operator=(const Structure& rhs) {
  if (this !=& rhs) {
    active_ = rhs.active();
    position_ = rhs.position();
    properties_ = rhs.properties();
  }
  return *this;
}

bool Structure::operator<(const Structure& other) const {
  if (*this == other) return false;
  if (position() != other.position()) return position() < other.position();
  if (properties().grid().dimensions() != other.properties().grid().dimensions()) return properties().grid().dimensions() < other.properties().grid().dimensions();
  return false;
}

bool Structure::operator>(const Structure& other) const {
  if (*this == other) return false;
  return !(*this < other);
}

bool Structure::operator==(const Structure& other) const {
  if (this == &other) return true;
  if (active() != other.active()) return false;
  if (position() != other.position()) return false;
  if (properties() != other.properties()) return false;
  return true;
}

bool Structure::operator!=(const Structure& other) const {
  return !(*this == other);
}

bool Structure::CheckIntegrity(const LifeGrid& life_grid) {
  active_ = true;
  for (const Vector2& offset : properties().checks()) {
    if (life_grid.GetCell(position() + offset) != properties().grid().GetCell(offset)) {
      active_ = false;
      break;
    }
  }
  return active_;
}

const StructureKey Structure::GetKey() const {
  const auto [x1, y1] = position();
  const auto [x2, y2] = properties().grid().dimensions();
  return std::make_tuple(x1, y1, x2, y2);
}

// ### Format
// ```
//     [*properties]
//     [active] [position]
// ```
// ### Example
// ```
//     Block 0 0 0
//     2 2
//     %#
//     ##
//     0 (5 10)
// ```
std::ostream& operator<<(std::ostream& out, const Structure& rhs) {
  out << rhs.properties()
  << rhs.active() << ' ' << rhs.position();
  return out;
}

std::istream& operator>>(std::istream& in, Structure& rhs) {
  in >> rhs.properties_ >> rhs.active_ >> rhs.position_;
  return in;
}

bool Structure::SerializeToOstream(std::ostream& out) const {
  out << *this;
  return true;
}

bool Structure::ParseFromIstream(std::istream& in) {
  in >> *this;
  return true;
}

conway::Structure& Structure::CopyToProtobuf(conway::Structure &pb) const {
  position().CopyToProtobuf(*pb.mutable_position());
  return pb;
}
