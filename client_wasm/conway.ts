/**
 * Typescript bindings for the emscripten outputs
 */

import ConwayWasm from "@/lib-wasm";

interface Type<T> extends Function {
  // eslint-disable-line @typescript-eslint/ban-types
  new (...args: any[]): T; // eslint-disable-line @typescript-eslint/no-explicit-any
}

export interface Vector2 {
  x: () => number;
  y: () => number;
  set_x: (x: number) => void;
  set_y: (y: number) => void;
}

enum LifeState {
  DEAD,
  ALIVE,
}

interface LifeGrid {
  dimensions: () => Vector2;
  GetCell: (position: Vector2) => boolean;
  SetCell: (position: Vector2) => void;
  ResetCell: (position: Vector2) => void;
  Load: (payload: LifeGrid, position: Vector2) => void;
  Compare: (payload: LifeGrid, position: Vector2) => number;
  Tick: () => void;
}

interface ConwayLib {
  Vector2: Type<Vector2>;
  LifeState: typeof LifeState;
  LifeGrid: Type<LifeGrid>;
}

const Conway = (await ConwayWasm()) as ConwayLib;
export default Conway;
