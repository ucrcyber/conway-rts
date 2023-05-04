#include "../include/LifeTemplate.h"
#include <sstream>

#include<iostream>

LifeTemplate::LifeTemplate(std::string s){
    std::string line;
    std::istringstream in(s);
    width = 0;
    for(int i = 0; in >> line; i ++){
        width = std::max(width, (int)line.size());
        grid.push_back(std::vector<bool>());
        for(auto c : line){
            grid.back().push_back(c == '#');
        }
    }
    for(auto &row : grid){
        while(row.size() < width){
            row.push_back(false);
        }
    }
    height = grid.size();
}

const int LifeTemplate::getHeight() const {
    return height;
}

const int LifeTemplate::getWidth() const {
    return width;
}

const std::vector<std::vector<bool>>& LifeTemplate::getTemplate() const {
    return grid;
}