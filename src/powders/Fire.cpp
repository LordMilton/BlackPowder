#include <functional>
#include <stdexcept>

#include "Fire.h"
#include "Storage.h"
#include "Powder.h"

Powder::Fire::Fire(int xPos, int yPos) : 
        Powder::Powder(xPos, yPos, true, -.4f, glm::vec4(0.929f, 0.388f, 0.18f, 0.91f), PowderType::fire, 80) {
}

Powder::Fire::~Fire() {}

powder_ptr Powder::Fire::copyPowder() {
    return(copyPowder(this->x, this->y));
}

powder_ptr Powder::Fire::copyPowder(int newXPos, int newYPos) {
    return(std::make_shared<Fire>(newXPos, newYPos));
}
