#ifndef IPOWDER_H
#define IPOWDER_H

#include "type_vec4.hpp"
#include "piksel/graphics.hpp"

namespace Powder
{
    class IPowder {
        public:
            static const int PIXEL_SIZE = 1;

            virtual bool getGravity() = 0;
            virtual float getDensity() = 0;
            virtual glm::vec4 getColor() = 0;
            /**
             * Returns position as [x,y]
             */
            virtual int* getPosition() = 0;

            /**
             * Draw the powder as a pixel object
             */
            virtual void draw(piksel::Graphics& g) = 0;
        
    };
}

#endif