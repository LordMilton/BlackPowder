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
