#ifndef CONWAY_INCLUDE_LIFEGRID_HPP
#define CONWAY_INCLUDE_LIFEGRID_HPP

#include <vector>

#include "ISerializable.hpp"
#include "Vector2.hpp"
#include "LifeState.h"

// TODO: write iterators (they should exist?)

/// @brief basic implementation of a Life grid
class LifeGrid: public ISerializable<LifeGrid> {
  private:
    /// @brief width and height of the grid
    /// (yes it's finite, at least for now)
    Vector2 _dimensions;

    /// @brief grid to represent the game of life grid
    /// (feel free to change the type if you want)
    std::vector<std::vector<bool>> grid;

    /// @brief sets the internal grid to the given grid
    /// @param new_grid 
    void Initialize(const std::vector<std::vector<bool>>& new_grid);
  public:
    /// @brief public readonly width and height of the grid
    const Vector2& dimensions = _dimensions;
    
    /// @brief constructs an 1x1 empty life grid
    LifeGrid();

    LifeGrid(const LifeGrid& other);
    LifeGrid& operator=(const LifeGrid& rhs);

    /// @brief constructs an empty life grid
    /// @param width 
    /// @param height 
    LifeGrid(const int width, const int height);

    /// @brief constructors a lifegrid from the given `grid`
    /// @param grid a square vector
    LifeGrid(const std::vector<std::vector<bool>>& grid);

    /// @brief query the status of a single cell
    /// @param position which cell
    /// @return whether the cell is alive or dead
    LifeState GetCell(const Vector2& position) const;

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

    friend std::ostream& operator<<(std::ostream &out, const LifeGrid &rhs);
    friend std::istream& operator>>(std::istream &in, LifeGrid &rhs);
    bool SerializeToOstream(std::ostream &out) const;
    bool ParseFromIstream(std::istream &in);
};

#endif // CONWAY_INCLUDE_LIFEGRID_HPP