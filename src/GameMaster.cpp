#include <memory>
#include <stdexcept>

#include "GameMaster.h"
#include "Sand.h"
#include "Water.h"

std::pair<int,int> advancePowderFrame(int x, int y, bool gravity, float density) {
    std::pair<int,int> position = std::make_pair(x,y);
    if(gravity) {
        int rng = rand()%100;
        int yMove = density >= 0 ? 1 : -1;
        if(rng < density*100) {
            position.second = y + yMove;
        }
        else {
            position.first = x + ((rand() % 3) - 1);
        }
    }

    return position;
}

GameMaster::GameMaster() {
    powderStorage = std::make_shared<Storage>();
    curMouseLocation = std::make_pair(0,0);
    lmbPressed = false;
    rmbPressed = false;

    for(int i = 0; i < 10000; i++) {
        int typeRand = rand() % 2;
        bool success = false;
        if(typeRand == 0)
            success = powderStorage->addPowder(std::make_shared<Powder::Sand>(rand()%800, rand()%800));
        else if(typeRand == 1)
            success = powderStorage->addPowder(std::make_shared<Powder::Water>(rand()%800, rand()%200+600));
        i = success ? i : i-1;
    }
}

GameMaster::~GameMaster() {}

void GameMaster::run(piksel::Graphics& g) {
    // Create new powders via user
    if(lmbPressed) {
        powder_ptr toAdd = std::make_shared<Powder::Sand>(curMouseLocation.first,curMouseLocation.second);
        powderStorage->addPowder(toAdd);
    }
    else if(rmbPressed) {
        try{
            std::shared_ptr<std::vector<powder_ptr>> toRemove = std::make_shared<std::vector<std::shared_ptr<Powder::Powder>>>();
            toRemove->push_back(powderStorage->getPowderAtLocation(curMouseLocation.first,curMouseLocation.second));
            powderStorage->removePowders(toRemove);
        } catch(std::out_of_range e) {
            //No powders at cursor, nothing to remove
        }
    }
    
    powderStorage->startFrameHandling();

    // Handle normal frame stuff
    std::pair<int_powder_map::iterator, int_powder_map::iterator> powderIterators = powderStorage->getPowdersIterators();
    int_powder_map::iterator beginIter = powderIterators.first;
    int_powder_map::iterator endIter = powderIterators.second;

    // Do physics work
    for(int_powder_map::iterator iter = beginIter; iter != endIter; iter++) {
        powder_ptr curPowder = iter->second;
        curPowder->advanceOneFrame(advancePowderFrame, powderStorage);
    }
    
    // Draw all the powders
    //printf("Drawing Powders\n");
    for(int_powder_map::iterator iter = beginIter; iter != endIter; iter++) {
        iter->second->draw(g);
    }

    powderStorage->endFrameHandling();
}

void GameMaster::mouseMoved(int x, int y) {
    curMouseLocation = std::make_pair(x,y);
}

void GameMaster::mousePressed(int button) {
    mouseButtonChanged(button, true);
}

void GameMaster::mouseReleased(int button) {
    mouseButtonChanged(button, false);
}

void GameMaster::mouseButtonChanged(int button, bool pressed) {
    if(button == 0) {
        lmbPressed = pressed;
    }
    else if(button == 1) {
        rmbPressed = pressed;
    }
}