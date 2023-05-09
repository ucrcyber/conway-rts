#include "../include/LifeGrid.h"

LifeGrid::LifeGrid(int w, int h) : ILifeGrid() {
    this->width = w;
    this->height = h;
    this->grid.resize(this->height,std::vector<bool> (this->width,false));
}

LifeState LifeGrid::getCell(const Vector2& coordinate) const {
    return LifeState::ALIVE;
}

void LifeGrid::setCell(const Vector2& coordinate, const LifeState state) {
    this->grid[coordinate.getY()][coordinate.getX()] = state;
}

void LifeGrid::loadTemplate(const Vector2& offset, const LifeTemplate& lifeTemplate) {
    int oy = offset.getY();
    int ox = offset.getX();
    for(int i = 0; i < lifeTemplate.getHeight(); i++) {
        for(int j = 0; j < lifeTemplate.getWidth(); j++) {
            this->grid[oy+i][ox+j] = lifeTemplate.getTemplate()[i][j]; 
        }
    }
}

int LifeGrid::compareTemplate(const Vector2& offset, const LifeTemplate& lifeTemplate) const {
    int diffCount = 0;
    int oy = offset.getY();
    int ox = offset.getX();
    for(int i = 0; i < lifeTemplate.getHeight(); i++) {
        for(int j = 0; j < lifeTemplate.getWidth(); j++) {
            if(this->grid[oy+i][ox+j] != lifeTemplate.getTemplate()[i][j]) {
                diffCount++;
            }
        }
    }
    return diffCount;
}

void LifeGrid::step() {

}