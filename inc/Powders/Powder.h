#ifndef POWDER_H
#define POWDER_H

#include <stdexcept>
#include <functional>
#include <memory>

#include "type_vec4.hpp"
#include "piksel/graphics.hpp"
#include "Storage.h"

namespace Powder
{

    class Powder {
        protected:
            Powder(int xPos, int yPos, bool gravity, float density, glm::vec4 color, std::string name);

            /** 
             * If true then powder falls or rises (depends on density), else powder does not move
             */
            const bool gravity;
            /**
             * Density of the powder, range (-1, 1)
             * 
             * < 0, powder rises in vaccuum; > 0, powder falls in vaccuum; == 0 powder should remain static wrt gravity
             * If this powder < another powder, this powder rises wrt other powder and vice versa
             * If gravity is false, density is irrelevant
             */
            const float density;
            /**
             * Color of the powder
             */
            const glm::vec4 color;
            /**
             * Name of the powder
             * 
             * The name is the same for all instances of a powder, but needs to be accessible by things that don't know the powder type so shouldn't be static
             */
            const std::string name;
            /**
             * X coordinate
             */
            int x;
            /** 
             * Y coordinate
             */
            int y;

            /**
             * Whether this powder has moved this frame, whether by it's own physics or being displaced
             */
            bool changedThisFrame = false;
        
        public:
            static const int PIXEL_SIZE = 1;

            bool getGravity();
            float getDensity();
            glm::vec4 getColor();
            /**
             * Returns position as [x,y]
             */
            std::pair<int,int> getPosition();
            void setChanged();
            bool getChanged();
            std::string getName();

            /**
             * Draw the powder as a pixel object
             */
            void draw(piksel::Graphics& g);

            bool operator==(const Powder& other);

            /**
             * Advance the powder by one frame.
             * "Advance" currently just means basic physics movement, if the powder has already been shifted
             * due to the physics of another powder, this will do nothing
             * 
             * @return true if powder was advanced, false otherwise
             */
            bool advanceOneFrame(std::function<std::pair<int,int>(int,int,bool,float)> advanceFun, std::shared_ptr<Storage> powderStorage);

            /**
             * Shift the powder to a new location.
             * Lets other powders displace this one due to their own physics
             */
            void shiftPowder(int newXPos, int newYPos);

            virtual std::shared_ptr<Powder> copyPowder() = 0;

            virtual std::shared_ptr<Powder> copyPowder(int newXPos, int newYPos) = 0;
    };
}

#endif