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
  interface AssociativeContainer<K, V> extends HasDestructor {
    size(): number;
    set(key: K, value: V): boolean;
    get(key: K): V;
  }
  export interface Map<K, V> extends AssociativeContainer<K, V> {
    keys(): Vector<K>;
  }
  export interface Vector<T> extends AssociativeContainer<number, T> {
    push_back(value: T): void;
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
  export interface StructureProperties extends HasDestructor {
    name(): string;
    activationCost(): number;
    grid(): LifeGrid;
    income(): number;
    buildArea(): number;
    checks(): Vector<Vector2>;
  }
  /// a std::tuple of 4 ints
  interface StructureKey {}
  export interface Structure extends HasDestructor {
    getKey(): StructureKey;
    checkIntegrity(base: LifeGrid): boolean;
    active(): boolean;
    position(): Vector2;
    properties(): StructureProperties;
  }
  export interface Client extends HasDestructor {
    name(): string;
    id(): number;
  }
  export interface Room extends HasDestructor {
    Initialize(): void;
    SetName(newName: string): void;
    AddClient(client: Client): boolean;
    AddTeam(teamMembers: Vector<Client>): number;
    AddToTeam(teamId: Team, client: Client): boolean;
    GetTeam(teamId: number): Team;
    LoadStructures(structures: Vector<StructureProperties>): void;
    Tick(): void;
    name(): string;
    structureLookup(): Vector<StructureProperties>;
    time(): number;
    clients(): Map<number, Client>;
    teams(): Map<number, Team>;
    grid(): LifeGrid;
  }
  export interface Team extends HasDestructor {
    checkStructureIntegrity(grid: LifeGrid): void;
    addStructure(structure: Structure): void;
    id(): number;
    members(): Vector<Client>;
    structures(): Map<StructureKey, Structure>;
    resources(): number;
    income(): number;
    lastIncomeUpdate(): number;
  }

  export interface ConwayLib {
    Vector2: {
      new (x: number, y: number): Vector2;
    };
    LifeState: typeof LifeState;
    LifeGrid: {
      new (dimensions: Vector2): LifeGrid;
    };
    StructureProperties: {
      new (
        name: string,
        activationCost: number,
        income: number,
        buildArea: number,
        grid: LifeGrid,
        checks: Vector<Vector2>,
      ): StructureProperties;
    };
    Structure: {
      new (properties: StructureProperties, position: Vector2): Structure;
    };
    Client: {
      new (id: number, name: string): Client;
    };
    Room: {
      new (name: string, dimensions: Vector2): Room;
    };
    Team: {
      new (id: number, members: Vector<Client>): Team;
    };
    Vector2Vector: Type<Vector<Vector2>>;
    ClientVector: Type<Vector<Client>>;
    StructurePropertiesVector: Type<Vector<StructureProperties>>;
  }
}

const Conway = (await ConwayWasm()) as wasm.ConwayLib;
export default Conway;
