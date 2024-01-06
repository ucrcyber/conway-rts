#include "conway/structure_properties.hh"

#include <sstream>
#include <map>

StructureProperties::StructureProperties():
  StructureProperties::StructureProperties(
    "Empty 1x1", LifeGrid()
  )
{}

StructureProperties::StructureProperties(
  const std::string& name, const LifeGrid& grid
):
  StructureProperties::StructureProperties(
    name, 0, 0, 0, grid, std::vector<Vector2>()
  )
{}

StructureProperties::StructureProperties(
  const std::string& name, const int activation_cost, const int income,
  const int build_area, const LifeGrid& grid, const std::vector<Vector2>& checks
): 
  name_(name), activation_cost_(activation_cost), income_(income),
  build_area_(build_area), grid_(grid), checks_(checks)
{}

StructureProperties::StructureProperties(const StructureProperties& other): StructureProperties() {
  *this = other;
}

StructureProperties& StructureProperties::operator=(const StructureProperties& rhs) {
  if(this !=& rhs) {
    name_ = rhs.name();
    activation_cost_ = rhs.activation_cost();
    grid_ = rhs.grid();
    income_ = rhs.income();
    build_area_ = rhs.build_area();
    checks_ = rhs.checks();
  }
  return *this;
}

bool StructureProperties::operator==(const StructureProperties& other) const {
  if(this == &other) return true;
  if(activation_cost_ != other.activation_cost()) return false;
  if(build_area_ != other.build_area()) return false;
  if(checks_ != other.checks()) return false;
  if(income_ != other.income()) return false;
  if(name_ != other.name()) return false;
  if(grid_ != other.grid()) return false;
  return true;
}

bool StructureProperties::operator!=(const StructureProperties& other) const {
  return !(*this == other);
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
//     Block
//     0 0 0
//     2 2
//     %#
//     ##
// ```
std::ostream& operator<<(std::ostream& out, const StructureProperties& rhs){
  const int height = rhs.grid().dimensions().x();
  const int width = rhs.grid().dimensions().y();

  out << rhs.name() << "\n" << rhs.activation_cost() << " " << rhs.income() << " "
    << rhs.build_area() << "\n"
    << height << " " << width << "\n";
  const std::string grid_symbols = ".#:%";

  // std::cout << "??" << std::endl << rhs.grid.dimensions << std::endl;

  int k = 0;
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      const Vector2 pos(j, i);
      const bool set = rhs.grid().GetCell(pos) == LifeState::ALIVE;
      bool ok = false;
      if(k < rhs.checks().size()){
        if(rhs.checks()[k] == pos){
          ok = true;
          ++k;
        }
      }
      out << grid_symbols[2*(ok) | (int)set];
    }
    out << "\n";
  }

  return out;
}

std::istream& operator>>(std::istream& in, StructureProperties& rhs){
  int height, width;

  std::getline(in >> std::ws, rhs.name_);
  
  in >> rhs.activation_cost_ >> rhs.income_ >> rhs.build_area_;
  in >> height >> width;

  std::ostringstream grid_filtered;
  grid_filtered << height << " " << width << "\n";
  
  std::map<char, int> grid_symbols {
    {'.', 0},
    {'#', 1},
    {':', 2},
    {'%', 3},
  };

  rhs.checks_.clear();
  for(int i = 0; i < height; i ++){
    for(int j = 0; j < width; j ++){
      char c;
      in >> c;
      const int id = grid_symbols[c];
      grid_filtered << (id & 1 ? '#' : '.');
      if(id & 2){
        rhs.checks_.push_back(Vector2(j, i));
      }
    }
    grid_filtered << '\n';
  }
  std::istringstream grid_in(grid_filtered.str());
  grid_in >> rhs.grid_;
  
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

conway::StructureProperties& StructureProperties::CopyToProtobuf(conway::StructureProperties &pb) const {
  pb.set_activation_cost(activation_cost());
  pb.set_build_area(build_area());
  pb.set_income(income());
  pb.set_name(name());
  grid().CopyToProtobuf(*pb.mutable_grid());
  pb.clear_checks();
  for (const Vector2 &check : checks()) {
    conway::Vector2 *check_pb = pb.add_checks();
    check.CopyToProtobuf(*check_pb);
  }
  return pb;
}
