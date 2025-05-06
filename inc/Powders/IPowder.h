#ifndef IPOWDER_H
#define IPOWDER_H

#include "type_vec4.hpp"
#include "piksel/graphics.hpp"

namespace Powder
{
    class IPowder {
        private:
            static const int PIXEL_SIZE = 1;
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

        public:
            virtual bool getGravity();
            virtual float getDensity();
            virtual glm::vec4 getColor();
            /**
             * Returns position as [x,y]
             */
            virtual int* getPosition();

            /**
             * Draw the powder as a pixel object
             */
            virtual void draw(piksel::Graphics& g) {
                g.strokeWeight(1);
                g.stroke(color);
                g.point(x, y);
            }
        
    };
}

#endif