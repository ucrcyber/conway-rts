import { useEffect, useState } from "react";

type SocketLoggerProps = {
  socket: WebSocket;
};

function SocketLogger({ socket }: SocketLoggerProps) {
  const [logs, setLogs] = useState<string[]>([]);

  useEffect(() => {
    const processEvent = (event: MessageEvent) => {
      setLogs(logs => [...logs, event.data as string]);
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
