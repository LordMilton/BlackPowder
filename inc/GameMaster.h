#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <cstdlib>
#include "piksel/baseapp.hpp"
#include "IPowder.h"

class GameMaster {
    private:
        std::vector<Powder::IPowder*>* powders;

    public:
        GameMaster();
        ~GameMaster();

        void run(piksel::Graphics& g);
};

#endif