#include <cstdlib>
#include "App.h"

void App::setup() {
    // load fonts and images here
}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    g.strokeWeight(1);
    for(int i = 0; i < 10000; i++) {
        g.stroke(glm::vec4((rand()%100)/100.0, (rand()%100)/100.0, (rand()%100)/100.0, 1.0f));
        g.point(rand()%1920, rand()%1080);
    }
}

int main() {
	App app(1920, 1080, "Black Powder");
    //App app("Black Powder", true);
	app.start();
}