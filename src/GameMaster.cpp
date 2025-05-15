#include <memory>

#include "GameMaster.h"
#include "Sand.h"

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
        bool success = powderStorage->addPowder(std::make_shared<Powder::Sand>(rand()%1280, rand()%720));
        i = success ? i : i-1;
    }
}

GameMaster::~GameMaster() {}

void GameMaster::run(piksel::Graphics& g) {
    // Create new powders via user
    if(lmbPressed) {
        std::shared_ptr<Powder::Sand> toAdd = std::make_shared<Powder::Sand>(curMouseLocation.first,curMouseLocation.second);
        powderStorage->addPowder(toAdd);
    }
    
    // Handle normal frame stuff
    std::pair<std::vector<std::shared_ptr<Powder::IPowder>>::iterator, std::vector<std::shared_ptr<Powder::IPowder>>::iterator> powderIterators = powderStorage->getPowdersIterators();
    std::vector<std::shared_ptr<Powder::IPowder>>::iterator beginIter = powderIterators.first;
    std::vector<std::shared_ptr<Powder::IPowder>>::iterator endIter = powderIterators.second;

    // Do physics work
    for(std::vector<std::shared_ptr<Powder::IPowder>>::iterator iter = beginIter; iter != endIter; iter++) {
        std::pair<int,int> curPos = (*iter)->getPosition();
        powderStorage->removeFromLocations(*iter);

        (*iter)->advanceOneFrame(advancePowderFrame, powderStorage);

        powderStorage->addToLocations(*iter);
    }
    
    // Draw all the powders
    for(std::vector<std::shared_ptr<Powder::IPowder>>::iterator iter = beginIter; iter != endIter; iter++) {
        (*iter)->draw(g);
    }
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