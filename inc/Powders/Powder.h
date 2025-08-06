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
        public:
            enum class PowderType { 
                fire,
                sand,
                wall,
                water
            };

        protected:
            Powder(int curFrame, int xPos, int yPos, int startingXVelocity, int startingYVelocity, bool gravity, float density, glm::vec4 color, PowderType powderType, int halfLife = 0, bool liquid = false);

            /**
             * Table for translating the powder type into a name string
             */
            static std::string powderTypeNameList [];
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
             * True if the powder is a liquid
             */
            const bool liquid;
            /**
             * Type of the powder
             * 
             * The type is the same for all instances of a powder, but needs to be accessible by things that don't know the powder type so shouldn't be static
             */
            const PowderType powderType;
            /**
             * X coordinate
             */
            int x;
            /** 
             * Y coordinate
             */
            int y;
            /**
             * Horizontal Velocity
             */
            double xVel;
            /**
             * Vertical velocity
             */
            double yVel;
            /**
             * Half life of this powder, or how many frames on average it should exist before disappearing
             * If set to 0, this powder does not have a half life and can exist indefinitely
             */
            int halfLife;

            /**
             * The last frame this powder was updated
             *    Compared to a boolean, this allows invalidation without having to reupdate the powder
             */
            int frameLastChanged;
        
        public:

            static const int PIXEL_SIZE = 1;

            bool getGravity();
            float getDensity();
            glm::vec4 getColor();
            /**
             * Returns position as [x,y]
             */
            std::pair<int,int> getPosition();
            std::pair<double,double> getVelocities();
            /**
             * "Combines" the velocities of this object with the velocities provided
             */
            void combineVelocities(std::pair<double,double> velocities);
            /**
             * Whether this powder is valid (was last updated) this frame
             */
            bool validThisFrame(int curFrame);
            /**
             * Whether this powder was valid (was last updated) in the previous frame
             */
            bool validLastFrame(int curFrame);
            /**
             * Get the stringified name of this powder
             */
            std::string getName();
            /**
             * Get the enumerated type of this powder (far more efficient for comparisons)
             */
            PowderType getPowderType();

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
            bool advanceOneFrame(std::function<std::pair<int,int>(int,int,double,double)> advanceFun, std::shared_ptr<Storage> powderStorage);

            /**
             * Shift the powder to a new location.
             * Lets other powders displace this one due to their own physics
             * 
             * @param newYPos The new X position of the powder
             * @param newYPos The new Y position of the powder
             * @param curFrame The current frame that, once shifted, the powder is considered valid for
             */
            void shiftPowder(int newXPos, int newYPos, int curFrame);

            /** 
             * Creates another identical copy of this powder
             */
            virtual std::shared_ptr<Powder> copyPowder() = 0;
    };
}

typedef Powder::Powder::PowderType PowderType;

#endif