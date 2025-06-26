#include <stdexcept>
#include <functional>
#include <memory>

#include "type_vec4.hpp"
#include "piksel/graphics.hpp"
#include "Interactions.h"
#include "Powder.h"

Powder::Powder::Powder(int xPos, int yPos, bool gravity, float density, glm::vec4 color, std::string name) :
                    x(xPos),
                    y(yPos),
                    gravity(gravity),
                    density(density),
                    color(color),
                    name(name),
                    changedThisFrame(false) {}

bool Powder::Powder::advanceOneFrame(std::function<std::pair<int,int>(int,int,bool,float)> advanceFun, std::shared_ptr<Storage> powderStorage) {
    bool advanced = false;
    if(!changedThisFrame) {
        std::pair<int,int> newPos = advanceFun(x, y, gravity, density);
        std::shared_ptr<Powder> displacedPowder = NULL;

        bool specialInteractionOccurred = false;
        int_powder_map::iterator mapPointer = powderStorage->getPowderAtLocation(newPos.first,newPos.second);
        if(mapPointer != powderStorage->getPowdersIterators().second) {
            std::shared_ptr<Powder> overlap = mapPointer->second;
            specialInteractionOccurred = Interactions::interact(powderStorage->getPowderAtLocation(x,y)->second, overlap, true, powderStorage);
            if(!specialInteractionOccurred) {
                if(!overlap->getGravity() || this->density <= overlap->getDensity()) {
                    newPos = this->getPosition();
                }
                else {
                    displacedPowder = overlap;
                    powderStorage->removePowder(overlap);
                    overlap->shiftPowder(this->x, this->y);
                    x = newPos.first;
                    y = newPos.second;
                }
            }
        }
        else {
            x = newPos.first;
            y = newPos.second;
        }
        
        if(!specialInteractionOccurred) {
            // This isn't obviously less efficient than iterating to reset the changed flag
            setChanged();
            std::shared_ptr<Powder> newPowder = this->copyPowder(newPos.first, newPos.second);
            powderStorage->addPowder(newPowder);
            if(displacedPowder != NULL)
                powderStorage->addPowder(displacedPowder->copyPowder());
        }

        advanced = true;
    }
    return(advanced);
}

void Powder::Powder::shiftPowder(int newXPos, int newYPos) {
    //TODO Something about changing these coordinates feels wrong, not sure how to change it
    this->x = newXPos;
    this->y = newYPos;
    this->setChanged();
}

bool Powder::Powder::getGravity() {
    return gravity;
}

float Powder::Powder::getDensity() {
    return density;
}

glm::vec4 Powder::Powder::getColor() {
    return color;
}

std::pair<int,int> Powder::Powder::getPosition() {
    return(std::make_pair(x,y));
}

void Powder::Powder::setChanged() {
    changedThisFrame = true;
}

bool Powder::Powder::getChanged() {
    return(changedThisFrame);
}

std::string Powder::Powder::getName() {
    return name;
}

/**
 * Draw the powder as a pixel object
 */
void Powder::Powder::draw(piksel::Graphics& g){
    g.strokeWeight(PIXEL_SIZE);
    g.stroke(color);
    g.point(x,y);
}

bool Powder::Powder::operator==(const Powder& other) {
    if(typeid(*this) == typeid(other) &&
            this->color == other.color &&
            this->gravity == other.gravity &&
            this->density == other.density &&
            this->x == other.x &&
            this->y == other.y) {
        return true;
    }
    
    return false;
}