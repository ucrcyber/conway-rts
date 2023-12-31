import { useEffect, useState } from "react";
import SocketLogger from "./SocketLogger";
import SocketUtils from "./SocketUtils";

const server_url = "ws://localhost:3000";

function App() {
  const [socket, setSocket] = useState<WebSocket | null>(null);

  useEffect(() => {
    console.log("Creating websocket");
    const s = new WebSocket(server_url);
    s.onopen = ({ timeStamp }) => console.log(timeStamp, "opened");
    s.onclose = ({ timeStamp }) => console.log(timeStamp, "closed");
    s.addEventListener("message", ({ data }) => console.log(data));
    setSocket(s);
    return () => s?.close();
  }, []);

  return (
    <>
      <div>Hello world</div>
      {socket && <SocketUtils socket={socket} />}
      {socket && <SocketLogger socket={socket} />}
    </>
  );
}

export default App;
