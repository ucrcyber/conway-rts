#include "emscripten/bind.h"

#include "conway/life_grid.hh"
#include "conway/structure.hh"
#include "conway/structure_properties.hh"
#include "conway_rts/client.hh"
#include "conway_rts/room.hh"
#include "conway_rts/team.hh"
#include "utility/vector2.hh"

EMSCRIPTEN_BINDINGS(Utility) {
  emscripten::class_<Vector2>("Vector2")
      .constructor<>()
      .constructor<int, int>()
      .function("x", &Vector2::x)
      .function("y", &Vector2::y)
      .function("set_x", &Vector2::set_x)
      .function("set_y", &Vector2::set_y);
}

EMSCRIPTEN_BINDINGS(Conway) {
  emscripten::enum_<LifeState>("LifeState")
      .value("DEAD", LifeState::DEAD)
      .value("ALIVE", LifeState::ALIVE);

  emscripten::register_vector<std::vector<bool>>("Bool2DVector");
  emscripten::class_<LifeGrid>("LifeGrid")
      .constructor<const Vector2 &>()
      .function("dimensions", &LifeGrid::dimensions)
      .function("GetCell", &LifeGrid::IsCellAlive)
      .function("SetCell", &LifeGrid::SetCell)
      .function("ResetCell", &LifeGrid::ResetCell)
      .function("Load", &LifeGrid::Load)
      .function("Compare", &LifeGrid::Compare)
      .function("Tick", &LifeGrid::Tick);
  
  emscripten::register_vector<Vector2>("Vector2Vector");
  emscripten::class_<StructureProperties>("StructureProperties");
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

EMSCRIPTEN_BINDINGS(ConwayRTS) {
  emscripten::register_vector<StructureProperties>("StructurePropertiesVector");

  emscripten::class_<Client>("Client")
      .constructor<int, const std::string &>()
      .function("name", &Client::name)
      .function("id", &Client::id);
  
  emscripten::class_<Room>("Room")
      .constructor<const std::string &, const Vector2 &>()
      .function("Initialize", &Room::Initialize)
      .function("SetName", &Room::SetName)
      .function("AddClient", &Room::AddClient)
      .function("AddTeam", &Room::AddTeam)
      .function("AddToTeam", &Room::AddToTeam)
      .function("RemoveFromTeam", &Room::RemoveFromTeam)
      .function("RemoveClient", &Room::RemoveClient)
      .function("LoadStructures", &Room::LoadStructures)
      .function("Tick", &Room::Tick)
      .function("name", &Room::name)
      .function("structureLookup", &Room::structure_lookup)
      .function("time", &Room::time)
      .function("clients", &Room::clients)
      .function("teams", &Room::teams)
      .function("grid", &Room::grid)
      .function("eventQueue", &Room::event_queue);

  emscripten::class_<Team>("Team")
      .constructor<>()
      .constructor<int>()
      .constructor<int, const std::vector<Client> &>()
      .function("AddMember", &Team::AddMember)
      .function("GetLeader", &Team::GetLeader) // these methods seem to break emcc
      .function("SetLeader", &Team::SetLeader)
      .function("AddEventToQueue", &Team::AddEventToQueue)
      .function("Tick", &Team::Tick)
      .function("CheckStructureIntegrity", &Team::CheckStructureIntegrity)
      .function("AddStructure", &Team::AddStructure)
      .function("id", &Team::id)
      .function("members", &Team::members)
      .function("structures", &Team::structures)
      .function("event_queue", &Team::event_queue)
      .function("resources", &Team::resources)
      .function("income", &Team::income)
      .function("last_income_update", &Team::last_income_update)
      ;
}
