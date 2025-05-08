#include "Sand.h"

Powder::Sand::Sand(int xPos, int yPos) :
        x(xPos),
        y(yPos),
        gravity(true),
        density(.75f),
        color(glm::vec4(.5f,.5f,.5f,1.0f)) {
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

void Powder::Sand::draw(piksel::Graphics& g){
    g.strokeWeight(PIXEL_SIZE);
    g.stroke(color);
    g.point(x,y);
}