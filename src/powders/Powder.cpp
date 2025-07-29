#include <stdexcept>
#include <functional>
#include <memory>

#include "type_vec4.hpp"
#include "piksel/graphics.hpp"
#include "Interactions.h"
#include "Powder.h"

std::string Powder::Powder::powderTypeNameList[] = {"Fire", "Sand", "Wall", "Water"};

Powder::Powder::Powder(int xPos, int yPos, bool gravity, float density, glm::vec4 color, PowderType powderType, int halfLife, bool liquid) :
                    x(xPos),
                    y(yPos),
                    xVel(0),
                    yVel(0),
                    gravity(gravity),
                    density(density),
                    color(color),
                    powderType(powderType),
                    changedThisFrame(false),
                    halfLife(halfLife),
                    liquid(liquid) {}

bool Powder::Powder::advanceOneFrame(std::function<std::pair<int,int>(int,int,double,double)> advanceFun, std::shared_ptr<Storage> powderStorage) {
    bool advanced = false;

    // Deal with half life first, if it disappears then there's nothing else to do
    if(halfLife >= 1) {
        int rngRange = 10000;
        int rng = rand()%rngRange;
        double deleteChance = rngRange * (1.0 / halfLife);
        if(rng <= deleteChance) {
            powder_ptr toRemove;
            bool powderExists = powderStorage->getPowderAtLocation(this->x,this->y, toRemove);
            if(powderExists) {
                powderStorage->removePowder(toRemove);
            } else {
                printf("Something went wrong while trying to remove this powder");
            }
            this->setChanged();
        }
    }

    bool forceHorizontalMvmt = false;
    if(liquid) {
        powder_ptr below = NULL;
        bool isPowderBelow = false;
        if(gravity && density != 0) {
            isPowderBelow = powderStorage->getPowderAtLocation(x, y + (density / abs(density)), below);
        }
        bool canMoveVertically = true;
        if(isPowderBelow && (!below->getGravity() || below->getDensity() >= this->density)) {
            canMoveVertically = false;
        }
        forceHorizontalMvmt = !canMoveVertically;
    }

    // Update velocities
    if(gravity) {
        const double GRAVITY = 1.0;
        const double MAX_XWOBBLE = .1;
        double xWobble = ((rand() % 3) - 1) * MAX_XWOBBLE; //TODO change this negatively w/r/t density
        if(!forceHorizontalMvmt) {
            this->combineVelocities(std::make_pair(xWobble + xVel/2.0, GRAVITY * (density / abs(density))));
        }
        else {
            this->combineVelocities(std::make_pair((xWobble / MAX_XWOBBLE) + xVel / 2.0, yVel));
        }
    }
    else {
        yVel = 0;
        xVel = 0;
    }

    if(!changedThisFrame) {
        // Determine new position of this powder
        std::pair<int,int> newPos = advanceFun(x, y, xVel, yVel);
        powder_ptr displacedPowder = NULL;

        // Try to move this powder, deal with displacement/interaction of powder in the new position
        bool specialInteractionOccurred = false;
        bool isDisplacingPowder = powderStorage->getPowderAtLocation(newPos.first, newPos.second, displacedPowder);
        powder_ptr thisPowderShared;
        powderStorage->getPowderAtLocation(x, y, thisPowderShared);
        if(isDisplacingPowder) {
            displacedPowder->combineVelocities(std::make_pair(this->xVel, this->yVel));
            this->combineVelocities(displacedPowder->getVelocities());
            specialInteractionOccurred = Interactions::interact(thisPowderShared, displacedPowder, true, powderStorage);
            if(!specialInteractionOccurred) {
                if(!displacedPowder->getGravity() || this->density <= displacedPowder->getDensity()) {
                    newPos = this->getPosition();
                    isDisplacingPowder = false;
                }
                else {
                    powderStorage->removePowder(displacedPowder);
                    displacedPowder->shiftPowder(this->x, this->y);
                    x = newPos.first;
                    y = newPos.second;
                }
            }
        }
        else {
            x = newPos.first;
            y = newPos.second;
        }
        
        // Add changed powders to the next frame's powder list
        if(!specialInteractionOccurred) {
            // This isn't obviously less efficient than iterating to reset the changed flag
            setChanged();
            powderStorage->removePowder(thisPowderShared);
            std::shared_ptr<Powder> newPowder = this->copyPowder(newPos.first, newPos.second);
            powderStorage->addPowder(newPowder);
            if(isDisplacingPowder)
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
    return powderTypeNameList[int(powderType)];
}

Powder::Powder::PowderType Powder::Powder::getPowderType() {
    return powderType;
}

std::pair<double,double> Powder::Powder::getVelocities() {
    return(std::make_pair(xVel, yVel));
}

void Powder::Powder::combineVelocities(std::pair<double,double> velocities) {
    if(gravity) {
        xVel = (xVel + velocities.first) / 2.0;
        xVel = xVel * abs(density) * 2;
        yVel = (yVel + velocities.second) / 2.0;
        yVel = yVel * abs(density) * 2;
    }
    else {
        xVel = 0;
        yVel = 0;
    }
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