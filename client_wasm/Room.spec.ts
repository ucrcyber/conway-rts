/**
 * Test emscripten compiled //conway_rts:room
 */

import { expect, test } from "vitest";
import Conway from "@/lib";

test("constructor", () => {
  const room = new Conway.Room("TEST", new Conway.Vector2(1000, 1500));
  expect(room.name()).toBe("TEST");
  expect(room.grid().dimensions().x()).toBe(1000);
  expect(room.grid().dimensions().y()).toBe(1500);
  room.delete();
});

test("map wasm", () => {
  const room = new Conway.Room("TEST", new Conway.Vector2(10, 10));
  const c1 = new Conway.Client(1, "test");
  const teamMembers = new Conway.ClientVector();
  teamMembers.push_back(c1);
  room.AddTeam(teamMembers);
  // console.log(room.clients());
  // console.log(room.clients().get(1));
  // console.log(room.teams().get(1).members().get(0));

  const strGrid = new Conway.LifeGrid(new Conway.Vector2(3, 3));
  const strChecks = new Conway.Vector2Vector();
  const strProp = new Conway.StructureProperties("a", 0, 0, 0, strGrid, strChecks); // prettier-ignore
  const str = new Conway.Structure(strProp, new Conway.Vector2(5, 5));
  expect(str.checkIntegrity(room.grid())).toBe(true);
});
