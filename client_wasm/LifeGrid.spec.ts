/**
 * Test emscripten compiled //utility:vector2
 */

import { expect, test } from "vitest";
import Conway from "@/lib";

test("constructor", () => {
  const lifeGrid = new Conway.LifeGrid(new Conway.Vector2(10, 15));
  expect(lifeGrid.dimensions().x()).toBe(10);
  expect(lifeGrid.dimensions().y()).toBe(15);
  lifeGrid.Tick();
});
