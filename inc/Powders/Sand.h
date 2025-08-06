#ifndef SAND_H
#define SAND_H

#include <functional>
#include "Powder.h"
#include "Storage.h"

namespace Powder {
    class Sand : public Powder {

        public:
            Sand(int curFrame, int x, int y);
            Sand(int curFrame, int x, int y, int startingXVelocity, int startingYVelocity);
            ~Sand();

            powder_ptr copyPowder();

            powder_ptr copyPowder(int newXPos, int newYPos);
    };
}

#endif