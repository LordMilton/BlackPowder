#ifndef STORAGE_H
#define STORAGE_H

#include <memory>
#include <stdio.h>
#include <unordered_map>
#include <vector>

// Forward declare to break cyclical includes Powder <-> Storage
namespace Powder {
    class Powder;
}

typedef std::shared_ptr<Powder::Powder> powder_ptr;
typedef std::unordered_map<size_t, std::shared_ptr<Powder::Powder>> int_powder_map;

class Storage {
    private:
        /**
         * The maximum x position of any powder, used for creating the index of powders
         * in the map
         * 
         * TODO make this dynamic to be the max width of the window
         */
        const int MAX_X_POS = 4000;

        /**
         * Indicates that the simulation is in the middle of producing the next frame
         * The owner of this class needs to indicate this appropriately with the frameHandling methods
         */
        bool midFrame;

        /**
         * Returns a hashed value for the given powder
         * 
         * Alternative to having the powder be inherently hashable because only this class stores powders in maps and
         * this class has an expectation that no powder will be in another powder's space (i.e. no breaking the laws of physics)
         */
        size_t hashPowder(powder_ptr powder);

        /**
         * Returns a hashed value for the given coordinates
         */
        size_t hashPosition(int xPos, int yPos);

        /**
         * List of all present powders
         */
        std::unique_ptr<int_powder_map> powders;

        /**
         * List of next frame's powders
         */
        std::unique_ptr<int_powder_map> futurePowders;
        

    public:
        Storage();
        ~Storage();

        /**
         * Indicates that the simulation is in the middle of producing the next frame and
         * that the program may be iterating through powders
         */
        void startFrameHandling();
        /**
         * Indicates that the simulation has finished producing the next frame and that the
         * program is no longer iterating through powders
         */
        void endFrameHandling();
        
        std::pair<int_powder_map::iterator, int_powder_map::iterator> getPowdersIterators();

        /**
         * Adds a list of powders to the simulation
         */
        void addPowders(std::vector<powder_ptr> &toRemove);

        /**
         * Add a powder to the simulation
         * 
         * @return True if powder successfully added, else false
         */
        bool addPowder(powder_ptr toAdd);        

        /**
         * Remove powders from the simulation
         * 
         * To avoid breaking iteration through the list of powders, removal will be prevented when Storage
         * has been told it is in the middle of a frame (physics calculations/drawing/etc.)
         */
        void removePowders(std::vector<powder_ptr> &toRemove);

        /**
         * Remove a powder from the simulation
         * 
         * To avoid breaking iteration through the list of powders, removal will be prevented when Storage
         * has been told it is in the middle of a frame (physics calculations/drawing/etc.)
         * 
         * @return The powder removed
         * @throws out_of_range exception if provided powder doesn't exist
         */
        powder_ptr removePowder(powder_ptr toRemove);

        /**
         * Retrieves the powder at the given location
         */
        int_powder_map::iterator getPowderAtLocation(int xPos, int yPos);

        int getNumPowders();
};

#endif /* STORAGE_H */