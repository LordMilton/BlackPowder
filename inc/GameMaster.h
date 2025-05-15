#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <cstdlib>
#include "piksel/baseapp.hpp"
#include "IPowder.h"
#include "Storage.h"

class GameMaster {
    private:
        /**
         * Stores all necessary data about powders currently in the simulation
         */
        Storage* powderStorage;
        /**
         * The current location of the mouse cursor
         */
        int* curMouseLocation;
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

    public:
        GameMaster();
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
         */
        void mousePressed(int button);

        /**
         * Call whenever BaseApp::mouseReleased is called
         */
        void mouseReleased(int button);

};

#endif