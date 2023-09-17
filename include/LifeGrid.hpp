#ifndef CONWAY_INCLUDE_LIFEGRID_HPP
#define CONWAY_INCLUDE_LIFEGRID_HPP

#include <vector>

#include "ISerializable.hpp"
#include "Vector2.hpp"
#include "LifeState.hpp"

/// @brief basic implementation of a Life grid
class LifeGrid: public ISerializable<LifeGrid> {
  private:
    /// @brief width and height of the grid
    /// (yes it's finite, at least for now)
    Vector2 _dimensions;

    /// @brief grid to represent the game of life grid
    /// (feel free to change the type if you want)
    std::vector<std::vector<bool>> grid;
  public:
    /// @brief public readonly width and height of the grid
    const Vector2& dimensions = _dimensions;

    /// @brief query the status of a single cell
    /// @param position which cell
    /// @return whether the cell is alive or dead
    LifeState GetCell(const Vector2& position) const;

    /// @brief loads a payload LifeGrid onto the LifeGrid;
    /// used for loading templates when players build something
    /// @param offset where to load
    /// @param payload what to load
    /// @return whether the operation was successful
    bool Load(const Vector2& offset, const LifeGrid& payload);

    /// @brief compare the payload LifeGrid with the current LifeGrid;
    /// the difference in cells is used to calculate build cost
    /// @param offset where to compare
    /// @param payload what to compare
    /// @return amount of cells that differ
    int Compare(const Vector2& offset, const LifeGrid& payload) const;

    /// @brief advances the game of life one generation
    void Tick();
};

#endif // CONWAY_INCLUDE_LIFEGRID_HPP