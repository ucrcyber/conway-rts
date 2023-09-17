#ifndef CONWAY_INCLUDE_TEAM_HPP
#define CONWAY_INCLUDE_TEAM_HPP

#include <string>
#include <vector>

#include "ISerializable.hpp"
#include "Client.hpp"
#include "Structure.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"

/// @brief a single team and the actions it wants to do (controlled from client actions)
class Team: public ISerializable<Team> {
  private:
    int _id = 0;
    std::vector<Client> _members;
    EventQueue _events;

    /// @brief events from `Client`s to process
    EventQueue event_queue;
  public:
    const int& id = _id;
    const std::vector<Client>& members = _members;
    const EventQueue& events = _events;

    /// @brief adds a new `Client` to `members`
    /// @param new_member 
    /// @return whether `new member` could be added or not (fails if already in team)
    bool AddMember(const Client& new_member);

    /// @brief returns the leader of the team, located at `members.front()`
    /// @return 
    const Client& GetLeader() const;

    /// @brief sets a new leader of the team
    /// @param new_leader 
    /// @return whether `new_leader` was found and able to be set
    bool SetLeader(const Client& new_leader);

    /// @brief Add an event to the internal queue to be processed
    /// @param event 
    void AddEventToQueue(const Event& event);

    /// @brief processes a tick for income and also any events that are happening now
    /// @param time 
    /// @param event_queue place to push events to be processed into
    void Tick(const int time, const EventQueue& event_queue);
};

#endif // CONWAY_INCLUDE_TEAM_HPP