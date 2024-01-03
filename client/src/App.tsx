import { useEffect, useState } from "react";
import SocketLogger from "./SocketLogger";
import SocketUtils from "./SocketUtils";
import { ClientWebSocket } from "./Socket";
import RoomListing from "./RoomListing";
import Lobby from "./Lobby";

const server_url = "ws://localhost:3000";

function App() {
  const [clientSocket, setClientSocket] = useState<ClientWebSocket | null>(
    null,
  );

  useEffect(() => {
    const s = new ClientWebSocket(server_url);
    setClientSocket(s);
    return () => s?.close();
  }, []);

  return (
    <>
      <div>Hello world</div>
      {clientSocket && <SocketUtils socket={clientSocket.socket} />}
      {clientSocket && <SocketLogger socket={clientSocket.socket} />}
      {clientSocket && <RoomListing clientSocket={clientSocket} />}
      {clientSocket && <Lobby clientSocket={clientSocket} />}
    </>
  );
}

export default App;
