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
        // At some point we'll draw walls around the edges when we don't want powders leaving the screen
        if(!(newPos.first > 800 || newPos.second > 700 || newPos.first < 1 || newPos.second < 1)) {
            int_powder_map::iterator mapPointer = powderStorage->getPowderAtLocation(newPos.first,newPos.second);
            if(mapPointer != powderStorage->getPowdersIterators().second) {
                std::shared_ptr<Powder> overlap = (*mapPointer).second;
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
            }
            else {
                x = newPos.first;
                y = newPos.second;
            }
        }
        else {
            newPos = this->getPosition();
        }
        // Copy powders such that the new powder is not indicated as changed for the next frame
        // TODO we don't care about the changed flag when powders are in the future powders map,
        //    test efficiency of iterating that map and resetting the changed flag instead of doing the copying like below
        std::shared_ptr<Powder> newPowder = this->copyPowder(newPos.first, newPos.second);
        powderStorage->addPowder(newPowder);
        setChanged();
        if(displacedPowder != NULL)
            powderStorage->addPowder(displacedPowder->copyPowder());

        advanced = true;
    }
    return(advanced);
}