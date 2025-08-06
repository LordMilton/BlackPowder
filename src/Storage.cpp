#include <chrono>
#include <iostream>

#include "Storage.h"
#include "Powder.h"

Storage::Storage(int windowSizeX, int windowSizeY) :
        trueWindowSizeX(windowSizeX),
        trueWindowSizeY(windowSizeY),
        midFrame(false),
        numPowders(0),
        curFrameCount(0) {
    powders = std::make_unique<std::array<powder_ptr, MAX_PIXEL_COUNT>>();
    futurePowders = std::make_unique<std::array<powder_ptr, MAX_PIXEL_COUNT>>();
}

Storage::~Storage() {
}

void Storage::startFrameHandling() {
    curFrameCount++;
    midFrame = true;
}

void Storage::endFrameHandling() {
    midFrame = false;
    powders.swap(futurePowders);
}

std::pair<std::array<powder_ptr, Storage::MAX_PIXEL_COUNT>::iterator, std::array<powder_ptr, Storage::MAX_PIXEL_COUNT>::iterator> Storage::getPowdersIterators() {
    return std::make_pair(powders->begin(), powders->end());
}

void Storage::addPowders(std::vector<powder_ptr> &toAdd) {
    for(std::vector<powder_ptr>::iterator iter = toAdd.begin(); iter != toAdd.end(); iter++) {
        addPowder(*iter);
    }
}

bool Storage::addPowder(powder_ptr toAdd) {
    bool added = false;
    std::pair<int,int> position = toAdd->getPosition();
    if(isPositionInRange(position.first, position.second)) {
        size_t powderHash = hashPowder(toAdd);
        if(midFrame) {
            powder_ptr existingPowder = (*futurePowders)[powderHash];
            if(existingPowder == NULL || !existingPowder->validThisFrame(curFrameCount)) {
                (*futurePowders)[powderHash] = toAdd;
                added = true;
            } 
        }
        else {
            powder_ptr existingPowder = (*powders)[powderHash];
            if(existingPowder == NULL || !existingPowder->validThisFrame(curFrameCount)) {
                (*powders)[powderHash] = toAdd;
                added = true;
            }
        }

        if(!added) {
            //printf("WARNING: Tried to add powder where there already was one\n");
        } else {
            numPowders++;
        }
    }
    return added;
}

void Storage::removePowders(std::vector<powder_ptr> &toRemove) {
    for(std::vector<powder_ptr>::iterator iter = toRemove.begin(); iter != toRemove.end(); iter++) {
        removePowder(*iter);
    }
}

powder_ptr Storage::removePowder(powder_ptr toRemove) {
    std::pair<int,int> position = toRemove->getPosition();
    powder_ptr removed = NULL;
    if(isPositionInRange(position.first, position.second)) {
        if(midFrame) {
            removed = (*futurePowders)[hashPowder(toRemove)];
            (*futurePowders)[hashPowder(toRemove)] = NULL;
            // Powders will attempt to remove themselves from futurePowders before shifting themselves...
            //    assume what they're doing is correct and decrement the powder count no matter what
            numPowders--;
        }
        else {
            removed = (*powders)[hashPowder(toRemove)];
            (*powders)[hashPowder(toRemove)] = NULL;
            if(removed != NULL && removed->validThisFrame(curFrameCount)) {
                numPowders--;
            }
        }
    }
    return removed;
}

bool Storage::getPowderAtLocation(int xPos, int yPos, powder_ptr &retVal) {
    // IF there is no powder at the indicated location in the most recent frame OR
    // that powder has already had its physics calculated for this frame (i.e. it may no longer be in that location OR it was removed in some previous frame) THEN
    // return the powder that is there this frame if there is one
    retVal = NULL;
    if(isPositionInRange(xPos, yPos)) {
        if(((*powders)[hashPosition(xPos, yPos)] == NULL ||
            !(*powders)[hashPosition(xPos, yPos)]->validLastFrame(curFrameCount))) {
            retVal = (*futurePowders)[hashPosition(xPos, yPos)];
            if(retVal == NULL || !retVal->validThisFrame(curFrameCount)) {
                retVal = NULL;
            }
        }
        else if((*powders)[hashPosition(xPos, yPos)]->validLastFrame(curFrameCount)) {
            retVal = (*powders)[hashPosition(xPos, yPos)];
        }
    }
    return retVal != NULL;
}

int Storage::getNumPowders() {
    return numPowders;
}

int Storage::getCurFrameNum() {
    return curFrameCount;
}

size_t Storage::hashPowder(powder_ptr powder) {
    std::pair<int,int> coords = powder->getPosition();
    return(hashPosition(coords.first, coords.second));
}

size_t Storage::hashPosition(int xPos, int yPos) {
    return(xPos*trueWindowSizeX + yPos);
}

bool Storage::isPositionInRange(int xPos, int yPos) {
    return !(xPos < 0 || xPos >= trueWindowSizeX ||
            yPos < 0 || yPos >= trueWindowSizeY);
}