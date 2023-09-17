#ifndef CONWAY_INCLUDE_STRUCTURE_HPP
#define CONWAY_INCLUDE_STRUCTURE_HPP

#include <string>

#include "ISerializable.hpp"
#include "StructureProperties.hpp"
#include "Vector2.hpp"

/// @brief an instance of a structure type
class Structure: public ISerializable<Structure> {
  private:
    bool _active = true;
    Vector2 _position;
    StructureProperties _properties;
  public:
    const bool& active = _active;
    const Vector2& position = _position;
    const StructureProperties& properties = _properties;
    
    /// @brief checks whether the structure is still intact; updates `active` property
    /// @param  life_grid life grid the structure is a part of
    /// @return `active`
    bool CheckIntegrity(const LifeGrid& life_grid);

    Structure(const StructureProperties& structure_template);
};

#endif // CONWAY_INCLUDE_STRUCTURE_HPP