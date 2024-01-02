/**
 * Methods for interacting with the server.
 */

import * as Proto from "@/proto";
import { Vector2 } from "@/lib";
import { TypedEventTarget } from "typescript-event-target";

export type UseClientSocket = {
  clientSocket: ClientWebSocket;
};

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

export interface RegisterData {
  name: string;
  acknowledged: boolean;
}
export interface RoomDescription {
  id: number;
  name: string;
  size: number;
}
export type RoomListData = RoomDescription[];

/**
 * Sent to client when they join a room. Contains
 * room initialization data.
 */
export interface RoomCreateData {
  id: number;
  name: string;
  dimensions: Vector2;
}

interface ClientWebSocketEventMap {
  register: CustomEvent<RegisterData>;
  roomList: CustomEvent<RoomListData>;
  roomCreate: CustomEvent<number>;
  roomJoin: CustomEvent<number>;
  roomLeave: CustomEvent<number>;
}

export class ClientWebSocket extends TypedEventTarget<ClientWebSocketEventMap> {
  public readonly socket: WebSocket;
  constructor(url: string) {
    super();
    this.socket = new WebSocket(url);
    this.socket.addEventListener("message", (event: MessageEvent) =>
      this.processServerEvent(event),
    );
  }

  /**
   * Closes the socket.
   */
  public close() {
    this.socket.close();
  }

  /**
   * Sends a request to the server to join a room.
   * @param roomId which room to join
   */
  public joinRoom(roomId: number) {
    joinRoom(this.socket, roomId);
  }

  /**
   * Process server event, handler of WebSocket::message event
   * @param serverEvent MessageEvent to process
   */
  private async processServerEvent(serverEvent: MessageEvent) {
    const eventIssues = Proto.server.Event.verify(serverEvent);
    if (eventIssues !== null) throw new Error(eventIssues);
    if (serverEvent.data instanceof Blob) {
      const arrayBuffer = await serverEvent.data.arrayBuffer();
      const view = new Uint8Array(arrayBuffer);
      const event = Proto.server.Event.decode(view);
      switch (event.event) {
        case "register":
          {
            const name = event.register?.name ?? "?";
            const acknowledged = event.register?.acknowledged ?? false;
            const detail = { name, acknowledged };
            this.dispatchTypedEvent(
              "register",
              new CustomEvent("register", { detail }),
            );
          }
          break;
        case "roomList":
          {
            const rooms = event.roomList?.rooms ?? [];
            this.dispatchTypedEvent(
              "roomList",
              new CustomEvent("roomList", {
                detail: rooms.map((room) => ({
                  name: room.name ?? "?",
                  id: room.id ?? -1,
                  size: room.clientCount ?? -1,
                })),
              }),
            );
          }
          break;
        case "action":
          {
            this.processActionEvent(event.action as Proto.conway.Event);
            console.log(event.action);
          }
          break;
        default:
          throw new Error(`Invalid event type <${event.event}>`);
      }
    }
  }

  private processActionEvent(actionEvent: Proto.conway.Event) {}
}
