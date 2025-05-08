#include <cstdlib>
#include "App.h"
#include "IPowder.h"
#include "Sand.h"

//std::vector<Powder::IPowder*>* powders;
Powder::Sand* grain;

void App::setup() {
    // load fonts and images here
}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    grain->draw(g);
    /*
    for(std::vector<Powder::IPowder*>::iterator iter = powders->begin(); iter != powders->end(); iter++) {
        (*iter)->draw(g);
    }
    */
}

int main() {
    /*
    powders = new std::vector<Powder::IPowder*>();
    for(int i = 0; i < 10; i++){
        powders->push_back(new Powder::Sand(rand()%1920, rand()%1080));
        printf((""+ powders->size()));
    }
    */
    grain = new Powder::Sand(500,500);
	App app(1920, 1080, "Black Powder");
    //App app("Black Powder", false);
	app.start();
}