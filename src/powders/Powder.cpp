#include <stdexcept>
#include <functional>
#include <memory>

#include "type_vec4.hpp"
#include "piksel/graphics.hpp"
#include "Powder.h"

bool Powder::Powder::advanceOneFrame(std::function<std::pair<int,int>(int,int,bool,float)> advanceFun, std::shared_ptr<Storage> powderStorage) {
    bool advanced = false;
    if(!changedThisFrame) {
        std::pair<int,int> newPos = advanceFun(x, y, gravity, density);
        std::shared_ptr<Powder> displacedPowder = NULL;
        // Don't let powder exit the screen
        if(!(newPos.first > 800 || newPos.second > 800 || newPos.first < 1 || newPos.second < 1)) {
            try {
                std::shared_ptr<Powder> overlap = powderStorage->getPowderAtLocation(newPos.first, newPos.second);
                if(this->density <= overlap->getDensity()) {
                    newPos = this->getPosition();
                }
                else {
                    displacedPowder = overlap;
                    powderStorage->removePowder(overlap);
                    overlap->shiftPowder(this->x, this->y);
                    x = newPos.first;
                    y = newPos.second;
                }
            } catch (std::out_of_range e) {
                // Exception from trying to find powder at newPos, meaning the space is empty
                // TODO: Exceptions can be slow, consider changing this
                x = newPos.first;
                y = newPos.second;
            }
        }
        else {
            newPos = this->getPosition();
        }
        std::shared_ptr<Powder> newPowder = this->copyPowder(newPos.first, newPos.second);
        powderStorage->addPowder(newPowder);
        setChanged();
        if(displacedPowder != NULL)
            powderStorage->addPowder(displacedPowder->copyPowder());

        advanced = true;
    }
    return(advanced);
}