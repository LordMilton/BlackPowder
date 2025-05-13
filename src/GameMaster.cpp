#include "GameMaster.h"
#include "Sand.h"

int* advancePowderFrame(int x, int y, bool gravity, float density) {
    int* position = new int[2] {x,y};
    if(gravity) {
        int rng = rand()%100;
        int yMove = density >= 0 ? 1 : -1;
        if(rng < density) {
            position[1] = y + yMove;
        }
        else {
            position[0] = x + ((rand() % 2) - 1);
        }
    }

    return position;
}

GameMaster::GameMaster() {
    powders = new std::vector<Powder::IPowder*>();
    powderLocs = new std::unordered_map<int, std::unordered_map<int, Powder::IPowder*>*>();
    for(int i = 0; i < 10000; i++) {
        bool success = addPowder(new Powder::Sand(rand()%1280, rand()%720));
        i = success ? i : i-1;
    }
}

GameMaster::~GameMaster() {
    delete(powders);
}

void GameMaster::run(piksel::Graphics& g) {
    for(std::vector<Powder::IPowder*>::iterator iter = powders->begin(); iter != powders->end(); iter++) {
        (*iter)->advanceOneFrame(advancePowderFrame);
        (*iter)->draw(g);
    }
}

bool GameMaster::addPowder(Powder::IPowder* toAdd) {
    bool safeToAdd = addToLocations(toAdd);
    if(!safeToAdd) {
        printf("WARNING: Tried to add powder where there was already one");
    } else {
        powders->push_back(toAdd);
    }
    return safeToAdd;
}

bool GameMaster::addToLocations(Powder::IPowder* toAdd) {
    int* pos = toAdd->getPosition();
    
    powderLocs->emplace(std::make_pair(pos[0], new std::unordered_map<int, Powder::IPowder*>()));
    return(std::get<bool>(powderLocs->at(pos[0])->emplace(pos[1], toAdd)));
}