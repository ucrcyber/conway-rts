#ifndef CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP
#define CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP

#include <string>

#include "ISerializable.hpp"
#include "LifeGrid.hpp"

class StructureProperties: public ISerializable<StructureProperties> {
  private:
    std::string _name;
    int _activation_cost;
    LifeGrid _grid;
    int _income;
    int _build_area;
  public:
    const std::string& name = _name;
    const int& activation_cost = _activation_cost;
    const LifeGrid& grid = _grid;
    const int& income = _income;
    const int& build_area = _build_area;

    StructureProperties();
    StructureProperties(const std::string& name, const int activation_cost, const LifeGrid& grid, const int income, const int build_area);
};

#endif // CONWAY_INCLUDE_STRUCTUREPROPERTIES_HPP