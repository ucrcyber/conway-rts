#include "LifeGrid.hpp"

LifeGrid::LifeGrid(): LifeGrid::LifeGrid(1, 1) {}

LifeGrid::LifeGrid(int width, int height):
  LifeGrid::LifeGrid(std::vector<std::vector<bool>>(height, std::vector<bool>(width, false)))
{}

LifeGrid::LifeGrid(const std::vector<std::vector<bool>>& new_grid) {
  Initialize(new_grid);
}

LifeGrid::LifeGrid(const LifeGrid& other): LifeGrid() {
  *this = other;
}

LifeGrid& LifeGrid::operator=(const LifeGrid& other) {
  if(this != &other) {
    _dimensions = other.dimensions;
    grid = other.grid;
  }
  return *this;
}

void LifeGrid::Initialize(const std::vector<std::vector<bool>>& new_grid) {
  _dimensions = std::move(Vector2(new_grid.empty() ? 0 : new_grid.front().size(), new_grid.size()));
  grid = new_grid;
}

LifeState LifeGrid::GetCell(const Vector2& coordinate) const {
  return grid[coordinate.y][coordinate.x] ? LifeState::ALIVE : LifeState::DEAD;
}

bool LifeGrid::Load(const LifeGrid& life_grid, const Vector2& offset) {
  const Vector2 bottom_right = offset + life_grid.dimensions;
  if(bottom_right.x > dimensions.x || bottom_right.y > dimensions.y) return false;

  int oy = offset.y;
  int ox = offset.x;
  for(int i = 0; i < life_grid.dimensions.y; ++i) {
    for(int j = 0; j < life_grid.dimensions.x; ++j) {
      grid[oy+i][ox+j] = life_grid.grid[i][j]; 
    }
  }
  return true;
}

int LifeGrid::Compare(const LifeGrid& life_grid, const Vector2& offset) const {
  int diff_count = 0;
  int oy = offset.y;
  int ox = offset.x;
  for(int i = 0; i < life_grid.dimensions.y; ++i) {
    for(int j = 0; j < life_grid.dimensions.x; ++j) {
      if(this->grid[oy+i][ox+j] != life_grid.grid[i][j]) {
        ++diff_count;
      }
    }
  }
  return diff_count;
}

void LifeGrid::Tick() {
  // very unoptimized code
  std::vector<std::vector<bool>> new_grid(grid);
  const int width = dimensions.x, height = dimensions.y;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      // count live neighbors
      int live_neighbors = 0;
      for(int dy = -1; dy <= 1; dy++) {
        for(int dx = -1; dx <= 1; dx++) {
          if(dx == 0 && dy == 0) continue;
          int ny = i+dy;
          int nx = j+dx;
          if(ny < 0 || nx < 0 || ny >= height || nx >= width) continue;
          if(this->grid[ny][nx]) ++live_neighbors;
        }
      }

      // rules
      // < 2 - dies
      // =2,3 - survives
      // =  3 - born
      // > 3 - dies
      new_grid[i][j] =
        (grid[i][j] && (live_neighbors == 2 || live_neighbors == 3))
        || (!grid[i][j] && live_neighbors == 3);
    }
  }
  grid = new_grid;
}

// ### Format
// ```
//     [height] [width]
//     [...lines]
// ```
// `.` dead
// `#` alive
// ### Example
// ```
//     3 5
//     ..##.
//     ##..#
//     ..##.
// ```
std::ostream& operator<<(std::ostream &out, const LifeGrid &rhs) {
  out << rhs.dimensions.y << ' ' << rhs.dimensions.x << '\n';
  for(const auto &row : rhs.grid) {
    for(auto x : row) {
      out << (x ? '#' : '.');
    }
    out << '\n';
  }
  return out;
}

std::istream& operator>>(std::istream &in, LifeGrid &rhs) {
  int height, width;
  in >> height >> width;
  std::vector<std::vector<bool>> new_grid(height, std::vector<bool>(width));
  for(int i = 0; i < height; i ++) {
    for(int j = 0; j < width; j ++) {
      char x;
      in >> x;
      new_grid[i][j] = x == '#';
    }
  }
  rhs.Initialize(new_grid);
  return in;
}

bool LifeGrid::SerializeToOstream(std::ostream &out) const {
  out << *this;
  return true;
}

bool LifeGrid::ParseFromIstream(std::istream &in) {
  in >> *this;
  return true;
}