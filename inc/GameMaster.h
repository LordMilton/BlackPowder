#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <cstdlib>
#include "piksel/baseapp.hpp"
#include "IPowder.h"
#include "Storage.h"

class GameMaster {
    private:
        Storage* powderStorage;

    public:
        GameMaster();
        ~GameMaster();

        /**
         * Runs the simulation
         */
        void run(piksel::Graphics& g);
};

#endif