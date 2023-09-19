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

TEST(Event, iostream) {
  Event event(65535, 99999, {'q', 'w', 'e'});
  std::ostringstream o_buffer;
  o_buffer << event;
  std::istringstream i_buffer(o_buffer.str());
  Event event2;
  i_buffer >> event2;
  EXPECT_EQ(event.id, event2.id);
  EXPECT_EQ(event.time, event2.time);
  EXPECT_EQ(event.data, event2.data);
}