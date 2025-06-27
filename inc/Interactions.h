#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "Powder.h"
#include "Storage.h"

class Interactions {
    private:
        /**
         * Determines interaction between fire and water.
         * 
         * @param powder1 The fire powder
         * @param powder2 The water powder
         * @param firstMoved If true, then powder1 is attempting to shift into powder2's space, if false then vice versa
         * 
         * @return True
         */
        static bool fireWaterInteract(std::shared_ptr<Powder::Powder> powder1, std::shared_ptr<Powder::Powder> powder2, bool firstPowderMoved, std::shared_ptr<Storage> powderStorage);

    public:
        /**
         * Determines interaction between two generic Powders.
         * 
         * @param powder1 One of the powders in the interaction
         * @param powder2 One of the powders in the interaction
         * @param firstMoved If true, then powder1 is attempting to shift into powder2's space, if false then vice versa
         *                      Useful for permitting symmetry when performing interactions
         * 
         * @return True if a special interaction occurred, False otherwise
         */
        static bool interact(std::shared_ptr<Powder::Powder> powder1, std::shared_ptr<Powder::Powder> powder2, bool firstPowderMoved, std::shared_ptr<Storage> powderStorage);
};

#endif