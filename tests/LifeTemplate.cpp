#include "gtest/gtest.h"
#include "../include/LifeTemplate.h"

TEST(LifeTemplate, initialization) {
    LifeTemplate x("#");
    EXPECT_EQ(x.getHeight(), 1);
    EXPECT_EQ(x.getWidth(), 1);

    std::vector<std::vector<bool>> expected {{true}};
    EXPECT_EQ(x.getTemplate(), expected);
}

TEST(LifeTemplate, ensureRectangleVector) {
    LifeTemplate x("###\n#.#\n####");
    EXPECT_EQ(x.getHeight(), 3);
    EXPECT_EQ(x.getWidth(), 4);
    
    std::vector<std::vector<bool>> expected {{true,true,true,false},{true,false,true,false},{true,true,true,true}};
    EXPECT_EQ(x.getTemplate(), expected) << "all rows should be expanded to the same width";
}