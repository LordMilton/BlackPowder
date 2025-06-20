#include <cmath>
#include <memory>
#include <stdexcept>

#include "GameMaster.h"
#include "Sand.h"
#include "Water.h"

std::pair<int,int> advancePowderFrame(int x, int y, bool gravity, float density) {
    std::pair<int,int> position = std::make_pair(x,y);
    if(gravity) {
        int rng = pow(rand()%10, 2);
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

GameMaster::GameMaster(int windowWidth, int windowHeight) :
        windowWidth(windowWidth),
        windowHeight(windowHeight),
        powderStorage(std::make_shared<Storage>()),
        curMouseLocation(std::make_pair(0,0)),
        drawToolRadius(1),
        lmbPressed(false),
        rmbPressed(false){
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    powderStorage = std::make_shared<Storage>();
    curMouseLocation = std::make_pair(0,0);
    lmbPressed = false;
    rmbPressed = false;

    std::shared_ptr<std::vector<powder_ptr>> menuPowders = std::shared_ptr<std::vector<powder_ptr>>(new std::vector<powder_ptr>());
    menuPowders->push_back(std::shared_ptr<Powder::Sand>(new Powder::Sand(0,0)));
    menuPowders->push_back(std::shared_ptr<Powder::Water>(new Powder::Water(0,0)));
    selectionMenu = std::unique_ptr<Menu>(new Menu(this->windowWidth, this->windowHeight, menuPowders));
    menuPowders.reset();
    
    powderSpaceWidth = this->windowWidth;
    powderSpaceHeight = this->windowHeight - selectionMenu->getMenuDimensions().second;

    for(int i = 0; i < 10000; i++) {
        int typeRand = rand() % 2;
        bool success = false;
        if(typeRand == 0)
            success = powderStorage->addPowder(std::make_shared<Powder::Sand>(rand()%800, rand()%700));
        else if(typeRand == 1)
            success = powderStorage->addPowder(std::make_shared<Powder::Water>(rand()%800, rand()%200+500));
        i = success ? i : i-1;
    }
}

GameMaster::~GameMaster() {}

void GameMaster::run(piksel::Graphics& g) {
    // Draw the draw tool
    if(curMouseLocation.second <= powderSpaceHeight) {
        g.noFill();
        g.stroke(glm::vec4(0.588f, 0.588f, 0.588f, 1.0f));
        g.ellipse(curMouseLocation.first, curMouseLocation.second, drawToolRadius*2 - 1, drawToolRadius*2 - 1);
    }
    
    // Draw powder selection menu
    selectionMenu->draw(g);

    // Create new powders via user
    if(lmbPressed) {
        if(curMouseLocation.second <= powderSpaceHeight) {
            // TODO Make a Factory for Powders to do this logic
            std::vector<powder_ptr> toAdd = std::vector<powder_ptr>();
            for(int xPos = curMouseLocation.first - (drawToolRadius-1); xPos <= curMouseLocation.first + (drawToolRadius-1); xPos++) {
                float percentAcrossCircle = (abs(xPos - curMouseLocation.first) / (drawToolRadius*1.0f));
                int verticalPixels = drawToolRadius * (cos(percentAcrossCircle * .5 * 3.14f));
                for(int yPos = curMouseLocation.second - verticalPixels; yPos <= curMouseLocation.second + verticalPixels; yPos++) {
                    if(selectionMenu->getCurrentSelection() == "Sand") {
                        toAdd.push_back(std::make_shared<Powder::Sand>(xPos,yPos));
                    }
                    else if(selectionMenu->getCurrentSelection() == "Water") {
                        toAdd.push_back(std::make_shared<Powder::Water>(xPos,yPos));
                    }
                    else {
                        printf("WARNING: Selection menu indicated a powder that we couldn't make: %s\n", selectionMenu->getCurrentSelection().c_str());
                    }
                }
            }
            powderStorage->addPowders(toAdd);
        }
        else if(curMouseLocation.second > powderSpaceHeight) {
            selectionMenu->clicked(curMouseLocation.first, curMouseLocation.second);
        }
        
    }
    else if(rmbPressed) {
        if(curMouseLocation.second <= powderSpaceHeight) {
            std::vector<powder_ptr> toRemove = std::vector<powder_ptr>();
            for(int xPos = curMouseLocation.first - (drawToolRadius-1); xPos <= curMouseLocation.first + (drawToolRadius-1); xPos++) {
                float percentAcrossCircle = (abs(xPos - curMouseLocation.first) / (drawToolRadius*1.0f));
                int verticalPixels = drawToolRadius * (cos(percentAcrossCircle * .5 * 3.14f));
                for(int yPos = curMouseLocation.second - verticalPixels; yPos <= curMouseLocation.second + verticalPixels; yPos++) {
                    int_powder_map::iterator mapPointer = powderStorage->getPowderAtLocation(xPos,yPos);
                    if(mapPointer != powderStorage->getPowdersIterators().second) {
                        toRemove.push_back(mapPointer->second);
                    }
                }
            }
            powderStorage->removePowders(toRemove);
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
    for(int_powder_map::iterator iter = beginIter; iter != endIter; iter++) {
        std::pair<int,int> pos = iter->second->getPosition();
        if(pos.first < 1 || pos.first > this->powderSpaceWidth ||
            pos.second < 1 || pos.second > this->powderSpaceHeight) {
            powderStorage->removePowder(iter->second);
        } else {
            iter->second->draw(g);
        }
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

void GameMaster::mouseWheel(int delta) {
    drawToolRadius += delta;
    drawToolRadius = fmax(1, drawToolRadius);
    drawToolRadius = fmin(20, drawToolRadius);
}