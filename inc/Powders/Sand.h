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

            powder_ptr advanceOneFrame(std::function<std::pair<int,int>(int,int,bool,float)> advanceFun, std::shared_ptr<Storage> powderStorage);
    };
}

#endif