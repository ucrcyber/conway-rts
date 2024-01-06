import { useEffect } from "react";
import { RoomCreateData, UseClientSocket } from "./Socket";
import { P5CanvasInstance, ReactP5Wrapper } from "@p5-wrapper/react";
import Conway from "@/lib";

function GameClient({ clientSocket }: UseClientSocket) {
  const grid = new Conway.LifeGrid(new Conway.Vector2(100, 100));
  const structureTypes = [
    [
      [1, 1],
      [1, 1],
    ],
    [
      [1, 1, 0, 1, 1],
      [1, 1, 0, 1, 1],
      [0, 0, 0, 0, 0],
      [1, 1, 0, 1, 1],
      [1, 1, 0, 1, 1],
    ],
    [
      [0, 1, 0],
      [0, 0, 1],
      [1, 1, 1],
    ],
    [
      [0, 0, 0, 0, 0, 0, 1, 0],
      [1, 1, 0, 0, 0, 0, 0, 0],
      [0, 1, 0, 0, 0, 1, 1, 1],
    ],
  ].map((baseGrid) => {
    const n = baseGrid.length;
    const m = baseGrid[0].length;
    const layout = new Conway.LifeGrid(new Conway.Vector2(m, n));
    for (let i = 0; i < n; ++i) {
      for (let j = 0; j < m; ++j) {
        if (baseGrid[i][j]) {
          layout.SetCell(new Conway.Vector2(j, i));
        }
      }
    }
    return new Conway.StructureProperties("A", 0, 0, 0, layout, new Conway.Vector2Vector()); // prettier-ignore
  });
  let selectedStructureType = structureTypes[0];
  let display = "";

  useEffect(() => {
    const processEvent = (event: CustomEvent<RoomCreateData>) => {
      const { name } = event.detail;
      display = name;
    };
    clientSocket.addEventListener("roomCreate", processEvent);
    return () => clientSocket.removeEventListener("roomCreate", processEvent);
  }, []);

  let timeMax = 0;
  useEffect(() => {
    const interval = setInterval(() => ++timeMax, 50);
    return () => clearInterval(interval);
  }, []);

  function sketch(p5: P5CanvasInstance) {
    p5.preload = () => {};
    p5.setup = () => {
      p5.createCanvas(600, 400, p5.P2D);
      p5.rectMode(p5.CENTER);
      p5.textAlign(p5.CENTER, p5.CENTER);
    };
    p5.keyTyped = () => {
      const { keyCode } = p5;
      if (keyCode >= 49 && keyCode <= 57) {
        const id = keyCode - 49;
        if (id < structureTypes.length) {
          selectedStructureType = structureTypes[id];
        }
      }
    };
    let cameraX = 0;
    let cameraY = 0;
    let time = 0;
    const SIDE_LENGTH = 10;
    function renderLifeGrid(
      grid: InstanceType<typeof Conway.LifeGrid>,
      offsetI: number = 0,
      offsetJ: number = 0,
      aliveColor: number | number[] = [0],
      deadColor: number | number[] = [255],
    ) {
      if (aliveColor instanceof Number) aliveColor = [aliveColor as number];
      if (deadColor instanceof Number) deadColor = [deadColor as number];
      const n = grid.dimensions().y();
      const m = grid.dimensions().x();
      const padding = 1;
      const i_begin = ~~Math.max(0, cameraY / SIDE_LENGTH - padding - offsetI);
      const i_end = ~~Math.min(
        n,
        (cameraY + p5.height) / SIDE_LENGTH + padding - offsetI,
      );
      const j_begin = ~~Math.max(0, cameraX / SIDE_LENGTH - padding - offsetJ);
      const j_end = ~~Math.min(
        m,
        (cameraX + p5.width) / SIDE_LENGTH + padding - offsetJ,
      );
      p5.push();
      p5.translate(offsetJ * SIDE_LENGTH, offsetI * SIDE_LENGTH);
      p5.fill(255, 0, 0, 100); // corner markers
      p5.rect(0, 0, SIDE_LENGTH + 2, SIDE_LENGTH + 2);
      p5.fill(0, 255, 0, 100);
      p5.rect((m - 1) * SIDE_LENGTH, (n - 1) * SIDE_LENGTH, SIDE_LENGTH + 2, SIDE_LENGTH + 2); // prettier-ignore
      for (let i = i_begin; i < i_end; ++i) {
        for (let j = j_begin; j < j_end; ++j) {
          p5.fill(
            ...((grid.GetCell(new Conway.Vector2(j, i))
              ? aliveColor
              : deadColor) as number[]),
          );
          p5.rect(
            j * SIDE_LENGTH,
            i * SIDE_LENGTH,
            SIDE_LENGTH - 1,
            SIDE_LENGTH - 1,
          );
        }
      }
      p5.pop();
    }
    let mousePressed = false;
    p5.mousePressed = () => (mousePressed = true);
    p5.keyPressed = () => ++timeMax;
    p5.draw = () => {
      if (time < timeMax) {
        ++time;
        grid.Tick();
      }
      p5.background(250);
      p5.noStroke();
      if (p5.mouseIsPressed) {
        cameraX -= p5.mouseX - p5.pmouseX;
        cameraY -= p5.mouseY - p5.pmouseY;
      }
      p5.push();
      p5.translate(-cameraX, -cameraY);
      const mouseI = Math.max(
        0,
        Math.min(100, Math.round((p5.mouseY + cameraY) / SIDE_LENGTH)),
      );
      const mouseJ = Math.max(
        0,
        Math.min(100, Math.round((p5.mouseX + cameraX) / SIDE_LENGTH)),
      );
      renderLifeGrid(grid, 0, 0);

      const placeI =
        mouseI - (selectedStructureType.grid().dimensions().y() >> 1);
      const placeJ =
        mouseJ - (selectedStructureType.grid().dimensions().x() >> 1);
      const placeVector = new Conway.Vector2(placeJ, placeI);
      renderLifeGrid(
        selectedStructureType.grid(),
        placeI,
        placeJ,
        [50, 0, 0, 100],
        [255, 200, 200, 100],
      );
      p5.push();
      p5.fill(0);
      p5.text(selectedStructureType.name(), mouseJ * SIDE_LENGTH, (placeI-1) * SIDE_LENGTH); // prettier-ignore
      p5.textAlign(p5.RIGHT, p5.CENTER);
      p5.translate((placeJ - 0.5) * SIDE_LENGTH, 0);
      p5.text(grid.Compare(selectedStructureType.grid(), placeVector), 0, placeI * SIDE_LENGTH); // prettier-ignore
      p5.text(selectedStructureType.activationCost(), 0, (placeI+1) * SIDE_LENGTH); // prettier-ignore
      p5.text(selectedStructureType.income() + "/t", 0, (placeI+2) * SIDE_LENGTH); // prettier-ignore
      p5.pop();
      if (mousePressed) {
        grid.Load(selectedStructureType.grid(), placeVector);
      }
      p5.pop();

      p5.fill(200);
      p5.rect(100, 15, 50, 30);
      p5.fill(255, 0, 0);
      p5.text(p5.frameRate().toFixed(1) + "FPS", 100, 10);
      p5.text(`${mouseJ},${mouseI}`, 100, 20);
      mousePressed = false;
    };
  }

  return (
    <>
      <ReactP5Wrapper sketch={sketch} />
    </>
  );
}

export default GameClient;
