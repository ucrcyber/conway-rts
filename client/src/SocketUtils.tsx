/**
 * Debug component for manually sending payloads to server.
 */

import { createRoom, register, requestRoomList } from "./Socket";

export type UseSocket = {
  socket: WebSocket;
};

function SocketUtils({ socket }: UseSocket) {
  const utils = [
    {
      label: "register",
      callback: () => register(socket, "TEST"),
    },
    {
      label: "list rooms",
      callback: () => requestRoomList(socket),
    },
    {
      label: "create room",
      callback: () => createRoom(socket),
    },
  ];
  return (
    <div>
      {utils.map(({ label, callback }, index) => (
        <button key={index} onClick={callback}>
          {label}
        </button>
      ))}
    </div>
  );
}

export default SocketUtils;
