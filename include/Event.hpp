#ifndef CONWAY_INCLUDE_EVENT_HPP
#define CONWAY_INCLUDE_EVENT_HPP

#include <vector>

#include "ISerializable.hpp"

/// 2D vector for positional coordinates (immutable)
class Event: public ISerializable<Event> {
  private:
    int _time = 0;
    int _id = 0;
    std::vector<char> _data;
  public:
    // https://stackoverflow.com/a/5424521/21507383 public readonly, private variables

    /// @brief readonly time
    const int& time = _time;

    /// @brief readonly id
    const int& id = _id;

    /// @brief readonly data
    const std::vector<char>& data = _data;

    Event();
    Event(const int time, const int id, const std::vector<char>& data);
};

#endif // CONWAY_INCLUDE_EVENT_HPP