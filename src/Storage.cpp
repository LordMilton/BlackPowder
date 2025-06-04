#include "Storage.h"
#include "Powder.h"

Storage::Storage() {
    midFrame = false;
    powders = std::make_unique<int_powder_map>();
    futurePowders = std::make_unique<int_powder_map>();
}

Storage::~Storage() {
}

void Storage::startFrameHandling() {
    midFrame = true;
}

void Storage::endFrameHandling() {
    midFrame = false;
    powders = std::make_unique<int_powder_map>(*futurePowders);
    futurePowders = std::make_unique<int_powder_map>();
}

std::pair<int_powder_map::iterator, int_powder_map::iterator> Storage::getPowdersIterators() {
    return std::make_pair(powders->begin(), powders->end());
}

bool Storage::addPowder(powder_ptr toAdd) {
    bool added = false;
    if(midFrame) {
        added = std::get<bool>(futurePowders->emplace(std::make_pair(hashPowder(toAdd), toAdd)));
    }
    else {
        added = std::get<bool>(powders->emplace(std::make_pair(hashPowder(toAdd), toAdd)));
    }

    if(!added) {
        printf("WARNING: Tried to add powder where there already was one\n");
    }
    return added;
}

void Storage::removePowders(std::shared_ptr<std::vector<powder_ptr>> toRemove) {
    for(std::vector<powder_ptr>::iterator iter = toRemove->begin(); iter != toRemove->end(); iter++) {
        removePowder(*iter);
    }
}

powder_ptr Storage::removePowder(powder_ptr toRemove) {
    if(midFrame) {
        futurePowders->erase(hashPowder(toRemove));
    }
    else {
        powders->erase(hashPowder(toRemove));
    }
    return toRemove;
}

powder_ptr Storage::getPowderAtLocation(int xPos, int yPos) {
    // IF there is no powder at the indicated location in the most recent frame OR
    // that powder has already had its physics calculated for the next frame (i.e. it may no longer be in that location) THEN
    // return the powder that will be there in the next frame if there is one
    if(powders->count(hashPosition(xPos, yPos)) == 0 || powders->at(hashPosition(xPos, yPos))->getChanged()) {
        return futurePowders->at(hashPosition(xPos, yPos));
    }
    return powders->at(hashPosition(xPos, yPos));
}

size_t Storage::hashPowder(powder_ptr powder) {
    std::pair<int,int> coords = powder->getPosition();
    return(hashPosition(coords.first, coords.second));
}

size_t Storage::hashPosition(int xPos, int yPos) {
    return(xPos*MAX_X_POS + yPos);
}