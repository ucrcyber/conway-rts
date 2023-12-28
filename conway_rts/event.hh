#ifndef CONWAY_INCLUDE_EVENT_HPP
#define CONWAY_INCLUDE_EVENT_HPP

#include <iostream>
#include <vector>

#include "conway_rts/array_buffer.hh"

// TODO: maybe make individual classes if there are more events in the future?
// enum class EventType {
//   EMPTY = 0,

//   BUILD,
// };

/// this is exclusively the BUILD EVENT (for now)
class Event {
 public:
  Event();
  Event(const int time, const int id, const ArrayBuffer& data);

  Event(const Event& other);
  Event& operator=(const Event& rhs);

  bool operator<(const Event& other) const;
  bool operator>(const Event& other) const;
  bool operator==(const Event& other) const;
  bool operator!=(const Event& other) const;

  friend std::ostream& operator<<(std::ostream& out, const Event& rhs);
  friend std::istream& operator>>(std::istream& in, Event& rhs);
  bool SerializeToOstream(std::ostream& out) const;
  bool ParseFromIstream(std::istream& in);

  int time() const {
    return time_;
  }
  int id() const {
    return id_;
  }
  const ArrayBuffer& data() const {
    return data_;
  }

 private:
  int time_ = 0;

  /// @brief ids are not assigned until they are broadcast
  // to determine the order they should be processed in, and to detect
  // missing events
  int id_ = 0;
  ArrayBuffer data_;
};

#endif // CONWAY_INCLUDE_EVENT_HPP