#include "StructureProperties.hpp"

StructureProperties::StructureProperties(
  const std::string& name, const int activation_cost, const LifeGrid& grid,
  const int income, const int build_area
): 
  _name(name), _activation_cost(activation_cost), _grid(grid),
  _income(income), _build_area(build_area)
{}

// ### Format
// ```
//     [name] [cost] [income] [area]
//     [height] [width]
//     [...lines]
// ```
// `:` empty (checked)
// `.` empty
// `#` filled
// `%` filled (checked)
// ### Example
// ```
//     Block 0 0 0
//     2 2
//     ##
//     ##
// ```
std::ostream& operator<<(std::ostream &out, const StructureProperties &rhs){
  out << rhs.name << " " << rhs.activation_cost << " " << rhs.income << " "
    << rhs.build_area << "\n"
    << rhs.grid.dimensions.y << " " << rhs.grid.dimensions.x << "\n";
  
  for(int i = 0; i < rhs.grid.dimensions.y; i ++){
    for(int j = 0; j < rhs.grid.dimensions.x; j ++){
      const bool set = rhs.grid.GetCell(Vector2(i, j)) == LifeState::ALIVE;
      out << (set ? '#' : '.');
    }
    out << "\n";
  }

  return out;
}

std::istream& operator>>(std::istream &in, StructureProperties &rhs){
  int height, width;

  in >> rhs._name >> rhs._activation_cost >> rhs._income >> rhs._build_area;
  in >> height >> width;

  Vector2 v(width, height);
  
  return in;
}