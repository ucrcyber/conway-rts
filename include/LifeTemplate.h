#ifndef CW_LIFETEMPLATE_H
#define CW_LIFETEMPLATE_H

#include <vector>
#include <string>

/// a cell configuration "template" to be loaded onto a LifeGrid (immutable)
class LifeTemplate {
    private:
        int width, height;
        std::vector<std::vector<bool>> grid;
    public:
        /// @brief generates LifeTemplate from a string (new line is a row, '.' is empty, '#' is active)
        /// @param  string to be read from
        LifeTemplate(std::string);

        /// @return width of template
        const int getWidth() const;
        
        /// @return height of template
        const int getHeight() const;

        /// @brief get template to read from it
        /// @return 2D bool array representing the template
        const std::vector<std::vector<bool>>& getTemplate() const;
};

#endif