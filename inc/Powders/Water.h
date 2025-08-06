#ifndef WATER_H
#define WATER_H

#include <functional>
#include "Powder.h"
#include "Storage.h"

namespace Powder {
    class Water : public Powder {

        public:
            Water(int curFrame, int x, int y);
            ~Water();

            powder_ptr copyPowder();

            powder_ptr copyPowder(int newXPos, int newYPos);
    };
}

#endif