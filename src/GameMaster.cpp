#include "GameMaster.h"
#include "Sand.h"

int* advancePowderFrame(int x, int y, bool gravity, float density) {
    int* position = new int[2] {x,y};
    if(gravity) {
        int rng = rand()%100;
        int yMove = density >= 0 ? 1 : -1;
        if(rng < density*100) {
            position[1] = y + yMove;
        }
        else {
            position[0] = x + ((rand() % 3) - 1);
        }
    }

    return position;
}

GameMaster::GameMaster() {
    powderStorage = new Storage();
    for(int i = 0; i < 10000; i++) {
        bool success = powderStorage->addPowder(new Powder::Sand(rand()%1280, rand()%720));
        i = success ? i : i-1;
    }
}

GameMaster::~GameMaster() {
    delete(powderStorage);
}

void GameMaster::run(piksel::Graphics& g) {
    std::pair<std::vector<Powder::IPowder*>::iterator, std::vector<Powder::IPowder*>::iterator> powderIterators = powderStorage->getPowdersIterators();
    std::vector<Powder::IPowder*>::iterator beginIter = powderIterators.first;
    std::vector<Powder::IPowder*>::iterator endIter = powderIterators.second;
    for(std::vector<Powder::IPowder*>::iterator iter = beginIter; iter != endIter; iter++) {
        int* curPos = (*iter)->getPosition();
        powderStorage->removeFromLocations(*iter);

        (*iter)->advanceOneFrame(advancePowderFrame, powderStorage);

        powderStorage->addToLocations(*iter);
    }
    for(std::vector<Powder::IPowder*>::iterator iter = beginIter; iter != endIter; iter++) {
        (*iter)->draw(g);
    }
}