#ifndef CW_ILIFEGRID_H
#define CW_ILIFEGRID_H

#include "Vector2.h"
#include "LifeState.h"
#include "LifeTemplate.h"

/// @brief interface for creating a LifeGrid
class ILifeGrid {
    public:
        ILifeGrid();

        /// @brief query a single cell on the grid
        /// @param Vector2 coordinate
        /// @return state of the queried cell
        LifeState getCell(const Vector2&) const;

        /// @brief set a single cell (loadTemplate should be used for larger collections)
        /// @param Vector2 coordinate 
        /// @param LifeState new state for the cell at {coordinate}
        void setCell(const Vector2&, const LifeState);

        /// @brief set a group of cells to the set template TODO: maybe padding would be nice?
        /// @param Vector2 coordinate of top left corner of template position
        /// @param LifeTemplate template to be pasted onto the grid
        void loadTemplate(const Vector2&, const LifeTemplate&);

        /// @brief calculate number of different cells
        /// @param  Vector2 coordinate of top left corner of template position
        /// @param  LifeTemplate template to be compared against the grid
        /// @return number of different cells
        int compareTemplate(const Vector2&, const LifeTemplate&) const;

        /// @brief advance the LifeGrid by one generation
        void step();
};

#endif