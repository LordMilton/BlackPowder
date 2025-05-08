#ifndef APP_HPP
#define APP_HPP

#include "piksel/baseapp.hpp"
#include "IPowder.h"

class App : public piksel::BaseApp {
    private:
        std::vector<Powder::IPowder*>* powders;

    public:
        App(std::string title, bool fullscreen) : piksel::BaseApp(title, fullscreen) {}
        App(int width, int height, std::string title) : piksel::BaseApp(width, height, title) {}
        void setup();
        void draw(piksel::Graphics& g);
};
#endif /* APP_HPP */