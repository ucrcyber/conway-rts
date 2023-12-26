#ifndef CONWAY_INCLUDE_STRUCTURE_HPP
#define CONWAY_INCLUDE_STRUCTURE_HPP

#include <string>
#include <tuple>
#include <iostream>

#include "conway/structure_properties.hh"
#include "utility/vector2.hh"

/// @brief used for sorting, but when you still want to modify non-sort properties
// `[position] [properties.grid.dimensions]`
typedef std::tuple<int, int, int, int> StructureKey;

/// @brief an instance of a structure type
class Structure {
 public:
  Structure();
  Structure(const StructureProperties& structure_template, const Vector2& position);

  Structure(const Structure& other);
  Structure& operator=(const Structure& rhs);

  bool operator<(const Structure& other) const;
  bool operator>(const Structure& other) const;
  bool operator==(const Structure& other) const;
  bool operator!=(const Structure& other) const;

  /// @brief generates a tuple of references that is used for sorting
  /// @return 
  const StructureKey GetKey() const;

  /// @brief checks whether the structure is still intact; updates `active` property
  /// @param  life_grid life grid the structure is a part of
  /// @return `active`
  bool CheckIntegrity(const LifeGrid& life_grid);

  friend std::ostream& operator<<(std::ostream& out, const Structure& rhs);
  friend std::istream& operator>>(std::istream& in, Structure& rhs);
  bool SerializeToOstream(std::ostream& out) const;
  bool ParseFromIstream(std::istream& in);

  bool active() const {
    return active_;
  }
  Vector2 position() const {
    return position_;
  }
  const StructureProperties& properties() const {
    return properties_;
  }
 private:
  bool active_ = false; // initially off, afte
  Vector2 position_;
  StructureProperties properties_;
};

#endif // CONWAY_INCLUDE_STRUCTURE_HPP