#include <functional>
#include <stdexcept>

#include "Sand.h"
#include "Storage.h"

Powder::Sand::Sand(int xPos, int yPos) :
        x(xPos),
        y(yPos),
        gravity(true),
        density(.75f),
        color(glm::vec4(1.0f,.984f,0.0f,1.0f)) {
}

Powder::Sand::~Sand() {}

bool Powder::Sand::getGravity(){
    return gravity;
}

float Powder::Sand::getDensity(){
    return density;
}

glm::vec4 Powder::Sand::getColor(){
    return color;
}

std::pair<int,int> Powder::Sand::getPosition(){
    return(std::make_pair(x,y));
}

void Powder::Sand::advanceOneFrame(std::function<std::pair<int,int>(int,int,bool,float)> advanceFun, std::shared_ptr<Storage> powderStorage){
    std::pair<int,int> newPos = advanceFun(x, y, gravity, density);
    // Don't let powder exit the screen
    if(!(newPos.first > 1280 || newPos.second > 720 || newPos.first < 1 || newPos.second < 1)) {
        try {
            std::shared_ptr<Powder::IPowder> overlap = powderStorage->getPowderAtLocation(newPos.first, newPos.second);
        } catch (std::out_of_range e) {
            // Exception from trying to find powder at newPos, meaning the space is empty
            x = newPos.first;
            y = newPos.second;
        }
    }
}

void Powder::Sand::draw(piksel::Graphics& g){
    g.strokeWeight(PIXEL_SIZE);
    g.stroke(color);
    g.point(x,y);
}