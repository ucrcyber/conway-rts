#include "LifeGrid.hpp"

#include "gtest/gtest.h"

TEST(LifeGrid, initialization){
  LifeGrid x(5, 5);
  for(int i = 0; i < 5; i ++){
    for(int j = 0; j < 5; j ++){
      EXPECT_EQ(x.getCell(Vector2(i, j)), LifeState::DEAD);
    }
  }
}

TEST(LifeGrid, templateLoading_setCell){
  LifeGrid x(5, 5);
  for(int i = 0; i < 5; i ++){
    for(int j = 0; j < 5; j ++){
      x.setCell(Vector2(i, j), LifeState::ALIVE);
      EXPECT_EQ(x.getCell(Vector2(i, j)), LifeState::ALIVE) << "setCell should've updated the cell to be alive";
      x.setCell(Vector2(i, j), LifeState::DEAD);
      EXPECT_EQ(x.getCell(Vector2(i, j)), LifeState::DEAD) << "setCell should've re-updated the cell to be dead";
    }
  }
}

TEST(LifeGrid, templateLoading_smallTemplate){
  LifeGrid x(5, 5);
  for(int i = 0; i < 5; i ++){
    for(int j = 0; j < 5; j ++){
      x.loadTemplate(Vector2(i, j), LifeTemplate("#"));
      EXPECT_EQ(x.getCell(Vector2(i, j)), LifeState::ALIVE) << "loadTemplate should've updated the cell to alive";
    }
  }
}

TEST(LifeGrid, templateDifference){
  LifeGrid x(5, 5);
  EXPECT_EQ(x.compareTemplate(Vector2(0, 0), LifeTemplate("#")), 1) << "initial board is all dead";
  EXPECT_EQ(x.compareTemplate(Vector2(0, 0), LifeTemplate("#####\n###..\n..###")), 11) << "initial board is all dead so there should be 5+3+3=11 alive from the template (that aren't alive on the board)";
  x.loadTemplate(Vector2(1, 1), LifeTemplate("##\n##"));
  EXPECT_EQ(x.compareTemplate(Vector2(1, 1), LifeTemplate("##\n##")), 0) << "template should've been loaded correctly (so now difference is zero)";
  EXPECT_EQ(x.compareTemplate(Vector2(0, 0), LifeTemplate("###\n...\n###")), 3+2+1);
}

TEST(LifeGrid, nextGeneration){
  LifeGrid g(10, 10);
  LifeTemplate glider(".#.\n..#\n###"),
    glider2("...\n#.#\n.##\n.#."),
    glider3("...\n..#\n#.#\n.##"),
    glider4(".\n.#\n..##\n.##");
  // .#.. .... .... .... ....
  // ..#. #.#. ..#. .#.. ..#.
  // ###. .##. #.#. ..## ...#
  // .... .#.. .##. .##. .###
  Vector2 offset(2, 2);
  g.loadTemplate(offset, glider);
  for(int steps = 0; steps < 3; steps ++){
    EXPECT_EQ(g.compareTemplate(offset, glider), 0);
    g.step();
    EXPECT_EQ(g.compareTemplate(offset, glider2), 0);
    g.step();
    EXPECT_EQ(g.compareTemplate(offset, glider3), 0);
    g.step();
    EXPECT_EQ(g.compareTemplate(offset, glider4), 0);
    g.step();
    offset = offset + Vector2(1, 1);
  }
}