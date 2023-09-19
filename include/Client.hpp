#ifndef CONWAY_INCLUDE_CLIENT_HPP
#define CONWAY_INCLUDE_CLIENT_HPP

#include <vector>
#include <string>

#include "ISerializable.hpp"
#include "StructureProperties.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"

/// @brief a single client and the actions they want to do
class Client: public ISerializable<Client> {
  private:
    std::string _name;
    int _id;
  public:
    const std::string& name = _name;
    const int& id = _id;

    Client();
    Client(const int id, const std::string& name);

    Client(const Client& other);
    Client& operator=(const Client& rhs);

    bool operator==(const Client& other) const;
    bool operator!=(const Client& other) const;

    // adds a build event to the given `queue`
    // ### Event Format
    // 4 bytes
    // ```
    // [client_id] [x] [y] [building_id]
    // ```
    void AddBuildEvent(EventQueue& queue, const int time, const int building_id, const Vector2& position);

    friend std::ostream& operator<<(std::ostream& out, const Client& rhs);
    friend std::istream& operator>>(std::istream& in, Client& rhs);
    bool SerializeToOstream(std::ostream& out) const;
    bool ParseFromIstream(std::istream& in);
};

#endif // CONWAY_INCLUDE_CLIENT_HPP