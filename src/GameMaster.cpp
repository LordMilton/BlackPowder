#include "GameMaster.h"
#include "Sand.h"

int* advancePowderFrame(int x, int y, bool gravity, float density) {
    int* position = new int[2] {x,y};
    if(gravity) {
        int rng = rand()%100;
        int yMove = density >= 0 ? 1 : -1;
        if(rng > density) {
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
    for(int i = 0; i < 10000; i++) {
        powders->push_back(new Powder::Sand(rand()%1920, rand()%1080));
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