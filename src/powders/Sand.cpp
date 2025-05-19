#include <functional>
#include <stdexcept>

#include "Sand.h"
#include "Storage.h"
#include "Powder.h"

Powder::Sand::Sand(int xPos, int yPos) : 
        Powder::Powder(xPos, yPos, true, .75f, glm::vec4(1.0f,.984f,0.0f,1.0f)) {
}

Powder::Sand::~Sand() {}

powder_ptr Powder::Sand::advanceOneFrame(std::function<std::pair<int,int>(int,int,bool,float)> advanceFun, std::shared_ptr<Storage> powderStorage){    
    std::pair<int,int> newPos = advanceFun(x, y, gravity, density);
    // Don't let powder exit the screen
    if(!(newPos.first > 800 || newPos.second > 800 || newPos.first < 1 || newPos.second < 1)) {
        try {
            std::shared_ptr<Powder> overlap = powderStorage->getPowderAtLocation(newPos.first, newPos.second);
            newPos = this->getPosition();
        } catch (std::out_of_range e) {
            // Exception from trying to find powder at newPos, meaning the space is empty
            x = newPos.first;
            y = newPos.second;
        }
    }
    else {
        newPos = this->getPosition();
    }
    std::shared_ptr<Powder> newPowder = std::make_shared<Sand>(newPos.first, newPos.second);

    setChanged();
    return(newPowder);
}
