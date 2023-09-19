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

    Structure();
    Structure(const StructureProperties& structure_template, const Vector2& position);

    Structure(const Structure& other);
    Structure& operator=(const Structure& rhs);

    friend std::ostream& operator<<(std::ostream& out, const Structure& rhs);
    friend std::istream& operator>>(std::istream& in, Structure& rhs);
    bool SerializeToOstream(std::ostream& out) const;
    bool ParseFromIstream(std::istream& in);
};

#endif // CONWAY_INCLUDE_STRUCTURE_HPP