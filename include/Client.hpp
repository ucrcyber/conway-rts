#ifndef CONWAY_INCLUDE_CLIENT_HPP
#define CONWAY_INCLUDE_CLIENT_HPP

#include <vector>
#include <string>

#include "ISerializable.hpp"
#include "StructureProperties.hpp"
#include "Event.hpp"

/// @brief a single client and the actions they want to do
class Client: public ISerializable<Client> {
  private:
    std::string _name;
    int _id;
    /// @brief events from the client to process
    std::vector<Event> _events;
  public:
    const std::string& name = _name;
    const int& id = _id;
    const std::vector<Event>& events = _events;

    void AddBuildEvent(const int time, const StructureProperties& building, const Vector2& position);
};

#endif // CONWAY_INCLUDE_CLIENT_HPP