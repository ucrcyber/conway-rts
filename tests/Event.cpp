#include "Event.hpp"

#include "gtest/gtest.h"

TEST(Event, initialization) {
  Event event;
  EXPECT_EQ(event.time, 0);
  EXPECT_EQ(event.id, 0);
  EXPECT_EQ(event.data.empty(), true);

  Event event_with_data(65535, 99999, {'q', 'w', 'e'});
  EXPECT_EQ(event_with_data.time, 65535);
  EXPECT_EQ(event_with_data.id, 99999);
  ASSERT_EQ(event_with_data.data.size(), 3);
  EXPECT_EQ(event_with_data.data.front(), 'q');
}
