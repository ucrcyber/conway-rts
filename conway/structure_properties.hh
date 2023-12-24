#ifndef CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP
#define CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP

#include <sstream>
#include <string>
#include <vector>

#include "conway/life_grid.hh"
#include "utility/vector2.hh"

class StructureProperties {
  private:
    std::string _name;
    int _activation_cost;
    LifeGrid _grid;
    int _income;
    int _build_area;
    std::vector<Vector2> _checks;
  public:
    const std::string& name = _name;
    const int& activation_cost = _activation_cost;
    const LifeGrid& grid = _grid;
    const int& income = _income;
    const int& build_area = _build_area;

    /// @brief coordinate offsets to check during an structure integrity check
    // (this *should* be sorted by y first then x from construction)
    const std::vector<Vector2>& checks = _checks;

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
};

#endif // CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP