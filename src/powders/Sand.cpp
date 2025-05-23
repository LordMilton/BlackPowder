#include <functional>
#include <stdexcept>

#include "Sand.h"
#include "Storage.h"
#include "Powder.h"

Powder::Sand::Sand(int xPos, int yPos) : 
        Powder::Powder(xPos, yPos, true, .75f, glm::vec4(1.0f,.984f,0.0f,1.0f)) {
}

Powder::Sand::~Sand() {}

powder_ptr Powder::Sand::copyPowder() {
    return(copyPowder(this->x, this->y));
}

powder_ptr Powder::Sand::copyPowder(int newXPos, int newYPos) {
    return(std::make_shared<Sand>(newXPos, newYPos));
}
