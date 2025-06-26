#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "Powder.h"
#include "Storage.h"
#include "Wall.h"
#include "Water.h"

class Interactions {
    public:
        /**
         * Determines interaction between two generic Powders. This is the generic case that will be hit
         * if there is not a more specific interact() method for the called case. No special interaction
         * will take place and the return value will always be false.
         * 
         * @param powder1 One of the powders in the interaction
         * @param powder2 One of the powders in the interaction
         * @param firstMoved If true, then powder1 is attempting to shift into powder2's space, if false then vice versa
         *                      Useful for permitting symmetry between interact() methods of the same two Powders
         * 
         * @return False
         */
        static bool interact(std::shared_ptr<Powder::Powder> powder1, std::shared_ptr<Powder::Powder> powder2, bool firstPowderMoved, std::shared_ptr<Storage> powderStorage);
};

#endif