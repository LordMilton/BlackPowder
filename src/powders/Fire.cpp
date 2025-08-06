#include <functional>
#include <stdexcept>

#include "Fire.h"
#include "Storage.h"
#include "Powder.h"

Powder::Fire::Fire(int curFrame, int xPos, int yPos) : 
        Powder::Powder(curFrame, xPos, yPos, 0, 0, true, -.4f, glm::vec4(0.929f, 0.388f, 0.18f, 0.91f), PowderType::fire, 80) {
}

Powder::Fire::Fire(int curFrame, int xPos, int yPos, int startingXVelocity, int startingYVelocity) : 
        Powder::Powder(curFrame, xPos, yPos, startingXVelocity, startingYVelocity, true, -.4f, glm::vec4(0.929f, 0.388f, 0.18f, 0.91f), PowderType::fire, 80) {
}

Powder::Fire::~Fire() {}

powder_ptr Powder::Fire::copyPowder() {
    return(std::make_shared<Fire>(this->frameLastChanged, x, y, xVel, yVel));
}
