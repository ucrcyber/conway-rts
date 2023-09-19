#include "Structure.hpp"

#include "gtest/gtest.h"

TEST(Structure, initialization) {
  LifeGrid empty(5, 5);
  Structure structure;
}

TEST(Structure, CheckIntegrity) {
  std::istringstream buffer("Block 2x2\n65535 65535 65535 2 2 ## %#");
  StructureProperties props;
  buffer >> props;

  Vector2 position(1, 1);
  LifeGrid grid(5, 5);
  Structure structure(props, position);
  
  EXPECT_EQ(structure.CheckIntegrity(grid), false)
    << "structure has not been loaded yet (so it should fail the check)";
  grid.Load(position, props.grid);
  EXPECT_EQ(structure.CheckIntegrity(grid), true)
    << "structure is not loaded, check should pass";
}