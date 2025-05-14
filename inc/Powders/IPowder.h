#ifndef IPOWDER_H
#define IPOWDER_H

#include <functional>
#include "type_vec4.hpp"
#include "piksel/graphics.hpp"

class Storage; //Forward declaring to break cycle IPowder <-> Storage

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

            /**
             * Advance the powder by one frame.
             * "Advance" currently just means movement, it may indicate more change in the future
             * 
             * @return coordinates after advancement
             */
            virtual int* advanceOneFrame(std::function<int*(int,int,bool,float)> advanceFun, Storage* powderStorage) = 0;
        
    };
}

#endif