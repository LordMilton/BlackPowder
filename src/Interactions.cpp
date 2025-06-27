#include "Interactions.h"
#include "Powder.h"

bool Interactions::interact(std::shared_ptr<Powder::Powder> powder1,
                            std::shared_ptr<Powder::Powder> powder2,
                            bool firstPowderMoved,
                            std::shared_ptr<Storage> powderStorage) {
    
    if(powder1->getName() == "Fire") {
        if(powder2->getName() == "Water") {
            fireWaterInteract(powder1, powder2, firstPowderMoved, powderStorage);
            
            return true;
        }
    }

    if(powder1->getName() == "Water") {
        if(powder2->getName() == "Fire") {
            fireWaterInteract(powder2, powder1, !firstPowderMoved, powderStorage);
            
            return true;
        }
    }

    // Interactions between two powders should generally be covered by generic gravity/density/etc. physics
    return false;
}

void Interactions::fireWaterInteract(std::shared_ptr<Powder::Powder> powder1, std::shared_ptr<Powder::Powder> powder2, bool firstPowderMoved, std::shared_ptr<Storage> powderStorage) {
    powderStorage->removePowder(powder1);
    powderStorage->removePowder(powder2);
    
    std::pair<int,int> powder1Pos = powder1->getPosition();
    std::pair<int,int> powder2Pos = powder2->getPosition();
    std::pair<int,int> contactPos = firstPowderMoved ? powder2Pos : powder1Pos;

    powder2->shiftPowder(contactPos.first, contactPos.second);
    powder_ptr newPowder2 = powder2->copyPowder(contactPos.first, contactPos.second);

    powder1->shiftPowder(contactPos.first, contactPos.second);
    powderStorage->addPowder(newPowder2);
}