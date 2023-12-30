import Conway from "@/lib";
import { useCallback, useEffect, useState } from "react";

type InteractiveLifeGridProps = {
  width: number;
  height: number;
};

function InteractiveLifeGrid({ width, height }: InteractiveLifeGridProps) {
  const [, updateState] = useState({});
  const [isPlaying, setPlaying] = useState(false);
  const forceUpdate = useCallback(() => updateState({}), []);
  const [grid] = useState(
    new Conway.LifeGrid(new Conway.Vector2(width, height)),
  );

  useEffect(() => {
    const interval = setInterval(() => {
      if (isPlaying) {
        grid.Tick();
        forceUpdate();
      }
    }, 50);
    return () => clearInterval(interval);
  }, [isPlaying]);

  return (
    <>
      <div className='lifegrid'>
        {[...new Array(grid.dimensions().y())].map((_, i) => (
          <div key={i} className='lifegrid-row'>
            {[...new Array(grid.dimensions().x())].map((_, j) => (
              <div
                key={j}
                className={
                  grid.GetCell(new Conway.Vector2(j, i))
                    ? "lifegrid-alive"
                    : "lifegrid-dead"
                }
                onClick={() => {
                  const pos = new Conway.Vector2(j, i);
                  if (!grid.GetCell(pos)) grid.SetCell(pos);
                  else grid.ResetCell(pos);
                  forceUpdate();
                }}
              ></div>
            ))}
          </div>
        ))}
      </div>
      <button
        onClick={() => {
          grid.Tick();
          forceUpdate();
        }}
      >
        Tick
      </button>
      <button onClick={() => setPlaying(!isPlaying)}>
        {isPlaying ? "Pause" : "Play"}
      </button>
    </>
  );
}

export default InteractiveLifeGrid;
