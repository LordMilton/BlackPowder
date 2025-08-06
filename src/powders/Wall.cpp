#include <functional>
#include <stdexcept>

#include "Wall.h"
#include "Storage.h"
#include "Powder.h"

Powder::Wall::Wall(int curFrame, int xPos, int yPos) : 
        Powder::Powder(curFrame, xPos, yPos, false, 0, glm::vec4(0.561f, 0.561f, 0.561f, 1.0f), PowderType::wall) {
}

Powder::Wall::~Wall() {}

powder_ptr Powder::Wall::copyPowder() {
    return(copyPowder(this->x, this->y));
}

powder_ptr Powder::Wall::copyPowder(int newXPos, int newYPos) {
    return(std::make_shared<Wall>(this->frameLastChanged, newXPos, newYPos));
}
