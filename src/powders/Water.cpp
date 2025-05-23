#include <functional>
#include <stdexcept>

#include "Water.h"
#include "Storage.h"
#include "Powder.h"

Powder::Water::Water(int xPos, int yPos) : 
        Powder::Powder(xPos, yPos, true, .25f, glm::vec4(0.102f, 0.102f, 0.969f, 1.0f)) {
}

Powder::Water::~Water() {}

powder_ptr Powder::Water::copyPowder() {
    return(copyPowder(this->x, this->y));
}

powder_ptr Powder::Water::copyPowder(int newXPos, int newYPos) {
    return(std::make_shared<Water>(newXPos, newYPos));
}

/*
bool Powder::Water::advanceOneFrame(std::function<std::pair<int,int>(int,int,bool,float)> advanceFun, std::shared_ptr<Storage> powderStorage){    
    bool advanced = false;
    if(!changedThisFrame) {
        std::pair<int,int> newPos = advanceFun(x, y, gravity, density);
        std::shared_ptr<Powder> displacedPowder = NULL;
        // Don't let powder exit the screen
        if(!(newPos.first > 800 || newPos.second > 800 || newPos.first < 1 || newPos.second < 1)) {
            try {
                powder_ptr overlap = powderStorage->getPowderAtLocation(newPos.first, newPos.second);
                if(this->density <= overlap->getDensity()) {
                    newPos = this->getPosition();
                }
                else {
                    displacedPowder = overlap;
                    if(overlap->getChanged())
                        powderStorage->removePowder(overlap);
                    overlap->shiftPowder(this->x, this->y);
                    x = newPos.first;
                    y = newPos.second;
                }
            } catch (std::out_of_range e) {
                // Exception from trying to find powder at newPos, meaning the space is empty
                x = newPos.first;
                y = newPos.second;
            }
        }
        else {
            newPos = this->getPosition();
        }
        std::shared_ptr<Powder> newPowder = std::make_shared<Water>(newPos.first, newPos.second);
        powderStorage->addPowder(newPowder);
        setChanged();
        if(displacedPowder != NULL)
            powderStorage->addPowder(displacedPowder);

        advanced = true;
    }
    return(advanced);
}
*/