#include "Storage.h"
#include "Powder.h"

Storage::Storage() :
        midFrame(false),
        powders(std::make_unique<int_powder_map>()),
        futurePowders(std::make_unique<int_powder_map>()){}

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

bool Storage::addPowders(std::vector<powder_ptr> &toAdd) {
    powdersMtx.lock();
    bool added = true;
    for(std::vector<powder_ptr>::iterator iter = toAdd.begin(); iter != toAdd.end(); iter++) {
        if(midFrame) {
            added = std::get<bool>(futurePowders->emplace(std::make_pair(hashPowder(*iter), *iter))) && added;
        }
        else {
            added = std::get<bool>(powders->emplace(std::make_pair(hashPowder(*iter), *iter))) && added;
        }
    }
    powdersMtx.unlock();
    return added;
}

bool Storage::addPowder(powder_ptr toAdd) {
    std::vector<powder_ptr> toAddVec = std::vector<powder_ptr>();
    toAddVec.push_back(toAdd);
    return addPowders(toAddVec);
}

bool Storage::removePowders(std::vector<powder_ptr> &toRemove) {
    powdersMtx.lock();

    bool removed = true;
    for(std::vector<powder_ptr>::iterator iter = toRemove.begin(); iter != toRemove.end(); iter++) {
        try {
            if(midFrame) {
                futurePowders->erase(hashPowder(*iter));
                removed = removed && true;
            }
            else {
                powders->erase(hashPowder(*iter));
                removed = removed && true;
            }
        } catch(std::exception e) {
            removed = false;
        }
    }

    powdersMtx.unlock();
    return removed;
}

bool Storage::removePowder(powder_ptr toRemove) {
    std::vector<powder_ptr> toRemoveVec = std::vector<powder_ptr>();
    toRemoveVec.push_back(toRemove);
    return removePowders(toRemoveVec);
}

int_powder_map::iterator Storage::getPowderAtLocation(int xPos, int yPos) {
    powdersMtx.lock();
    int_powder_map::iterator toReturn;
    // IF there is no powder at the indicated location in the most recent frame OR
    // that powder has already had its physics calculated for the next frame (i.e. it may no longer be in that location) THEN
    // return the powder that will be there in the next frame if there is one
    if(powders->count(hashPosition(xPos, yPos)) == 0 || powders->at(hashPosition(xPos, yPos))->getChanged()) {
        toReturn = futurePowders->find(hashPosition(xPos, yPos));
    }
    else {
        toReturn = powders->find(hashPosition(xPos, yPos));
    }

    powdersMtx.unlock();
    return toReturn;
}

int Storage::getNumPowders() {
    return powders->size();
}

size_t Storage::hashPowder(powder_ptr powder) {
    std::pair<int,int> coords = powder->getPosition();
    return(hashPosition(coords.first, coords.second));
}

size_t Storage::hashPosition(int xPos, int yPos) {
    return(xPos*MAX_X_POS + yPos);
}