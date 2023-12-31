import { useEffect, useState } from "react";
import { UseSocket } from "./SocketUtils";

function SocketLogger({ socket }: UseSocket) {
  const [logs, setLogs] = useState<string[]>([]);

  useEffect(() => {
    const processEvent = async (event: MessageEvent) => {
      console.log(event.data);
      if (event.data instanceof Blob) {
        const arrayBuffer = await event.data.arrayBuffer();
        const view = new Uint8Array(arrayBuffer);
        const log = [...view]
          .map((x: number) => x.toString(16).padStart(2, "0"))
          .join(" ");
        setLogs((logs) => [...logs, log]);
      } else {
        setLogs((logs) => [...logs, event.data as string]);
      }
    };
    socket.addEventListener("message", processEvent);
    return () => socket.removeEventListener("message", processEvent);
  }, []);

  return (
    <>
      <button onClick={() => socket.send("ping")}>Ping</button>
      <div>
        {logs.map((log, index) => (
          <div key={index}>{log}</div>
        ))}
      </div>
    </>
  );
}

export default SocketLogger;
