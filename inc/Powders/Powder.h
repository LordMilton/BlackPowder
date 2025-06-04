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
            Powder(int xPos, int yPos, bool gravity, float density, glm::vec4 color) :
                    x(xPos),
                    y(yPos),
                    gravity(gravity),
                    density(density),
                    color(color),
                    changedThisFrame(false) {}

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

            bool getGravity() {
                return gravity;
            }

            float getDensity() {
                return density;
            }

            glm::vec4 getColor() {
                return color;
            }
            /**
             * Returns position as [x,y]
             */
            std::pair<int,int> getPosition() {
                return(std::make_pair(x,y));
            }

            void setChanged() {
                changedThisFrame = true;
            }

            bool getChanged() {
                return(changedThisFrame);
            }

            /**
             * Draw the powder as a pixel object
             */
            void draw(piksel::Graphics& g){
                g.strokeWeight(PIXEL_SIZE);
                g.stroke(color);
                g.point(x,y);
            }

            bool operator==(const Powder& other) {
                if(typeid(*this) == typeid(other) &&
                        this->color == other.color &&
                        this->gravity == other.gravity &&
                        this->density == other.density &&
                        this->x == other.x &&
                        this->y == other.y) {
                    return true;
                }
                
                return false;
            }

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
            void shiftPowder(int newXPos, int newYPos) {
                //TODO Something about changing these coordinates feels wrong, not sure how to change it
                this->x = newXPos;
                this->y = newYPos;
                this->setChanged();
            }

            virtual std::shared_ptr<Powder> copyPowder() = 0;

            virtual std::shared_ptr<Powder> copyPowder(int newXPos, int newYPos) = 0;
    };
}

#endif