#include "Menu.h"
#include "piksel/graphics.hpp"
#include "Powder.h"


Menu::Menu(int windowWidth, int windowHeight, std::shared_ptr<std::vector<std::shared_ptr<Powder::Powder>>> powderTypesList) :
        windowWidth(windowWidth),
        windowHeight(windowHeight),
        menuWidth(windowWidth),
        menuHeight(100),
        curMenuSelection("Sand") {
    std::pair<int,int> nextTopLeft = std::make_pair(0, windowHeight - menuHeight);
    for(std::vector<std::shared_ptr<Powder::Powder>>::iterator iter = powderTypesList->begin(); iter != powderTypesList->end(); iter++) {
        menuButtons.push_back(MenuButton(nextTopLeft, std::make_pair(nextTopLeft.first + Menu::MenuButton::BUTTON_WIDTH, nextTopLeft.second + Menu::MenuButton::BUTTON_HEIGHT), (*iter)->getColor(), (*iter)->getName()));
        nextTopLeft.first = nextTopLeft.first + Menu::MenuButton::BUTTON_WIDTH;
    }
}

Menu::~Menu() {}

void Menu::draw(piksel::Graphics& g) {
    g.push();
    g.rectMode(piksel::DrawMode::CORNERS);
    g.fill(glm::vec4(0.0f,0.0f,0.0f,1.0f));
    g.rect(0, windowHeight - menuHeight, windowWidth, windowHeight);
    g.noFill();
    for(std::vector<MenuButton>::iterator iter = menuButtons.begin(); iter != menuButtons.end(); iter++) {
        g.push();
        if(getCurrentSelection() == iter->name) {
            g.strokeWeight(2.0f);
        }
        iter->draw(g);
        g.pop();
    }

    g.pop();
}

std::pair<int,int> Menu::getMenuDimensions() {
    return std::make_pair(menuWidth, menuHeight);
}

std::string Menu::getCurrentSelection() {
    return curMenuSelection;
}

void Menu::clicked(int mouseX, int mouseY) {
    for(std::vector<MenuButton>::iterator iter = menuButtons.begin(); iter != menuButtons.end(); iter++) {
        if(iter->isClickInBounds(mouseX, mouseY)) {
            curMenuSelection = iter->name;
            break;
        }
    }
}