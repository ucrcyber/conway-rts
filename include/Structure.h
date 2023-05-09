#ifndef CW_STRUCTURE_H
#define CW_STRUCTURE_H

#include "Vector2.h"

/// @brief Abstract class for gol structures
class Structure {
    private:
        bool active;
        Vector2 position;
    public:
        /// @brief Return if the structure is active
        /// @return If the structure is active
        bool isActive();

        /// @brief Return the position of the structure
        /// @return A `Vector2` representing the location
        Vector2 getPosition();

        /// @brief Check if the structure is still intact
        /// @return If the structure is still intact
        virtual bool checkIntegrity() = 0;
};

#endif