#ifndef FIRE_H
#define FIRE_H

#include <functional>
#include "Powder.h"
#include "Storage.h"

namespace Powder {
    class Fire : public Powder {

        public:
            Fire(int curFrame, int x, int y);
            ~Fire();

            powder_ptr copyPowder();

            powder_ptr copyPowder(int newXPos, int newYPos);
    };
}

#endif