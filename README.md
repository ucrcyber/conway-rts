# conway-rts
conway rts cyber project (but still being designed)

## Dependencies

### Windows
- [chocolately](https://chocolatey.org/install)
  - [bazelisk](https://github.com/bazelbuild/bazelisk)
  - [git](https://community.chocolatey.org/packages/git.install)
  - [python](https://community.chocolatey.org/packages/python/3.12.1)
  - [nvm](https://community.chocolatey.org/packages/nvm)
- [VS Build Tools, C++ compiler](https://visualstudio.microsoft.com/downloads/?q=build+tools#build-tools-for-visual-studio-2022)

### Linux
- [bazelisk](https://github.com/bazelbuild/bazelisk)
- gcc version 8+ (using c++2a), ideally gcc version 10+ (for c++20 support)
  - [gsrc](https://www.gnu.org/software/gsrc/) can be used if pre-built binaries aren't available.

## Running
```
bazel query ...                       # list targets
bazel test ...                        # run all tests
bazel build ...                       # build all targets (config pattern still applies)
bazel run //:refresh_compile_commands # initialize intellisense files
bazel run //server                    # builds and starts the game server
npm run test                          # runs vitest (clientside tests)
npm run dev                           # runs the client
```

# Rough UML Diagram
![Conway UML (rough outline)](https://user-images.githubusercontent.com/12877445/228439601-63ad39d7-092e-426e-adc2-eb87175a0ccd.jpeg)

## UML Description
- `Player` represents an individual client
- `Team` is an actual player with resources and existing structures, but might have multiple operators aka `Player`
- `Room` represents a game room.
  - `Room::initialize()` is used to start a game (clear the board and setup player positions)
  - `Room::processTick()` handles updating the game state to advance a step
  - `Room::buildStructure()` is used to figure out who
- `ILifeGrid` is the interface for implementing a LifeGrid (grid for Conway's game of life)
  - `ILifeGrid::getCell()` for querying cells (determine if a structure is still active)
  - `ILifeGrid::setCell()` for setting individual cells (probably to be private)
  - `ILifeGrid::loadTemplate()` for loading a template (cell configuration)
  - `ILifeGrid::compareTemplate()` returns the amount of cells that differ from the template
  - `ILifeGrid::step()` advances the grid by one generation according to Conway's game of  life rules
- `Vector2` is just a 2D Vector for positions
- `LifeTemplate` represents a cell configuration "template"
- `StructureTemplate` includes a `LifeTemplate` and various other structure stats (cost, resourceRate - either income or upkeep, buildArea - how much it extends area you can build, visionArea - how much it shows you if we're doing fog of war)
- `Structure` abstract class buidls on `StructureTemplate` but requires a method for checking a structure's integrity (is it still active?)
- server `main()` manages the `Room` instances and also processes socket input, mapping them to a player to invoke an action

- `Panel` is a general JSX component (div) that we treat as widget for UI elements.
- `TeamPanel` is used to display team details
- `StructurePanel` is used to display structure status for a client
- `StructureTemplatePanel` is to show building options for the user
- `LifeGrid` is the JS implementation of GameOfLife that pretty much handles everything the server also handles. We might use a second LifeGrid as a "future preview" so user can see what happens more intuitively.
