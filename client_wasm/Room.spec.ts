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
});
