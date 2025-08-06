#include <functional>
#include <stdexcept>

#include "Water.h"
#include "Storage.h"
#include "Powder.h"

Powder::Water::Water(int curFrame, int xPos, int yPos) : 
        Powder::Powder(curFrame, xPos, yPos, true, .4f, glm::vec4(0.102f, 0.102f, 0.969f, 1.0f), PowderType::water, 0, true) {
}

Powder::Water::~Water() {}

powder_ptr Powder::Water::copyPowder() {
    return(copyPowder(this->x, this->y));
}

powder_ptr Powder::Water::copyPowder(int newXPos, int newYPos) {
    return(std::make_shared<Water>(this->frameLastChanged, newXPos, newYPos));
}
