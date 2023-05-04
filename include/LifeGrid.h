#ifndef CW_LIFEGRID_H
#define CW_LIFEGRID_H

#include <vector>
#include "ILifeGrid.h"

class LifeGrid : ILifeGrid {
    private:
        std::vector<std::vector<bool>> grid;
};

#endif