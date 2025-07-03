#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <cstdlib>
#include <memory>

#include "piksel/baseapp.hpp"
#include "piksel/graphics.hpp"
#include "Menu.h"
#include "Powder.h"
#include "Storage.h"

class GameMaster {
    private:
        std::unique_ptr<Menu> selectionMenu;
        /**
         * Stores all necessary data about powders currently in the simulation
         */
        std::shared_ptr<Storage> powderStorage;
        /**
         * Dimensions of the game window
         */
        int windowWidth;
        int windowHeight;
        /**
         * Dimensions of the space where powders can exist
         */
        int powderSpaceWidth;
        int powderSpaceHeight;
        /**
         * The current location of the mouse cursor
         */
        std::pair<int,int> curMouseLocation;
        /**
         * Current radius of the draw tool
         */
        int drawToolRadius;
        /**
         * Whether the left mouse button is currently held down
         */
        bool lmbPressed;
        /**
         * Whether the right mouse button is currently held down
         */
        bool rmbPressed;

        /**
         * Helper method for when a mouse button is pressed or released
         */
        void mouseButtonChanged(int button, bool pressed);

        /**
         * Draws the selection menu
         */
        std::pair<int,int> drawMenu();

        /**
         * The last time (w/r/t the time the simulation started) that a frame was drawn
         * Needed for tracking/limiting fps
         */
        int lastFrameTime;

    public:
        GameMaster(int windowHeight, int windowWidth);
        ~GameMaster();

        /**
         * Runs the simulation
         */
        void run(piksel::Graphics& g);

        /**
         * Call whenever BaseApp.mouseMoved is called
         */
        void mouseMoved(int x, int y);

        /**
         * Call whenever BaseApp::mousePressed is called
         * 
         * @param 0 is lmb, 1 is rmb, 2 is mmb
         */
        void mousePressed(int button);

        /**
         * Call whenever BaseApp::mouseReleased is called
         * 
         * @param 0 is lmb, 1 is rmb, 2 is mmb
         */
        void mouseReleased(int button);

        /**
         * Call whenever BaseApp::mouseWheel is called
         */
        void mouseWheel(int delta);
};

#endif