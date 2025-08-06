#include <functional>
#include <stdexcept>

#include "Sand.h"
#include "Storage.h"
#include "Powder.h"

Powder::Sand::Sand(int curFrame, int xPos, int yPos) : 
        Powder::Powder(curFrame, xPos, yPos, 0, 0, true, .75f, glm::vec4(1.0f,.984f,0.0f,1.0f), PowderType::sand) {
}

Powder::Sand::Sand(int curFrame, int xPos, int yPos, int startingXVelocity, int startingYVelocity) : 
        Powder::Powder(curFrame, xPos, yPos, startingXVelocity, startingYVelocity, true, .75f, glm::vec4(1.0f,.984f,0.0f,1.0f), PowderType::sand) {
}

Powder::Sand::~Sand() {}

powder_ptr Powder::Sand::copyPowder() {
    return(std::make_shared<Sand>(this->frameLastChanged, x, y, xVel, yVel));;
}
