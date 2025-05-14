#include "Storage.h"

Storage::Storage() {
    powders = new std::vector<Powder::IPowder*>();
    powderLocs = new std::unordered_map<int, std::unordered_map<int, Powder::IPowder*>*>();
}

Storage::~Storage() {
    delete powders;
    powderLocs->clear();
    delete powderLocs;
}

std::pair<std::vector<Powder::IPowder*>::iterator, std::vector<Powder::IPowder*>::iterator> Storage::getPowdersIterators() {
    return std::make_pair(powders->begin(), powders->end());
}

bool Storage::addPowder(Powder::IPowder* toAdd) {
    bool safeToAdd = addToLocations(toAdd);
    if(!safeToAdd) {
        printf("WARNING: Tried to add powder where there was already one\n");
    } else {
        powders->push_back(toAdd);
    }
    return safeToAdd;
}

Powder::IPowder* Storage::removePowders(std::vector<Powder::IPowder*>* toRemove) {
    
}

bool Storage::addToLocations(Powder::IPowder* toAdd) {
    int* pos = toAdd->getPosition();
    
    powderLocs->emplace(std::make_pair(pos[0], new std::unordered_map<int, Powder::IPowder*>()));
    return(std::get<bool>(powderLocs->at(pos[0])->emplace(pos[1], toAdd)));
}

Powder::IPowder* Storage::removeFromLocations(Powder::IPowder* toRemove) {
    int* curPos = toRemove->getPosition();
    powderLocs->at(curPos[0])->erase(curPos[1]);
    return(toRemove);
}

Powder::IPowder* Storage::getPowderAtLocation(int xPos, int yPos) {
    return powderLocs->at(xPos)->at(yPos);
}