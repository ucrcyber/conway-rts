/**
 * Test emscripten compiled //utility:vector2
 */

import { expect, test } from "vitest";
import Conway from '@/lib';

test("default constructor", () => {
  const u = new Conway.Vector2();
  expect(u.x()).toBe(0);
  expect(u.y()).toBe(0);
});

test("parameterized constructor", () => {
  const u = new Conway.Vector2(-727, 1234);
  expect(u.x()).toBe(-727);
  expect(u.y()).toBe(1234);
});

test("accessor & mutators", () => {
  const u = new Conway.Vector2();
  expect(u.x()).toBe(0);
  expect(u.y()).toBe(0);
  u.set_x(1234);
  expect(u.x()).toBe(1234);
  expect(u.y()).toBe(0);
  u.set_y(-9876);
  expect(u.x()).toBe(1234);
  expect(u.y()).toBe(-9876);
});
