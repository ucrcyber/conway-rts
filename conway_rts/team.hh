#ifndef CONWAY_INCLUDE_TEAM_HPP
#define CONWAY_INCLUDE_TEAM_HPP

#include <string>
#include <vector>
#include <map>

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

    std::map<StructureKey, Structure> _structures;

    /// @brief events from `Client`s to process
    EventQueue _event_queue;

    int _resources = 0;
    int _income = 0;

    /// @brief when the last income update was processed
    int _last_income_update = 0;
  public:
    const int& id = _id;
    const std::vector<Client>& members = _members;
    const std::map<StructureKey, Structure>& structures = _structures;
    const EventQueue& event_queue = _event_queue;
    const int& resources = _resources;
    const int& income = _income;

    // shouldn't have copy constructor since events, event_queue shouldn't
    // be copied since the main program only has a reference to one at the
    // beginning; workaround might be possible though with pointers?
    Team();
    Team(const int id);
    Team(const int id, const std::vector<Client>& members);

    // team with initial resources for testing; might be used in future as
    // part of configuration settings
    Team(const int id, const int initial_resources);

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
    /// @param grid
    /// @param structure_lookup structure lookup table to figure out what's going on so it can process it there
    void Tick(const int time, EventQueue& event_queue, const LifeGrid& grid, const std::vector<StructureProperties>& structure_lookup);

    /// @brief check integrity and update all structures
    /// @param grid 
    void CheckStructureIntegrity(const LifeGrid& grid);

    /// @brief add a new structure to the set of structures managed by this team
    /// @param new_structure
    void AddStructure(const Structure& new_structure);

    friend std::ostream& operator<<(std::ostream& out, const Team& rhs);
    friend std::istream& operator>>(std::istream& in, Team& rhs);
    bool SerializeToOstream(std::ostream& out) const;
    bool ParseFromIstream(std::istream& in);
};

#endif // CONWAY_INCLUDE_TEAM_HPP