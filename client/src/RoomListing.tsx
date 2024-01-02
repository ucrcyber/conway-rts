import { useEffect, useState } from "react";
import { RoomListData, UseClientSocket } from "./Socket";

function RoomListing({ clientSocket }: UseClientSocket) {
  const [rooms, setRooms] = useState<RoomListData>([]);

  useEffect(() => {
    const processEvent = (event: CustomEvent<RoomListData>) => {
      setRooms(event.detail);
      console.log(event.detail);
    };
    clientSocket.addEventListener("roomList", processEvent);
    return () => clientSocket.removeEventListener("roomList", processEvent);
  }, []);

  return (
    <>
      <div>
        {rooms.map(({ name, id, size }, index) => (
          <div key={index}>
            {name} ({size})<div>#{id}</div>
            <button onClick={() => clientSocket.joinRoom(id)}>Join</button>
          </div>
        ))}
      </div>
    </>
  );
}

export default RoomListing;
