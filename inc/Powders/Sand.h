#ifndef SAND_H
#define SAND_H

#include <functional>
#include "IPowder.h"

namespace Powder {
    class Sand : public IPowder {
        private:
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
            Sand(int x, int y);
            ~Sand();

            bool getGravity();
            float getDensity();
            glm::vec4 getColor();
            int* getPosition();
            int* advanceOneFrame(std::function<int*(int,int,bool,float)> advanceFun, std::unordered_map<int, std::unordered_map<int, Powder::IPowder*>*>* powderLocations);
            void draw(piksel::Graphics& g);

    };
}

#endif