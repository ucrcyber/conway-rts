import { Client } from "@/lib";
import * as Proto from "@/proto";

export function decodePbClient(
  pb: Proto.conway.IClient | null | undefined,
): Client {
  return {
    id: pb?.id ?? -1,
    name: pb?.name ?? "",
  };
}
