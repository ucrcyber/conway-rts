#ifndef CONWAY_INCLUDE_CLIENT_HPP
#define CONWAY_INCLUDE_CLIENT_HPP

#include <string>

#include "conway_rts/client.pb.h"
#include "conway_rts/event.hh"
#include "utility/vector2.hh"

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

  conway::Client& CopyToProtobuf(conway::Client &pb) const;

  // accessors/mutators
  const std::string& name() const {
    return name_;
  }
  int id() const {
    return id_;
  }

 private:
  int id_;
  std::string name_;
};

#endif // CONWAY_INCLUDE_CLIENT_HPP