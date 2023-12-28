#include "emscripten/bind.h"

#include "conway/life_grid.hh"
#include "conway/structure.hh"
#include "conway/structure_properties.hh"
#include "utility/vector2.hh"

EMSCRIPTEN_BINDINGS(Utility) {
  emscripten::class_<Vector2>("Vector2")
      .constructor<int, int>()
      .function("x", &Vector2::x)
      .function("y", &Vector2::y)
      .function("set_x", &Vector2::set_x)
      .function("set_y", &Vector2::set_y);
}

EMSCRIPTEN_BINDINGS(Conway) {
  emscripten::class_<LifeGrid>("LifeGrid")
      .constructor<const Vector2 &>()
      .function("dimensions", &LifeGrid::dimensions)
      .function("GetCell", &LifeGrid::GetCell)
      .function("Load", &LifeGrid::Load)
      .function("Compare", &LifeGrid::Compare)
      .function("Tick", &LifeGrid::Tick);

  emscripten::class_<StructureProperties>("StructureProperties")
      .constructor<const std::string &, int, int, int, const LifeGrid &,
                   const std::vector<Vector2> &>()
      .function("name", &StructureProperties::name)
      .function("activation_cost", &StructureProperties::activation_cost)
      .function("grid", &StructureProperties::grid)
      .function("income", &StructureProperties::income)
      .function("build_area", &StructureProperties::build_area)
      .function("checks", &StructureProperties::checks);

  emscripten::class_<Structure>("Structure")
      .constructor<const StructureProperties &, const Vector2 &>()
      .function("CheckIntegrity", &Structure::CheckIntegrity)
      .function("active", &Structure::active)
      .function("position", &Structure::position)
      .function("properties", &Structure::properties);
}
