#include "../include/LifeGrid.h"

LifeGrid::LifeGrid(int, int) : ILifeGrid() {

}

LifeState LifeGrid::getCell(const Vector2& coordinate) const {
    return LifeState::ALIVE;
}

void LifeGrid::setCell(const Vector2& coordinate, const LifeState state) {

}

void LifeGrid::loadTemplate(const Vector2& offset, const LifeTemplate& lifeTemplate) {

}

int LifeGrid::compareTemplate(const Vector2& offset, const LifeTemplate& lifeTemplate) const {
    return -1;
}

void LifeGrid::step() {

}