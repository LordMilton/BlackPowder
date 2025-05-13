#include <cstdlib>
#include "App.h"
#include "GameMaster.h"
#include "IPowder.h"
#include "Sand.h"

App::App() : piksel::BaseApp() {
    initialize();
}

App::App(std::string title, bool fullscreen) : piksel::BaseApp(title, fullscreen) {
    initialize();
}

App::App(int width, int height, std::string title) : piksel::BaseApp(width, height, title) {
    initialize();
}

App::~App() {
    delete(this->gm);
}

void App::initialize() {
    this->gm = new GameMaster();
}

void App::setup() {
    // load fonts and images here
}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    this->gm->run(g);
}

int main() {
	App* app = new App(1280, 720, "Black Powder");
    //App app("Black Powder", false);
	app->start();
    
    delete(app);
}