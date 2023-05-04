#ifndef CW_LIFEGRID_H
#define CW_LIFEGRID_H

#include <vector>
#include "ILifeGrid.h"

/// @brief basic implementation of a Life grid
class LifeGrid : ILifeGrid {
    private:
        int width, height;

        /// @brief grid to represent the game of life grid (feel free to change the type if you want)
        std::vector<std::vector<bool>> grid;
    public:
        /// @brief creates empty (all dead) grid with `width` per row and `height` rows
        /// @param  width
        /// @param  height
        LifeGrid(int, int);

        /// @brief query a single cell on the grid
        /// @param Vector2 coordinate
        /// @return state of the queried cell
        virtual LifeState getCell(const Vector2&) const;

        /// @brief set a single cell (loadTemplate should be used for larger collections)
        /// @param Vector2 coordinate 
        /// @param LifeState new state for the cell at {coordinate}
        virtual void setCell(const Vector2&, const LifeState);

        /// @brief set a group of cells to the set template TODO: maybe padding would be nice?
        /// @param Vector2 coordinate of top left corner of template position
        /// @param LifeTemplate template to be pasted onto the grid
        virtual void loadTemplate(const Vector2&, const LifeTemplate&);

        /// @brief calculate number of different cells
        /// @param  Vector2 coordinate of top left corner of template position
        /// @param  LifeTemplate template to be compared against the grid
        /// @return number of different cells
        virtual int compareTemplate(const Vector2&, const LifeTemplate&) const;

        /// @brief advance the LifeGrid by one generation
        void step();
};

#endif