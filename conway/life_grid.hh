#ifndef CONWAY_INCLUDE_LIFEGRID_HPP
#define CONWAY_INCLUDE_LIFEGRID_HPP

#include <vector>

#include "conway/life_state.hh"
#include "conway/life_grid.pb.h"
#include "utility/vector2.hh"

// TODO: write iterators (they should exist?)

/// @brief basic implementation of a Life grid
class LifeGrid {
 public:
  /// @brief constructs an 1x1 empty life grid
  LifeGrid();

  LifeGrid(const LifeGrid& other);
  LifeGrid& operator=(const LifeGrid& rhs);

  bool operator==(const LifeGrid& other) const;
  bool operator!=(const LifeGrid& other) const;

  /// @brief constructs an empty life grid
  /// @param width 
  /// @param height 
  LifeGrid(const int width, const int height);

  /// @brief constructors an empty life grid
  /// @param dimensions 
  LifeGrid(const Vector2& dimensions);

  /// @brief constructors a lifegrid from the given `grid`
  /// @param grid a square vector
  LifeGrid(const std::vector<std::vector<bool>>& grid);

  /// @brief query the status of a single cell
  /// @param position which cell
  /// @return cell state
  LifeState GetCell(const Vector2& position) const;

  /// @brief query the status of a single cell
  /// @param position which cell
  /// @return whether the cell is alive or dead
  bool IsCellAlive(const Vector2& position) const;

  /// @brief sets the specified cell as alive (set)
  /// @param position which cell
  void SetCell(const Vector2& position);

  /// @brief sets the specified cell as dead (reset)
  /// @param position which cell
  void ResetCell(const Vector2& position);

  /// @brief loads a payload LifeGrid onto the LifeGrid;
  /// used for loading templates when players build something
  /// @param payload what to load
  /// @param offset where to load
  /// @return whether the operation was successful
  bool Load(const LifeGrid& payload, const Vector2& offset);

  /// @brief compare the payload LifeGrid with the current LifeGrid;
  /// the difference in cells is used to calculate build cost
  /// @param payload what to compare
  /// @param offset where to compare
  /// @return amount of cells that differ
  int Compare(const LifeGrid& payload, const Vector2& offset) const;

  /// @brief advances the game of life one generation
  void Tick();

  friend std::ostream& operator<<(std::ostream& out, const LifeGrid& rhs);
  friend std::istream& operator>>(std::istream& in, LifeGrid& rhs);
  bool SerializeToOstream(std::ostream& out) const;
  bool ParseFromIstream(std::istream& in);

  conway::LifeGrid& CopyToProtobuf(conway::LifeGrid& pb) const;

  // accessor/mutators
  Vector2 dimensions() const {
    return dimensions_;
  }
 private:
  /// @brief width and height of the grid
  /// (yes it's finite, at least for now)
  Vector2 dimensions_;

  /// @brief grid to represent the game of life grid
  /// (feel free to change the type if you want)
  std::vector<std::vector<bool>> grid_;

  /// @brief sets the internal grid to the given grid
  /// @param new_grid 
  void Initialize(const std::vector<std::vector<bool>>& new_grid);
};

#endif // CONWAY_INCLUDE_LIFEGRID_HPP