#ifndef WALL_H
#define WALL_H

#include <functional>
#include "Powder.h"
#include "Storage.h"

namespace Powder {
    class Wall : public Powder {

        public:
            Wall(int curFrame, int x, int y);
            Wall(int curFrame, int x, int y, int startingXVelocity, int startingYVelocity);
            ~Wall();

            powder_ptr copyPowder();

            powder_ptr copyPowder(int newXPos, int newYPos);
    };
}

#endif