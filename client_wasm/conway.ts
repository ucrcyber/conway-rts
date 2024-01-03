/**
 * Typescript bindings for the emscripten outputs
 */

import ConwayWasm from "@/lib-wasm";

interface Type<T> extends Function {
  // eslint-disable-line @typescript-eslint/ban-types
  new (...args: any[]): T; // eslint-disable-line @typescript-eslint/no-explicit-any
}

export interface Vector2 {
  x: number;
  y: number;
}

enum LifeState {
  DEAD,
  ALIVE,
}

export interface LifeGrid {
  dimensions: Vector2;
  contents: boolean[][];
}

export interface StructureProperties {
  grid: LifeGrid;
  name: string;
  activationCost: number;
  income: number;
  buildArea: number;
  checks: Vector2[];
}

export interface Structure {
  position: Vector2;
  properties: StructureProperties;
}

export interface Client {
  id: number;
  name: string;
}

export interface Team {
  id: number;
  name: string;
  resources: number;
  income: number;
  members: Client[];
  structures: Structure[];
}

namespace wasm {
  export interface HasDestructor {
    delete(): void;
  }
  export interface Vector2 extends HasDestructor {
    x(): number;
    y(): number;
    set_x(x: number): void;
    set_y(y: number): void;
  }
  export interface LifeGrid extends HasDestructor {
    dimensions(): Vector2;
    GetCell(position: Vector2): boolean;
    SetCell(position: Vector2): void;
    ResetCell(position: Vector2): void;
    Load(payload: LifeGrid, position: Vector2): void;
    Compare(payload: LifeGrid, position: Vector2): number;
    Tick(): void;
  }
  export interface Client extends HasDestructor {
    name(): string;
    id(): number;
  }
  export interface Room extends HasDestructor {
    Initialize(): void;
    SetName(newName: string): void;
    // AddClient(client: Client): boolean;
    AddTeam(teamMembers: Client[]): number;
    // AddToTeam(teamId: Team, client: Client): boolean;
    GetTeam(teamId: number): Team;
    LoadStructures(structures: StructureProperties[]): void;
    Tick(): void;
    name(): string;
    structureLookup(): StructureProperties[];
    time(): number;
    // clients(): any;
    // teams(): any;
    grid(): LifeGrid;
  }
  export interface Team extends HasDestructor {}
}

interface ConwayLib {
  Vector2: Type<wasm.Vector2>;
  LifeState: typeof LifeState;
  LifeGrid: Type<wasm.LifeGrid>;
  Client: Type<wasm.Client>;
  Room: Type<wasm.Room>;
  Team: Type<wasm.Team>;
}

const Conway = (await ConwayWasm()) as ConwayLib;
export default Conway;
