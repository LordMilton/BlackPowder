#ifndef APP_HPP
#define APP_HPP

#include "piksel/baseapp.hpp"
#include "GameMaster.h"
#include "IPowder.h"

class App : public piksel::BaseApp {
    private:
        GameMaster* gm;

    public:
        App();
        App(std::string title, bool fullscreen);
        App(int width, int height, std::string title);
        ~App();
        
        void initialize();
        void setup();
        void draw(piksel::Graphics& g);
};
#endif /* APP_HPP */