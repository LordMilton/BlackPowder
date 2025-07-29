#ifndef STORAGE_H
#define STORAGE_H

#include <array>
#include <memory>
#include <stdio.h>
#include <unordered_map>
#include <vector>

// Forward declare to break cyclical includes Powder <-> Storage
namespace Powder {
    class Powder;
}

typedef std::shared_ptr<Powder::Powder> powder_ptr;

class Storage {
    public:
        static const int MAX_WINDOW_SIZE_X = 1920;
        static const int MAX_WINDOW_SIZE_Y = 1080;
        static const int MAX_PIXEL_COUNT = MAX_WINDOW_SIZE_X * MAX_WINDOW_SIZE_Y;

    private:
        int trueWindowSizeX;
        int trueWindowSizeY;

        int numPowders;

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
        std::unique_ptr<std::array<powder_ptr, MAX_PIXEL_COUNT>> powders;

        /**
         * List of next frame's powders
         */
        std::unique_ptr<std::array<powder_ptr, MAX_PIXEL_COUNT>> futurePowders;
        

    public:
        typedef std::array<powder_ptr, MAX_PIXEL_COUNT> powder_array;

        Storage(int windowSizeX, int windowSizeY);
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
        
        std::pair<powder_array::iterator, powder_array::iterator> getPowdersIterators();

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
        bool getPowderAtLocation(int xPos, int yPos, powder_ptr &retVal);

        int getNumPowders();
};

#endif /* STORAGE_H */