#ifndef STORAGE_H
#define STORAGE_H

#include "IPowder.h"

class Storage {
    private:
        /**
         * List of all present powders
         */
        std::vector<Powder::IPowder*>* powders;
        /**
         * 2-d map for tracking powder locations
         */
        std::unordered_map<int, std::unordered_map<int, Powder::IPowder*>*>* powderLocs;

    public:
        Storage();
        ~Storage();
        
        std::pair<std::vector<Powder::IPowder*>::iterator, std::vector<Powder::IPowder*>::iterator> getPowdersIterators();

        /**
         * Add a powder to the simulation
         * 
         * @return True if powder successfully added, else false
         */
        bool addPowder(Powder::IPowder* toAdd);

        Powder::IPowder* removePowders(std::vector<Powder::IPowder*>* toRemove);

        /**
         * Add a powder to the locations map, adding new indices to the map as needed
         * 
         * @return True if powder successfully added, else false
         */
        bool addToLocations(Powder::IPowder* toAdd);

        /**
         * Remove a powder from the locations map
         * 
         * @return A pointer to the removed Powder
         */
        Powder::IPowder* removeFromLocations(Powder::IPowder* toRemove);

        Powder::IPowder* getPowderAtLocation(int xPos, int yPos);
};

#endif /* STORAGE_H */