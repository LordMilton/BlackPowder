#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <cstdlib>
#include "piksel/baseapp.hpp"
#include "IPowder.h"

class GameMaster {
    private:
        /**
         * List of all present powders
         */
        std::vector<Powder::IPowder*>* powders;
        /**
         * 2-d map for tracking powder locations
         */
        std::unordered_map<int, std::unordered_map<int, Powder::IPowder*>*>* powderLocs;

        /**
         * Add a powder to the simulation
         * 
         * @return True if powder successfully added, else false
         */
        bool addPowder(Powder::IPowder* newPowder);

        /**
         * Add a powder to the locations map, adding new indices to the map as needed
         * 
         * @return True if powder successfully added, else false
         */
        bool addToLocations(Powder::IPowder* newPowder);

    public:
        GameMaster();
        ~GameMaster();

        /**
         * Runs the simulation
         */
        void run(piksel::Graphics& g);
};

#endif