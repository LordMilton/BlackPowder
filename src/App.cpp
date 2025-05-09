#include <cstdlib>
#include "App.h"
#include "IPowder.h"
#include "Sand.h"


void App::setup() {
    // load fonts and images here
}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    for(std::vector<Powder::IPowder*>::iterator iter = powders->begin(); iter != powders->end(); iter++) {
        (*iter)->draw(g);
    }
}

void App::setInitialPowders() {
    powders = new std::vector<Powder::IPowder*>();
    for(int i = 0; i < 100; i++){
        powders->push_back(new Powder::Sand(rand()%1920, rand()%1080));
    }
}

int main() {
	App app(1920, 1080, "Black Powder");
    app.setInitialPowders();
    //App app("Black Powder", false);
	app.start();
}