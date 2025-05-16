#ifndef STORAGE_H
#define STORAGE_H

#include <memory>

#include "IPowder.h"

class Storage {
    private:
        /**
         * List of all present powders
         */
        std::unique_ptr<std::vector<std::shared_ptr<Powder::IPowder>>> powders;
        /**
         * 2-d map for tracking powder locations
         */
        std::shared_ptr<std::unordered_map<int, std::shared_ptr<std::unordered_map<int, std::shared_ptr<Powder::IPowder>>>>> powderLocs;

    public:
        Storage();
        ~Storage();
        
        std::pair<std::vector<std::shared_ptr<Powder::IPowder>>::iterator, std::vector<std::shared_ptr<Powder::IPowder>>::iterator> getPowdersIterators();

        /**
         * Add a powder to the simulation
         * 
         * @return True if powder successfully added, else false
         */
        bool addPowder(std::shared_ptr<Powder::IPowder> toAdd);

        std::shared_ptr<Powder::IPowder> removePowders(std::shared_ptr<std::vector<std::shared_ptr<Powder::IPowder>>> toRemove);

        /**
         * Add a powder to the locations map, adding new indices to the map as needed
         * 
         * @return True if powder successfully added, else false
         */
        bool addToLocations(std::shared_ptr<Powder::IPowder> toAdd);

        /**
         * Remove a powder from the locations map
         * 
         * @return A pointer to the removed Powder
         */
        std::shared_ptr<Powder::IPowder> removeFromLocations(std::shared_ptr<Powder::IPowder> toRemove);

        std::shared_ptr<Powder::IPowder> getPowderAtLocation(int xPos, int yPos);
};

#endif /* STORAGE_H */