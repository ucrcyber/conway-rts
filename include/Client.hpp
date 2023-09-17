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

    void AddBuildEvent(const EventQueue& queue, const int time, const StructureProperties& building, const Vector2& position);
};

#endif // CONWAY_INCLUDE_CLIENT_HPP