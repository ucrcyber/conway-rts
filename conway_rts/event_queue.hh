#ifndef CONWAY_INCLUDE_EVENTQUEUE_HPP
#define CONWAY_INCLUDE_EVENTQUEUE_HPP

#include <functional>
#include <queue>
#include <deque>

#include "conway_rts/event.hh"

typedef std::pair<int, Event> EventWithTime;
typedef std::priority_queue<
  EventWithTime,
  std::vector<EventWithTime>,
  std::greater<EventWithTime>
> EventPriorityQueue;

typedef std::deque<Event> EventQueue;

#endif // CONWAY_INCLUDE_EVENTQUEUE_HPP