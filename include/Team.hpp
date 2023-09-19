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

    // shouldn't have copy constructor since events, event_queue shouldn't
    // be copied since the main program only has a reference to one at the
    // beginning; workaround might be possible though with pointers?
    Team();
    Team(const int id);
    Team(const int id, const std::vector<Client>& members);

    bool operator==(const Team& other) const;
    bool operator!=(const Team& other) const;

    /// @brief adds a new `Client` to `members`
    /// @param new_member 
    /// @return whether `new member` could be added or not (fails if already in team)
    bool AddMember(const Client& new_member);

    /// @brief returns the leader of the team, located at `members.front()`.
    // please don't call this on something with no members
    /// @return `members.front()`, or throws `std::logic_error` when there are no members
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

    friend std::ostream& operator<<(std::ostream& out, const Team& rhs);
    friend std::istream& operator>>(std::istream& in, Team& rhs);
    bool SerializeToOstream(std::ostream& out) const;
    bool ParseFromIstream(std::istream& in);
};

#endif // CONWAY_INCLUDE_TEAM_HPP