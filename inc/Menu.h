#ifndef MENU_H
#define MENU_H

#include "piksel/graphics.hpp"
#include "Powder.h"

class Menu {
    private:
        class MenuButton {
            public:
                static const int BUTTON_HEIGHT = 30;
                static const int BUTTON_WIDTH = 100;

                bool selected;
                const std::pair<int,int> topLeft;
                const std::pair<int,int> bottomRight;
                const glm::vec4 color;
                const std::string name;

                MenuButton(std::pair<int,int> topLeftCorner, std::pair<int,int> bottomRightCorner, glm::vec4 color, std::string name, bool selected = false) :
                        topLeft(topLeftCorner),
                        bottomRight(bottomRightCorner),
                        color(color),
                        name(name),
                        selected(selected) {
                }
                ~MenuButton() {}
                
                void draw(piksel::Graphics& g) {
                    // Assumes rectMode == CORNERS
                    g.stroke(color);
                    g.rect(topLeft.first, topLeft.second, bottomRight.first, bottomRight.second);
                    g.text(name, topLeft.first + 5, (topLeft.second + bottomRight.second)/2 + 10);
                }

                bool isClickInBounds(int xPos, int yPos) {
                    if(xPos >= topLeft.first && xPos <= bottomRight.first &&
                       yPos >= topLeft.second && xPos <= bottomRight.second) {
                       return true;
                    }
                    return false;
                }
        };

        const int windowWidth;
        const int windowHeight;

        const int menuHeight;
        const int menuWidth;

        std::vector<MenuButton> menuButtons;

        std::string curMenuSelection;

    public:
        Menu(int windowWidth, int windowHeight, std::shared_ptr<std::vector<std::shared_ptr<Powder::Powder>>> powderTypesList);
        ~Menu();

        void draw(piksel::Graphics& g);

        std::pair<int,int> getMenuDimensions();

        std::string getCurrentSelection();

        void clicked(int mouseX, int mouseY);
};

#endif // MENU_H