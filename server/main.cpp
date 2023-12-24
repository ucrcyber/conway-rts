#include "App.h"

/* Note that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support */

constexpr int PORT = 3000;
constexpr bool using_SSL = true;

/* ws->getUserData returns one of these */
struct PerSocketData {
  int counter = 0; // counts how many messages a client sent (for testing)
};

// typedef uWS::WebSocket<using_SSL, true, PerSocketData> WebSocket;
// this type is really buggy with vscode intellisense

int main() {
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
    .open = [](auto *ws) -> void {
      PerSocketData& user_data = *(ws->getUserData());
      std::cout << "open" << user_data.counter << std::endl;
    },
    .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
      PerSocketData& user_data = *(ws->getUserData());
      ++(user_data.counter);

      // echo message back
      ws->send(message, opCode, message.length() > 16 * 1024);
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
      PerSocketData& user_data = *(ws->getUserData());
      std::cout << "close" << user_data.counter << std::endl;
    }
  }).listen(PORT, [](auto *listen_socket) {
    if (listen_socket) {
      std::cout << "Listening on port " << PORT << std::endl;
    }
  }).run();

  std::cout << "Failed to listen on port " << PORT << std::endl;
}
