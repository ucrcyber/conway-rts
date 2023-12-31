#include "App.h"

#include <map>

#include "conway_rts/room.hh"
#include "server/client_socket.hh"
#include "server/socket.pb.h"
#include "utility/vector2.hh"

/* Note that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support */

constexpr int PORT = 3000;
constexpr bool using_SSL = true;

typedef ClientSocket PerSocketData;
typedef uWS::WebSocket<using_SSL, true, PerSocketData> WebSocket;
// Note: make sure you're using C++20 for VScode intellisense

int main() {
  std::map<int, Room> rooms;
  rooms[-1] = Room("kitchen", Vector2(100, 100));

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
    .message = [&](WebSocket *ws, std::string_view message, uWS::OpCode opCode) {
      PerSocketData& user_data = *(ws->getUserData());
      ++(user_data.counter);

      // echo message back
      // ws->send(message, opCode, message.length() > 16 * 1024);
      
      server::Event event;
      if (event.ParseFromArray(&*message.begin(), message.size())) {
        std::cout << "[rx] event\n";
        switch (event.event_case()) {
          case server::Event::EventCase::EVENT_NOT_SET:
            std::cout << "unset event??";
            break;
          case server::Event::EventCase::kRegister: {
            if (event.has_register_() && !user_data.IsInitialized()) {
              user_data.Initialize(event.register_().name());
              event.mutable_register_()->set_acknowledged(true);
              std::string ack;
              event.SerializeToString(&ack);
              ws->send(ack);
            }
            break;
          }
          case server::Event::EventCase::kRoomList: {
            event.mutable_room_list()->clear_rooms();
            for (const auto& [room_key, room] : rooms) {
              conway::RoomListing &room_listing = *event.mutable_room_list()->add_rooms();
              room_listing.set_id(room_key);
              room_listing.set_client_count(room.clients().size());
              room_listing.set_name(room.name());
            }
            std::string ack;
            event.SerializeToString(&ack);
            ws->send(ack);
            break;
          }
          case server::Event::EventCase::kAction: {
            switch (event.action().event_case()) {
              case conway::Event::EventCase::EVENT_NOT_SET: break;
              case conway::Event::EventCase::kRoomCreate: {
                break;
              }
              case conway::Event::EventCase::kRoomJoin: {
                break;
              }
              case conway::Event::EventCase::kRoomLeave: {
                break;
              }
              case conway::Event::EventCase::kBaseInitialize: break;
              case conway::Event::EventCase::kBaseBuild: break;
              default:
                std::cout << "invalid action case??";
            }
            break;
          }
          default:
            std::cout << "event undefined??";
        }
        std::cout << std::endl;
      } else {
        std::cout << "[rx] (unknown) " << message << std::endl;
      }
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
