#include "Structure.hpp"

#include <istream>
#include <ostream>

#include "StructureProperties.hpp"

Structure::Structure(): Structure::Structure(StructureProperties(), Vector2(0, 0))
{}

Structure::Structure(const StructureProperties& structure_properties, const Vector2& position):
  _active(true),
  _position(position),
  _properties(structure_properties)
{}

Structure::Structure(const Structure& other): Structure() {
  *this = other;
}

Structure& Structure::operator=(const Structure& rhs) {
  if (this !=& rhs) {
    _active = rhs.active;
    _position = rhs.position;
    _properties = rhs.properties;
  }
  return *this;
}

bool Structure::operator<(const Structure& other) const {
  if (*this == other) return false;
  if (position.x != other.position.x) return position.x < other.position.x;
  if (position.y != other.position.y) return position.y < other.position.y;
  if (properties.grid.dimensions.x != other.properties.grid.dimensions.x) return properties.grid.dimensions.x < other.properties.grid.dimensions.x;
  if (properties.grid.dimensions.y != other.properties.grid.dimensions.y) return properties.grid.dimensions.y < other.properties.grid.dimensions.y;
  return false;
}

bool Structure::operator>(const Structure& other) const {
  if (*this == other) return false;
  return !(*this < other);
}

bool Structure::operator==(const Structure& other) const {
  if (this == &other) return true;
  if (active != other.active) return false;
  if (position != other.position) return false;
  if (properties != other.properties) return false;
  return true;
}

bool Structure::operator!=(const Structure& other) const {
  return !(*this == other);
}

bool Structure::CheckIntegrity(const LifeGrid& life_grid) {
  for (const auto offset : properties.checks) {
    if (life_grid.GetCell(position + offset) != properties.grid.GetCell(offset)) {
      return false;
    }
  }
  return true;
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
  out << rhs.properties
  << rhs.active << ' ' << rhs.position;
  return out;
}

std::istream& operator>>(std::istream& in, Structure& rhs) {
  in >> rhs._properties >> rhs._active >> rhs._position;
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