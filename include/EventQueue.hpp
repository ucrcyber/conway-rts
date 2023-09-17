#ifndef CONWAY_INCLUDE_EVENTQUEUE_HPP
#define CONWAY_INCLUDE_EVENTQUEUE_HPP

#include <functional>
#include <queue>

#include "Event.hpp"

typedef std::pair<int, Event> EventWithTime;
typedef std::priority_queue<EventWithTime, std::vector<EventWithTime>, std::greater<>()> EventQueue;

#endif // CONWAY_INCLUDE_EVENTQUEUE_HPP