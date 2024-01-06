import { useEffect, useState } from "react";
import { RoomCreateData, RoomJoinData, UseClientSocket } from "./Socket";
import { Client } from "@/lib";

function Lobby({ clientSocket }: UseClientSocket) {
  const [name, setName] = useState<string>("");
  const [members, setMembers] = useState<Client[]>([]);

  useEffect(() => {
    const processEvent = (event: CustomEvent<RoomCreateData>) => {
      const { name, clients } = event.detail;
      setName(name);
      setMembers(clients);
    };
    clientSocket.addEventListener("roomCreate", processEvent);
    return () => clientSocket.removeEventListener("roomCreate", processEvent);
  }, []);

  useEffect(() => {
    const processEvent = (event: CustomEvent<RoomJoinData>) => {
      const { newClient } = event.detail;
      setMembers((members) => [...members, newClient]);
    };
    clientSocket.addEventListener("roomJoin", processEvent);
    return () => clientSocket.removeEventListener("roomJoin", processEvent);
  }, []);

  return (
    <>
      <div>
        Room name: {name} <br />
        Members: {members.map(({ name }) => name).join(", ")}
      </div>
    </>
  );
}

export default Lobby;
