#ifndef CONWAY_INCLUDE_MAGICBYTES_H
#define CONWAY_INCLUDE_MAGICBYTES_H

/// @brief bytes used when doing serialization for network
enum class MagicBytes {
  EVENT,
  VECTOR2,

  STRUCTURE,
  STRUCTURE_PROPERTIES,
  LIFE_GRID,

  CLIENT,
  TEAM,
  ROOM,

  NONVECTOR = 2047,
  VECTOR = 2048,
};

#endif // CONWAY_INCLUDE_MAGICBYTES_H