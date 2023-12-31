/**
 * Methods for interacting with the server.
 */

import * as Proto from "@/proto";

export function register(socket: WebSocket, name: string) {
  const event = Proto.server.Event.create();
  event.register = { name };
  socket.send(Proto.server.Event.encode(event).finish());
}

export function requestRoomList(socket: WebSocket) {
  const event = Proto.server.Event.create();
  event.roomList = {};
  socket.send(Proto.server.Event.encode(event).finish());
}

export function createRoom(socket: WebSocket) {
  const event = Proto.server.Event.create();
  event.action = {};
  event.action.roomCreate = {};
  socket.send(Proto.server.Event.encode(event).finish());
}

export function joinRoom(socket: WebSocket, roomId: number) {
  const event = Proto.server.Event.create();
  event.action = {};
  event.action.roomJoin = {};
  event.action.roomJoin.roomId = roomId;
  socket.send(Proto.server.Event.encode(event).finish());
}
