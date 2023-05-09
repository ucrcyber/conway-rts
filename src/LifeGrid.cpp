#include "../include/LifeGrid.h"

LifeGrid::LifeGrid(int w, int h) : ILifeGrid() {
    this->width = w;
    this->height = h;
    this->grid.resize(this->height,std::vector<bool> (this->width,false));
}

LifeState LifeGrid::getCell(const Vector2& coordinate) const {
    return (LifeState)this->grid[coordinate.getY()][coordinate.getX()];
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
    //very unoptimized code
    int ny,nx,liveNeighbors;
    std::vector<std::vector<bool>> newGrid(this->height,std::vector<bool>(this->width));
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            //count live neighbors
            liveNeighbors = 0;
            for(int dy = -1; dy <= 1; dy++) {
                for(int dx = -1; dx <= 1; dx++) {
                    if(dx==0 && dy==0) continue;
                    ny = i+dy;
                    nx = j+dx;
                    if(ny<0 || nx<0 || ny>=this->height || nx>=this->width) continue;
                    if(this->grid[ny][nx]) liveNeighbors++;
                }
            }

            //rules
            newGrid[i][j] = (this->grid[i][j] && (liveNeighbors==2||liveNeighbors==3)) || (!this->grid[i][j] && liveNeighbors==3);
        }
    }
    grid = newGrid;
}