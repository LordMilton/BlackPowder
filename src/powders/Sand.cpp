#include <functional>
#include <stdexcept>
#include "Sand.h"

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

int* Powder::Sand::getPosition(){
    int* position = new int[2] {x,y};
    return position;
}

int* Powder::Sand::advanceOneFrame(std::function<int*(int,int,bool,float)> advanceFun, std::unordered_map<int, std::unordered_map<int, Powder::IPowder*>*>* powderLocations){
    int* newPos = advanceFun(x, y, gravity, density);
    if(!(newPos[0] > 1280 || newPos[1] > 720)) {
        try {
            Powder::IPowder* overlap = powderLocations->at(newPos[0])->at(newPos[1]);
        } catch (std::out_of_range e) {
            // Exception from trying to find powder at newPos, meaning the space is empty
            x = newPos[0];
            y = newPos[1];
        }
    }
    delete(newPos);
    return getPosition();
}

void Powder::Sand::draw(piksel::Graphics& g){
    g.strokeWeight(PIXEL_SIZE);
    g.stroke(color);
    g.point(x,y);
}