#include "StructureProperties.hpp"

#include <sstream>
#include <map>

StructureProperties::StructureProperties():
  StructureProperties::StructureProperties(
    "Empty 1x1", 0, 0, 0, LifeGrid(), std::vector<Vector2>()
  )
{}

StructureProperties::StructureProperties(
  const std::string& name, const int activation_cost, const int income,
  const int build_area, const LifeGrid& grid, const std::vector<Vector2>& checks
): 
  _name(name), _activation_cost(activation_cost), _income(income),
  _build_area(build_area), _grid(grid), _checks(checks)
{}

StructureProperties::StructureProperties(const StructureProperties& other): StructureProperties() {
  *this = other;
}

StructureProperties& StructureProperties::operator=(const StructureProperties& rhs) {
  if(this !=& rhs) {
    _name = rhs.name;
    _activation_cost = rhs.activation_cost;
    _grid = rhs.grid;
    _income = rhs.income;
    _build_area = rhs.build_area;
    _checks = rhs.checks;
  }
  return *this;
}

// ### Format
// ```
//     [name]
//     [cost] [income] [area]
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
//     %#
//     ##
// ```
std::ostream& operator<<(std::ostream& out, const StructureProperties& rhs){
  out << rhs.name << "\n" << rhs.activation_cost << " " << rhs.income << " "
    << rhs.build_area << "\n"
    << rhs.grid.dimensions.y << " " << rhs.grid.dimensions.x << "\n";
  const std::string grid_symbols = ".#:%";

  // std::cout << "??" << std::endl << rhs.grid.dimensions << std::endl;

  int k = 0;
  for(int i = 0; i < rhs.grid.dimensions.y; ++i){
    for(int j = 0; j < rhs.grid.dimensions.x; ++j){
      const Vector2 pos(j, i);
      const bool set = rhs.grid.GetCell(pos) == LifeState::ALIVE;
      bool ok = false;
      if(k < rhs.checks.size()){
        if(rhs.checks[k] == pos){
          ok = true;
          ++k;
        }
      }
      out << grid_symbols[2*(ok) | set];
    }
    out << "\n";
  }

  return out;
}

std::istream& operator>>(std::istream& in, StructureProperties& rhs){
  int height, width;

  std::getline(in >> std::ws, rhs._name);
  
  in >> rhs._activation_cost >> rhs._income >> rhs._build_area;
  in >> height >> width;

  std::ostringstream grid_filtered;
  grid_filtered << height << " " << width << "\n";
  
  std::map<char, int> grid_symbols {
    {'.', 0},
    {'#', 1},
    {':', 2},
    {'%', 3},
  };

  rhs._checks.clear();
  for(int i = 0; i < height; i ++){
    for(int j = 0; j < width; j ++){
      char c;
      in >> c;
      const int id = grid_symbols[c];
      grid_filtered << (id & 1 ? '#' : '.');
      if(id & 2){
        rhs._checks.push_back(Vector2(j, i));
      }
    }
    grid_filtered << '\n';
  }
  std::istringstream grid_in(grid_filtered.str());
  grid_in >> rhs._grid;
  
  return in;
}

bool StructureProperties::SerializeToOstream(std::ostream& out) const {
  out << *this;
  return true;
}

bool StructureProperties::ParseFromIstream(std::istream& in) {
  in >> *this;
  return true;
}