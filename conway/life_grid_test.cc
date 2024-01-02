#include "conway/life_grid.hh"

#include <gtest/gtest.h>

TEST(LifeGrid, initialization) {
  LifeGrid grid(5, 5);
  for(int i = 0; i < 5; ++i) {
    for(int j = 0; j < 5; ++j) {
      EXPECT_EQ(grid.GetCell(Vector2(i, j)), LifeState::DEAD);
    }
  }
}

TEST(LifeGrid, initialization_small_nonzero) {
  const std::vector<std::vector<bool>> base {{true, false}, {false, false}};
  const LifeGrid grid(base);
  EXPECT_EQ(grid.GetCell(Vector2(0, 0)), LifeState::ALIVE);
  EXPECT_EQ(grid.GetCell(Vector2(1, 0)), LifeState::DEAD);
  EXPECT_EQ(grid.GetCell(Vector2(0, 1)), LifeState::DEAD);
  EXPECT_EQ(grid.GetCell(Vector2(1, 1)), LifeState::DEAD);
}

TEST(LifeGrid, load_small) {
  const std::vector<std::vector<bool>> single {{true}};
  LifeGrid grid(5, 5), small_grid(single);
  for(int i = 0; i < 5; i ++){
    for(int j = 0; j < 5; j ++){
      grid.Load(small_grid, Vector2(i, j));
      EXPECT_EQ(grid.GetCell(Vector2(i, j)), LifeState::ALIVE) 
        << "loadTemplate should've updated the cell to alive"
        " at " << Vector2(i, j);
    }
  }
}

TEST(LifeGrid, istream_extraction){
  std::istringstream in("3 3 ### #.# .#.");
  LifeGrid grid;
  in >> grid;
  std::vector<std::vector<bool>> expected {
    {true, true, true},
    {true, false, true},
    {false, true, false},
  };
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(grid.GetCell(Vector2(i, j)), expected[j][i] ? LifeState::ALIVE : LifeState::DEAD);
    }
  }
}

TEST(LifeGrid, templateDifference) {
  std::istringstream in(
    "1 1 # "
    "3 5 ##### ###.. ..### "
    "2 2 ## ## "
    "3 3 ### ... ###"
  );
  LifeGrid single, large, block, hamburger;
  in >> single >> large >> block >> hamburger;

  // std::cout << single << "\n" << large << std::endl;

  LifeGrid grid(5, 5);
  EXPECT_EQ(grid.Compare(single, Vector2(0, 0)), 1)
    << "initial board is all dead";
  EXPECT_EQ(grid.Compare(large, Vector2(0, 0)), 11)
    << "initial board is all dead so there should be 5+3+3=11 alive"
      "from the template (that aren't alive on the board)";
  grid.Load(block, Vector2(1, 1));
  EXPECT_EQ(grid.Compare(block, Vector2(1, 1)), 0)
    << "template should've been loaded correctly (so now difference is zero)";
  EXPECT_EQ(grid.Compare(block, Vector2(0, 0)), 3)
    << "only one of the original set cells is alive in this shifted offset";
  EXPECT_EQ(grid.Compare(hamburger, Vector2(0, 0)), 3+2+1);
}

TEST(LifeGrid, nextGeneration){
  std::istringstream in(
    "3 3 .#. ..# ### "
    "4 3 ... #.# .## .#. "
    "4 3 ... ..# #.# .## "
    "4 4 .... .#.. ..## .##. "
  );
  // .#.. .... .... .... ....
  // ..#. #.#. ..#. .#.. ..#.
  // ###. .##. #.#. ..## ...#
  // .... .#.. .##. .##. .###
  LifeGrid glider1, glider2, glider3, glider4;
  in >> glider1 >> glider2 >> glider3 >> glider4;

  LifeGrid grid(10, 10);
  Vector2 offset(2, 2);
  grid.Load(glider1, offset);
  for(int steps = 0; steps < 3; steps ++){
    EXPECT_EQ(grid.Compare(glider1, offset), 0);
    grid.Tick();
    EXPECT_EQ(grid.Compare(glider2, offset), 0);
    grid.Tick();
    EXPECT_EQ(grid.Compare(glider3, offset), 0);
    grid.Tick();
    EXPECT_EQ(grid.Compare(glider4, offset), 0);
    grid.Tick();
    offset = offset + Vector2(1, 1);
  }
}

TEST(LifeGrid, copy_into_proto) {
  conway::LifeGrid pb;
  LifeGrid glider;

  // .#.
  // ..#
  // ###
  // ...
  std::istringstream in("4 3 .#. ..# ### ...");
  in >> glider;

  glider.CopyToProtobuf(pb);
  EXPECT_EQ(pb.dimensions().x(), 3);
  EXPECT_EQ(pb.dimensions().y(), 4);
  const std::vector<bool> expected { 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 };
  for (int i = 0; i < 12; ++i) {
    EXPECT_EQ(pb.flat_grid().at(i), expected[i]) << "checking i=" << i;
  }
}