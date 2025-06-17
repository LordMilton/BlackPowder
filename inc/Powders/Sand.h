#ifndef SAND_H
#define SAND_H

#include <functional>
#include "Powder.h"
#include "Storage.h"

namespace Powder {
    class Sand : public Powder {

        public:
            Sand(int x, int y);
            ~Sand();

            powder_ptr copyPowder();

            powder_ptr copyPowder(int newXPos, int newYPos);

            std::string getName();
    };
}

#endif