#include <chrono>
#include <iostream>

#include "Storage.h"
#include "Powder.h"

Storage::Storage(int windowSizeX, int windowSizeY) :
        trueWindowSizeX(windowSizeX),
        trueWindowSizeY(windowSizeY),
        midFrame(false),
        numPowders(0) {
    powders = std::make_unique<std::array<powder_ptr, MAX_PIXEL_COUNT>>();
    for(int i = 0; i < MAX_PIXEL_COUNT; i++) {
        printf("%s", (*powders)[i]);
    }
    futurePowders = std::make_unique<std::array<powder_ptr, MAX_PIXEL_COUNT>>();
}

Storage::~Storage() {
}

void Storage::startFrameHandling() {
    midFrame = true;
}

void Storage::endFrameHandling() {
    midFrame = false;
    powders.swap(futurePowders);
    for(int i = 0; i < trueWindowSizeX; i++) {
        for(int j = 0; j < trueWindowSizeY; j++) {
            (*futurePowders)[hashPosition(i,j)] = NULL;
        }
    }
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
    if(position.first < 0 || position.first >= trueWindowSizeX ||
       position.second < 0 || position.second >= trueWindowSizeY) {
    }
    else {
        size_t powderHash = hashPowder(toAdd);
        if(midFrame) {
            if((*futurePowders)[powderHash] == NULL) {
                (*futurePowders)[powderHash] = toAdd;
                added = true;
            }
        }
        else {
            if((*powders)[powderHash] == NULL) {
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
    if(midFrame) {
        (*futurePowders)[hashPowder(toRemove)] = 0;
    }
    else {
        (*powders)[hashPowder(toRemove)] = 0;
    }
    numPowders--; //Trusting that powder given exists in the sim
    return toRemove;
}

bool Storage::getPowderAtLocation(int xPos, int yPos, powder_ptr &retVal) {
    // IF there is no powder at the indicated location in the most recent frame OR
    // that powder has already had its physics calculated for the next frame (i.e. it may no longer be in that location) THEN
    // return the powder that will be there in the next frame if there is one
    retVal = NULL;
    if(xPos < 0 || xPos >= trueWindowSizeX ||
       yPos < 0 || yPos >= trueWindowSizeY) {
    }
    else {
        if((*powders)[hashPosition(xPos, yPos)] == 0 || (*powders)[hashPosition(xPos, yPos)]->getChanged()) {
            retVal = (*futurePowders)[hashPosition(xPos, yPos)];
        }
        else {
            retVal = (*powders)[hashPosition(xPos, yPos)];
        }
    }
    return retVal != NULL;
}

int Storage::getNumPowders() {
    return numPowders;
}

size_t Storage::hashPowder(powder_ptr powder) {
    std::pair<int,int> coords = powder->getPosition();
    return(hashPosition(coords.first, coords.second));
}

size_t Storage::hashPosition(int xPos, int yPos) {
    return(xPos*trueWindowSizeX + yPos);
}