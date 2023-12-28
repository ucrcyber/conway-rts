#ifndef CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP
#define CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP

#include <sstream>
#include <string>
#include <vector>

#include "conway/life_grid.hh"
#include "utility/vector2.hh"

class StructureProperties {
 public:
  /// @brief default constructor makes an empty 1x1 structure
  StructureProperties();

  /// @brief static one-time structure
  /// @param name 
  /// @param grid 
  StructureProperties(const std::string& name, const LifeGrid& grid);

  /// @brief dynamic structure
  /// @param name 
  /// @param activation_cost 
  /// @param income 
  /// @param build_area 
  /// @param grid 
  /// @param checks 
  StructureProperties(
    const std::string& name, const int activation_cost, const int income,
    const int build_area, const LifeGrid& grid, const std::vector<Vector2>& checks
  );

  StructureProperties(const StructureProperties& other);
  StructureProperties& operator=(const StructureProperties& rhs);

  bool operator==(const StructureProperties& other) const;
  bool operator!=(const StructureProperties& other) const;

  friend std::ostream& operator<<(std::ostream& out, const StructureProperties& rhs);
  friend std::istream& operator>>(std::istream& in, StructureProperties& rhs);
  bool SerializeToOstream(std::ostream& out) const;
  bool ParseFromIstream(std::istream& in);

  // accessors/mutators
  const std::string& name() const {
    return name_;
  }
  int activation_cost() const {
    return activation_cost_;
  }
  const LifeGrid& grid() const {
    return grid_;
  }
  int income() const {
    return income_;
  }
  int build_area() const {
    return build_area_;
  }
  const std::vector<Vector2>& checks() const {
    return checks_;
  }
 private:
  std::string name_;
  int activation_cost_;
  int income_;
  int build_area_;
  LifeGrid grid_;

  /// @brief coordinate offsets to check during an structure integrity check
  // (this *should* be sorted by y first then x from construction)
  std::vector<Vector2> checks_;
};

#endif // CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP