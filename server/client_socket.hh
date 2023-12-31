#ifndef SERVER_CLIENTSOCKET_HH_
#define SERVER_CLIENTSOCKET_HH_

#include <string>

#include "conway_rts/client.hh"
#include "conway_rts/room.hh"
#include "conway_rts/team.hh"

/// @brief ws->getUserData returns one of these, used in the uwebsocket server
struct ClientSocket {
  int counter = 0;       // counts how many messages a client sent (for testing)
  Client client;         // client object, use to transform inputs into events
  Team *team = nullptr;  // team this client belongs to; push events into here
  Room *room = nullptr;  // room this client is in; used to notify client about the room

  /// used to determine next id (counter)
  static int instance_count;

  /// initializes the client with a name and unique id (name should be non empty)
  void Initialize(const std::string &name);

  /// returns whether this was initialized or not (non empty name)
  bool IsInitialized() const;
};

#endif // SERVER_CLIENTSOCKET_HH_
