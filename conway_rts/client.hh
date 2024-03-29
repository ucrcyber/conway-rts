#ifndef CONWAY_INCLUDE_CLIENT_HPP
#define CONWAY_INCLUDE_CLIENT_HPP

#include <vector>
#include <string>

#include "conway/structure.hh"
#include "conway_rts/array_buffer.hh"
#include "conway_rts/event.hh"

/// @brief a single client and the actions they want to do
class Client {
 public:
  Client();
  Client(const int id, const std::string& name);

  Client(const Client& other);
  Client& operator=(const Client& rhs);

  bool operator==(const Client& other) const;
  bool operator!=(const Client& other) const;

  // adds a build event to the given `queue`
  // ### Event Format
  // 4 ints (16? bytes)
  // ```
  // [client_id] [x] [y] [building_id]
  // ```
  const Event CreateBuildEvent(const int time, const int building_id, const Vector2& position) const;

  friend std::ostream& operator<<(std::ostream& out, const Client& rhs);
  friend std::istream& operator>>(std::istream& in, Client& rhs);
  bool SerializeToOstream(std::ostream& out) const;
  bool ParseFromIstream(std::istream& in);

  const std::string& name() const {
    return name_;
  }
  int id() const {
    return id_;
  }

 private:
  std::string name_;
  int id_;
};

#endif // CONWAY_INCLUDE_CLIENT_HPP