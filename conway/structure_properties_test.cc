#include "conway/structure_properties.hh"

#include <gtest/gtest.h>

TEST(StructureProperties, initialization) {
  StructureProperties props;
  // std::cout << "from ostream<<\n" << props.grid;
  EXPECT_EQ(props.name(), "Empty 1x1");
  EXPECT_EQ(props.activation_cost(), 0);
  EXPECT_EQ(props.build_area(), 0);
  EXPECT_EQ(props.income(), 0);
  EXPECT_EQ(props.grid().dimensions(), Vector2(1, 1));
  EXPECT_EQ(props.checks().empty(), true);
}

TEST(StructureProperties, initialization_block) {
  std::istringstream buffer("2 2 ## ##");
  LifeGrid block;
  buffer >> block;
  StructureProperties props("Block", 65535, 65535, 65535, block, std::vector<Vector2>(1, Vector2(0, 1)));
  EXPECT_EQ(props.name(), "Block");
  EXPECT_EQ(props.activation_cost(), 65535);
  EXPECT_EQ(props.build_area(), 65535);
  EXPECT_EQ(props.income(), 65535);
  EXPECT_EQ(props.grid().dimensions(), Vector2(2, 2));
  EXPECT_EQ(props.checks().front(), Vector2(0, 1));
}

TEST(StructureProperties, istream_extraction) {
  std::istringstream buffer("Block 2x2\n65535 65535 65535 2 2 ## %#");
  StructureProperties props;
  buffer >> props;
  EXPECT_EQ(props.name(), "Block 2x2");
  EXPECT_EQ(props.activation_cost(), 65535);
  EXPECT_EQ(props.build_area(), 65535);
  EXPECT_EQ(props.income(), 65535);
  EXPECT_EQ(props.grid().dimensions(), Vector2(2, 2));
  ASSERT_EQ(props.checks().empty(), false)
    << "there should be 1 check for the template `2 2 ## #%`"
  ; // .front() will segfault if it's empty
  EXPECT_EQ(props.checks().front(), Vector2(0, 1));
}

TEST(StructureProperties, ostream_insertion) {
  // theres this funky stuff to ignore whitespace (any space is good enough)
  std::string base = "Block 2x2\n65535 65535 65535 2 2 ## %#";
  std::istringstream buffer(base), buffer_validate(base);
  std::ostringstream output_validate;
  StructureProperties props;
  buffer >> props;
  output_validate << props;
  std::istringstream result_buffer(output_validate.str());
  std::vector<std::string> expected_words, result_words;
  for(std::string s; buffer_validate >> s;) expected_words.push_back(s);
  for(std::string s; result_buffer >> s;) result_words.push_back(s);
  // for(auto x : result_words) std::cout << x << " ";
  EXPECT_EQ(expected_words, result_words);
}