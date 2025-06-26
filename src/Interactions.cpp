#include "Interactions.h"
#include "Powder.h"

bool Interactions::interact(std::shared_ptr<Powder::Powder> powder1,
                            std::shared_ptr<Powder::Powder> powder2,
                            bool firstPowderMoved,
                            std::shared_ptr<Storage> powderStorage) {
    /* Leaving this is as an example since there aren't any special interactions rn
    if(powder1->getName() == "Water" || powder2->getName() == "Water") {
        if(powder1->getName() == "Wall" || powder2->getName() == "Wall") {
            
        }
    }
    */

    // Interactions between two powders should generally be covered by generic gravity/density/etc. determinations
    return false;
}