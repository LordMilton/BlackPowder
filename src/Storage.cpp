#include "Storage.h"

Storage::Storage() {
    powders = std::make_unique<std::vector<std::shared_ptr<Powder::IPowder>>>();
    powderLocs = std::make_shared<std::unordered_map<int, std::shared_ptr<std::unordered_map<int, std::shared_ptr<Powder::IPowder>>>>>();
}

Storage::~Storage() {
}

std::pair<std::vector<std::shared_ptr<Powder::IPowder>>::iterator, std::vector<std::shared_ptr<Powder::IPowder>>::iterator> Storage::getPowdersIterators() {
    return std::make_pair(powders->begin(), powders->end());
}

bool Storage::addPowder(std::shared_ptr<Powder::IPowder> toAdd) {
    bool safeToAdd = addToLocations(toAdd);
    if(!safeToAdd) {
        printf("WARNING: Tried to add powder where there was already one\n");
    } else {
        powders->push_back(toAdd);
    }
    return safeToAdd;
}

std::shared_ptr<Powder::IPowder> Storage::removePowders(std::shared_ptr<std::vector<std::shared_ptr<Powder::IPowder>>> toRemove) {
    
}

bool Storage::addToLocations(std::shared_ptr<Powder::IPowder> toAdd) {
    std::pair<int,int> pos = toAdd->getPosition();
    
    powderLocs->emplace(std::make_pair(pos.first, std::make_shared<std::unordered_map<int, std::shared_ptr<Powder::IPowder>>>()));
    return(std::get<bool>(powderLocs->at(pos.first)->emplace(pos.second, toAdd)));
}

std::shared_ptr<Powder::IPowder> Storage::removeFromLocations(std::shared_ptr<Powder::IPowder> toRemove) {
    std::pair<int,int> curPos = toRemove->getPosition();
    powderLocs->at(curPos.first)->erase(curPos.second);
    return(toRemove);
}

std::shared_ptr<Powder::IPowder> Storage::getPowderAtLocation(int xPos, int yPos) {
    return powderLocs->at(xPos)->at(yPos);
}