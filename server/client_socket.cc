#include "server/client_socket.hh"

#include <stdexcept>

int ClientSocket::instance_count = 1;

void ClientSocket::Initialize(const std::string &name) {
  if (name.empty()) throw std::invalid_argument("name should not be an empty string");
  client = Client(ClientSocket::instance_count, name);
  ++ClientSocket::instance_count;
}

bool ClientSocket::IsInitialized() const {
  return !client.name().empty();
}
