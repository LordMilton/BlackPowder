#include <functional>
#include <stdexcept>

#include "Wall.h"
#include "Storage.h"
#include "Powder.h"

Powder::Wall::Wall(int curFrame, int xPos, int yPos) : 
        Powder::Powder(curFrame, xPos, yPos, 0, 0, false, 0, glm::vec4(0.561f, 0.561f, 0.561f, 1.0f), PowderType::wall) {
}

Powder::Wall::Wall(int curFrame, int xPos, int yPos, int startingXVelocity, int startingYVelocity) : 
        Powder::Powder(curFrame, xPos, yPos, startingXVelocity, startingYVelocity, false, 0, glm::vec4(0.561f, 0.561f, 0.561f, 1.0f), PowderType::wall) {
}

Powder::Wall::~Wall() {}

powder_ptr Powder::Wall::copyPowder() {
    return(std::make_shared<Wall>(this->frameLastChanged, x, y, xVel, yVel));
}
