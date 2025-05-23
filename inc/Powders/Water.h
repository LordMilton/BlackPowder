#ifndef WATER_H
#define WATER_H

#include <functional>
#include "Powder.h"
#include "Storage.h"

namespace Powder {
    class Water : public Powder {

        public:
            Water(int x, int y);
            ~Water();

            //bool advanceOneFrame(std::function<std::pair<int,int>(int,int,bool,float)> advanceFun, std::shared_ptr<Storage> powderStorage);
            powder_ptr copyPowder();

            powder_ptr copyPowder(int newXPos, int newYPos);
    };
}

#endif