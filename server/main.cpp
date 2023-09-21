#include "App.h"

/* Note that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support */

constexpr int PORT = 3000;
constexpr bool using_SSL = true;

/* ws->getUserData returns one of these */
struct PerSocketData {
  int counter = 0; // counts how many messages a client sent (for testing)
};
typedef uWS::WebSocket<using_SSL, true, PerSocketData> WebSocket;

int main() {
  /* Overly simple hello world app */
  uWS::SSLApp({
    .key_file_name = "misc/key.pem",
    .cert_file_name = "misc/cert.pem",
    .passphrase = "1234"
  }).get("/*", [](auto *res, auto * /*req*/) {
    res->end("Hello world!");
  }).ws<PerSocketData>("/*", {
    /* Settings */
    .compression = uWS::CompressOptions(uWS::DEDICATED_COMPRESSOR_4KB | uWS::DEDICATED_DECOMPRESSOR),
    .maxPayloadLength = 100 * 1024 * 1024,
    .idleTimeout = 16,
    .maxBackpressure = 100 * 1024 * 1024,
    .closeOnBackpressureLimit = false,
    .resetIdleTimeoutOnSend = false,
    .sendPingsAutomatically = true,
    /* Handlers */
    .upgrade = nullptr,
    .open = [](auto *ws) {
      /* Open event here, you may access ws->getUserData() which points to a PerSocketData struct */
      std::cout << "open" << ws->getUserData()->counter << std::endl;
    },
    .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
      /* This is the opposite of what you probably want; compress if message is LARGER than 16 kb
        * the reason we do the opposite here; compress if SMALLER than 16 kb is to allow for 
        * benchmarking of large message sending without compression */
      ws->send(message, opCode, message.length() < 16 * 1024);
      ++(ws->getUserData()->counter);
    },
    .drain = [](auto */*ws*/) {
      /* Check ws->getBufferedAmount() here */
    },
    .ping = [](auto */*ws*/, std::string_view) {
      /* Not implemented yet */
    },
    .pong = [](auto */*ws*/, std::string_view) {
      /* Not implemented yet */
    },
    .close = [](auto *ws, int /*code*/, std::string_view /*message*/) {
      /* You may access ws->getUserData() here */
      std::cout << "close" << ws->getUserData()->counter << std::endl;
    }
  }).listen(PORT, [](auto *listen_socket) {
    if (listen_socket) {
      std::cout << "Listening on port " << PORT << std::endl;
    }
  }).run();

  std::cout << "Failed to listen on port " << PORT << std::endl;
}
