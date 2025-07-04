﻿#ifndef APP_HPP
#define APP_HPP

#include <memory>

#include "piksel/baseapp.hpp"
#include "GameMaster.h"

class App : public piksel::BaseApp {
    private:
        std::unique_ptr<GameMaster> gm;

    public:
        App();
        App(std::string title, bool fullscreen);
        App(int width, int height, std::string title);
        ~App();
        
        void initialize();
        void setup();
        void draw(piksel::Graphics& g);

        /**
         * Called by BaseApp whenever the mouse moves
         * 
         * @param x X coordinate of where the mouse was moved to
         * @param y Y coordinate of where the mouse was moved to
         */
        void mouseMoved(int x, int y);

        /**
         * Called by BaseApp whenever a mouse button is pressed
         * 
         * @param button An integer indicating which button was pressed
         */
        void mousePressed(int button);

        /**
         * Called by BaseApp whenever a mouse button is released
         * 
         * @param button An integer indicating which button was released
         */
        void mouseReleased(int button);

        /**
         * Called by BaseApp whenever the mouse wheel is moved
         * 
         * @param delta An integer indicating how far the wheel was moved
         */
        void mouseWheel(int delta);
};
#endif /* APP_HPP */